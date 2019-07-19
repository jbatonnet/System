using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Tools.Generator
{
    using Parser;
    using Parser.Units;
    using File = System.IO.File;

    public class Headers
    {
        public static void Generate()
        {
            string systemPath = Path.Combine(Bootstrap.Source, @"System");
            string systemHeader = Path.Combine(systemPath, "System.h");

            /*
            using (StreamWriter output = File.CreateText(kernelPath))
            {
                output.WriteLine("#ifndef _KERNEL_KERNEL_H_");
                output.WriteLine("#define _KERNEL_KERNEL_H_");
                output.WriteLine();
            }
            */

            using (StreamWriter output = File.CreateText(systemHeader))
            {
                output.WriteLine("#ifndef _SYSTEM_SYSTEM_H_");
                output.WriteLine("#define _SYSTEM_SYSTEM_H_");
                output.WriteLine();
                output.WriteLine("extern \"C\" void AppMain();");
                output.WriteLine();
                output.WriteLine("#include <System/Common.h>");
                output.WriteLine();

                List<List<string>> headers = Directory.GetFiles(systemPath, "*.h", SearchOption.AllDirectories)
                                                      .Select(f => f.Replace(systemPath + "\\", ""))
                                                      .GroupBy(f => f.Before("\\"), (d, f) => f.ToList())
                                                      .Where(f => f.Count > 1)
                                                      .ToList();

                foreach (List<string> files in headers)
                {
                    output.WriteLine("// " + files[0].Before("\\"));

                    foreach (string file in files)
                        output.WriteLine("#include <System/{0}>", file.Replace("\\", "/"));

                    output.WriteLine();
                }

                output.WriteLine("#endif");
            }
        }
    }
}