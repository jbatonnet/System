using Debugger;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Tools.Pdb;

namespace System.Generator
{
    class Wrappers
    {
        public static void Generate()
        {
            string pdbPath = Path.Combine(Program.Root, @"System\Kernel\Kernel.pdb");
            string wrappersPath = Path.Combine(Program.Root, @"System\[Tools]\Debugger\Wrappers\Wrappers.cs");

            PdbFile pdbFile = new PdbFile(pdbPath);
            PdbSession pdbSession = pdbFile.OpenSession(0x100000);

            using (StreamWriter output = File.CreateText(wrappersPath))
            {
                output.WriteLine("using System;");
                output.WriteLine("using System.Collections.Generic;");
                output.WriteLine("using System.IO;");
                output.WriteLine("using System.Linq;");
                output.WriteLine();

                output.WriteLine("namespace Debugger.Wrappers");
                output.WriteLine("{");

                /*foreach (PdbSymbol customType in pdbSession.Global.FindChildren(PdbSymbolTag.CustomType))
                {
                    output.WriteLine("    class _{0} : Object", customType.VirtualAddress);
                    output.WriteLine("    {");
                    output.WriteLine("    }");
                }*/

                output.Write("}");
            }
        }
    }
}