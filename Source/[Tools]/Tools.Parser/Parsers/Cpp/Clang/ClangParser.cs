using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

using Tools.Parser.Parsers;
using Tools.Parser.Units;

namespace Tools.Parser
{
    using File = Units.File;
    using Type = Units.Type;

    using ClangSharp;

    public class ClangParser : Parser
	{
        public string Root { get; private set; }

        public override IEnumerable<File> Files
        {
            get
            {
                return files;
            }
        }
        public IEnumerable<Namespace> Namespaces
        {
            get
            {
                return namespaces;
            }
        }
        public IEnumerable<Type> Types
        {
            get
            {
                return types;
            }
        }

        private CXIndex index;
        private Dictionary<CXCursor, Unit> units = new Dictionary<CXCursor, Unit>();
		private Dictionary<Type, Modifiers> modifiers = new Dictionary<Type, Modifiers>();
		private List<Field> properties = new List<Field>();

        private List<CppFile> files = new List<CppFile>();
        private List<CppNamespace> namespaces = new List<CppNamespace>();
        private List<Type> types = new List<Type>();

        public ClangParser(string root)
		{
			Root = root;
			index = clang.createIndex(0, 0);
		}

		public override void AddFile(string path)
		{
			if (!Path.IsPathRooted(path))
				path = Path.Combine(Root, path);

			CXUnsavedFile unsavedFile;
			CXTranslationUnit translationUnit;
			CXErrorCode error;

			string[] args =
			{
				"-x", "c++",
				"-I", Root,
				"-std=c++11",
				"-fms-extensions"
			};

			error = clang.parseTranslationUnit2(index, path, args, 6, out unsavedFile, 0, 0, out translationUnit);
			if (error != CXErrorCode.CXError_Success)
			{
				Console.WriteLine("Error: " + error);
				var numDiagnostics = clang.getNumDiagnostics(translationUnit);

				for (uint i = 0; i < numDiagnostics; ++i)
				{
					var diagnostic = clang.getDiagnostic(translationUnit, i);
					Console.WriteLine(clang.getDiagnosticSpelling(diagnostic).ToString());
					clang.disposeDiagnostic(diagnostic);
				}
			}

			clang.visitChildren(clang.getTranslationUnitCursor(translationUnit), Visit, new CXClientData(IntPtr.Zero));
		}
		/*public override void Resolve()
		{
			// List all namespaces
			IEnumerable<Namespace> namespaces = Files.SelectMany(f => f.Namespaces);
			for (; ;)
			{
				IEnumerable<Namespace> subNamespaces = namespaces.SelectMany(n => n.Namespaces).Except(namespaces);
				if (!subNamespaces.Any())
					break;
				namespaces = namespaces.Concat(subNamespaces);
			}
            Namespaces.Clear();
            Namespaces.AddRange(namespaces);

			// List all types
			IEnumerable<Type> types = Files.SelectMany(f => f.Types).Concat(Namespaces.SelectMany(n => n.Types));
			for (; ;)
			{
				IEnumerable<Type> subTypes = types.SelectMany(t => t.Types).Where(t => t.Name != "").Except(types);
				if (!subTypes.Any())
					break;
				types = types.Concat(subTypes);
			}
            Types.Clear();
            Types.AddRange(types);

			// Merge namespaces
			for (int i = 0; i < Namespaces.Count; i++)
			{
				CppNamespace currentNamespace = Namespaces[i] as CppNamespace;
				List<Namespace> otherNamespaces = Namespaces.Where(n => n != currentNamespace && n.Equals(currentNamespace)).ToList();

				currentNamespace.Namespaces.AddRange(otherNamespaces.SelectMany(n => n.Namespaces)
																	.Select(n => { n.Parent = currentNamespace; return n; })
																	.ToList());
				currentNamespace.Types.AddRange(otherNamespaces.SelectMany(n => n.Types)
															   .Select(t => { t.Parent = currentNamespace; return t; })
															   .ToList());

				foreach (Namespace nameSpace in Namespaces)
					foreach (Namespace otherNamespace in otherNamespaces)
						nameSpace.Namespaces.Remove(otherNamespace);

				foreach (Namespace otherNamespace in otherNamespaces)
					Namespaces.Remove(otherNamespace);
			}
			foreach (Namespace ns in Namespaces)
				if (ns.Parent is Namespace)
					ns.Parent = Namespaces.First(n => n.Name == ns.Parent.Name);
			foreach (Type type in Types)
				if (type.Parent is Type)
					type.Parent = Types.First(t => t.Name == type.Parent.Name);

			// Methods
			IEnumerable<Method> methods = types.SelectMany(t => t.Methods);
			IEnumerable<Method> statics = types.SelectMany(t => t.Methods).Where(m => (m.Modifiers & Modifiers.Static) == Modifiers.Static);

			// Resolve everything
			foreach (File f in Files)
				f.Resolve(Types);

			// Remove getters and setters
			/*foreach (Type type in Types)
            {
                foreach (Field field in type.Fields)
                {
                    if (field.GetAccessor != null)
                        type.Methods.Remove(field.GetAccessor);
                    if (field.SetAccessor != null)
                        type.Methods.Remove(field.SetAccessor);
                }
            }*/
		/*}*/

		private CXChildVisitResult Visit(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			if (!units.ContainsKey(parent))
			{
				CXCursorKind parentKind = clang.getCursorKind(parent);
				string parentName = clang.getCString(clang.getCursorSpelling(parent));

				if (parentKind != CXCursorKind.CXCursor_TranslationUnit)
					throw new Exception("Root parents must be translation units");

                CppFile file = new CppFile(parentName);
				files.Add(file);

				units.Add(parent, file);
			}

			CXCursorKind kind = clang.getCursorKind(cursor);

			switch (kind)
			{
				case CXCursorKind.CXCursor_Namespace:
					return VisitNamespace(cursor, parent, data);

				case CXCursorKind.CXCursor_ClassDecl:
				case CXCursorKind.CXCursor_StructDecl:
				case CXCursorKind.CXCursor_EnumDecl:
				case CXCursorKind.CXCursor_TypedefDecl:
				case CXCursorKind.CXCursor_UnionDecl:
				case CXCursorKind.CXCursor_ClassTemplate:
					return VisitType(cursor, parent, data);

				case CXCursorKind.CXCursor_CXXAccessSpecifier:
					return VisitTypeModifier(cursor, parent, data);

				case CXCursorKind.CXCursor_EnumConstantDecl:
					return VisitEnumConstant(cursor, parent, data);

				case CXCursorKind.CXCursor_FieldDecl:
				case CXCursorKind.CXCursor_MemberRef:
				case CXCursorKind.CXCursor_VarDecl:
					return VisitField(cursor, parent, data);

				case CXCursorKind.CXCursor_Constructor:
				case CXCursorKind.CXCursor_Destructor:
				case CXCursorKind.CXCursor_CXXMethod:
				case CXCursorKind.CXCursor_FunctionDecl:
				case CXCursorKind.CXCursor_FunctionTemplate:
					return VisitMethod(cursor, parent, data);

				case CXCursorKind.CXCursor_TemplateTypeParameter:
				case CXCursorKind.CXCursor_NonTypeTemplateParameter:
					return VisitTemplateParameter(cursor, parent, data);

				case CXCursorKind.CXCursor_ParmDecl:
					return VisitMethodParameter(cursor, parent, data);

				case CXCursorKind.CXCursor_FirstDecl:
				case CXCursorKind.CXCursor_TypeRef:
				case CXCursorKind.CXCursor_NamespaceRef:

				case CXCursorKind.CXCursor_CompoundStmt:
					break;

				default:
					break;
			}

			return CXChildVisitResult.CXChildVisit_Continue;
		}
		private CXChildVisitResult VisitNamespace(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Unit unitParent = units[parent];
			string unitName = clang.getCString(clang.getCursorSpelling(cursor));

            CppNamespace unit = null;

            // Try to find existing namespace
			if (unitParent is File)
				unit = namespaces.FirstOrDefault(n => n.Name == unitName);
			else if (unitParent is Namespace)
				unit = (unitParent as Namespace).Namespaces.FirstOrDefault(n => n.Name == unitName) as CppNamespace;

            // Register the new namespace
			if (unit == null)
			{
				unit = new CppNamespace(unitParent is CppFile ? null : unitParent, unitName);

                if (unitParent is CppFile)
                {
                    (unitParent as CppFile).namespaces.Add(unit);
                    namespaces.Add(unit);
                }
                else if (unitParent is CppNamespace)
                    (unitParent as CppNamespace).namespaces.Add(unit);
			}
            
			units.Add(cursor, unit);

			return CXChildVisitResult.CXChildVisit_Recurse;
		}
		private CXChildVisitResult VisitType(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Unit unitParent = units[parent];
            string unitName = clang.getCString(clang.getCursorSpelling(cursor));
            Type unit = null;

            // Try to find existing type
            if (unitParent is File)
				unit = types.FirstOrDefault(t => t.Name == unitName);
			else if (unitParent is Namespace)
				unit = (unitParent as Namespace).Types.FirstOrDefault(t => t.Name == unitName);
			else if (unitParent is Type)
				unit = (unitParent as Type).Types.FirstOrDefault(t => t.Name == unitName);

            // Register the new type
            if (unit == null)
			{
                CXCursorKind kind = clang.getCursorKind(cursor);

                if (kind == CXCursorKind.CXCursor_TypedefDecl)
					unit = new Type.Alias(unitName, FromCXType(clang.getTypedefDeclUnderlyingType(cursor)));
				else
				{
                    CppType cppUnit = new CppType(unitName);

					switch (kind)
					{
						case CXCursorKind.CXCursor_ClassDecl: cppUnit.style = TypeStyle.Class; break;
						case CXCursorKind.CXCursor_StructDecl: cppUnit.style = TypeStyle.Struct; break;
						case CXCursorKind.CXCursor_UnionDecl: cppUnit.style = TypeStyle.Union; break;
						case CXCursorKind.CXCursor_EnumDecl: cppUnit.style = TypeStyle.Enum; break;
					}

                    if (unitParent is Type && modifiers.ContainsKey(unitParent as Type))
                        cppUnit.modifiers = modifiers[unitParent as Type];

                    unit = cppUnit;
				}

                if (unitParent is CppFile)
                {
                    (unitParent as CppFile).types.Add(unit);
                    types.Add(unit);
                }
                else if (unitParent is CppNamespace)
                    (unitParent as CppNamespace).types.Add(unit);
                else if (unitParent is CppType)
                    (unitParent as CppType).types.Add(unit);
			}

			unit.Parent = unitParent;

            if (!units.ContainsKey(cursor))
			    units.Add(cursor, unit);

			switch (unit.Style)
			{
				case TypeStyle.Class: modifiers[unit] = Modifiers.Private; break;
				case TypeStyle.Struct: modifiers[unit] = Modifiers.Public; break;
				case TypeStyle.Enum: modifiers[unit] = Modifiers.Public; break;
				case TypeStyle.Union: modifiers[unit] = Modifiers.Public; break;
			}

			return CXChildVisitResult.CXChildVisit_Recurse;
		}
		private CXChildVisitResult VisitTypeModifier(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Type parentUnit = units[parent] as Type;

			CX_CXXAccessSpecifier accessSpecifier = clang.getCXXAccessSpecifier(cursor);
			switch (accessSpecifier)
			{
				case CX_CXXAccessSpecifier.CX_CXXPrivate: modifiers[parentUnit] = Modifiers.Private; break;
				case CX_CXXAccessSpecifier.CX_CXXProtected: modifiers[parentUnit] = Modifiers.Protected; break;
				case CX_CXXAccessSpecifier.CX_CXXPublic: modifiers[parentUnit] = Modifiers.Public; break;
			}

			return CXChildVisitResult.CXChildVisit_Continue;
		}
		private CXChildVisitResult VisitEnumConstant(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Unit unitParent = units[parent];
			string unitName = clang.getCString(clang.getCursorSpelling(cursor));
            CppField unit = new CppField(unitParent, unitName);

			units.Add(cursor, unit);

			if (unitParent is CppType)
				(unitParent as CppType).fields.Add(unit);

			return CXChildVisitResult.CXChildVisit_Continue;
		}
		private CXChildVisitResult VisitField(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Unit unitParent = units[parent];
			string unitName = clang.getCString(clang.getCursorSpelling(cursor));
            CppField unit = new CppField(unitParent, unitName);

            CXType type = clang.getCursorType(cursor);

			uint isVolatile = clang.isVolatileQualifiedType(type); // property = const volatile
			uint isConst = clang.isConstQualifiedType(type);
			if (isVolatile > 0 && isConst > 0)
			{
				properties.Add(unit);

				if (unitParent is Type)
				{
					unit.getAccessor = (unitParent as Type).Methods.FirstOrDefault(m => m.Name == "Get" + unit.Name);
					unit.setAccessor = (unitParent as Type).Methods.FirstOrDefault(m => m.Name == "Set" + unit.Name);
				}
			}

            unit.type = FromCXType(type);

            CXCursor parentTypeCursor = units.First(u => u.Value == unitParent).Key;
            CXType parentType = clang.getCursorType(parentTypeCursor);
            unit.offset = clang.Type_getOffsetOf(parentType, unitName);

			if (unitParent is Type && modifiers.ContainsKey(unitParent as Type))
				unit.modifiers = modifiers[unitParent as Type];
            if (clang.CXXMethod_isStatic(cursor) > 0) // FIXME ?
                unit.modifiers |= Modifiers.Static;

            if (!units.ContainsKey(cursor))
			    units.Add(cursor, unit);

			if (unitParent is CppType)
				(unitParent as CppType).fields.Add(unit);

			return CXChildVisitResult.CXChildVisit_Recurse;
		}
		private CXChildVisitResult VisitMethod(CXCursor cursor, CXCursor parent, IntPtr data)
		{
            Unit unitParent = units[parent];
            string unitName = clang.getCString(clang.getCursorSpelling(cursor));
            CXCursorKind unitKind = clang.getCursorKind(cursor);

            CppMethod unit;

            if (unitKind == CXCursorKind.CXCursor_Constructor && unitParent is CppType) unit = new CppConstructor(unitParent as CppType);
            else if (unitKind == CXCursorKind.CXCursor_Destructor && unitParent is CppType) unit = new CppDestructor(unitParent as CppType);
            else unit = new CppMethod(unitParent, unitName);

            // Find modifiers
            if (unitParent is Type && modifiers.ContainsKey(unitParent as Type))
                unit.modifiers = modifiers[unitParent as Type];
            if (clang.CXXMethod_isStatic(cursor) > 0)
                unit.modifiers |= Modifiers.Static;

            // Find result type
            if (unitKind != CXCursorKind.CXCursor_Constructor && unitKind != CXCursorKind.CXCursor_Destructor)
            {
                CXType result = clang.getCursorResultType(cursor);
                unit.result = FromCXType(result, GetAllTemplates(unitParent).Concat(new[] { unitParent as Type }));
            }

            // Merge with properties
			/*if (unitName.StartsWith("Get") || unitName.StartsWith("Set"))
			{
                CppField property = properties.FirstOrDefault(p => p.Name == unitName.Substring(3) && p.Parent == unitParent) as CppField;
				if (property != null)
				{
					if (unitName.StartsWith("Get"))
                        property.getAccessor = unit;
					else
                        property.setAccessor = unit;
				}
			}*/

            // Parse templates
            int startPosition = unitName.IndexOf('<');
            int stopPosition = startPosition == -1 ? -1 : unitName.IndexOf('>', startPosition);
            if (startPosition >= 0 && stopPosition >= 0)
            {
                string[] typeStrings = unitName.Substring(startPosition, stopPosition - startPosition).Split(',').Select(t => t.Trim()).ToArray();

                foreach (string typeString in typeStrings)
                    unit.templates.Add(CppType.GetReference(typeString));

                if (unitParent is Type)
                {
                    foreach (Type type in (unitParent as Type).Templates)
                        unit.templates.RemoveAll(t => t.Equals(type));
                }
            }

			units.Add(cursor, unit);

			if (unitParent is CppType)
				(unitParent as CppType).methods.Add(unit);

			return CXChildVisitResult.CXChildVisit_Recurse;
		}
		private CXChildVisitResult VisitTemplateParameter(CXCursor cursor, CXCursor parent, IntPtr data)
		{
			Unit unit = units[parent];

			string name = clang.getCString(clang.getCursorSpelling(cursor));

			if (unit is CppType)
				(unit as CppType).templates.Add(new Type.Template(name));
			else if (unit is CppMethod)
				(unit as CppMethod).templates.Add(new Type.Template(name));

			return CXChildVisitResult.CXChildVisit_Continue;
		}
		private CXChildVisitResult VisitMethodParameter(CXCursor cursor, CXCursor parent, IntPtr data)
		{
            CppMethod method = units[parent] as CppMethod;
			if (method == null)
				return CXChildVisitResult.CXChildVisit_Continue;

			string name = clang.getCString(clang.getCursorSpelling(cursor));
			Type type = FromCXType(clang.getCursorType(cursor), method.Templates.Concat(new[] { method.Parent as Type }));

			method.parameters.Add(name, type);

			return CXChildVisitResult.CXChildVisit_Continue;
		}

		private Type FromCXType(CXType type, IEnumerable<Type> hintTypes = null)
		{
            Type typeResult = null;

			switch (type.kind)
			{
				case CXTypeKind.CXType_DependentSizedArray:
				case CXTypeKind.CXType_ConstantArray:
                    typeResult = new Type.Pointer(FromCXType(clang.getArrayElementType(type), hintTypes));
                    break;

				case CXTypeKind.CXType_MemberPointer:
				case CXTypeKind.CXType_Pointer:
                    typeResult = new Type.Pointer(FromCXType(clang.getPointeeType(type), hintTypes));
                    break;

				case CXTypeKind.CXType_LValueReference:
				case CXTypeKind.CXType_RValueReference:
                    typeResult = new Type.Reference(FromCXType(clang.getPointeeType(type), hintTypes));
                    break;

				case CXTypeKind.CXType_FirstBuiltin: return Units.Types.Void;
				case CXTypeKind.CXType_Bool: return Units.Types.Bool;
                case CXTypeKind.CXType_SChar: return Units.Types.S8;
				case CXTypeKind.CXType_Char_S: return Units.Types.S8;
				case CXTypeKind.CXType_UChar: return Units.Types.U8;
				case CXTypeKind.CXType_Char_U: return Units.Types.U8;
				case CXTypeKind.CXType_Short: return Units.Types.S16;
				case CXTypeKind.CXType_UShort: return Units.Types.U16;
				case CXTypeKind.CXType_Int: return Units.Types.S32;
				case CXTypeKind.CXType_UInt: return Units.Types.U32;
				case CXTypeKind.CXType_LongLong: return Units.Types.S64;
				case CXTypeKind.CXType_ULongLong: return Units.Types.U64;
				case CXTypeKind.CXType_Float: return Units.Types.Single;
				case CXTypeKind.CXType_Double: return Units.Types.Double;

				case CXTypeKind.CXType_Unexposed:
				{
					string name = clang.getCString(clang.getTypeSpelling(type)).Replace("...", "").Replace("const ", "").Replace("volatile ", "");
                    typeResult = hintTypes?.FirstOrDefault(t => t?.Name == name) ?? CppType.GetReference(name, hintTypes);
                    break;
				}

				case CXTypeKind.CXType_Record:
				{
					string name = clang.getCString(clang.getTypeSpelling(type)).Replace("...", "").Replace("const ", "").Replace("volatile ", "");
                    typeResult = hintTypes?.FirstOrDefault(t => t?.Name == name) ?? CppType.GetReference(name, hintTypes);
                    break;
				}

				case CXTypeKind.CXType_Enum:
				case CXTypeKind.CXType_Typedef:
                {
                    CXCursor cursor = clang.getTypeDeclaration(type);
                    Unit resolvedType;
                    typeResult = units.TryGetValue(cursor, out resolvedType) ? resolvedType as Type : null;
                    break;
                }
			}

            int templateCount = clang.Type_getNumTemplateArguments(type);
            if (typeResult != null && templateCount > 0 && !typeResult.Templates.Any() && typeResult is CppType)
            {
                for (uint i = 0; i < templateCount; i++)
                {
                    Type templateType = FromCXType(clang.Type_getTemplateArgumentAsType(type, i), hintTypes);
                    if (templateType != null)
                        (typeResult as CppType).templates.Add(templateType);
                }
            }

			return typeResult;
		}

        private IEnumerable<Type> GetAllTemplates(Unit unit)
        {
            if (unit is Type)
                return (unit as Type).Templates.Concat(GetAllTemplates(unit.Parent));
            
            return Enumerable.Empty<Type>();
        }
    }
}