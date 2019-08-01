using System;

using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class String : Object, IEquatable<String>
    {
        public string Value
        {
            get
            {
                return null;
            }
        }

        public String(GdbMemory memory, ulong address) : base(memory, address)
        {
        }

        public override bool Equals(object obj)
        {
            return obj is String && (obj as String).Value == Value;
        }
        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }
        public bool Equals(String other)
        {
            return other.Value == Value;
        }
    }
}