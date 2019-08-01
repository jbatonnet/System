using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Collection<T> : Object where T : Object
    {
        public uint Count
        {
            get
            {
                return memory.ReadUInt32(Address + 12);
            }
        }
        public uint Limit
        {
            get
            {
                return memory.ReadUInt32(Address + 16);
            }
        }

        public Collection(GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}