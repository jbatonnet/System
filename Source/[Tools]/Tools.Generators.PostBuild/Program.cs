using System;

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
            Output.Generate();

            Console.WriteLine("Generator.PostBuild: End");
        }
    }
}