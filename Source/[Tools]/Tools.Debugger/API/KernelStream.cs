using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Tools.Debugger
{
    public class KernelStream
    {
        private static Stream stream;
        private static BinaryReader reader;
        private static BinaryWriter writer;

        public static object Mutex = new object();

        public static void Initialize(Stream baseStream)
        {
            stream = baseStream;
            reader = new BinaryReader(stream);
            writer = new BinaryWriter(stream);
        }

        public static bool CanRead
        {
            get
            {
                return stream.CanRead;
            }
        }
        public static bool CanSeek
        {
            get
            {
                return stream.CanSeek;
            }
        }
        public static bool CanWrite
        {
            get
            {
                return stream.CanWrite;
            }
        }
        public static void Flush()
        {
            stream.Flush();
        }
        public static long Length
        {
            get
            {
                return stream.Length;
            }
        }
        public static long Position
        {
            get
            {
                return stream.Position;
            }
            set
            {
                stream.Position = value;
            }
        }
        public static int Read(byte[] buffer, int offset, int count)
        {
            return stream.Read(buffer, offset, count);
        }
        public static long Seek(long offset, SeekOrigin origin)
        {
            return stream.Seek(offset, origin);
        }
        public static void SetLength(long value)
        {
            stream.SetLength(value);
        }
        public static void Write(byte[] buffer, int offset, int count)
        {
            stream.Write(buffer, offset, count);
        }

        public static bool ReadBoolean()
        {
            return reader.ReadBoolean();
        }
        public static byte ReadByte()
        {
            return reader.ReadByte();
        }
        public static byte[] ReadBytes(int count)
        {
            return reader.ReadBytes(count);
        }
        public static char ReadChar()
        {
            return reader.ReadChar();
        }
        public static char[] ReadChars(int count)
        {
            return reader.ReadChars(count);
        }
        public static decimal ReadDecimal()
        {
            return reader.ReadDecimal();
        }
        public static double ReadDouble()
        {
            return reader.ReadDouble();
        }
        public static short ReadInt16()
        {
            return reader.ReadInt16();
        }
        public static int ReadInt32()
        {
            return reader.ReadInt32();
        }
        public static long ReadInt64()
        {
            return reader.ReadInt64();
        }
        public static sbyte ReadSByte()
        {
            return reader.ReadSByte();
        }
        public static float ReadSingle()
        {
            return reader.ReadSingle();
        }
        public static string ReadString()
        {
            return reader.ReadString();
        }
        public static ushort ReadUInt16()
        {
            return reader.ReadUInt16();
        }
        public static uint ReadUInt32()
        {
            return reader.ReadUInt32();
        }
        public static ulong ReadUInt64()
        {
            return reader.ReadUInt64();
        }
        public static IntPtr ReadIntPtr()
        {
            return new IntPtr(reader.ReadInt32());
        }
        public static T Read<T>()
        {
            return (T)Read(typeof(T));
        }
        public static object Read(Type type)
        {
            if (type == typeof(bool)) return ReadBoolean();
            if (type == typeof(byte)) return ReadByte();
            if (type == typeof(char)) return ReadChar();
            if (type == typeof(decimal)) return ReadDecimal();
            if (type == typeof(double)) return ReadDouble();
            if (type == typeof(float)) return ReadSingle();
            if (type == typeof(int)) return ReadInt32();
            if (type == typeof(long)) return ReadInt64();
            if (type == typeof(sbyte)) return ReadSByte();
            if (type == typeof(short)) return ReadInt16();
            if (type == typeof(string)) return ReadString();
            if (type == typeof(uint)) return ReadUInt32();
            if (type == typeof(ulong)) return ReadUInt64();
            if (type == typeof(ushort)) return ReadUInt16();
            if (type == typeof(IntPtr)) return ReadIntPtr();

            if (type.IsEnum) return Read(type.GetEnumUnderlyingType());

            return Activator.CreateInstance(type);
        }

        public static void Write(bool value)
        {
            writer.Write(value);
        }
        public static void Write(byte value)
        {
            writer.Write(value);
        }
        public static void Write(byte[] buffer)
        {
            writer.Write(buffer);
        }
        public static void Write(char ch)
        {
            writer.Write(ch);
        }
        public static void Write(char[] chars)
        {
            writer.Write(chars);
        }
        public static void Write(decimal value)
        {
            writer.Write(value);
        }
        public static void Write(double value)
        {
            writer.Write(value);
        }
        public static void Write(float value)
        {
            writer.Write(value);
        }
        public static void Write(int value)
        {
            writer.Write(value);
        }
        public static void Write(long value)
        {
            writer.Write(value);
        }
        public static void Write(sbyte value)
        {
            writer.Write(value);
        }
        public static void Write(short value)
        {
            writer.Write(value);
        }
        public static void Write(string value)
        {
            writer.Write(value);
        }
        public static void Write(uint value)
        {
            writer.Write(value);
        }
        public static void Write(ulong value)
        {
            writer.Write(value);
        }
        public static void Write(ushort value)
        {
            writer.Write(value);
        }
        public static void Write(IntPtr value)
        {
            writer.Write(value.ToInt32());
        }
        public static void Write(char[] chars, int index, int count)
        {
            writer.Write(chars, index, count);
        }
        public static void Write<T>(T value)
        {
            Write(typeof(T), (object)value);
        }
        public static void Write(Type type, object value)
        {
            if (type == typeof(bool))
                Write((bool)value);
            else if (type == typeof(byte))
                Write((byte)value);
            else if (type == typeof(char))
                Write((char)value);
            else if (type == typeof(decimal))
                Write((decimal)value);
            else if (type == typeof(double))
                Write((double)value);
            else if (type == typeof(float))
                Write((float)value);
            else if (type == typeof(int))
                Write((int)value);
        }
    }
}