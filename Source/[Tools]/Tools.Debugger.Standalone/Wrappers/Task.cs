using System;

using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Task : Object, IEquatable<Task>
    {
        public uint Id
        {
            get
            {
                return memory.ReadUInt32(Address);
            }
        }
        public Task Next
        {
            get
            {
                uint next = memory.ReadUInt32(Address + 19);
                return next == 0 ? null : new Task(memory, next);
            }
        }
        public ulong Tick
        {
            get
            {
                return memory.ReadUInt64(Address + 23);
            }
        }
        public uint Eip
        {
            get
            {
                return memory.ReadUInt32(Address + 47);
            }
        }
        public uint Esp
        {
            get
            {
                return memory.ReadUInt32(Address + 51);
            }
        }
        public uint Ebp
        {
            get
            {
                return memory.ReadUInt32(Address + 55);
            }
        }

        public Task(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }

        public override bool Equals(object obj)
        {
            return obj is Task && (obj as Task).Id == Id;
        }
        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }
        public bool Equals(Task other)
        {
            return other.Id == Id;
        }
    }
}