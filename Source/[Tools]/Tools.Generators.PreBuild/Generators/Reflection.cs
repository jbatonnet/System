using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

using CFile = System.IO.File;

namespace Tools.Generator
{
    using Parser;
    using Parser.Units;
    using Parser.Generators;

    public static class Reflection
	{
        private static CppGenerator cppGenerator = new CppGenerator();

		public static void Generate()
		{
			string reflectionPath = Path.Combine(Bootstrap.Source, @"Kernel\Runtime\Reflection\Reflection.Generated.cpp");

			using (StreamWriter output = CFile.CreateText(reflectionPath))
			{
                output.WriteLine("#include <System/System.h>");
                output.WriteLine("#include <Kernel/Runtime/Reflection/Reflection.h>");
				output.WriteLine();

                //Type[] types = Program.Parser.Types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared))
                //                                   .Where(t => !t.Name.Contains("RTTI"))
                //                                   .ToArray();
                //List<Method> methods = types.SelectMany(t => t.Methods).ToList();

                //foreach (var file in Program.Parser.Files)
                //	output.WriteLine("#include <{0}>", file.Path.Replace(context.Path + "\\", "").Replace("\\", "/"));
                //output.WriteLine();

                output.WriteLine("using namespace System::Runtime;");
                output.WriteLine();

                foreach (Namespace ns in Program.Parser.Namespaces)
					output.WriteLine("using namespace {0};", ns.ToIdentifier(cppGenerator));
				output.WriteLine();

				output.WriteLine("void Reflection::Initialize()");
				output.WriteLine("{");

                Type[] types = Program.Parser.Types.Where(t => !(t.Parent is Namespace) && !(t is Type.Alias) && !t.Templates.Any())
                                                   .Where(t => !t.Name.Contains("RTTI"))
                                                   .Where(t => t.Name != "type_info" && t.Name != "initializer_list")
                                                   .ToArray();
                foreach (Type t in types)
					output.WriteLine(string.Join(Environment.NewLine, GenerateType(t).Select(l => "    " + l)));



				//foreach (Namespace ns in Program.Parser.Namespaces.Where(n => !(n.Parent is Namespace)))
				//	output.WriteLine(string.Join(Environment.NewLine, GenerateNamespace(ns).Select(l => "    " + l)));

				output.WriteLine("}");
			}
		}

		public static List<string> GenerateNamespace(Namespace ns)
		{
			List<string> result = new List<string>();

			result.Add(string.Format("Namespace* {0}Namespace = Reflection::RegisterNamespace({1}\"{2}\"); // {3}", ns.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower(),
																													ns.Parent is Namespace ? ((ns.Parent as Namespace).ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + "Namespace, ") : "",
																													ns.Name,
																													ns.ToIdentifier(cppGenerator)));

			foreach (Namespace n in ns.Namespaces)
				result.AddRange(GenerateNamespace(n).Select(l => "    " + l));

			foreach (Type t in ns.Types.Where(t => !t.Modifiers.HasFlag(Modifiers.Template) && !t.Modifiers.HasFlag(Modifiers.Private) && !t.Templates.Any()))
				result.AddRange(GenerateType(t).Select(l => "    " + l));

			return result;
		}
		public static List<string> GenerateType(Type type)
		{
			List<string> result = new List<string>();

			Unit parent = type.Parent is File ? null : type.Parent;
			result.Add(string.Format("Type* {0}Type = Reflection::RegisterType<{1}>({2}\"{3}\"); // {4}", type.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower(),
																										  type.ToIdentifier(cppGenerator),
																										  parent?.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + parent?.GetType().Name + (parent != null ? ", " : ""),
																										  type.Name,
																										  type.ToIdentifier(cppGenerator)));

			foreach (Type t in type.Types.Where(t => t.Name != ""))
				result.AddRange(GenerateType(t).Select(l => "    " + l));

			foreach (Method m in type.Methods.Where(m => m.Parent == type && !m.Templates.Any()))
				result.AddRange(GenerateMethod(m).Select(l => "    " + l));

			foreach (Field f in type.Fields.Where(f => f.GetAccessor != null || f.SetAccessor != null))
			    result.AddRange(GenerateProperty(f).Select(l => "    " + l));

			return result;
		}
		public static List<string> GenerateMethod(Method method)
		{
			List<string> result = new List<string>();

			if (method.Result == null)
			{
				result.Add(string.Format("Reflection::RegisterConstructor<{0}{1}>({2});",
					method.Parent.ToIdentifier(cppGenerator),
					(method.Parameters.Any() ? ", " : "") + method.Parameters.Select(p => p.Value?.ToIdentifier(cppGenerator)).Join(", "),
					method.Parent.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + method.Parent.GetType().Name.Replace("Cpp", "")
				));
			}
			else if (!method.Name.StartsWith("operator"))
			{
				result.Add(string.Format("Method* {0}Method = Reflection::Register{1}<{2}>({3}, \"{4}\");",
					method.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower(),
					method.Result?.Name == "void" ? "Action" : "Function",
					(method.Result?.Name == "void" ? "" : method.Result?.ToIdentifier(cppGenerator)) + (method.Result?.Name != "void" && method.Parameters.Any() ? ", " : "") + method.Parameters.Select(p => p.Value?.ToIdentifier(cppGenerator)).Join(", "),
					method.Parent.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + method.Parent.GetType().Name.Replace("Cpp", ""),
					method.Name
				));
			}

			return result;
		}
		public static List<string> GenerateProperty(Field property)
		{
			List<string> result = new List<string>();

			result.Add(string.Format("Property* {0}Property = Reflection::RegisterProperty<{1}>({2}, \"{3}\", {4}, {5});",
				property.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower(),
				property.Type.ToIdentifier(cppGenerator),
				property.Parent.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + property.Parent.GetType().Name.Replace("Cpp", ""),
				property.Name,
				property.GetAccessor == null ? "null" : property.GetAccessor.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + "Method",
				property.SetAccessor == null ? "null" : property.SetAccessor.ToIdentifier(cppGenerator).Replace("::", "").ToFirstLower() + "Method"
            ));

			return result;
		}
    }
}