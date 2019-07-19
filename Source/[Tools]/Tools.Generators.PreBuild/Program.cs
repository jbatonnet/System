using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows.Forms;

namespace Tools.Generator
{
    using Parser;

    public class Program
    {
        public static ClangParser Parser { get; private set; }

        static void Main(string[] args)
        {
            Console.WriteLine("Generator.PreBuild: Begin");

            // Generate headers index
            Headers.Generate();

            // Use clang to parse headers
            Parser = new ClangParser(Bootstrap.Source);
            Parser.AddFile(@"System\System.h");
            //Parser.Resolve();

            // Generate everything
            Doxygen.Generate();
            Wrappers.Generate();
            //Debugger.Generate();
            Reflection.Generate();

            Console.WriteLine("Generator.PreBuild: End");
        }
    }
}