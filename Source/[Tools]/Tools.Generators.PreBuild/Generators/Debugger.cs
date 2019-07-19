using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

using Tools.Parser.Units;
using Tools.Parser.Generators;

namespace Tools.Generator
{
    using File = Parser.Units.File;
    using Type = Parser.Units.Type;

    public class Debugger
    {
        private static CsGenerator csGenerator = new CsGenerator();

        private static Dictionary<string, string> cppToCsMapping = new Dictionary<string, string>();
        private static Dictionary<string, string> csToDisplayMapping = new Dictionary<string, string>();

        private const string pointerType = "IntPtr";

        static Debugger()
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
            string apiPath = Path.Combine(Bootstrap.Source, @"[Tools]\Debugger\API.cs");
            string kernelPath = Path.Combine(Bootstrap.Source, @"Kernel\Debugging\Debugger\Debugger.cpp");

            #region C# API

            using (StreamWriter file = System.IO.File.CreateText(apiPath))
            {
                List<string> output = new List<string>();

                output.Add("using System;");
                output.Add("using KernelStream = System.Debugger.KernelStream;");
                output.Add("");

                foreach (Type.Alias type in Program.Parser.Types.OfType<Type.Alias>())
                    if (!type.ToIdentifier(csGenerator).Contains("::") && !cppToCsMapping.ContainsKey(type.ToIdentifier(csGenerator)))
                        output.Add("using " + type.ToIdentifier(csGenerator) + " = API." + GetTypeIdentifier(type.Type) + ";");
                output.Add("");

                output.Add("namespace API");
                output.Add("{");
                output.AddRange(Program.Parser.Types.Where(t => t.Parent is File && !cppToCsMapping.ContainsKey(t.Name))
                                                    .Where(t => !(t is Type.Alias))
                                                    .SelectMany(t => GenerateType(t), null)
                                                    .Select(l => "    " + l));
                output.Add("}");
                output.Add("");

                output.AddRange(Program.Parser.Namespaces//.Where(n => n.Name == "IO")
                                                         .SelectMany(n => GenerateNamespace(n), null));

                file.Write(string.Join(Environment.NewLine, output));
            }

            #endregion
            #region Kernel API

            using (StreamWriter file = System.IO.File.CreateText(kernelPath))
            {
                List<string> output = new List<string>();

                //foreach (System.Parser.Units.File f in Program.Parser.Files)
                //    output.Add("#include <" + f.Path.Replace(context.Path + "\\", "").Replace("\\", "/") + ">");
                //output.Add("");

                foreach (Namespace n in Program.Parser.Namespaces)
                    output.Add("using namespace " + n.ToIdentifier(csGenerator) + ";");
                output.Add("");

                output.Add("void DebuggerLoop()");
                output.Add("{");
                output.Add("    DataStream* debuggerStream = new DataStream(null);");
                output.Add("");
                output.Add("    switch (debuggerStream->Read<u32>())");
                output.Add("    {");

                List<Type> types = Program.Parser.Types.Concat(Program.Parser.Namespaces.SelectMany(n => n.Types)).ToList();

                output.AddRange(types.Where(t => t.Parent is File && !cppToCsMapping.ContainsKey(t.Name) && !t.Modifiers.HasFlag(Modifiers.Template) && t.Style != TypeStyle.Enum && (t.Modifiers.HasFlag(Modifiers.Shared) || t.Style != TypeStyle.Class))
                                     .SelectMany(t => GenerateTypeCases(t))
                                     .Select(l => "        " + l));

                output.Add("    }");
                output.Add("}");

                file.Write(string.Join(Environment.NewLine, output));
            }

            #endregion
        }

        public static List<string> GenerateNamespace(Namespace nameSpace)
        {
            List<string> result = new List<string>();

            result.Add("namespace " + GetNamespaceIdentifier(nameSpace));
            result.Add("{");

            result.AddRange(nameSpace.Types.Where(t => true)
                                           //.Skip(7)
                                           .SelectMany(t => GenerateType(t))//, null)
                                           .Select(l => "    " + l));

            result.Add("}");

            return result;
        }
        public static List<string> GenerateType(Type type)
        {
            List<string> output = new List<string>();
            string indentation = "    ";
            bool bypassType = type.Parent is Type && type.Name == "";

            if (!bypassType)
            {
                string template = "";
                if (type.Templates.Any()) template = "<" + type.Templates.Select(t => t.Name).Join(", ") + ">";

                if (type.Documentation.Any())
                    output.AddRange(type.Documentation.Select(l => "/// " + l));

                string style = type.Style.ToString().ToLower().Replace("struct", "class");
                //if (!type.Methods.Any(m => !m.Modifiers.HasFlag(Modifiers.Static)))
                //    style = "static " + style;

                if (!type.Bases.Any() || type.Bases.First().Name.ToLower() == "object")
                    output.Add("public " + style + " " + type.Name + template);
                else
                    output.Add("public " + style + " " + type.Name + template + " : " + GetDisplayIdentifier(GetTypeIdentifier(type.Bases.First())));

                output.Add("{");

                if (type.Style != TypeStyle.Enum)
                {
                    string baseCall = type.Bases.Any() && type.Bases.First().Name.ToLower() != "object" ? " : base(pointer)" : "";

                    output.Add("    private " + pointerType + " pointer;");
                    output.Add("");
                    output.Add("    internal " + type.Name + "(" + pointerType + " pointer)" + baseCall);
                    output.Add("    {");
                    output.Add("        this.pointer = pointer;");
                    output.Add("    }");
                    output.Add("");
                }
            }
            else
                indentation = "";

            if (type.Style == TypeStyle.Enum)
                output.AddRange(type.Fields.Select(f => indentation + f.Name + ","));

            List<string> types = type.Types.Where(t => t.Modifiers.HasFlag(Modifiers.Public))
                                           .SelectMany(t => GenerateType(t), null)
                                           .Select(l => indentation + l)
                                           .ToList();
            List<string> fields = type.Fields.Where(t => t.Modifiers.HasFlag(Modifiers.Public))
                                             .Where(t => t.Type.Name != "Event")
                                             .SelectMany(f => GenerateField(f))
                                             .Select(l => indentation + l)
                                             .ToList();
            List<string> events = type.Fields.Where(t => t.Modifiers.HasFlag(Modifiers.Public))
                                             .Where(t => t.Type.Name == "Event")
                                             .SelectMany(f => GenerateEvent(f))
                                             .Select(l => indentation + l)
                                             .ToList();
            List<string> methods = type.Methods.Where(m => m.Modifiers.HasFlag(Modifiers.Public) && !type.Fields.SelectMany(f => new[] { f.GetAccessor, f.SetAccessor }).Contains(m) && m.Result != null && m.Name != "operator()" && m.Name != "operator=" && m.Name != "operator==" && m.Name != "operator!=" && m.Name != "operator+=" && m.Name != "operator-=" && m.Name != "operator*=" && m.Name != "operator/=" && m.Name != "operator->" && m.Name != "operator[]" && m.Name != "operator<" && m.Name != "operator>" && (m.Name != "operator*" || m.Parameters.Any()))
                                               .Where(m => m.Name.Before("<") != type.Name)
                                               .GroupBy(m => m.Name).Select(g => g.First()) // FIXME: This is a dirty trick to avoid templates traits
                                               .SelectMany(m => GenerateMethod(m))
                                               .Select(l => indentation + l)
                                               .ToList();

            output.AddRange(types);
            if (types.Count > 0 && (fields.Count > 0 || methods.Count > 0 || events.Count > 0))
                output.Add("");
            output.AddRange(fields);
            if (fields.Count > 0 && methods.Count > 0)
                output.Add("");
            output.AddRange(methods);
            if (methods.Count > 0 && events.Count > 0)
                output.Add("");
            output.AddRange(events);

            if (!bypassType)
                output.Add("}");

            return output;
        }
        public static List<string> GenerateMethod(Method method)
        {
            List<string> output = new List<string>();

            if (method.Documentation.Any())
                output.AddRange(method.Documentation.Select(l => "/// " + l));

            string template = "";
            if (method.Templates.Any()) template = "<" + method.Templates.Where(t => !t.Name.EndsWith("...")).Select(t => t.Name).Join(", ") + ">";
            
            string modifier = "";
            if (method.Modifiers.HasFlag(Modifiers.Public)) modifier += "public ";
            if (method.Modifiers.HasFlag(Modifiers.Protected)) modifier += "protected ";
            if (method.Modifiers.HasFlag(Modifiers.Private)) modifier += "private ";
            //if (method.Modifiers.HasFlag(Modifiers.Virtual)) modifier += "virtual ";
            if (method.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            Dictionary<string, Type> parameters = method.Parameters.ToDictionary();
            if (method.Name.StartsWith("operator"))
            {
                modifier += "static ";
                parameters = new[] { new KeyValuePair<string, Type>("me", method.Parent as Type) }.Concat(method.Parameters).ToDictionary(kvp => (kvp.Key == "" ? "param" : kvp.Key), kvp => kvp.Value);
            }
            if (method.Name == "ToString")
                modifier += "override ";

            string result = "";
            if (method.Result != null)
                result = GetTypeIdentifier(method.Result);

            output.Add(modifier + GetDisplayIdentifier(result) + (result != "" ? " " : "") + method.Name.Before("<") + template + "(" + parameters.Select(p => p.Value == null ? "?" : GetDisplayIdentifier(GetTypeIdentifier(p.Value)) + " " + GetVariableIdentifier(p.Key)).Join(", ") + ")");
            output.Add("{");
            output.Add("    lock (KernelStream.Mutex)");
            output.Add("    {");
            output.Add("        KernelStream.Write((uint)0x" + method.GetHashCode().ToString("X8") + ");");

            if (!method.Modifiers.HasFlag(Modifiers.Static) && !method.Name.StartsWith("operator"))
                output.Add("        KernelStream.Write(pointer.ToInt32());");

            foreach (var parameter in parameters)
                output.Add("        KernelStream.Write(" + GetVariableIdentifier(parameter.Key) + ");");

            if (method.Result != null && method.Result.ToIdentifier(csGenerator) != "void")
            {
                if (!cppToCsMapping.ContainsValue(result) || result.Contains("."))
                    output.Add("        return KernelStream.Read<" + result + ">();");
                else
                    output.Add("        return KernelStream.Read" + result + "();");
            }

            output.Add("    }");
            output.Add("}");

            return output;
        }
        public static List<string> GenerateField(Field field)
        {
            List<string> output = new List<string>();

            Type fieldType = field.Type;

            if (fieldType == null)
                return output;
            if (fieldType is Type.Alias)
                if (!cppToCsMapping.ContainsKey(fieldType.Name))
                    fieldType = (fieldType as Type.Alias).Type;

            string modifier = null;
            if (field.Modifiers.HasFlag(Modifiers.Public)) modifier += "public ";
            if (field.Modifiers.HasFlag(Modifiers.Protected)) modifier += "protected ";
            if (field.Modifiers.HasFlag(Modifiers.Private)) modifier += "private ";
            if (field.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            if (field.Documentation.Any())
                output.AddRange(field.Documentation.Select(l => "/// " + l));

            string name = field.Name;
            if (name.Contains("["))
                name = "[] " + name.Before("[");
            else
                name = " " + name;

            output.Add(modifier + GetDisplayIdentifier(GetTypeIdentifier(fieldType)) + name);
            output.Add("{");

            if (field.GetAccessor != null || field.SetAccessor == null)
            {
                output.Add("    get");
                output.Add("    {");
                output.Add("        lock (KernelStream.Mutex)");
                output.Add("        {");

                if (field.GetAccessor == null)
                    output.Add("            KernelStream.Write((uint)0x" + field.GetGetAccessorHashCode().ToString("X8") + ");");
                else
                    output.Add("            KernelStream.Write((uint)0x" + field.GetAccessor.GetHashCode().ToString("X8") + ");");

                if (!field.Modifiers.HasFlag(Modifiers.Static))
                    output.Add("            KernelStream.Write(pointer.ToInt32());");

                string fieldIdentifier = GetTypeIdentifier(fieldType);
                if (field.Name.Contains("["))
                    fieldIdentifier += "[]";

                if (cppToCsMapping.ContainsValue(fieldIdentifier) && !fieldIdentifier.Contains("."))
                    output.Add("            return KernelStream.Read" + fieldIdentifier + "();");
                else
                    output.Add("            return KernelStream.Read<" + fieldIdentifier + ">();");

                output.Add("        }");
                output.Add("    }");
            }
            if (field.SetAccessor != null || field.GetAccessor == null)
            {
                output.Add("    set");
                output.Add("    {");
                output.Add("        lock (KernelStream.Mutex)");
                output.Add("        {");

                if (field.GetAccessor == null)
                    output.Add("            KernelStream.Write((uint)0x" + field.GetSetAccessorHashCode().ToString("X8") + ");");
                else
                    output.Add("            KernelStream.Write((uint)0x" + field.SetAccessor.GetHashCode().ToString("X8") + ");");

                if (!field.Modifiers.HasFlag(Modifiers.Static))
                    output.Add("            KernelStream.Write(pointer.ToInt32());");

                string fieldIdentifier = GetTypeIdentifier(fieldType);
                if (field.Name.Contains("["))
                    fieldIdentifier += "[]";

                if (cppToCsMapping.ContainsValue(fieldIdentifier) && !fieldIdentifier.Contains("."))
                    output.Add("            KernelStream.Write(value);");
                else
                    output.Add("            KernelStream.Write<" + fieldIdentifier + ">(value);");

                output.Add("        }");
                output.Add("    }");
            }

            output.Add("}");

            return output;
        }
        public static List<string> GenerateEvent(Field field)
        {
            List<string> output = new List<string>();

            Type fieldType = field.Type;

            if (fieldType == null)
                return output;
            if (fieldType is Type.Alias)
                if (!cppToCsMapping.ContainsKey(fieldType.Name))
                    fieldType = (fieldType as Type.Alias).Type;

            string modifier = null;
            if (field.Modifiers.HasFlag(Modifiers.Public)) modifier += "public ";
            if (field.Modifiers.HasFlag(Modifiers.Protected)) modifier += "protected ";
            if (field.Modifiers.HasFlag(Modifiers.Private)) modifier += "private ";
            if (field.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            if (field.Documentation.Any())
                output.AddRange(field.Documentation.Select(l => "/// " + l));

            string name = field.Name;
            if (name.Contains("["))
                name = "[] " + name.Before("[");
            else
                name = " " + name;

            string template = GetDisplayIdentifier(GetTypeIdentifier(fieldType.Templates.First()));
            if (template == "void")
                template = "";
            else
                template = "<" + template + ">";

            output.Add(modifier + "event Action" + template + name);
            output.Add("{");

            if (field.GetAccessor != null || field.SetAccessor == null)
            {
                output.Add("    add");
                output.Add("    {");
                output.Add("        lock (KernelStream.Mutex)");
                output.Add("        {");
                output.Add("        }");
                output.Add("    }");
            }
            if (field.SetAccessor != null || field.GetAccessor == null)
            {
                output.Add("    remove");
                output.Add("    {");
                output.Add("        lock (KernelStream.Mutex)");
                output.Add("        {");
                output.Add("        }");
                output.Add("    }");
            }

            output.Add("}");

            return output;
        }

        public static List<string> GenerateTypeCases(Type type)
        {
            List<string> output = new List<string>();

            foreach (Field field in type.Fields.Where(f => f.GetAccessor == null && f.SetAccessor == null && f.Modifiers.HasFlag(Modifiers.Public)))
            {
                output.Add(string.Format("case 0x{0:X8}: // {1}::get()", field.GetGetAccessorHashCode(), field));
                output.Add("{");

                if (field.Modifiers.HasFlag(Modifiers.Static))
                {
                    if (field.Type != null)
                        output.Add(string.Format("    {0}* result = ({0}*)&{1};", field.Type.ToIdentifier(csGenerator), field.ToIdentifier(csGenerator)));
                }
                else
                {
                    output.Add(string.Format("    {0}* object = debuggerStream->Read<{0}*>();", type.ToIdentifier(csGenerator)));
                    if (field.Type != null)
                        output.Add(string.Format("    {0} result = object->{1};", field.Type.ToIdentifier(csGenerator), field.Name));
                }

                output.Add("    debuggerStream->Write(result);");

                output.Add("}");
                output.Add("break;");
                output.Add("");

                if (field.Type != null)
                {
                    output.Add(string.Format("case 0x{0:X8}: // void {1}::set({2} value)", field.GetSetAccessorHashCode(), field.ToIdentifier(csGenerator), field.Type.ToIdentifier(csGenerator)));
                    output.Add("{");

                    output.Add("}");
                    output.Add("break;");
                    output.Add("");
                }
            }

            foreach (Method method in type.Methods.Where(m => !m.Modifiers.HasFlag(Modifiers.Template) && (m.Result != null || !type.Methods.Any(me => me.Abstract))))
            {
                Dictionary<string, Type> parameters = method.Parameters.ToDictionary(kvp =>
                {
                    if (kvp.Value is Type.Pointer)
                        return kvp.Key;
                    else if (kvp.Value is Type.Reference && !cppToCsMapping.ContainsKey((kvp.Value as Type.Reference).Type.ToIdentifier(csGenerator)))
                        return "*" + kvp.Key;
                    //else if (!cppToCsMapping.ContainsKey(kvp.Value.ToIdentifier()))
                    //    return "*" + kvp.Key;

                    return kvp.Key;
                }, kvp => kvp.Value);

                output.Add("case 0x" + method.GetHashCode().ToString("X8") + ": // " + method);
                output.Add("{");

                if (!method.Modifiers.HasFlag(Modifiers.Static) && method.Result != null)
                    output.Add(string.Format("    {0}* object = debuggerStream->Read<{0}*>();", type.ToIdentifier(csGenerator)));

                foreach (var kvp in method.Parameters.Where(p => p.Value != null && p.Key != "me"))
                {
                    string t = kvp.Value.ToIdentifier(csGenerator);

                    if (kvp.Value is Type.Pointer) ;
                    else if (kvp.Value is Type.Reference)
                    {
                        t = (kvp.Value as Type.Reference).Type.ToIdentifier(csGenerator);
                        if (!cppToCsMapping.ContainsKey(t))
                            t += "*";
                    }
                    else if (!cppToCsMapping.ContainsKey(t))
                        t += "*";

                    output.Add(string.Format("    {0} {1} = debuggerStream->Read<{0}>();", t, kvp.Key));
                }

                if (method.Modifiers.HasFlag(Modifiers.Static))
                {
                    if (method.Result.ToIdentifier(csGenerator) == "void")
                        output.Add(string.Format("    {0}::{1}({2});", type.ToIdentifier(csGenerator), method.Name, parameters.Select(p => p.Key).Join(", ")));
                    else
                        output.Add(string.Format("    {0} result = {1}::{2}({3});", method.Result.ToIdentifier(csGenerator), type.ToIdentifier(csGenerator), method.Name, parameters.Select(p => p.Key).Join(", ")));
                }
                else if (method.Result != null)
                {
                    if (method.Result.ToIdentifier(csGenerator) == "void")
                        output.Add(string.Format("    object->{0}({1});", method.Name, parameters.Select(p => p.Key).Join(", ")));
                    else
                        output.Add(string.Format("    {0} result = object->{1}({2});", method.Result.ToIdentifier(csGenerator), method.Name, parameters.Select(p => p.Key).Join(", ").Replace("me, ", "")).Replace("(me)", "()"));
                }
                else if (method.Result == null)
                    output.Add(string.Format("    {0}* result = new {0}({1});", type.ToIdentifier(csGenerator), parameters.Select(p => p.Key).Join(", ")));

                if (method.Result == null || method.Result.ToIdentifier(csGenerator) != "void")
                    output.Add("    debuggerStream->Write(" + (method.Result != null && !cppToCsMapping.ContainsKey(method.Result.ToIdentifier(csGenerator)) ? "&" : "") + "result);");

                output.Add("}");
                output.Add("break;");
                output.Add("");
            }

            return output;
        }

        public static string GetNamespaceIdentifier(Namespace nameSpace)
        {
            if (nameSpace.Parent is Namespace)
                return GetNamespaceIdentifier(nameSpace.Parent as Namespace) + "." + nameSpace.Name;
            else
                return "API." + nameSpace.Name;
        }
        public static string GetTypeIdentifier(Type type, IEnumerable<Type> hintTypes = null)
        {
            return type.ToIdentifier(csGenerator);

            if (type is Type.Pointer)
            {
                if (type.ToIdentifier(csGenerator) == "void*")
                    return cppToCsMapping["void*"];
                else
                    return GetTypeIdentifier((type as Type.Pointer).Type, hintTypes);
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
                    return cppToCsMapping[type.Name];
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
            return identifier;
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