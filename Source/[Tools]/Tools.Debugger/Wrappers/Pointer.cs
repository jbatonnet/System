using System;

using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Pointer<T> : Object where T : Object
    {
        public T Object
        {
            get
            {
                uint value = memory.ReadUInt32(Address);
                return value == 0 ? null : Activator.CreateInstance(typeof(T), memory, value) as T;
            }
        }

        public Pointer(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}