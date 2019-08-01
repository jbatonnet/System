using System;
using System.Runtime.InteropServices;

using Tools.Gdb;

namespace Tools.Debugger.Wrappers
{
    public class Value<T> : Object
    {
        public T Data
        {
            get
            {
                int size = Marshal.SizeOf(typeof(T));

                byte[] buffer = new byte[size];
                memory.Read(Address, buffer, 0, size);

                T result = default(T);
                

                Type type = typeof(T);

                if (type == typeof(bool))
                    return (T)(object)(memory.ReadUInt8(Address) != 0);

                throw new NotSupportedException("Not supported value type");
            }
            set
            {

            }
        }

        public Value(GdbMemory memory, ulong address) : base(memory, address)
        {
            Type type = typeof(T);

            if (type.IsClass && type != typeof(string))
                throw new Exception("Cannot get value of this type");
        }
    }
}