using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Process : Object
    {
        public Process(GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}