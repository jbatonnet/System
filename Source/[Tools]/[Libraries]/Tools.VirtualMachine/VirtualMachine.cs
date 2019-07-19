using System;

namespace Tools.VirtualMachine
{
    public abstract class VirtualMachine : IDisposable
    {
        public string Path { get; protected set; }
        public abstract bool Running { get; }

        public abstract void Start();
        public abstract void Stop();
        public virtual void Restart()
        {
            Stop();
            Start();
        }

        public virtual void Dispose()
        {
            Stop();
        }

        public abstract event EventHandler Started;
        public abstract event EventHandler Stopped;
    }
}