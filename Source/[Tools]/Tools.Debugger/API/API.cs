using System;
using KernelStream = System.Debugger.KernelStream;

using RTTI_TypeDescriptor = API.type_info;
using unit = API.Unit;
using SizeUnit = API.Units.Size.Units;
using TemperatureUnit = API.Units.Temperature.Units;
using FileSizeUnit = API.Units.FileSize.Units;

namespace API
{
    public class Flag
    {
        private IntPtr pointer;
    
        internal Flag(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static bool Test<T, U>(T value, U flag)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2D5E4E31);
                KernelStream.Write(value);
                KernelStream.Write(flag);
                return KernelStream.ReadBoolean();
            }
        }
        public static U Get<T, U>(T value, U mask)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE825883B);
                KernelStream.Write(value);
                KernelStream.Write(mask);
                return KernelStream.Read<U>();
            }
        }
    }
    
    public class type_info
    {
        private IntPtr pointer;
    
        internal type_info(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public IntPtr data
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6B13A986);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadIntPtr();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8D2A9557);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public sbyte name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0D950BD2);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8C584673);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class RTTI_ClassHierarchyDescriptor
    {
        private IntPtr pointer;
    
        internal RTTI_ClassHierarchyDescriptor(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Signature
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0CFBF3F4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8E482A5C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint Attributes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x057B11F9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x11EB542D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint BaseClassesCount
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x41A68EAD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9628C8F5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public RTTI_BaseClassDescriptor BaseClasses
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE7BA4C8E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_BaseClassDescriptor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x62FF5680);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_BaseClassDescriptor>(value);
                }
            }
        }
    }
    
    public class RTTI_PMD
    {
        private IntPtr pointer;
    
        internal RTTI_PMD(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public int MemberOffset
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5F40A8D6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8F757EAD);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public int VTableOffset
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9A57B3AB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4C145A15);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public int vdisp
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2BAE3BBC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x241B5418);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class RTTI_BaseClassDescriptor
    {
        private IntPtr pointer;
    
        internal RTTI_BaseClassDescriptor(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public RTTI_TypeDescriptor Type
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8EC606C0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_TypeDescriptor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC58CC89D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_TypeDescriptor>(value);
                }
            }
        }
        public uint BaseClassesCount
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEA4DEB61);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x22AC85B6);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public RTTI_PMD Pmd
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD5BCF458);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_PMD>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5AD17F12);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_PMD>(value);
                }
            }
        }
        public uint Attributes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x281008DE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA60C9FB0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public RTTI_ClassHierarchyDescriptor Hierarchy
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC6DD40C3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_ClassHierarchyDescriptor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3564BFCB);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_ClassHierarchyDescriptor>(value);
                }
            }
        }
    }
    
    public class RTTI_CompleteObjectLocator
    {
        private IntPtr pointer;
    
        internal RTTI_CompleteObjectLocator(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Signature
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x28BA24B3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4622027A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint Offset
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEC0C43E2);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x30F9D8D5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint CdOffset
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA85E2855);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB1FE7988);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public RTTI_TypeDescriptor Type
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5EEF7F2C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_TypeDescriptor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDBBD9767);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_TypeDescriptor>(value);
                }
            }
        }
        public RTTI_ClassHierarchyDescriptor Hierarchy
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8B6A3D7B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<RTTI_ClassHierarchyDescriptor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x47B6D982);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<RTTI_ClassHierarchyDescriptor>(value);
                }
            }
        }
    }
    
    public enum Month
    {
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    }
    
    public enum Day
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday,
    }
    
    public enum Casing
    {
        Upper,
        Lower,
        FirstUpper,
        WordsUpper,
        Words,
        Sentence,
    }
    
    public class Memory
    {
        private IntPtr pointer;
    
        internal Memory(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static void Copy(IntPtr source, IntPtr destination, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x58974E24);
                KernelStream.Write(source);
                KernelStream.Write(destination);
                KernelStream.Write(count);
            }
        }
        public static void Clear(IntPtr address, uint count, byte value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x43FFD943);
                KernelStream.Write(address);
                KernelStream.Write(count);
                KernelStream.Write(value);
            }
        }
        public static void Set<T>(IntPtr address, T value, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD4E19BC0);
                KernelStream.Write(address);
                KernelStream.Write(value);
                KernelStream.Write(count);
            }
        }
        public static bool Compare(IntPtr address1, IntPtr address2, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x11A6BBC9);
                KernelStream.Write(address1);
                KernelStream.Write(address2);
                KernelStream.Write(count);
                return KernelStream.ReadBoolean();
            }
        }
        public static T Allocate<T>(uint count, short value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6D044766);
                KernelStream.Write(count);
                KernelStream.Write(value);
                return KernelStream.Read<T>();
            }
        }
        public static void Free(IntPtr address)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x00ED6A8D);
                KernelStream.Write(address);
            }
        }
    }
    
    public class Function<Result, Args>
    {
        private IntPtr pointer;
    
        internal Function(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public IntPtr GetPointer()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x424FBE64);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadIntPtr();
            }
        }
    }
    
    public class Reference<T>
    {
        private IntPtr pointer;
    
        internal Reference(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Dynamic<T>
    {
        private IntPtr pointer;
    
        internal Dynamic(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T Pointer
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB8D18CDC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<T>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0389000F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<T>(value);
                }
            }
        }
    
        public T GetPointer()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x704C9BB3);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
    }
    
    public class Unit
    {
        private IntPtr pointer;
    
        internal Unit(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static Unit operator+(Unit me, Unit other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x79932B73);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<Unit>();
            }
        }
        public static Unit operator-(Unit me, Unit other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD976F4AE);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<Unit>();
            }
        }
        public static Unit operator*(Unit me, Unit other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA405F2F6);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<Unit>();
            }
        }
        public static Unit operator!(Unit me)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFF5F3F21);
                KernelStream.Write(me);
                return KernelStream.Read<Unit>();
            }
        }
    }
    
    public class Parameters<T>
    {
        private IntPtr pointer;
    
        internal Parameters(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T GetValue(uint i)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA01227C9);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(i);
                return KernelStream.Read<T>();
            }
        }
        public T GetPointer()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x58F45D89);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
    }
    
    public class Iterator<T>
    {
        private IntPtr pointer;
    
        internal Iterator(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T Current
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDE0B28A9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<T>();
                }
            }
        }
    
        public bool Next()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xDCFFC93C);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadBoolean();
            }
        }
    }
    
    public class Collection<T>
    {
        private IntPtr pointer;
    
        internal Collection(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Reference<Iterator<T>> GetIterator()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9400273E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Reference<Iterator<T>>>();
            }
        }
        public T First()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x0E70B855);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public T Last()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE94B2C8E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public bool Any()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xEB8EB8F6);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadBoolean();
            }
        }
        public uint Count()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9A4227BD);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt32();
            }
        }
        public Reference<Collection<T>> Where(Function filter)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3BCF28DB);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(filter);
                return KernelStream.Read<Reference<Collection<T>>>();
            }
        }
        public Reference<Collection<U>> OfType<U>()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x17C68FEF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Reference<Collection<U>>>();
            }
        }
        public Reference<Collection<U>> Select<U>(Function projection)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x62C93245);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(projection);
                return KernelStream.Read<Reference<Collection<U>>>();
            }
        }
        public Reference<Collection<U>> SelectMany<U>(Function<Reference<Collection>> projection)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7F72DEC6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(projection);
                return KernelStream.Read<Reference<Collection<U>>>();
            }
        }
        public Reference<Collection<T>> Concat(Reference<Collection<T>> other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x35B80975);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(other);
                return KernelStream.Read<Reference<Collection<T>>>();
            }
        }
    }
    
    public class RangeIterator<T>
    {
        private IntPtr pointer;
    
        internal RangeIterator(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T GetCurrent()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD844CB5E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public bool Next()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1EBD27C5);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadBoolean();
            }
        }
        public static void operator++(RangeIterator<T> me)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE9D486F3);
                KernelStream.Write(me);
            }
        }
    }
    
    public class Debug
    {
        private IntPtr pointer;
    
        internal Debug(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static void Assert(bool condition, string message)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5B16A9F6);
                KernelStream.Write(condition);
                KernelStream.Write(message);
            }
        }
        public static void NotImplemented()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE2A3EE6A);
            }
        }
    }
    
    public class List<T>
    {
        private IntPtr pointer;
    
        internal List(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Count
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE126FD6C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
        }
    
        public void Add(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2874D3D3);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public void Remove(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6D847314);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public void Clear()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3ACF6EC4);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public T At(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFCB8BE07);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.Read<T>();
            }
        }
        public void Move(uint from, uint to)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x45101CC8);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(from);
                KernelStream.Write(to);
            }
        }
        public void Swap(uint from, uint to)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA11C6C69);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(from);
                KernelStream.Write(to);
            }
        }
        public void BringToFront(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x66A2D21B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
            }
        }
        public void SendToBack(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF2DCE9A9);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
            }
        }
        public Reference<Iterator<T>> GetIterator()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x70FC46B5);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Reference<Iterator<T>>>();
            }
        }
        public T First()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x146778E4);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public T Last()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x245FE09A);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public bool Any()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x28443F03);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadBoolean();
            }
        }
        public int IndexOf(T element)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x54115AC5);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(element);
                return KernelStream.ReadInt32();
            }
        }
        public T Sum()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xAE5320D3);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public List<T> Where<Func>(Func predicate)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3A74E984);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(predicate);
                return KernelStream.Read<List<T>>();
            }
        }
    }
    
    public class Event<T>
    {
        private IntPtr pointer;
    
        internal Event(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class ChangeEventParameter<T>
    {
        private IntPtr pointer;
    
        internal ChangeEventParameter(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class ChangeEvent<T>
    {
        private IntPtr pointer;
    
        internal ChangeEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Exception
    {
        private IntPtr pointer;
    
        internal Exception(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static void Assert<T, Args>(bool condition, string message, Args parameters)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB6C3FE5A);
                KernelStream.Write(condition);
                KernelStream.Write(message);
                KernelStream.Write(parameters);
            }
        }
        public static void Throw<T, Args>(string message, Args parameters)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4A038F02);
                KernelStream.Write(message);
                KernelStream.Write(parameters);
            }
        }
    }
    
    public class DefaultValue<T>
    {
        private IntPtr pointer;
    
        internal DefaultValue(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static T Get()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7F29C069);
                return KernelStream.Read<T>();
            }
        }
    }
    
    public class ConsoleStream
    {
        private IntPtr pointer;
    
        internal ConsoleStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ulong GetLength()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xDD1E31FF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x817EB885);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x83D4728A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
    }
    
    public class Maths
    {
        private IntPtr pointer;
    
        internal Maths(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static T Max<T>(T left, T right)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x030CA19B);
                KernelStream.Write(left);
                KernelStream.Write(right);
                return KernelStream.Read<T>();
            }
        }
        public static T Min<T>(T left, T right)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCF01DA94);
                KernelStream.Write(left);
                KernelStream.Write(right);
                return KernelStream.Read<T>();
            }
        }
        public static T Clamp<T>(T value, T minimum, T maximum)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x305DA58E);
                KernelStream.Write(value);
                KernelStream.Write(minimum);
                KernelStream.Write(maximum);
                return KernelStream.Read<T>();
            }
        }
        public static T Abs<T>(T val)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1DC75B54);
                KernelStream.Write(val);
                return KernelStream.Read<T>();
            }
        }
        public static T Sign<T>(T val)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7EC2154A);
                KernelStream.Write(val);
                return KernelStream.Read<T>();
            }
        }
        public static void Swap<T>(T value1, T value2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x96E6542A);
                KernelStream.Write(value1);
                KernelStream.Write(value2);
            }
        }
        public static T Map<T>(T value, T fromMin, T fromMax, T toMin, T toMax)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x0A142D63);
                KernelStream.Write(value);
                KernelStream.Write(fromMin);
                KernelStream.Write(fromMax);
                KernelStream.Write(toMin);
                KernelStream.Write(toMax);
                return KernelStream.Read<T>();
            }
        }
        public static float Round(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x383AEAA4);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Ceil(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5BC4087E);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Floor(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x33E567E8);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Lerp(float start, float end, float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9640BE0B);
                KernelStream.Write(start);
                KernelStream.Write(end);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Sqrt(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5ABC1B15);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Pow(float value, float power)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x16852457);
                KernelStream.Write(value);
                KernelStream.Write(power);
                return KernelStream.ReadSingle();
            }
        }
        public static float Sin(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2B71033B);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Cos(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x987BDFA3);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Tan(float value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7275BA5A);
                KernelStream.Write(value);
                return KernelStream.ReadSingle();
            }
        }
        public static float Atan2(float x, float y)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCA805F06);
                KernelStream.Write(x);
                KernelStream.Write(y);
                return KernelStream.ReadSingle();
            }
        }
    }
    
    public class Matrix3
    {
        private IntPtr pointer;
    
        internal Matrix3(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Matrix3 Identity
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xECF00FF4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Matrix3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAFE94C2C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Matrix3>(value);
                }
            }
        }
        public float components
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAC8F1637);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6CD36279);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c11
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCDE99418);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6663BE83);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c12
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x436693FB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC535382A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c13
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8FCC9365);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x12D7B872);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c21
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF464A8DD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC9CAF349);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c22
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7AEBAF3E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6A9C75E0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c23
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB641AFA0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBD7EF5B8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c31
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE31FBC9E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xACADC80F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c32
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6D90BB7D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0FFB4EA6);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c33
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA13ABBE3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD819CEFE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public float Determinant()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x48D9429D);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSingle();
            }
        }
        public Matrix3 Transpose()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2A215020);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Matrix3>();
            }
        }
        public void Normalize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD9F74A4D);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public static Matrix3 CreateRotation(float pitch, float yaw, float roll)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD87DEA3D);
                KernelStream.Write(pitch);
                KernelStream.Write(yaw);
                KernelStream.Write(roll);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 CreateTranslation(float x, float y, float z)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x79668963);
                KernelStream.Write(x);
                KernelStream.Write(y);
                KernelStream.Write(z);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 CreateScale(float x, float y, float z)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCE1D7969);
                KernelStream.Write(x);
                KernelStream.Write(y);
                KernelStream.Write(z);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 operator+(Matrix3 me, Matrix3 matrix)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x611606DC);
                KernelStream.Write(me);
                KernelStream.Write(matrix);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 operator-(Matrix3 me, Matrix3 matrix)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE5359B09);
                KernelStream.Write(me);
                KernelStream.Write(matrix);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 operator*(Matrix3 me, Matrix3 matrix)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x04713D9A);
                KernelStream.Write(me);
                KernelStream.Write(matrix);
                return KernelStream.Read<Matrix3>();
            }
        }
        public static Matrix3 operator/(Matrix3 me, Matrix3 matrix)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2FFBED85);
                KernelStream.Write(me);
                KernelStream.Write(matrix);
                return KernelStream.Read<Matrix3>();
            }
        }
    }
    
    public class Point2
    {
        private IntPtr pointer;
    
        internal Point2(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public int X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF243F0A5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x54F27163);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public int Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3EE9F03B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD354BA20);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Point2 Zero
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE2490815);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA83B5ABA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point2>(value);
                }
            }
        }
        public Point2 One
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCDCDF3D7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x006D4FBA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point2>(value);
                }
            }
        }
    }
    
    public class Point3
    {
        private IntPtr pointer;
    
        internal Point3(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public int X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x33CD2F65);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x31954A25);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public int Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFF672FFB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB6338166);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public int Z
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x71E82818);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE5A9DAE2);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Point3 Zero
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7F46E963);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBEF5B3E4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point3>(value);
                }
            }
        }
        public Point3 One
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x105B2A52);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x799A40B8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point3>(value);
                }
            }
        }
    }
    
    public class Vector2
    {
        private IntPtr pointer;
    
        internal Vector2(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public float X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1763008F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3AA992C2);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDBC90011);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xED4B129A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Vector2 Zero
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF8410AB3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x42B46C19);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
        public Vector2 One
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1F1B28C3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x673AB1F0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
        public Vector2 Left
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6EFF3A3B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB67BF7E5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
        public Vector2 Up
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3C170736);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x728359B1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
        public Vector2 Right
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCF62734A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5621E5D4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
        public Vector2 Down
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x95DE3066);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4D2C632A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector2>(value);
                }
            }
        }
    
        public float Length()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9148A90B);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSingle();
            }
        }
        public static Vector2 Lerp(Vector2 v1, Vector2 v2, float c)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB7B8C389);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                KernelStream.Write(c);
                return KernelStream.Read<Vector2>();
            }
        }
        public static float Dot(Vector2 v1, Vector2 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA4F587E6);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.ReadSingle();
            }
        }
        public static Vector2 Normalize(Vector2 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7C87B05F);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector2>();
            }
        }
        public static float Angle(Vector2 v1, Vector2 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x75AA9EB5);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.ReadSingle();
            }
        }
        public static float Distance(Vector2 v1, Vector2 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x373B0C75);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.ReadSingle();
            }
        }
        public static Vector2 operator+(Vector2 me, Vector2 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB6BA7BB1);
                KernelStream.Write(me);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector2>();
            }
        }
        public static Vector2 operator-(Vector2 me, Vector2 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3299E664);
                KernelStream.Write(me);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector2>();
            }
        }
        public static Vector2 operator*(Vector2 me, float factor)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x33172983);
                KernelStream.Write(me);
                KernelStream.Write(factor);
                return KernelStream.Read<Vector2>();
            }
        }
        public static Vector2 operator/(Vector2 me, float factor)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC7B9C50F);
                KernelStream.Write(me);
                KernelStream.Write(factor);
                return KernelStream.Read<Vector2>();
            }
        }
    }
    
    public class Vector3
    {
        private IntPtr pointer;
    
        internal Vector3(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public float X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD6EDDF4F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2D81F602);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1A47DFD1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFA63765A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Z
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x94C8D832);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5935F0F3);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Vector3 Zero
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x654EEBC5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x36C8A17E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 One
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC28DF146);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x71F458AE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Backward
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA671A871);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x047F75A7);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Forward
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x13D99F81);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x27E522BF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Left
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF3F0DB4D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC2073A82);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Right
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7699A8A2);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7D3A129F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Down
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x08D1D110);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3950AE4D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
        public Vector3 Up
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA7B24B59);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Vector3>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0B7456B3);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Vector3>(value);
                }
            }
        }
    
        public float Length()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x50C676CB);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSingle();
            }
        }
        public static Vector3 Lerp(Vector3 v1, Vector3 v2, float c)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x199FC2C7);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                KernelStream.Write(c);
                return KernelStream.Read<Vector3>();
            }
        }
        public static Vector3 Cross(Vector3 v1, Vector3 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x34402D96);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.Read<Vector3>();
            }
        }
        public static float Dot(Vector3 v1, Vector3 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9FBC92C3);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.ReadSingle();
            }
        }
        public static Vector3 Normalize(Vector3 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6A6DBEA8);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector3>();
            }
        }
        public static float Distance(Vector3 v1, Vector3 v2)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE5885716);
                KernelStream.Write(v1);
                KernelStream.Write(v2);
                return KernelStream.ReadSingle();
            }
        }
        public static Vector3 operator+(Vector3 me, Vector3 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x223AB538);
                KernelStream.Write(me);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector3>();
            }
        }
        public static Vector3 operator-(Vector3 me, Vector3 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA61928ED);
                KernelStream.Write(me);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector3>();
            }
        }
        public static Vector3 operator*(Vector3 me, float factor)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x25D9C0DD);
                KernelStream.Write(me);
                KernelStream.Write(factor);
                return KernelStream.Read<Vector3>();
            }
        }
        public static Vector3 operator/(Vector3 me, float factor)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD1772C51);
                KernelStream.Write(me);
                KernelStream.Write(factor);
                return KernelStream.Read<Vector3>();
            }
        }
        public static Vector3 operator^(Vector3 me, Vector3 vector)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC6723E1F);
                KernelStream.Write(me);
                KernelStream.Write(vector);
                return KernelStream.Read<Vector3>();
            }
        }
    }
    
    public class Quaternion
    {
        private IntPtr pointer;
    
        internal Quaternion(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public float X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDCA874B6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8B72044D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x10027428);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5C908415);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Z
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9E8D73CB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFFC602BC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Quaternion Identity
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA7621AD0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Quaternion>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEB9E0123);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Quaternion>(value);
                }
            }
        }
        public float W
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0588661A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC8ED9283);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float Angle
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8A415B66);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3FA7795A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public static Quaternion Lerp(Quaternion q1, Quaternion q2, float c)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x399D2141);
                KernelStream.Write(q1);
                KernelStream.Write(q2);
                KernelStream.Write(c);
                return KernelStream.Read<Quaternion>();
            }
        }
    }
    
    public class UnitGroup
    {
        private IntPtr pointer;
    
        internal UnitGroup(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public enum Units
        {
        }
    }
    
    public class Units
    {
        private IntPtr pointer;
    
        internal Units(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Size
        {
            private IntPtr pointer;
        
            internal Size(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public enum Units
            {
                Pixel,
                Point,
                Centimeter,
                Inch,
                Count,
                Default,
            }
        
            public float Values
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xEDB83CFF);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadSingle();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x1D8E95C1);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
        }
        
        public class Temperature
        {
            private IntPtr pointer;
        
            internal Temperature(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public enum Units
            {
                Celsius,
                Fareneight,
                Count,
                Default,
            }
        
            public float Factors
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x9744141E);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadSingle();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x9D1C9188);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
            public float Deltas
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xCB6ADF12);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadSingle();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xDF6CF63C);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
        }
        
        public class FileSize
        {
            private IntPtr pointer;
        
            internal FileSize(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public enum Units
            {
                Bit,
                Byte,
                KiloByte,
                MegaByte,
                GigaByte,
                Count,
                Default,
                B,
                KB,
                MB,
                GB,
            }
        
            public uint Factors
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xC6A38361);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadUInt32();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x91110761);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
        }
    
        public static int Convert<T>(int value, T from, T to)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x23BC9CB5);
                KernelStream.Write(value);
                KernelStream.Write(from);
                KernelStream.Write(to);
                return KernelStream.ReadInt32();
            }
        }
    }
    
    public enum ConsoleColor
    {
        Black,
        DarkBlue,
        DarkGreen,
        DarkCyan,
        DarkRed,
        DarkMagenta,
        DarkYellow,
        Gray,
        DarkGray,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Yellow,
        White,
    }
    
    public class Console
    {
        private IntPtr pointer;
    
        internal Console(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ConsoleStream BaseConsoleStream
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x61F7F382);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ConsoleStream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x97DC9F31);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ConsoleStream>(value);
                }
            }
        }
        public System.IO.TextStream BaseStream
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5D5723BA);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.TextStream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA898A870);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.TextStream>(value);
                }
            }
        }
        public ConsoleColor Color
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7E6E0B92);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ConsoleColor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x298C77F8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ConsoleColor>(value);
                }
            }
        }
        public ConsoleColor BackColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE252242C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ConsoleColor>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1C2436CC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ConsoleColor>(value);
                }
            }
        }
    
        public static void Clear()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB5103AED);
            }
        }
        public static sbyte Read(bool intercept)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1D8075DB);
                KernelStream.Write(intercept);
                return KernelStream.ReadSByte();
            }
        }
        public static System.Devices.Buttons ReadKey()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xDA6F4924);
                return KernelStream.Read<System.Devices.Buttons>();
            }
        }
        public static string ReadLine()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD80B6134);
                return KernelStream.ReadString();
            }
        }
        public static void Write(string format)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x279457D1);
                KernelStream.Write(format);
            }
        }
        public static void WriteLine()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCBA6B1DC);
            }
        }
    }
    
    public class Log
    {
        private IntPtr pointer;
    
        internal Log(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.IO.Stream Trace
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x72DF143E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x956AEAC1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
        public System.IO.Stream Debug
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8FC2AF0F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x339BC887);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
        public System.IO.Stream Info
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1E2E6AF9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC834DE06);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
        public System.IO.Stream Warning
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA0CAE65D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x55727449);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
        public System.IO.Stream Error
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB9B14460);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD44BEDEA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
    
        public static void WriteLine(System.IO.Stream log)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6BDA0252);
                KernelStream.Write(log);
            }
        }
    }
    
    public class Serial
    {
        private IntPtr pointer;
    
        internal Serial(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.IO.TextStream BaseStream
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x218AEF47);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.TextStream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3EFB6C27);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.TextStream>(value);
                }
            }
        }
    
        public static void Write(string _base)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7EF27F0C);
                KernelStream.Write(_base);
            }
        }
        public static void WriteLine()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2A9D0F1E);
            }
        }
    }
    
    public class Color24
    {
        private IntPtr pointer;
    
        internal Color24(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Value
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6B8B523C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x122983D7);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte __Unused
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBBBD083F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB2F5B3A4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Red
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9FB72C7E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF9EAC6FA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Green
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC69D2488);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x60351EBA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Blue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDA6970BB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x97FEA60C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class Color32
    {
        private IntPtr pointer;
    
        internal Color32(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Value
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE719175F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x079F4189);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Blue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9B50E0E5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7E7C1658);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Green
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4A0F61EB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0CDA09E7);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Red
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA25D12D5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x18FFA7FC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Alpha
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB05A9491);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x59CB4079);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class Colors
    {
        private IntPtr pointer;
    
        internal Colors(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class System
        {
            private IntPtr pointer;
        
            internal System(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public Color24 Color
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xE969A15F);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x03FD7507);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 ActiveBackground
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xD03C9320);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x86B464D8);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 InactiveBackground
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x959220F3);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x42213617);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 Border
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x1807DD6E);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x9D0659C3);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 Menu
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x83C737FF);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xF32BC521);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 ActiveTab
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xD0A54D00);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xF26AA29C);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 InactiveTab
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x1F1720B9);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xD86021F9);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 ActiveSubtab
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xC9DDE8AD);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x73D49F66);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public Color24 InactiveSubtab
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xF66EEAB7);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xCDB3B411);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
        }
    
        public Color32 Transparent
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB7DC45DC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB9ABE098);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public Color24 Black
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xABF0740C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF3621114);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DeepGray
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x30F5D7AA);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x25CE2C23);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkGray
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9DA7B1C1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x42943C6D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Gray
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x795E5F9B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB9AFFBEE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightGray
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x41B3E743);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5654494D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 BrightGray
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC91A2209);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4F83444C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 White
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x416EE01C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0744B63A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawRed
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x62BC0576);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0F6B2E4C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawGreen
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4CF6CBE7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC3F628A8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawBlue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD44FF3A0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x40D6307F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawCyan
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x780069E7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC1DBF00A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawMagenta
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF19E5B55);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB2204AE4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 RawYellow
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x22ED3ACC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF379AB76);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Red
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCE3CE3D0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC129C368);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightRed
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFB46FF72);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEF8B4A2B);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkRed
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x391DB25C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2EA22537);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Green
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFDC23B45);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xECA59989);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightGreen
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x75F28C1B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA3959069);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkGreen
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x76987A41);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x98EF70D4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Blue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEB56759B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7C1B9643);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightBlue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD3BBCD43);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x93E024E0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkBlue
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0FAF9BC1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x872051C0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Cyan
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4719EFDC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFD165636);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightCyan
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7FF45704);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x12EDE495);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkCyan
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA3E00186);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x062D91B5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Magenta
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD012C616);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x82D9F34E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightMagenta
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA12F18D3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA57BF736);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkMagenta
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB5A5F94E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x541AFEC1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Yellow
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1A84CCF8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBF3FE899);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightYellow
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x96DF80BC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1F7A3AE8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkYellow
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1D6252A0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAA918F39);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Orange
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3CC1B8F8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1B528867);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightOrange
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB09AF4BC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBB175A16);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkOrange
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3B2726A0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0EFCEFC7);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Purple
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5708AFD4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x16AFFFE3);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightPurple
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDB53E390);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB6EA2D92);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkPurple
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x50EE318C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x03019843);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Brown
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF075B66B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF955EF55);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightBrown
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x78450135);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB665E6B5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkBrown
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7B2FF76F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8D1F0608);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Pink
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC0FA0D4B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x853E8756);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 LightPink
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF817B593);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6AC535F5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 DarkPink
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2403E311);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7E0540D5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Sky
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0E827786);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9C76B3A5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Brick
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x44A7DB35);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1FCC29D6);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Salmon
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAFEBD09F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEF892EBE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Gold
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBDFF966E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x334FDC29);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
        public Color24 Ice
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAEC2E0DB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAB967966);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
    
        public static void Initialize(Color24 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9B4D9FEC);
                KernelStream.Write(color);
            }
        }
    }
    
    public class Pair<TKey, TValue>
    {
        private IntPtr pointer;
    
        internal Pair(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Dictionary<TKey, TValue>
    {
        private IntPtr pointer;
    
        internal Dictionary(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Add(TKey key, TValue value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x12A97F67);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(key);
                KernelStream.Write(value);
            }
        }
        public void Remove(TKey key)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x8F5475AE);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(key);
            }
        }
        public TValue Get(TKey key)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x131561FD);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(key);
                return KernelStream.Read<TValue>();
            }
        }
    }
    
    public class Matrix4
    {
        private IntPtr pointer;
    
        internal Matrix4(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Matrix4 Identity
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0DDE0590);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Matrix4>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4B55D33C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Matrix4>(value);
                }
            }
        }
        public float components
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4DCBB0A4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD44670EC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c11
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB09A9240);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x577B89F4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c12
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3E1595A3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF42D0F5D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c13
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF2BF953D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x23CF8F05);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c14
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF87A9C24);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x69F1044E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c21
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8917AE85);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF8D2C43E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c22
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0798A966);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5B844297);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c23
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCB32A9F8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8C66C2CF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c24
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC1F7A0E1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC6584984);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c31
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9E6CBAC6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9DB5FF78);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c32
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x10E3BD25);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3EE379D1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c33
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDC49BDBB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE901F989);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c34
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD68CB4A2);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA33F72C2);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c41
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFA0DD70F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7CF159EB);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c42
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7482D0EC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xDFA7DF42);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c43
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB828D072);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x08455F1A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public float c44
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB2EDD96B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x427BD451);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public Matrix4 Transpose()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4FECFAE0);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Matrix4>();
            }
        }
        public float Determinant()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB520BAE8);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSingle();
            }
        }
        public static Matrix4 CreateTransformation(Vector3 translation, Matrix3 rotation, Vector3 scale)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7E824078);
                KernelStream.Write(translation);
                KernelStream.Write(rotation);
                KernelStream.Write(scale);
                return KernelStream.Read<Matrix4>();
            }
        }
        public static Matrix4 CreateView(Vector3 position, Vector3 target, Vector3 up)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA456E95C);
                KernelStream.Write(position);
                KernelStream.Write(target);
                KernelStream.Write(up);
                return KernelStream.Read<Matrix4>();
            }
        }
        public static Matrix4 CreateProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC0638A55);
                KernelStream.Write(fov);
                KernelStream.Write(aspectRatio);
                KernelStream.Write(nearPlane);
                KernelStream.Write(farPlane);
                return KernelStream.Read<Matrix4>();
            }
        }
        public static Matrix4 operator*(Matrix4 me, Matrix4 matrix)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5D1158A7);
                KernelStream.Write(me);
                KernelStream.Write(matrix);
                return KernelStream.Read<Matrix4>();
            }
        }
    }
    
    public class Array<T, Size>
    {
        private IntPtr pointer;
    
        internal Array(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Reference<Iterator<T>> GetIterator()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4D56B01A);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Reference<Iterator<T>>>();
            }
        }
    }
    
    public class ObservableList<T>
    {
        private IntPtr pointer;
    
        internal ObservableList(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Change
        {
            private IntPtr pointer;
        
            internal Change(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public uint NewItemsIndex
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x72648D03);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadUInt32();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xEDAD6DC9);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
            public List<T> NewItems
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xBDC1A400);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<List<T>>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x05524E27);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<List<T>>(value);
                    }
                }
            }
            public uint OldItemsIndex
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x0D65AAE2);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadUInt32();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x6F50278E);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
            public List<T> OldItems
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xA3A14ABC);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<List<T>>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xB4104F70);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<List<T>>(value);
                    }
                }
            }
        }
    
        public void Add(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE9AE75CE);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public void Remove(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE7216353);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public void Clear()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x8174D8FA);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    
        public event Action<ObservableList.Change> Changed
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class Queue<T>
    {
        private IntPtr pointer;
    
        internal Queue(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Count
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF106A67E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
        }
    
        public void Enqueue(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9B2E3F86);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public T Dequeue()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x43546E82);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public void Clear()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFB3BF1B9);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class Stack<T>
    {
        private IntPtr pointer;
    
        internal Stack(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Push(T item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9150E62B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
        public T Pop()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x113BA9FF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
        public void Clear()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9C4FE9D5);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class OrderedCollection<T>
    {
        private IntPtr pointer;
    
        internal OrderedCollection(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Reference<Iterator<T>> GetIterator()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1E4E0191);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Reference<Iterator<T>>>();
            }
        }
    }
    
    public class TreeNode<T>
    {
        private IntPtr pointer;
    
        internal TreeNode(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T Element
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE63A6DFC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<T>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD15848AC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<T>(value);
                }
            }
        }
    }
    
    public class Tree<T>
    {
        private IntPtr pointer;
    
        internal Tree(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Timer
    {
        private IntPtr pointer;
    
        internal Timer(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ulong Ticks
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6BAF4DC6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt64();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0360B813);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public static ulong Time()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x82FB4803);
                return KernelStream.ReadUInt64();
            }
        }
        public static void Sleep(ulong milliseconds)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9A0A324E);
                KernelStream.Write(milliseconds);
            }
        }
    }
    
    public class RandomStream
    {
        private IntPtr pointer;
    
        internal RandomStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x72806756);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9CFD0F3B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
    }
    
    public class Random
    {
        private IntPtr pointer;
    
        internal Random(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public T Generate<T>()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5505F05D);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<T>();
            }
        }
    }
    
    public class TimeSpan
    {
        private IntPtr pointer;
    
        internal TimeSpan(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public bool sign
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6919CBF3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8FDA4D87);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint days
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7EBFE756);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4A454247);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint milliseconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x83996D21);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x191D7328);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort Days
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD713CA42);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
        }
        public byte Hours
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF1A135E7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
        }
        public byte Minutes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x57EB3742);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
        }
        public byte Seconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x35301395);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
        }
        public ushort Milliseconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x136D2465);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
        }
    
        public override string ToString()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2FDEA9B6);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public static TimeSpan operator-(TimeSpan me, TimeSpan other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6880205E);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<TimeSpan>();
            }
        }
    }
    
    public class DateTime
    {
        private IntPtr pointer;
    
        internal DateTime(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ushort Year
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC38D31E5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x65FED392);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Month Month
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBCA30310);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Month>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x836B7B19);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Month>(value);
                }
            }
        }
        public byte Day
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBCA18716);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3053DFDB);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Hours
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCCB39969);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x43A00082);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Minutes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2D8B5056);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x89C6D466);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Seconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4F507481);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7BBC01B4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort Milliseconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBDFB80C1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBF37E0DF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Day DayOfWeek
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x21B92CC5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Day>();
                }
            }
        }
        public DateTime Date
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF7EB9438);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<DateTime>();
                }
            }
        }
        public DateTime Time
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE95CC577);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<DateTime>();
                }
            }
        }
        public string DateFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7B9DA05C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8FEF3BBA);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public string TimeFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2DCF2E4E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF6F238C9);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public string DateTimeFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x30697284);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC70C98EB);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public string LongDateFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x31B2F57A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x84E0E500);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public string LongTimeFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x67E07B68);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFDFDE673);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public string LongDateTimeFormat
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5B52FEDE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x229EEB68);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public DateTime Now
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1FD3F5DD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<DateTime>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6E2BFB0C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<DateTime>(value);
                }
            }
        }
        public ulong value
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2EBB4EE8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt64();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0BD8C5C3);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint date
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3F198426);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x04FD1957);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint time
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x825BF433);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3B3AEB02);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort year
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC3B9929C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEC244788);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Month month
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x89CCFDB3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Month>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2EBCF65D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Month>(value);
                }
            }
        }
        public byte day
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9AE4AF64);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEF95EE5F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte hours
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9CEAA44B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x788E5E8F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte minutes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0EEE1CA9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9AB64B32);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte seconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCC7C547D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAC7E0439);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort milliseconds
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9849DDAB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x54FEF83F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public override string ToString()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x12CC0538);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public string ToLongDate()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6BF4303F);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public static TimeSpan operator-(DateTime me, DateTime other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB2089A54);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<TimeSpan>();
            }
        }
        public static DateTime operator+(DateTime me, TimeSpan other)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF2589852);
                KernelStream.Write(me);
                KernelStream.Write(other);
                return KernelStream.Read<DateTime>();
            }
        }
    }
}

namespace API.System
{
}

namespace API.Types
{
    public class If<condition, Type1, Type2>
    {
        private IntPtr pointer;
    
        internal If(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Equals<Type1, Type2>
    {
        private IntPtr pointer;
    
        internal Equals(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
}

namespace API.Values
{
    public class If<condition, value1, value2>
    {
        private IntPtr pointer;
    
        internal If(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Min<value1, value2>
    {
        private IntPtr pointer;
    
        internal Min(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Max<value1, value2>
    {
        private IntPtr pointer;
    
        internal Max(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
}

namespace API.System.Runtime
{
    public class Type
    {
        private IntPtr pointer;
    
        internal Type(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string RawName
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1A90C9BD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC1F09F78);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public string FullName
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x140742E1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public List<System.Runtime.Type> BaseTypes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x78AA8683);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.Runtime.Type>>();
                }
            }
        }
    
        public static System.Runtime.Type Get<T>()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2C13EA5D);
                return KernelStream.Read<System.Runtime.Type>();
            }
        }
    }
    
    public class Mutex
    {
        private IntPtr pointer;
    
        internal Mutex(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public bool Lock(uint timeout)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x0F782A9A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(timeout);
                return KernelStream.ReadBoolean();
            }
        }
        public void Unlock()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCF12B8D7);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class MutexLocker
    {
        private IntPtr pointer;
    
        internal MutexLocker(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Runtime.Mutex mutex
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7C3919CD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Runtime.Mutex>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEBFA2BF5);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Runtime.Mutex>(value);
                }
            }
        }
    }
    
    public class Thread
    {
        private IntPtr pointer;
    
        internal Thread(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Signal
    {
        private IntPtr pointer;
    
        internal Signal(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Send()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7F2D75DC);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public bool Wait(uint timeout)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7BA680D2);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(timeout);
                return KernelStream.ReadBoolean();
            }
        }
    }
    
    public enum AccessibilityModifier
    {
        Public,
        Protected,
        Private,
        Static,
    }
    
    public class Symbol
    {
        private IntPtr pointer;
    
        internal Symbol(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB9AD2618);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
    
        public override string ToString()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE06CC9FF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
    }
    
    public class Constructor
    {
        private IntPtr pointer;
    
        internal Constructor(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static System.Runtime.Constructor Load(IntPtr address, string rawName)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9AC12F79);
                KernelStream.Write(address);
                KernelStream.Write(rawName);
                return KernelStream.Read<System.Runtime.Constructor>();
            }
        }
    }
    
    public enum VirtualizationModifier
    {
        None,
        Abstract,
        Virtual,
    }
    
    public class Method
    {
        private IntPtr pointer;
    
        internal Method(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static System.Runtime.Method AddFunction<C, T>(string name, System.Runtime.Type parent, IntPtr param)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2352ABB9);
                KernelStream.Write(name);
                KernelStream.Write(parent);
                KernelStream.Write(param);
                return KernelStream.Read<System.Runtime.Method>();
            }
        }
        public static System.Runtime.Method Load(IntPtr address, string rawName)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF2DC5D51);
                KernelStream.Write(address);
                KernelStream.Write(rawName);
                return KernelStream.Read<System.Runtime.Method>();
            }
        }
    }
    
    public class Reflection
    {
        private IntPtr pointer;
    
        internal Reflection(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Namespace
    {
        private IntPtr pointer;
    
        internal Namespace(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Property
    {
        private IntPtr pointer;
    
        internal Property(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static System.Runtime.Property Add<T>(string name, System.Runtime.Type parent, System.Runtime.Method getter)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE71988F8);
                KernelStream.Write(name);
                KernelStream.Write(parent);
                KernelStream.Write(getter);
                return KernelStream.Read<System.Runtime.Property>();
            }
        }
        public static System.Runtime.Property AddProperty<T>(string name, System.Runtime.Type parent, System.Runtime.Method getter, System.Runtime.Method setter)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x96FEE601);
                KernelStream.Write(name);
                KernelStream.Write(parent);
                KernelStream.Write(getter);
                KernelStream.Write(setter);
                return KernelStream.Read<System.Runtime.Property>();
            }
        }
    }
    
    public class Serializer
    {
        private IntPtr pointer;
    
        internal Serializer(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Process
    {
        private IntPtr pointer;
    
        internal Process(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public List<System.Runtime.Thread> Threads
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA4C2E3A9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.Runtime.Thread>>();
                }
            }
        }
        public System.Runtime.Process Current
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x75B901C3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Runtime.Process>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD0F25D17);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Runtime.Process>(value);
                }
            }
        }
    
        public void Start()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x663657F7);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Kill()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCD28EA79);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
}

namespace API.System.Data
{
    public class Record
    {
        private IntPtr pointer;
    
        internal Record(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string GetString(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x29024D22);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadString();
            }
        }
        public bool GetBool(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE9B4AD51);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadBoolean();
            }
        }
        public byte GetU8(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x464CC9D6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadByte();
            }
        }
        public ushort GetU16(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x850AC7C7);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadUInt16();
            }
        }
        public uint GetU32(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x890494F8);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadUInt32();
            }
        }
        public ulong GetU64(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x0D655842);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadUInt64();
            }
        }
        public sbyte GetS8(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x259CFCEC);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadSByte();
            }
        }
        public short GetS16(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4365CE40);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadInt16();
            }
        }
        public int GetS32(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4F6B9D7F);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadInt32();
            }
        }
        public long GetS64(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCB0A51C5);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadInt64();
            }
        }
        public float GetFloat(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x70C03AEB);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadSingle();
            }
        }
        public double GetDouble(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x92DD27C8);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.ReadDouble();
            }
        }
        public T Get<T>(uint index)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x478B8C58);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(index);
                return KernelStream.Read<T>();
            }
        }
    }
    
    public class Table
    {
        private IntPtr pointer;
    
        internal Table(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Database
    {
        private IntPtr pointer;
    
        internal Database(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Data.Database Default
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x37E6F4B6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Data.Database>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9589D1B9);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Data.Database>(value);
                }
            }
        }
    
        public uint Execute(string query)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x712DE8B5);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(query);
                return KernelStream.ReadUInt32();
            }
        }
        public Reference<System.Data.Table> QueryTable(string query)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x435A77B7);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(query);
                return KernelStream.Read<Reference<System.Data.Table>>();
            }
        }
        public Reference<System.Data.Record> QueryRecord<Args>(string query, Args parameters)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x23B4A57F);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(query);
                KernelStream.Write(parameters);
                return KernelStream.Read<Reference<System.Data.Record>>();
            }
        }
        public T QueryValue<T, Args>(string query, Args parameters)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x749E47C8);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(query);
                KernelStream.Write(parameters);
                return KernelStream.Read<T>();
            }
        }
    }
}

namespace API.System.IO
{
    public enum SeekOrigin
    {
        Begin,
        Current,
        End,
    }
    
    public class Stream
    {
        private IntPtr pointer;
    
        internal Stream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ulong Position
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x482CB04A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt64();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3EE223AD);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ulong Length
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5E29FC88);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt64();
                }
            }
        }
        public bool EndOfStream
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6213B8D8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x628E0282);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public System.IO.Stream Null
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x927E578F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Stream>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9CFCC80B);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Stream>(value);
                }
            }
        }
    
        public bool IsEndOfStream()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE9CF6894);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadBoolean();
            }
        }
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7F218A1C);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x0AF90658);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
        public void Seek(ulong offset, API.System.IO.SeekOrigin origin)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFFCA19D0);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(offset);
                KernelStream.Write(origin);
            }
        }
        public static ConsoleStream GetConsoleStream()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6F738C09);
                return KernelStream.Read<ConsoleStream>();
            }
        }
        public static System.IO.Stream GetSerialStream()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFAAEDE90);
                return KernelStream.Read<System.IO.Stream>();
            }
        }
    }
    
    public class TextStream
    {
        private IntPtr pointer;
    
        internal TextStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ulong GetPosition()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1E9E7879);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public ulong GetLength()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x8948CFC9);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7F405E65);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2320AE14);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
        public void Seek(ulong offset, API.System.IO.SeekOrigin origin)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4198A462);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(offset);
                KernelStream.Write(origin);
            }
        }
        public string ReadLine()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE8112A3E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public string ReadAll()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x588E9C7B);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public void WriteLine()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2B434289);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class BufferStream
    {
        private IntPtr pointer;
    
        internal BufferStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class Directory
    {
        private IntPtr pointer;
    
        internal Directory(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAE028CA3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public System.IO.Directory Parent
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x41B429AF);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Directory>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9324802A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Directory>(value);
                }
            }
        }
        public List<System.IO.Directory> Directories
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2C06C664);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.IO.Directory>>();
                }
            }
        }
        public List<System.IO.File> Files
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x44EF9295);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.IO.File>>();
                }
            }
        }
        public string FullPath
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1CA0760B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public System.IO.Directory Root
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4B4B0526);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Directory>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x05BE6A8A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Directory>(value);
                }
            }
        }
        public System.IO.Directory Current
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5A842ED1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Directory>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5B014D85);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Directory>(value);
                }
            }
        }
    
        public System.IO.Directory GetParent()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7EB8834F);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.IO.Directory>();
            }
        }
        public void AddDirectory(System.IO.Directory directory)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE55959C7);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(directory);
            }
        }
        public void AddFile(System.IO.File file)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6C975A76);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(file);
            }
        }
        public System.IO.Directory GetDirectory(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x221E066B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.Directory>();
            }
        }
        public System.IO.File GetFile(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x88D3AA3A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.File>();
            }
        }
        public static System.IO.Directory Open(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC43E19F6);
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.Directory>();
            }
        }
        public static System.IO.Directory GetRootDirectory()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x808C9EB8);
                return KernelStream.Read<System.IO.Directory>();
            }
        }
    }
    
    public enum FileAttributes
    {
        None,
        Hidden,
        System,
    }
    
    public class File
    {
        private IntPtr pointer;
    
        internal File(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string Path
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x977FF228);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8B6A1A85);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public string Extension
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC541E069);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
        public ulong Size
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC99C2F27);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt64();
                }
            }
        }
    
        public System.IO.Stream GetStream()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x54F72F51);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.IO.Stream>();
            }
        }
        public static System.IO.File Open(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9C8CE777);
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.File>();
            }
        }
        public static System.IO.Stream OpenStream(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFCC9E804);
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.Stream>();
            }
        }
    }
    
    public class DirectoryLink
    {
        private IntPtr pointer;
    
        internal DirectoryLink(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.IO.Directory Target
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x48BD21CD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.IO.Directory>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1C34D5EB);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.IO.Directory>(value);
                }
            }
        }
    
        public System.IO.Directory GetTarget()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x33E063E2);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.IO.Directory>();
            }
        }
        public List<System.IO.Directory> GetDirectories()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x13AFB64D);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<List<System.IO.Directory>>();
            }
        }
        public List<System.IO.File> GetFiles()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFC7D648C);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<List<System.IO.File>>();
            }
        }
        public void AddDirectory(System.IO.Directory directory)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1488D502);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(directory);
            }
        }
        public void AddFile(System.IO.File file)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB3E8C7F4);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(file);
            }
        }
        public System.IO.Directory GetDirectory(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6276A412);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.Directory>();
            }
        }
        public System.IO.File GetFile(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x94A55E9C);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(path);
                return KernelStream.Read<System.IO.File>();
            }
        }
    }
    
    public class FileStream
    {
        private IntPtr pointer;
    
        internal FileStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class AsyncStream
    {
        private IntPtr pointer;
    
        internal AsyncStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class DataStream
    {
        private IntPtr pointer;
    
        internal DataStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ulong GetPosition()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCD149E7C);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public void SetPosition(ulong value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3D010BB8);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public ulong GetLength()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x28DCAC72);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7CC2A209);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6727019B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
        public byte ReadByte()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC8AFAE96);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadByte();
            }
        }
        public byte ReadU8()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x48CE4C3D);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadByte();
            }
        }
        public ushort ReadU16()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xBA3B050D);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt16();
            }
        }
        public uint ReadU32()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x173B655A);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt32();
            }
        }
        public ulong ReadU64()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2468E9DA);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadUInt64();
            }
        }
        public sbyte ReadS8()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6DA513E1);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSByte();
            }
        }
        public short ReadS16()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x357BF0AD);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadInt16();
            }
        }
        public int ReadS32()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x987B90FA);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadInt32();
            }
        }
        public long ReadS64()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xAB281C7A);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadInt64();
            }
        }
        public float ReadFloat()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCAAF8E54);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSingle();
            }
        }
        public double ReadDouble()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9EA85BED);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadDouble();
            }
        }
        public sbyte ReadChar()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x20DDD159);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadSByte();
            }
        }
        public string ReadString(uint length)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6CD2781E);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(length);
                return KernelStream.ReadString();
            }
        }
    }
    
    public class TeeStream
    {
        private IntPtr pointer;
    
        internal TeeStream(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Read(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x16023214);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr buffer, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x044BADD2);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(count);
            }
        }
    }
}

namespace API.System.Devices
{
    public class Device
    {
        private IntPtr pointer;
    
        internal Device(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public bool Loaded
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7A6E21F0);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
        }
    
        public string GetVendor()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB525DE2E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public string GetName()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x31CB1341);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
        public void Load()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB784A32C);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Unload()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB84B001E);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class PointerEvent
    {
        private IntPtr pointer;
    
        internal PointerEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public byte Index
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4E946C0B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6CFC0D06);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class PointerPositionEvent
    {
        private IntPtr pointer;
    
        internal PointerPositionEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ushort X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4D5FB26D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD0151482);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x81F5B2F3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x57B3DFC1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class PointerMoveEvent
    {
        private IntPtr pointer;
    
        internal PointerMoveEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public sbyte X
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6CDFD6AC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE5F50C3C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public sbyte Y
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA075D632);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4B9D9DAD);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class PointerDevice
    {
        private IntPtr pointer;
    
        internal PointerDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public event Action<System.Devices.PointerMoveEvent> PointerMove
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.PointerEvent> PointerDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.PointerEvent> PointerUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public enum Buttons
    {
        Unknown,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Digit0,
        Digit1,
        Digit2,
        Digit3,
        Digit4,
        Digit5,
        Digit6,
        Digit7,
        Digit8,
        Digit9,
        CapsLock,
        NumLock,
        Shift,
        LeftShift,
        RightShift,
        Control,
        LeftControl,
        RightControl,
        Alt,
        LeftAlt,
        RightAlt,
        Escape,
        Space,
        Enter,
        Backspace,
        Start,
        Select,
        Menu,
        Tab,
        Up,
        Right,
        Down,
        Left,
        Insert,
        Delete,
        PageUp,
        PageDown,
        Origin,
        End,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Oem1,
        Oem2,
        Oem3,
        Oem4,
        Oem5,
        Oem6,
        Oem7,
        Oem8,
        Oem9,
        Oem10,
        Oem11,
        Oem12,
        Count,
    }
    
    public class RawButtonEvent
    {
        private IntPtr pointer;
    
        internal RawButtonEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public API.System.Devices.Buttons Button
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE695B5B5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Devices.Buttons>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x612D8629);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Devices.Buttons>(value);
                }
            }
        }
    }
    
    public class ButtonEvent
    {
        private IntPtr pointer;
    
        internal ButtonEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public API.System.Devices.Buttons Button
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB74A955D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Devices.Buttons>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7002FE16);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Devices.Buttons>(value);
                }
            }
        }
        public sbyte Character
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF1823A3C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC7EFABAE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class ButtonsMapping
    {
        private IntPtr pointer;
    
        internal ButtonsMapping(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class CharactersMapping
    {
        private IntPtr pointer;
    
        internal CharactersMapping(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class ButtonsState
    {
        private IntPtr pointer;
    
        internal ButtonsState(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class ButtonsDevice
    {
        private IntPtr pointer;
    
        internal ButtonsDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public event Action<System.Devices.RawButtonEvent> ButtonDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.RawButtonEvent> ButtonUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public enum Jauges
    {
        LeftStickX,
        LeftStickY,
        RightStickX,
        RightStickY,
        LeftTrigger,
        RightTrigger,
    }
    
    public class JaugeEvent
    {
        private IntPtr pointer;
    
        internal JaugeEvent(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public API.System.Devices.Jauges Jauge
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD3EF8DCD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Devices.Jauges>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB236552B);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Devices.Jauges>(value);
                }
            }
        }
        public float Value
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8370ED65);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadSingle();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x03A82B9F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class InputManager
    {
        private IntPtr pointer;
    
        internal InputManager(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Point2 PointerPosition
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1B2E6E5A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBF44C050);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point2>(value);
                }
            }
        }
    
        public static void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD49C4D53);
            }
        }
        public static void AddDevice(System.Devices.PointerDevice pointer, bool param)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9378CDA2);
                KernelStream.Write(pointer);
                KernelStream.Write(param);
            }
        }
        public static void SetDefaultPointer(System.Devices.PointerDevice pointer)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x90A7892A);
                KernelStream.Write(pointer);
            }
        }
    
        public event Action<System.Devices.PointerPositionEvent> PointerMove
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.PointerEvent> PointerDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.PointerEvent> PointerUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.ButtonEvent> ButtonDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.ButtonEvent> ButtonUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Devices.JaugeEvent> JaugeChange
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class DeviceEnumerator
    {
        private IntPtr pointer;
    
        internal DeviceEnumerator(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class CommunicationDevice
    {
        private IntPtr pointer;
    
        internal CommunicationDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public List<IO.Stream> Streams
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0DF0B73B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<IO.Stream>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x93E66F1A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<List<IO.Stream>>(value);
                }
            }
        }
    
        public List<IO.Stream> GetStreams()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x40F6C037);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<List<IO.Stream>>();
            }
        }
    }
    
    public class NetworkDevice
    {
        private IntPtr pointer;
    
        internal NetworkDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class FileSystem
    {
        private IntPtr pointer;
    
        internal FileSystem(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public IO.Directory Root
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBA6F4B2D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<IO.Directory>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC61AB3EC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<IO.Directory>(value);
                }
            }
        }
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0DD81933);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
    
        public IO.Directory GetRoot()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7111647E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<IO.Directory>();
            }
        }
        public static void Register<T>(API.System.Devices.FileSystemType type)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFDDF40AB);
                KernelStream.Write(type);
            }
        }
        public static System.Devices.FileSystem Create(API.System.Devices.FileSystemType type, System.Devices.StorageDevice device, ulong position)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2717BAED);
                KernelStream.Write(type);
                KernelStream.Write(device);
                KernelStream.Write(position);
                return KernelStream.Read<System.Devices.FileSystem>();
            }
        }
        public uint Read(sbyte buffer, uint offset, ulong position, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCB2B147B);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(offset);
                KernelStream.Write(position);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(sbyte source, uint offset, ulong position, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x88D4A9C1);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(source);
                KernelStream.Write(offset);
                KernelStream.Write(position);
                KernelStream.Write(count);
            }
        }
    }
    
    public class DisplayMode
    {
        private IntPtr pointer;
    
        internal DisplayMode(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ushort Id
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0337766D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA3F234D1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort Width
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA788947D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9A77380D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ushort Height
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8B61DFBD);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB011C377);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Bpp
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8A84DFC9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5AA154F1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public class DisplayOverlay
    {
        private IntPtr pointer;
    
        internal DisplayOverlay(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public bool Visible
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x29215F69);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x78A64F59);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Point2 Position
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC52DC82E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point2>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC4971792);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Point2>(value);
                }
            }
        }
        public Graphics.Bitmap Bitmap
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x21DA2CD4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Bitmap>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD694E6AC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Bitmap>(value);
                }
            }
        }
    
        public Graphics.Bitmap GetBitmap()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD2D1DCFB);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Bitmap>();
            }
        }
        public void SetBitmap(Graphics.Bitmap surface)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5BF13CF6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(surface);
            }
        }
    }
    
    public class DisplayDevice
    {
        private IntPtr pointer;
    
        internal DisplayDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Graphics.Surface Surface
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3600E85C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Surface>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x19FFB96F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Surface>(value);
                }
            }
        }
        public Runtime.Signal VSync
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x29A5EBD7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Runtime.Signal>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x16CDF372);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Runtime.Signal>(value);
                }
            }
        }
        public System.Devices.DisplayOverlay Overlay
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x513E1DBB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Devices.DisplayOverlay>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC70B1B1E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Devices.DisplayOverlay>(value);
                }
            }
        }
        public System.Devices.DisplayMode DisplayMode
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9CCB426F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Devices.DisplayMode>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF81902BF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Devices.DisplayMode>(value);
                }
            }
        }
    
        public Graphics.Surface GetSurface()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9435E02F);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Surface>();
            }
        }
        public Runtime.Signal GetVSync()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3E82671F);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Runtime.Signal>();
            }
        }
        public System.Devices.DisplayOverlay GetOverlay()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2DD5E24A);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.Devices.DisplayOverlay>();
            }
        }
        public System.Devices.DisplayMode FindDisplayMode(ushort width, ushort height, byte bpp, bool exact)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA9EEC7B9);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(width);
                KernelStream.Write(height);
                KernelStream.Write(bpp);
                KernelStream.Write(exact);
                return KernelStream.Read<System.Devices.DisplayMode>();
            }
        }
        public System.Devices.DisplayMode GetDisplayMode()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x77D57166);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.Devices.DisplayMode>();
            }
        }
        public void SetDisplayMode(System.Devices.DisplayMode displayMode)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE154E842);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(displayMode);
            }
        }
        public void Update()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1589E42A);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public enum InputType
    {
        Button,
        Pointer,
        Stick,
    }
    
    public enum InputDeviceType
    {
        Keyboard,
        Mouse,
        Touch,
        Pad,
    }
    
    public class InputDevice
    {
        private IntPtr pointer;
    
        internal InputDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class StorageDevice
    {
        private IntPtr pointer;
    
        internal StorageDevice(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public List<System.Devices.FileSystem> FileSystems
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB29E2BA6);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.Devices.FileSystem>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD42D2EBE);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<List<System.Devices.FileSystem>>(value);
                }
            }
        }
    
        public List<System.Devices.FileSystem> GetFileSystems()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5F51158E);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<List<System.Devices.FileSystem>>();
            }
        }
        public uint Read(IntPtr buffer, ulong position, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xE0679782);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(buffer);
                KernelStream.Write(position);
                KernelStream.Write(count);
                return KernelStream.ReadUInt32();
            }
        }
        public void Write(IntPtr source, ulong position, uint count)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x057C7861);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(source);
                KernelStream.Write(position);
                KernelStream.Write(count);
            }
        }
    }
    
    public class FileSystemConstructorBase
    {
        private IntPtr pointer;
    
        internal FileSystemConstructorBase(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class FileSystemConstructor<T>
    {
        private IntPtr pointer;
    
        internal FileSystemConstructor(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public enum FileSystemType
    {
        None,
        Fat16,
        ExFat,
        Fat32,
    }
}

namespace API.System.Graphics
{
    public class Point
    {
        private IntPtr pointer;
    
        internal Point(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Units.Size.Units Unit
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB81916BC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Units.Size.Units>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x14F0C40B);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Units.Size.Units>(value);
                }
            }
        }
    }
    
    public class Rectangle
    {
        private IntPtr pointer;
    
        internal Rectangle(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Graphics.Point Position
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD9950A5E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Point>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x94D1FD11);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Point>(value);
                }
            }
        }
        public System.Graphics.Point Size
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD67CDB87);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Point>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFEDF0AC0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Point>(value);
                }
            }
        }
    
        public System.Graphics.Rectangle Expand(int size)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x03C196DF);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(size);
                return KernelStream.Read<System.Graphics.Rectangle>();
            }
        }
    }
    
    public class Outline
    {
        private IntPtr pointer;
    
        internal Outline(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Top
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x159B1344);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEA93D016);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint Right
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x772842FC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD402BAA7);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint Bottom
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9CA3B365);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x77670F5F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public uint Left
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x996B830C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAD552B82);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public enum Alignment
    {
        Top,
        Middle,
        Baseline,
        Bottom,
        Left,
        Center,
        Right,
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BaselineLeft,
        BaselineCenter,
        BaselineRight,
        BottomLeft,
        BottomCenter,
        BottomRight,
    }
    
    public enum Orientation
    {
        LeftToRight,
        RightToLeft,
        TopToBottom,
        BottomToTop,
        Horizontal,
        Vertical,
    }
    
    public enum Direction
    {
        Left,
        Up,
        Right,
        Down,
    }
    
    public enum PixelType
    {
        Gray,
        Argb,
        Default,
    }
    
    public class Bitmap
    {
        private IntPtr pointer;
    
        internal Bitmap(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public IntPtr Data
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4ED2AD47);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadIntPtr();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xFACCBDA4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Point2 Size
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE645B6D7);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Point2>();
                }
            }
        }
        public System.Graphics.Bitmap Slot
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x262F145C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Bitmap>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x08D8CD86);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Bitmap>(value);
                }
            }
        }
    
        public IntPtr GetData()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2F3010DA);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadIntPtr();
            }
        }
        public static System.Graphics.Bitmap Load(string path)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA09107B2);
                KernelStream.Write(path);
                return KernelStream.Read<System.Graphics.Bitmap>();
            }
        }
        public override string ToString()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD372CABF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadString();
            }
        }
    }
    
    public class Bitmaps
    {
        private IntPtr pointer;
    
        internal Bitmaps(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Cursors
        {
            private IntPtr pointer;
        
            internal Cursors(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public Dynamic<System.Graphics.Bitmap> Normal
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xB8289BCD);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Dynamic<System.Graphics.Bitmap>>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xF96F1498);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Dynamic<System.Graphics.Bitmap>>(value);
                    }
                }
            }
        }
        
        public class Icons
        {
            private IntPtr pointer;
        
            internal Icons(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public Dynamic<System.Graphics.Bitmap> Close
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x63CEB4FE);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Dynamic<System.Graphics.Bitmap>>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x9C17A268);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Dynamic<System.Graphics.Bitmap>>(value);
                    }
                }
            }
        }
    }
    
    public enum FontType
    {
        None,
        Serif,
        Monospace,
    }
    
    public enum FontAttribute
    {
        Thin,
        Light,
        Regular,
        Medium,
        SemiBold,
        Bold,
        ExtraBold,
        UltraBold,
        Italic,
    }
    
    public class FontFamily
    {
        private IntPtr pointer;
    
        internal FontFamily(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Graphics.Font GetFont(byte height, API.System.Graphics.FontAttribute attributes)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF70B9008);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(height);
                KernelStream.Write(attributes);
                return KernelStream.Read<System.Graphics.Font>();
            }
        }
        public static System.Graphics.FontFamily Load<T>(IO.Stream stream)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xAC29B238);
                KernelStream.Write(stream);
                return KernelStream.Read<System.Graphics.FontFamily>();
            }
        }
        public static void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x39A7CC9E);
            }
        }
        public static void Register(System.Graphics.FontFamily family)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x81CB3C21);
                KernelStream.Write(family);
            }
        }
        public static System.Graphics.FontFamily GetFamily(string name)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6DD0FDFD);
                KernelStream.Write(name);
                return KernelStream.Read<System.Graphics.FontFamily>();
            }
        }
        public static System.Graphics.FontFamily GetDefaultFamily(API.System.Graphics.FontType type)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC6F6DA0C);
                KernelStream.Write(type);
                return KernelStream.Read<System.Graphics.FontFamily>();
            }
        }
    }
    
    public class Font
    {
        private IntPtr pointer;
    
        internal Font(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Graphics.FontFamily Family
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4FE305CE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.FontFamily>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3F7AF1F0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.FontFamily>(value);
                }
            }
        }
        public byte Size
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEF26F3E4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x35C93846);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public API.System.Graphics.FontAttribute Attributes
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0A294F3F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Graphics.FontAttribute>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6E42FF3C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Graphics.FontAttribute>(value);
                }
            }
        }
        public ushort Positions
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x66765F5A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA37EE6A4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public byte Baseline
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA5586379);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadByte();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4DEFC303);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public System.Graphics.Bitmap Cache
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBFB463C1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Bitmap>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD9089CC1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Bitmap>(value);
                }
            }
        }
        public System.Graphics.Font Default
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9FFB59F4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB9AC47F0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Font>(value);
                }
            }
        }
        public System.Graphics.Font Slot
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5F490E2B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x24CB22DD);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Graphics.Font>(value);
                }
            }
        }
    
        public Point2 Measure(string text)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x44BC1B56);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(text);
                return KernelStream.Read<Point2>();
            }
        }
    }
    
    public class Surface
    {
        private IntPtr pointer;
    
        internal Surface(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Clear(Color32 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1CE9E759);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(color);
            }
        }
        public void Resize(Point2 size)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xEF9EA53C);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(size);
            }
        }
        public void DrawPoint(ushort x, ushort y, Color32 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1E42E36A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(x);
                KernelStream.Write(y);
                KernelStream.Write(color);
            }
        }
        public void DrawLine(ushort x1, ushort y1, ushort x2, ushort y2, Color32 color, bool antialiased)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3AB7F3E1);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(x1);
                KernelStream.Write(y1);
                KernelStream.Write(x2);
                KernelStream.Write(y2);
                KernelStream.Write(color);
                KernelStream.Write(antialiased);
            }
        }
        public void DrawRectangle(Point2 position, Point2 size, Color32 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1BEA917A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(position);
                KernelStream.Write(size);
                KernelStream.Write(color);
            }
        }
        public void FillRectangle(Point2 position, Point2 size, Color32 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xAC8C870A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(position);
                KernelStream.Write(size);
                KernelStream.Write(color);
            }
        }
        public void DrawBitmap(System.Graphics.Bitmap bitmap)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xEA9C9168);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(bitmap);
            }
        }
        public void DrawText(string text, System.Graphics.Font font, Point2 position, Color32 color, API.System.Graphics.Alignment alignment)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC00E1952);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(text);
                KernelStream.Write(font);
                KernelStream.Write(position);
                KernelStream.Write(color);
                KernelStream.Write(alignment);
            }
        }
        public void Darken(ushort x, ushort y, ushort width, ushort height, ushort multiplier, ushort divisor)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x86794E6F);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(x);
                KernelStream.Write(y);
                KernelStream.Write(width);
                KernelStream.Write(height);
                KernelStream.Write(multiplier);
                KernelStream.Write(divisor);
            }
        }
    }
    
    public class SubSurface
    {
        private IntPtr pointer;
    
        internal SubSurface(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Resize(Point2 newSize)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x97BF0191);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(newSize);
            }
        }
    }
}

namespace API.System.Interface
{
    public enum DockStyle
    {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        LeftFull,
        RightFull,
        TopFull,
        BottomFull,
        LeftRight,
        TopBottom,
        Full,
    }
    
    public class Element
    {
        private IntPtr pointer;
    
        internal Element(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public bool pointed
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7D2F3E9B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x41B86DF1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ChangeEvent<Graphics.Point> PositionChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3968360D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Point>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x313ACE6F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Point>>(value);
                }
            }
        }
        public Graphics.Point Position
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x130273E8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Point>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCAA44E56);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Point>(value);
                }
            }
        }
        public ChangeEvent<Graphics.Point> SizeChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x91C4DF1B);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Point>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x37E150CF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Point>>(value);
                }
            }
        }
        public Graphics.Point Size
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCCC55AB5);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Point>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB4710DBF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Point>(value);
                }
            }
        }
        public ChangeEvent<Boolean> EnabledChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEFB6F7DB);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Boolean>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE583698D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Boolean>>(value);
                }
            }
        }
        public bool Enabled
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x16CDE09C);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x43B1813C);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ChangeEvent<Boolean> VisibleChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x818DA272);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Boolean>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x623AD33A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Boolean>>(value);
                }
            }
        }
        public bool Visible
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD03971C9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4164EF57);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ChangeEvent<Color32> BackColorChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x76F99D64);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Color32>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x00E0EC47);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Color32>>(value);
                }
            }
        }
        public Color32 BackColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0475E83E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD638867A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public ChangeEvent<System.Interface.DockStyle> DockChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2F52165A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<System.Interface.DockStyle>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC6600992);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<System.Interface.DockStyle>>(value);
                }
            }
        }
        public API.System.Interface.DockStyle Dock
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7AD9A829);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Interface.DockStyle>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB6C9B8B4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Interface.DockStyle>(value);
                }
            }
        }
        public ChangeEvent<Graphics.Outline> MarginChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCE97064D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Outline>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x690F56B9);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Outline>>(value);
                }
            }
        }
        public Graphics.Outline Margin
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD60A1285);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Outline>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF01E4020);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Outline>(value);
                }
            }
        }
        public IntPtr Tag
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF90E415A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadIntPtr();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9C70B404);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public IntPtr GetTag()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x97FD95B9);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.ReadIntPtr();
            }
        }
        public void SetTag(IntPtr value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x645A6973);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC650A0E8);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    
        public event Action<Devices.PointerPositionEvent> PointerMove
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.PointerEvent> PointerIn
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.PointerEvent> PointerOut
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.PointerEvent> PointerDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.PointerEvent> PointerUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.ButtonEvent> ButtonDown
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<Devices.ButtonEvent> ButtonUp
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class Control
    {
        private IntPtr pointer;
    
        internal Control(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Graphics.Surface Surface
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2E47FA56);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Surface>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x87E2D627);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Surface>(value);
                }
            }
        }
    
        public Graphics.Surface GetSurface()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xCEDB73BF);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Surface>();
            }
        }
        public void SetSize(Graphics.Point value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xFFF857C5);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF1D31052);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2CDF7EF2);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    
        public event Action<Graphics.Rectangle> Redrawn
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class Container
    {
        private IntPtr pointer;
    
        internal Container(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ChangeEvent<Graphics.Outline> BorderChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA9A2837F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Outline>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6B08A8C9);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Outline>>(value);
                }
            }
        }
        public Graphics.Outline Border
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA8CEEDFC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Outline>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x80567BC0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Outline>(value);
                }
            }
        }
        public Color32 BorderColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB5B15880);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCB287AD0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
    
        public void SetSize(Graphics.Point value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2B7A7B5A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void SetBackColor(Color32 value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2118C079);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Add(System.Interface.Container container)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xECC42101);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(container);
            }
        }
        public void Remove(System.Interface.Container container)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x016C6766);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(container);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7C6F07E4);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw(Graphics.Surface surface, Graphics.Rectangle rectangle)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x1F428308);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(surface);
                KernelStream.Write(rectangle);
            }
        }
    
        public event Action<Graphics.Rectangle> Refreshed
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class Tab
    {
        private IntPtr pointer;
    
        internal Tab(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string Title
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5D8B4489);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x96273476);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    }
    
    public enum ButtonStyle
    {
        None,
        Text,
        Image,
    }
    
    public enum ButtonState
    {
        Idle,
        Over,
        Down,
    }
    
    public class Button
    {
        private IntPtr pointer;
    
        internal Button(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public ChangeEvent<Graphics.Bitmap> ImageChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF884EBE3);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Bitmap>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1DAEE1AF);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Bitmap>>(value);
                }
            }
        }
        public Graphics.Bitmap Image
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEA655DE9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Bitmap>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x114F52FD);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Bitmap>(value);
                }
            }
        }
        public ChangeEvent<String> TextChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC903D3DC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<String>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCA2D138A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<String>>(value);
                }
            }
        }
        public string Text
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD4A54D19);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF33E91D1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public ChangeEvent<Graphics.Font> FontChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x65EE6C64);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Font>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x709D4735);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Font>>(value);
                }
            }
        }
        public Graphics.Font Font
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA7F94C75);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF199AF45);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Font>(value);
                }
            }
        }
        public ChangeEvent<System.Interface.ButtonStyle> StyleChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEBE97236);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<System.Interface.ButtonStyle>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3100BF63);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<System.Interface.ButtonStyle>>(value);
                }
            }
        }
        public API.System.Interface.ButtonStyle Style
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x30B6ECCE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Interface.ButtonStyle>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x85D5E1FC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Interface.ButtonStyle>(value);
                }
            }
        }
        public ChangeEvent<Graphics.Outline> BorderChanged
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCAF90431);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<ChangeEvent<Graphics.Outline>>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x122C6F74);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<ChangeEvent<Graphics.Outline>>(value);
                }
            }
        }
        public Graphics.Outline Border
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x1B13F61E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Outline>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAED223A2);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Outline>(value);
                }
            }
        }
        public Color32 BorderColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2A0447B9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x725CEB4F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public Color32 OverColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0548CED4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x44D1F1E9);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public Color32 DownColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x54F0AD21);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x129C0AF1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
    
        public Graphics.Bitmap GetImage()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x5050275F);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Bitmap>();
            }
        }
        public void SetImage(Graphics.Bitmap value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x2266093D);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public Graphics.Font GetFont()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA579FE6B);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public void SetFont(Graphics.Font value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA10BC0E0);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void SetBackColor(Color32 value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD367E620);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x32D859AB);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x8D2C9EB8);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public enum WindowState
    {
        Normal,
        Maximized,
        Hidden,
        Docked,
    }
    
    public enum WindowLayer
    {
        Bottom,
        Normal,
        Top,
    }
    
    public class Window
    {
        private IntPtr pointer;
    
        internal Window(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Graphics.Surface cachedSurface
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3C086675);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Surface>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF1C6E026);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Surface>(value);
                }
            }
        }
        public string Title
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9FBD7CA8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE5E1E835);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public API.System.Interface.WindowState State
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD8FF34E1);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Interface.WindowState>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA0C0C7E1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Interface.WindowState>(value);
                }
            }
        }
        public API.System.Interface.WindowLayer Layer
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBB2E12A2);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<API.System.Interface.WindowLayer>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x6CDE770E);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<API.System.Interface.WindowLayer>(value);
                }
            }
        }
    
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x13788136);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    
        public event Action<System.Interface.WindowState> StateChanged
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action<System.Interface.WindowLayer> LayerChanged
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
        public event Action Closed
        {
            add
            {
                lock (KernelStream.Mutex)
                {
                }
            }
            remove
            {
                lock (KernelStream.Mutex)
                {
                }
            }
        }
    }
    
    public class WindowManager
    {
        private IntPtr pointer;
    
        internal WindowManager(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public static void Add(System.Interface.Window window)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF34F5536);
                KernelStream.Write(window);
            }
        }
        public static void Remove(System.Interface.Window window)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x51993682);
                KernelStream.Write(window);
            }
        }
        public static void Loop()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x014061D8);
            }
        }
    }
    
    public class Field
    {
        private IntPtr pointer;
    
        internal Field(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Color32 Color
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4EE5B742);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF6A619D0);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public string Text
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4266457E);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x4BD96058);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Graphics.Font Font
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x839EAFE4);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0A97F915);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Font>(value);
                }
            }
        }
    
        public Graphics.Font GetFont()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x33BAF60C);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public Graphics.Font SetFont(Graphics.Font value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x096D0D6D);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xB5F49D9A);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x478C77F2);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class Graph
    {
        private IntPtr pointer;
    
        internal Graph(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Curve
        {
            private IntPtr pointer;
        
            internal Curve(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public Color24 Color
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xA4DB2750);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<Color24>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x4547D9A3);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<Color24>(value);
                    }
                }
            }
            public int Values
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xED3C68AE);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadInt32();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x73694C03);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
        
            public void AddValue(int value)
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBE46A2D2);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
            public void Clear(int value)
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xBF69A379);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public ushort SegmentSize
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xEE930330);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x0CF7AD1D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Graphics.Point GridSize
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3A01A711);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Point>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x47F04BE6);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Point>(value);
                }
            }
        }
        public ushort GridShift
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x782E2138);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt16();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8EF5FD78);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public bool FillBelow
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x3505201A);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAC752BA8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
    
        public System.Interface.Graph.Curve AddCurve(Color24 color)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3BABD82F);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(color);
                return KernelStream.Read<System.Interface.Graph.Curve>();
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC69A51C9);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x144CF3B7);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class Image
    {
        private IntPtr pointer;
    
        internal Image(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Graphics.Surface Surface
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x2F8CCD12);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Surface>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x35C0C25D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Surface>(value);
                }
            }
        }
    
        public Graphics.Surface GetSurface()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x52E36825);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Surface>();
            }
        }
        public void SetBackColor(Color32 value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x3C0A5D11);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6DEB0BC8);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x7A0D2A2C);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class Label
    {
        private IntPtr pointer;
    
        internal Label(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Color32 Color
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x608ED463);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color32>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x895F5431);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color32>(value);
                }
            }
        }
        public string Text
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x9D08E503);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xD16E13EC);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Graphics.Font Font
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xCFD9D4D9);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x82435DF1);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Font>(value);
                }
            }
        }
        public bool AutoSize
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xE9E90850);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x527E931A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Graphics.Alignment Alignment
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB5CA3CEF);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Alignment>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x733B9B50);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Alignment>(value);
                }
            }
        }
    
        public Graphics.Font GetFont()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xECD45671);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public Graphics.Font SetFont(Graphics.Font value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x69043B9A);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public void SetSize(Graphics.Point value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x837C7A64);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xEDD096F0);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x49C3C95E);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class ListViewItem
    {
        private IntPtr pointer;
    
        internal ListViewItem(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class ListView
    {
        private IntPtr pointer;
    
        internal ListView(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
    
    public class StackContainer
    {
        private IntPtr pointer;
    
        internal StackContainer(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public Graphics.Orientation Orientation
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5959477D);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Orientation>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8F38E2B3);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Orientation>(value);
                }
            }
        }
        public bool AutoSize
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x8E75DB0F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x40FD366A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public List<System.Interface.Element> Elements
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x38043F92);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.Interface.Element>>();
                }
            }
        }
    
        public void Add(System.Interface.Container container)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD82606B6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(container);
            }
        }
        public void Remove(System.Interface.Container container)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x55BCBEF6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(container);
            }
        }
    }
    
    public class Menu
    {
        private IntPtr pointer;
    
        internal Menu(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Item
        {
            private IntPtr pointer;
        
            internal Item(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
        }
    
        public void Add(System.Interface.Menu.Item item)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF9D3D7E6);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(item);
            }
        }
    }
    
    public class ScrollContainer
    {
        private IntPtr pointer;
    
        internal ScrollContainer(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6214FFCD);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD3941F86);
                KernelStream.Write(pointer.ToInt32());
            }
        }
    }
    
    public class Grid
    {
        private IntPtr pointer;
    
        internal Grid(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public class Column
        {
            private IntPtr pointer;
        
            internal Column(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public string Title
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x0F9F2D04);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.ReadString();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xA47917BD);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write(value);
                    }
                }
            }
            public List<System.Interface.Grid.Cell> Cells
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x921F4CBE);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<List<System.Interface.Grid.Cell>>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0xF91E6A57);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<List<System.Interface.Grid.Cell>>(value);
                    }
                }
            }
        
            public System.Interface.Grid.Cell AddCell()
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x348E0410);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Interface.Grid.Cell>();
                }
            }
        }
        
        public class Cell
        {
            private IntPtr pointer;
        
            internal Cell(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
            public System.Interface.Control Control
            {
                get
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x6E2CB3C3);
                        KernelStream.Write(pointer.ToInt32());
                        return KernelStream.Read<System.Interface.Control>();
                    }
                }
                set
                {
                    lock (KernelStream.Mutex)
                    {
                        KernelStream.Write((uint)0x730CDECC);
                        KernelStream.Write(pointer.ToInt32());
                        KernelStream.Write<System.Interface.Control>(value);
                    }
                }
            }
        
            public Interface.Control GetControl()
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xA7748AC8);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Interface.Control>();
                }
            }
            public Interface.Control SetControl(Interface.Control value)
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x88C27CB4);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                    return KernelStream.Read<Interface.Control>();
                }
            }
        }
        
        public class Row
        {
            private IntPtr pointer;
        
            internal Row(IntPtr pointer)
            {
                this.pointer = pointer;
            }
        
        }
    
        public List<System.Interface.Grid.Column> Columns
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x85A28C7F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<List<System.Interface.Grid.Column>>();
                }
            }
        }
        public bool ShowHeaders
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xAEE67C45);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadBoolean();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xC313C209);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write(value);
                }
            }
        }
        public Graphics.Font Font
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x220A7683);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Font>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x86FABE0F);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Font>(value);
                }
            }
        }
        public Color24 AlternateBackColor
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x86AC7A36);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Color24>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x5A26A05A);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Color24>(value);
                }
            }
        }
    
        public Graphics.Font GetFont()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xA6FF2221);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public Graphics.Font SetFont(Graphics.Font value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xEDFB8D87);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
                return KernelStream.Read<Graphics.Font>();
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6683FDB8);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw(Graphics.Surface surface, Graphics.Rectangle rectangle)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x9CE31768);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(surface);
                KernelStream.Write(rectangle);
            }
        }
        public System.Interface.Grid.Column AddColumn()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x4D298058);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.Interface.Grid.Column>();
            }
        }
        public System.Interface.Grid.Row AddRow()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xC84FBD71);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.Interface.Grid.Row>();
            }
        }
    }
    
    public class TabContainer
    {
        private IntPtr pointer;
    
        internal TabContainer(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public System.Interface.Tab CurrentTab
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x160964AC);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<System.Interface.Tab>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xB036059D);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<System.Interface.Tab>(value);
                }
            }
        }
        public Graphics.Orientation Orientation
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x27458CBE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.Read<Graphics.Orientation>();
                }
            }
            set
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x58CE16E8);
                    KernelStream.Write(pointer.ToInt32());
                    KernelStream.Write<Graphics.Orientation>(value);
                }
            }
        }
    
        public System.Interface.Tab GetCurrentTab()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x632F6988);
                KernelStream.Write(pointer.ToInt32());
                return KernelStream.Read<System.Interface.Tab>();
            }
        }
        public void SetCurrentTab(System.Interface.Tab value)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x75A9B83C);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(value);
            }
        }
        public void Add(System.Interface.Tab tab)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xD882B1F1);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(tab);
            }
        }
        public void Initialize()
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0xF87C6E21);
                KernelStream.Write(pointer.ToInt32());
            }
        }
        public void Redraw(Graphics.Surface surface, Graphics.Rectangle rectangle)
        {
            lock (KernelStream.Mutex)
            {
                KernelStream.Write((uint)0x6EE772DB);
                KernelStream.Write(pointer.ToInt32());
                KernelStream.Write(surface);
                KernelStream.Write(rectangle);
            }
        }
    }
    
    public class Table
    {
        private IntPtr pointer;
    
        internal Table(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
    }
}

namespace API.System.Objects
{
    public class Entity
    {
        private IntPtr pointer;
    
        internal Entity(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public uint Id
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0xF454634F);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadUInt32();
                }
            }
        }
    }
    
    public class User
    {
        private IntPtr pointer;
    
        internal User(IntPtr pointer)
        {
            this.pointer = pointer;
        }
    
        public string Name
        {
            get
            {
                lock (KernelStream.Mutex)
                {
                    KernelStream.Write((uint)0x7B4ECDAE);
                    KernelStream.Write(pointer.ToInt32());
                    return KernelStream.ReadString();
                }
            }
        }
    }
}