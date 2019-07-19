using System;

using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Object : IEquatable<Object>
    {
        public ulong Address { get; protected set; }

        protected GdbStub.GdbMemory memory;

        protected Object(GdbStub.GdbMemory memory, ulong address)
        {
            this.memory = memory;
            Address = address;
        }

        public override bool Equals(object obj)
        {
            return obj is Object && (obj as Object).Address == Address;
        }
        public override int GetHashCode()
        {
            return Address.GetHashCode();
        }
        public bool Equals(Object other)
        {
            return other.Address == Address;
        }
    }
}