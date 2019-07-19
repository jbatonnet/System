using System;
using System.IO;

namespace Tools.Generator
{
    using Tools.VirtualMachine;

    public static class Program
    {
        public static VirtualMachine VirtualMachine { get; private set; }

        static void Main(string[] args)
        {
            Console.WriteLine("Generator.PostBuild: Begin");

            //HyperVOutput.Generate();

            // Construct environment and run the interface
            //using (VirtualMachine = new VMwareVirtualMachine(Path.Combine(Bootstrap.Root, @"VMware\System.vmx")))
                //;// Output.Generate();

            //Wrappers.Generate();

            Console.WriteLine("Generator.PostBuild: End");
        }
    }
}