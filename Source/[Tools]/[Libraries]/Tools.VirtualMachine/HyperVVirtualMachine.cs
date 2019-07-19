using System;
using System.IO;

namespace Tools.VirtualMachine
{
    public class HyperVVirtualMachine : VirtualMachine
    {
        public override bool Running
        {
            get
            {
                return false;
            }
        }

        public HyperVVirtualMachine(string path)
        {
            if (!File.Exists(path))
                throw new IOException("The specified file could not be found");

            Path = System.IO.Path.GetFullPath(path);
        }

        public override void Start()
        {
        }
        public override void Stop()
        {
        }
        public override void Restart()
        {
        }

        public override void Dispose()
        {
            throw new NotImplementedException();
        }

        public override event EventHandler Started;
        public override event EventHandler Stopped;
    }
}