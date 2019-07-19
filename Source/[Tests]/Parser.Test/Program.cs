using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Tools.Parser;
using Tools.Parser.Units;

namespace Tools.Parser.Test
{
    using Generators;
    using File = Units.File;
    using Type = Units.Type;

    class Program
    {
        private static List<string> texts = new List<string>();
        private static string none = "______";

        private static int GetTextIndex(string text)
        {
            int index = texts.IndexOf(text);

            if (index >= 0)
                return index;

            texts.Add(text);
            return texts.Count - 1;
        }

        static void Main(string[] args)
        {
            // Create a parser
            ClangParser parser = new ClangParser(Bootstrap.Source);
            parser.AddFile(Bootstrap.Source + @"\System\System.h");
            //foreach (string header in Directory.EnumerateFiles(Bootstrap.Source + @"\System\Base", "*.h", SearchOption.AllDirectories))//.Take(5))
            //    parser.AddFile(header);

            CppGenerator generator = new CppGenerator();

            // Generate sample reflection
            using (TextWriter output = new StreamWriter(Bootstrap.Source + @"\[Tests]\Parser.Cpp\Reflection.Generated.cpp"))
            {
                output.WriteLine("#include <System/System.h>");
                output.WriteLine("#include \"Reflection.h\"");
                output.WriteLine();

                output.WriteLine("#pragma const_seg(push, reflection, \".reflection\")");
                output.WriteLine();
                output.WriteLine("#define " + none + " -1");
                output.WriteLine("#define _ -1");
                output.WriteLine();
                output.WriteLine("#define N IdentifierType::Namespace");
                output.WriteLine("#define T IdentifierType::Type");
                output.WriteLine();

                output.WriteLine("static const Namespace _reflection_namespaces[] =");
                output.WriteLine("{");
                output.WriteLine("    // Parent, Name");

                #region Namespaces

                List<Namespace> namespaces = parser.Namespaces.ToList();

                while (true)
                {
                    Namespace[] subNamespaces = namespaces.SelectMany(n => n.Namespaces)
                                                          .Except(namespaces)
                                                          .ToArray();

                    if (subNamespaces.Length == 0)
                        break;

                    namespaces.AddRange(subNamespaces);
                }

                namespaces = namespaces.Where(n => n.Name != "std")
                                       .ToList();

                foreach (Namespace ns in namespaces)
                {
                    int parentIndex = namespaces.IndexOf(ns.Parent as Namespace);

                    output.WriteLine(string.Format("    {{ {0}, \"{1}\" }}, // {2}",
                                         parentIndex >= 0 ? ("0x" + parentIndex.ToString("X4")) : none,
                                         ns.Name,
                                         ns.ToIdentifier(generator)));
                }

                #endregion

                output.WriteLine("};");
                output.WriteLine();

                output.WriteLine("static const Type _reflection_types[] =");
                output.WriteLine("{");
                output.WriteLine("    // Parent, Name, TypeId");

                #region Types

                List<Type> types = Types.All.ToList();
                types.AddRange(parser.Types);

                foreach (Namespace ns in namespaces)
                    types.AddRange(ns.Types);

                types = types.Where(t => !(t is Type.Alias) && !t.Templates.Any())
                             .Where(t => !t.Name.Contains("RTTI"))
                             .Where(t => t.Name != "type_info")
                             .ToList();

                //types = types.Where(t => t.Name == "String").Take(1).ToList();

                foreach (Type type in types)
                {
                    int parentIndex = namespaces.IndexOf(type.Parent as Namespace);

                    output.WriteLine(string.Format("    {{ {{ N, {0} }}, \"{1}\", &typeid({2}) }},",
                                         parentIndex >= 0 ? ("0x" + parentIndex.ToString("X4")) : none,
                                         type.Name,
                                         type.ToIdentifier(generator)));
                }

                #endregion

                output.WriteLine("};");
                output.WriteLine();

                //output.WriteLine("static const Method _reflection_methods[] =");
                //output.WriteLine("{");
                //output.WriteLine("    // Parent, Name, Pointer");

                #region Methods

                // TODO: Add global and namespace methods

                List<Method> methods = new List<Method>();

                foreach (Type type in types)
                    methods.AddRange(type.Methods);

                methods = methods.Where(m => !m.Templates.Any())
                                 .Where(m => m.Modifiers.HasFlag(Modifiers.Public))
                                 .Where(m => m.Name != m.Parent?.Name)
                                 .Where(m => !m.Modifiers.HasFlag(Modifiers.Virtual))
                                 .ToList();

                foreach (Method method in methods)
                {
                    int parentIndex = types.IndexOf(method.Parent as Type);

                    //output.WriteLine(string.Format("    {{ {{ T, {0} }}, \"{1}\", (void*)&{2} }},",
                    //                     parentIndex >= 0 ? ("0x" + parentIndex.ToString("X4")) : none,
                    //                     method.Name,
                    //                     method.ToIdentifier(generator)));
                }

                #endregion

                //output.WriteLine("};");
                //output.WriteLine();

                output.WriteLine("static const Field _reflection_fields[] =");
                output.WriteLine("{");
                output.WriteLine("    // Parent, Name, Type");

                #region Fields

                List<Field> fields = new List<Field>();

                foreach (Type type in types)
                    fields.AddRange(type.Fields);

                fields = fields.Where(f => f.Modifiers.HasFlag(Modifiers.Public))
                               .ToList();

                //fields = fields.Where(t => t.Name == "String").Take(1).ToList();

                foreach (Field field in fields)
                {
                    int parentIndex = types.IndexOf(field.Parent as Type);



                    int typeIndex = types.IndexOf((field.Type as Type.Alias)?.Type ?? field.Type);

                    output.WriteLine(string.Format("    {{ {{ T, {0} }}, \"{1}\", 0x{2:x4} }}, // {3}",
                                         parentIndex >= 0 ? ("0x" + parentIndex.ToString("X4")) : none,
                                         field.Name,
                                         typeIndex,
                                         field.ToIdentifier(generator)));
                }

                #endregion

                output.WriteLine("};");
                output.WriteLine();

                if (texts.Count > 0)
                {
                    output.WriteLine("static const char* texts[] =");
                    output.WriteLine("{");

                    // Output texts
                    foreach (string text in texts)
                        output.WriteLine(string.Format("    \"{0}\",", text));

                    output.WriteLine("};");
                    output.WriteLine();
                }

                output.WriteLine("#pragma const_seg(pop, reflection)");
            }

            // Exit
            //Console.WriteLine();
            //Console.WriteLine("Press any key to exit ...");
            //Console.ReadKey(true);
        }
    }
}