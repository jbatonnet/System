using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools.Generator
{
    using Parser;
    using Parser.Units;
    using Parser.Generators;

    class Wrappers
    {
        private static CppGenerator cppGenerator = new CppGenerator();

        private static Dictionary<string, string> cppToCsMapping = new Dictionary<string, string>();
        private static Dictionary<string, string> csToDisplayMapping = new Dictionary<string, string>();

        private const string pointerType = "IntPtr";

        private static string[] excludeList = new string[]
        {
            "Object",
            "Task",
            "Exception",
            "type_info",
            "String",
            "Type",
            "Log",

            "ButtonsMapping",
            "Label",
            "StackContainer",
            "TabContainer",
            "ButtonsDevice"
        };

        static Wrappers()
        {
            AddType("void", "void");
            AddType("void*", pointerType);
            AddType("pointer", pointerType);
            AddType("bool", "Boolean", "bool");
            AddType("char", "Char", "char");
            AddType("u8", "Byte", "byte");
            AddType("byte", "Byte", "byte");
            AddType("s8", "SByte", "sbyte");
            AddType("u16", "UInt16", "ushort");
            AddType("s16", "Int16", "short");
            AddType("u32", "UInt32", "uint");
            AddType("s32", "Int32", "int");
            AddType("u64", "UInt64", "ulong");
            AddType("s64", "Int64", "long");
            AddType("float", "Single", "float");
            AddType("double", "Double", "double");
            AddType("f32", "Single", "float");
            AddType("f64", "Double", "double");
            AddType("string", "String", "string");
            AddType("String", "String", "string");
            AddType("Object", "Object", "object");

            AddType("signed char", "SByte", "sbyte");
        }

        private static void AddType(string cppType, string csType, string displayType = null)
        {
            if (displayType == null)
                displayType = csType;

            if (!cppToCsMapping.ContainsKey(cppType))
                cppToCsMapping.Add(cppType, csType);

            if (!csToDisplayMapping.ContainsKey(csType))
                csToDisplayMapping.Add(csType, displayType);
        }

        public static void Generate()
        {
            string wrappersPath = System.IO.Path.Combine(Bootstrap.Source, @"[Tools]\Tools.Debugger\Wrappers\Wrappers.cs");

            List<string> result = new List<string>();

            result.Add("using System;");
            result.Add("using System.Collections.Generic;");
            result.Add("using System.IO;");
            result.Add("using System.Linq;");
            result.Add("");
            result.Add("using Tools.Gdb;");
            result.Add("");

            result.Add("namespace Debugger.Wrappers");
            result.Add("{");

            result.AddRange(Program.Parser.Types.Where(t => t.Parent is File && !(t is Type.Alias) && !t.Templates.Any() && !excludeList.Contains(t.Name) && !t.Name.Contains("RTTI"))
                                                .SelectMany(t => GenerateType(t))
                                                .Select(l => "    " + l));

            result.Add("}");

            result.AddRange(Program.Parser.Namespaces.Where(n => !(n.Parent is Namespace))
                                                     .SelectMany(n => GenerateNamespace(n)));

            System.IO.File.WriteAllLines(wrappersPath, result);
        }

        public static List<string> GenerateNamespace(Namespace ns)
        {
            List<string> result = new List<string>();

            result.Add("namespace " + GetNamespaceIdentifier(ns));
            result.Add("{");

            result.AddRange(ns.Types.Where(t => !(t is Type.Alias) && !t.Templates.Any() && !excludeList.Contains(t.Name))
                                    .SelectMany(t => GenerateType(t), null)
                                    .Select(l => "    " + l));

            result.Add("}");

            result.AddRange(ns.Namespaces.SelectMany(n => GenerateNamespace(n), null));

            return result;
        }
        public static List<string> GenerateType(Type type)
        {
            List<string> output = new List<string>();

            if (type.Documentation != null)
                output.AddRange(type.Documentation.Select(l => "/// " + l));

            string style = type.Style == TypeStyle.Enum ? "enum" : "class";
            if (!type.Bases.Any())
                output.Add("public " + style + " " + type.Name + (type.Style == TypeStyle.Enum ? "" : " : Object"));
            else
                output.Add("public " + style + " " + type.Name + " : " + type.Bases.Select(b => GetTypeIdentifier(b)).Join(", "));
            output.Add("{");

            if (type.Style == TypeStyle.Enum)
                output.AddRange(type.Fields.Select(f => "    " + f.Name + ","));
            else
                output.AddRange(type.Fields.Where(t => t.Name != "Unit" && t.Type.Style != TypeStyle.Enum && !t.Modifiers.HasFlag(Modifiers.Static) && !t.Type.Templates.Any() && t.GetAccessor == null && t.SetAccessor == null && t.Type.ToIdentifier(cppGenerator) != "void*")
                                           .SelectMany(f => GenerateField(f))
                                           .Select(l => "    " + l));

            if (type.Style != TypeStyle.Enum)
            {
                output.Add("");
                output.Add("    public " + type.Name + "(GdbStub.GdbMemory memory, ulong address) : base(memory, address)");
                output.Add("    {");
                output.Add("    }");
            }

            output.Add("}");

            return output;
        }
        public static List<string> GenerateField(Field field)
        {
            List<string> result = new List<string>();

            if (field.Type == null)
                return result;

            string modifier = "public ";
            if (field.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            if (field.Documentation != null)
                result.AddRange(field.Documentation.Select(l => "/// " + l));

            result.Add(modifier + GetDisplayIdentifier(GetTypeIdentifier(field.Type)) + " " + field.Name);
            result.Add("{");
            result.Add("    get");
            result.Add("    {");
            result.Add("        return new " + GetDisplayIdentifier(GetTypeIdentifier(field.Type)) + "(memory, (ulong)((long)Address + " + 0/*field.Offset*/ + "));");
            result.Add("    }");
            result.Add("}");

            return result;
        }

        public static string GetNamespaceIdentifier(Namespace nameSpace)
        {
            if (nameSpace.Parent is Namespace)
                return GetNamespaceIdentifier(nameSpace.Parent as Namespace) + "." + nameSpace.Name;
            else
                return "Debugger.Wrappers." + nameSpace.Name;
        }
        public static string GetTypeIdentifier(Type type, IEnumerable<Type> hintTypes = null)
        {
            if (type is Type.Pointer)
            {
                if (type.ToIdentifier(cppGenerator) == "void*")
                    return cppToCsMapping["void*"];
                else
                    return "Pointer<" + GetTypeIdentifier((type as Type.Pointer).Type, hintTypes) + ">";
            }
            else if (type is Type.Reference)
                return GetTypeIdentifier((type as Type.Reference).Type, hintTypes);
            else if (type is Type.Template)
                return type.Name;

            string templates = "";
            if (type.Templates.Any())
                templates = "<" + type.Templates.Select(t => GetTypeIdentifier(t, hintTypes)).Join(", ") + ">";

            if (type.Parent == null || type.Parent is File)
            {
                if (cppToCsMapping.ContainsKey(type.Name))
                    return "Value<" + GetDisplayIdentifier(cppToCsMapping[type.Name]) + ">";
                else
                    return type.Name.Replace("::", ".") + templates;
            }
            else if (type.Parent is Namespace)
                return GetNamespaceIdentifier(type.Parent as Namespace) + "." + (type.Name == "" ? "[Anonymous]" : type.Name) + templates;
            else if (type.Parent is Type)
                return GetTypeIdentifier(type.Parent as Type, hintTypes) + "." + (type.Name == "" ? "[Anonymous]" : type.Name) + templates;

            return "?";
        }
        public static string GetDisplayIdentifier(string identifier)
        {
            if (csToDisplayMapping.ContainsKey(identifier))
                return csToDisplayMapping[identifier];
            return identifier.Replace("List<", "Collection<");
        }
        public static string GetVariableIdentifier(string identifier)
        {
            if (identifier == "")
                return "param";

            return identifier.Replace("object", "_object")
                             .Replace("base", "_base");
        }
    }
}