using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Tools.Generator
{
    using Parser;
    using Parser.Units;
    using Parser.Generators;

    public class Doxygen
    {
        private static CppGenerator cppGenerator = new CppGenerator();

        public static void Generate()
        {
            string path = Path.Combine(Bootstrap.Source, @"System\Doxygen.h");

            List<string> result = new List<string>();

            result.AddRange(Program.Parser.Types.Where(t => t.Parent is File)
                                                .SelectMany(t => GenerateType(t), null));
            result.AddRange(Program.Parser.Namespaces.Where(n => !(n.Parent is Namespace))
                                                     .SelectMany(n => GenerateNamespace(n)));

            System.IO.File.WriteAllLines(path, result);
        }

        public static List<string> GenerateNamespace(Namespace nameSpace)
        {
            List<string> result = new List<string>();

            result.Add("namespace " + nameSpace.Name);
            result.Add("{");

            result.AddRange(nameSpace.Types.SelectMany(t => GenerateType(t), null).Select(l => "    " + l));
            result.AddRange(nameSpace.Namespaces.SelectMany(n => GenerateNamespace(n), null).Select(l => "    " + l));

            result.Add("}");

            return result;
        }
        public static List<string> GenerateType(Type type)
        {
            List<string> output = new List<string>();

            if (type is Type.Alias)
            {
                output.Add("typedef ... " + type.Name + ";");
                return output;
            }

            string modifier = "";
            if (type.Modifiers.HasFlag(Modifiers.Template)) modifier += "template<" + type.Templates.Select(t => "typename " + t.Name).Join(", ") + "> ";

            if (type.Documentation != null)
                output.AddRange(type.Documentation.Select(l => "/// " + l));

            string style = type.Style == TypeStyle.Enum ? "enum class" : type.Style.ToString().ToLower();
            if (!type.Bases.Any())
                output.Add(modifier + style + " " + type.Name);
            else
                output.Add(modifier + style + " " + type.Name + " : " + type.Bases.Select(b => b.Name).Join(", "));
            output.Add("{");

            if (type.Style == TypeStyle.Class)
                output.Add("public:");

            if (type.Style == TypeStyle.Enum)
                output.AddRange(type.Fields.Select(f => "    " + f.Name + ","));

            output.AddRange(type.Types.Where(t => t.Modifiers.HasFlag(Modifiers.Public)).SelectMany(t => GenerateType(t), null).Select(l => "    " + l));
            output.AddRange(type.Fields.Where(t => t.Modifiers.HasFlag(Modifiers.Public)).SelectMany(f => GenerateField(f)).Select(l => "    " + l));
            output.AddRange(type.Methods.Where(m => m.Modifiers.HasFlag(Modifiers.Public) && !type.Fields.SelectMany(f => new[] { f.GetAccessor, f.SetAccessor }).Contains(m)).SelectMany(m => GenerateMethod(m)).Select(l => "    " + l));

            output.Add("};");

            return output;
        }
        public static List<string> GenerateMethod(Method method)
        {
            List<string> output = new List<string>();

            if (method.Documentation != null)
                output.AddRange(method.Documentation.Select(l => "/// " + l));

            string modifier = "";
            if (method.Modifiers.HasFlag(Modifiers.Template)) modifier += "template<" + method.Templates.Select(t => "typename " + t.Name).Join(", ") + "> ";
            if (method.Modifiers.HasFlag(Modifiers.Virtual)) modifier += "virtual ";
            if (method.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            string result = "";
            if (method.Result != null)
                result = method.Result.ToIdentifier(cppGenerator) + " ";

            output.Add(modifier + result + method.Name + "(" + method.Parameters.Select(p => p.Value == null ? "?" : p.Value.ToIdentifier(cppGenerator) + " " + p.Key).Join(", ") + ");");

            return output;
        }
        public static List<string> GenerateField(Field field)
        {
            List<string> result = new List<string>();

            if (field.Type == null)
                return result;

            string modifier = null;
            if (field.Modifiers.HasFlag(Modifiers.Static)) modifier += "static ";

            if (field.Documentation != null)
                result.AddRange(field.Documentation.Select(l => "/// " + l));

            result.Add(modifier + field.Type.ToIdentifier(cppGenerator) + " " + field.Name + ";");

            return result;
        }
    }
}
