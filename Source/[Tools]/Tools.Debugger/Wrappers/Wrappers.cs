using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

using Tools.Gdb;

namespace Debugger.Wrappers
{
    public class Flag : Object
    {
    
        public Flag(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    public enum MemoryType
    {
        Heap,
        Stack,
    }
    public class Memory : Object
    {
    
        public Memory(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Unit : Object
    {
        public Value<byte> value
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Unit(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class ILockable : Object
    {
    
        public ILockable(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class LockableLocker : Object
    {
        public Pointer<ILockable> lockable
        {
            get
            {
                return new Pointer<ILockable>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public LockableLocker(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class AssertException : Object
    {
    
        public AssertException(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class ConsoleStream : Object
    {
    
        public ConsoleStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Maths : Object
    {
    
        public Maths(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Matrix3 : Object
    {
        public Matrix3 Identity
        {
            get
            {
                return new Matrix3(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Matrix3(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Point2 : Object
    {
        public Value<int> X
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<int> Y
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 Zero
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 One
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Point2(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Point3 : Object
    {
        public Value<int> X
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<int> Y
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<int> Z
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Point3 Zero
        {
            get
            {
                return new Point3(memory, (ulong)((long)Address + 0));
            }
        }
        public Point3 One
        {
            get
            {
                return new Point3(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Point3(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Vector2 : Object
    {
        public Value<float> X
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> Y
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 Zero
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 One
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 Left
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 Up
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 Right
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector2 Down
        {
            get
            {
                return new Vector2(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Vector2(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Vector3 : Object
    {
        public Value<float> X
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> Y
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> Z
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Zero
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 One
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Backward
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Forward
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Left
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Right
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Down
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
        public Vector3 Up
        {
            get
            {
                return new Vector3(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Vector3(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Quaternion : Object
    {
        public Value<float> X
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> Y
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> Z
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Quaternion Identity
        {
            get
            {
                return new Quaternion(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Quaternion(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class UnitGroup : Object
    {
    
        public UnitGroup(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Units : Object
    {
    
        public Units(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    public class Console : Object
    {
        public Pointer<ConsoleStream> BaseConsoleStream
        {
            get
            {
                return new Pointer<ConsoleStream>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.TextStream> BaseStream
        {
            get
            {
                return new Pointer<System.IO.TextStream>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Console(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Serial : Object
    {
        public Pointer<System.IO.TextStream> BaseStream
        {
            get
            {
                return new Pointer<System.IO.TextStream>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Serial(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Color24 : Object
    {
    
        public Color24(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Color32 : Object
    {
    
        public Color32(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Matrix4 : Object
    {
        public Matrix4 Identity
        {
            get
            {
                return new Matrix4(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Matrix4(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Application : Object
    {
    
        public Application(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Game : Object
    {
        public Value<bool> running
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Interface.Window> window
        {
            get
            {
                return new Pointer<System.Interface.Window>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Interface.Image> image
        {
            get
            {
                return new Pointer<System.Interface.Image>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> frameRate
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> frameSkip
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> vSync
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> ups
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<float> dps
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Game(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Timer : Object
    {
        public Value<ulong> Ticks
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Timer(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class RandomStream : Object
    {
        public Value<uint> next
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public RandomStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class Random : Object
    {
        public Random random
        {
            get
            {
                return new Random(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> next
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public RandomStream stream
        {
            get
            {
                return new RandomStream(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Random(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class TimeSpan : Object
    {
        public Value<bool> sign
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> days
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> milliseconds
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Days
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Hours
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Minutes
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Seconds
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Milliseconds
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public TimeSpan(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    public class DateTime : Object
    {
        public Value<ushort> Year
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Day
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Hours
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Minutes
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Seconds
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Milliseconds
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Day DayOfWeek
        {
            get
            {
                return new Day(memory, (ulong)((long)Address + 0));
            }
        }
        public DateTime Date
        {
            get
            {
                return new DateTime(memory, (ulong)((long)Address + 0));
            }
        }
        public DateTime Time
        {
            get
            {
                return new DateTime(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> DateFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> TimeFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> DateTimeFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> LongDateFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> LongTimeFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> LongDateTimeFormat
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public DateTime Now
        {
            get
            {
                return new DateTime(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DateTime(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}
namespace Debugger.Wrappers.System
{
}
namespace Debugger.Wrappers.System.Runtime
{
    public class Mutex : Object
    {
        public Value<uint> id
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> locked
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Mutex(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Process : Object
    {
        public Collection Threads
        {
            get
            {
                return new Collection(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Process(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Dispatcher : Object
    {
        public Value<bool> bufferIndex
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public List frameBuffer1
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List frameBuffer2
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Runtime.Spinlock invokeLock
        {
            get
            {
                return new System.Runtime.Spinlock(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Runtime.Spinlock flushLock
        {
            get
            {
                return new System.Runtime.Spinlock(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Dispatcher(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Thread : Object
    {
        public Pointer<System.Runtime.Process> Process
        {
            get
            {
                return new Pointer<System.Runtime.Process>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Runtime.Dispatcher> Dispatcher
        {
            get
            {
                return new Pointer<System.Runtime.Dispatcher>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Thread(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Spinlock : Object
    {
        public Value<uint> state
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Spinlock(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Signal : Object
    {
        public Value<uint> id
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Signal(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Debugger : Object
    {
    
        public Debugger(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Profiler : Object
    {
    
        public Profiler(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public enum AccessibilityModifier
    {
        Public,
        Protected,
        Private,
        Static,
    }
    
    public class Symbol : Object
    {
        public Value<string> name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Symbol(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Constructor : Object
    {
        public Value<string> rawName
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Constructor(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public enum VirtualizationModifier
    {
        None,
        Abstract,
        Virtual,
    }
    
    public class Method : Object
    {
        public Value<string> rawName
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Method(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Reflection : Object
    {
    
        public Reflection(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Namespace : Object
    {
        public Pointer<System.Runtime.Namespace> parent
        {
            get
            {
                return new Pointer<System.Runtime.Namespace>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Namespace(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Property : Object
    {
    
        public Property(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Serializer : Object
    {
    
        public Serializer(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Executable : Object
    {
        public Value<bool> allowMultipleInstances
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Executable(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}

namespace Debugger.Wrappers.System.Data
{
    public class Record : Object
    {
    
        public Record(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Table : Object
    {
    
        public Table(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Database : Object
    {
        public Pointer<System.Data.Database> Default
        {
            get
            {
                return new Pointer<System.Data.Database>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Database(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}

namespace Debugger.Wrappers.System.IO
{
    public enum SeekOrigin
    {
        Begin,
        Current,
        End,
    }
    
    public class Stream : Object
    {
        public Value<ulong> length
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ulong> position
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ulong> Position
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ulong> Length
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> EndOfStream
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.Stream> Null
        {
            get
            {
                return new Pointer<System.IO.Stream>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Stream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class TextStream : Object
    {
        public Pointer<System.IO.Stream> baseStream
        {
            get
            {
                return new Pointer<System.IO.Stream>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public TextStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class BufferStream : Object
    {
        public Pointer<Pointer<Value<byte>>> indexes
        {
            get
            {
                return new Pointer<Pointer<Value<byte>>>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> indexesCapacity
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Value<byte>> buffer
        {
            get
            {
                return new Pointer<Value<byte>>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> bufferCapacity
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> position
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> length
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> limit
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public BufferStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public enum FileAttributes
    {
        None,
        Hidden,
        System,
    }
    
    public class File : Object
    {
        public Value<string> Path
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Extension
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ulong> Size
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public File(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Directory : Object
    {
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.Directory> Parent
        {
            get
            {
                return new Pointer<System.IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference Directories
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference Files
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> FullPath
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.Directory> Root
        {
            get
            {
                return new Pointer<System.IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.Directory> Current
        {
            get
            {
                return new Pointer<System.IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Directory(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class FileStream : Object
    {
    
        public FileStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DirectoryLink : Object
    {
        public Pointer<System.IO.Directory> target
        {
            get
            {
                return new Pointer<System.IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.IO.Directory> Target
        {
            get
            {
                return new Pointer<System.IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DirectoryLink(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class AsyncStream : Object
    {
    
        public AsyncStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DataStream : Object
    {
        public Pointer<System.IO.Stream> baseStream
        {
            get
            {
                return new Pointer<System.IO.Stream>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Value<sbyte>> buffer
        {
            get
            {
                return new Pointer<Value<sbyte>>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DataStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class TeeStream : Object
    {
        public List streams
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> length
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public TeeStream(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}

namespace Debugger.Wrappers.System.Devices
{
    public class Device : Object
    {
        public Value<bool> loaded
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Device(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class PointerEvent : Object
    {
        public Value<byte> Index
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public PointerEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class PointerPositionEvent : Object
    {
        public Value<ushort> X
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Y
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public PointerPositionEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class PointerMoveEvent : Object
    {
        public Value<sbyte> X
        {
            get
            {
                return new Value<sbyte>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<sbyte> Y
        {
            get
            {
                return new Value<sbyte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public PointerMoveEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class PointerScrollEvent : Object
    {
        public Value<short> Delta
        {
            get
            {
                return new Value<short>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public PointerScrollEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class PointerDevice : Object
    {
        public Event PointerMove
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerDown
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerUp
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerScroll
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public PointerDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class RawButtonEvent : Object
    {
    
        public RawButtonEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ButtonEvent : Object
    {
        public Value<sbyte> Character
        {
            get
            {
                return new Value<sbyte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public ButtonEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class CharactersMapping : Object
    {
        public Pointer<Value<sbyte>> map
        {
            get
            {
                return new Pointer<Value<sbyte>>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public CharactersMapping(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ButtonsState : Object
    {
        public Pointer<Value<bool>> state
        {
            get
            {
                return new Pointer<Value<bool>>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public ButtonsState(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class JaugeEvent : Object
    {
        public Value<float> Value
        {
            get
            {
                return new Value<float>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public JaugeEvent(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class InputManager : Object
    {
        public List pointers
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Devices.PointerDevice> defaultPointer
        {
            get
            {
                return new Pointer<System.Devices.PointerDevice>(memory, (ulong)((long)Address + 0));
            }
        }
        public List buttons
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Devices.CharactersMapping charactersMappingNormal
        {
            get
            {
                return new System.Devices.CharactersMapping(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Devices.CharactersMapping charactersMappingShift
        {
            get
            {
                return new System.Devices.CharactersMapping(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Devices.CharactersMapping charactersMappingAlt
        {
            get
            {
                return new System.Devices.CharactersMapping(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Devices.ButtonsState buttonsState
        {
            get
            {
                return new System.Devices.ButtonsState(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<IO.BufferStream> buttonsBuffer
        {
            get
            {
                return new Pointer<IO.BufferStream>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<IO.TextStream> buttonsStream
        {
            get
            {
                return new Pointer<IO.TextStream>(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerMove
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerDown
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerUp
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 PointerPosition
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Event ButtonDown
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event ButtonUp
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event JaugeChange
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public InputManager(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DeviceEnumerator : Object
    {
    
        public DeviceEnumerator(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class CommunicationDevice : Object
    {
        public Pointer<List> streams
        {
            get
            {
                return new Pointer<List>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<List> Streams
        {
            get
            {
                return new Pointer<List>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public CommunicationDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class NetworkDevice : Object
    {
    
        public NetworkDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DisplayMode : Object
    {
        public Value<ushort> Id
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Width
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> Height
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Bpp
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DisplayMode(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DisplayOverlay : Object
    {
        public Pointer<Graphics.Bitmap> Bitmap
        {
            get
            {
                return new Pointer<Graphics.Bitmap>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DisplayOverlay(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class DisplayDevice : Object
    {
        public Pointer<Graphics.Surface> Surface
        {
            get
            {
                return new Pointer<Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Runtime.Signal> VSync
        {
            get
            {
                return new Pointer<Runtime.Signal>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Devices.DisplayOverlay> Overlay
        {
            get
            {
                return new Pointer<System.Devices.DisplayOverlay>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Devices.DisplayMode> DisplayMode
        {
            get
            {
                return new Pointer<System.Devices.DisplayMode>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public DisplayDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class InputDevice : Object
    {
    
        public InputDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class StorageDevice : Object
    {
        public Pointer<List> fileSystems
        {
            get
            {
                return new Pointer<List>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<List> FileSystems
        {
            get
            {
                return new Pointer<List>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public StorageDevice(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class FileSystem : Object
    {
        public Pointer<Pointer<System.Devices.FileSystemConstructorBase>> fileSystems
        {
            get
            {
                return new Pointer<Pointer<System.Devices.FileSystemConstructorBase>>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Devices.StorageDevice> device
        {
            get
            {
                return new Pointer<System.Devices.StorageDevice>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ulong> position
        {
            get
            {
                return new Value<ulong>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<IO.Directory> root
        {
            get
            {
                return new Pointer<IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<IO.Directory> Root
        {
            get
            {
                return new Pointer<IO.Directory>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public FileSystem(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class FileSystemConstructorBase : Object
    {
    
        public FileSystemConstructorBase(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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

namespace Debugger.Wrappers.System.Graphics
{
    public class Point : Object
    {
    
        public Point(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Rectangle : Object
    {
        public System.Graphics.Point Position
        {
            get
            {
                return new System.Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
        public System.Graphics.Point Size
        {
            get
            {
                return new System.Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Rectangle(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Outline : Object
    {
        public Value<uint> Top
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> Right
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> Bottom
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> Left
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Outline(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class BitmapLoaderBase : Object
    {
    
        public BitmapLoaderBase(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Bitmap : Object
    {
        public Pointer<Debugger.Wrappers.System.Graphics.Bitmap.Pixel> data
        {
            get
            {
                return new Pointer<Debugger.Wrappers.System.Graphics.Bitmap.Pixel>(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 size
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> padding
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> _pitch
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> _size
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Bitmap(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Bitmaps : Object
    {
    
        public Bitmaps(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Font : Object
    {
        public Reference Family
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<byte> Size
        {
            get
            {
                return new Value<byte>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Font(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class FontFamily : Object
    {
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public FontFamily(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Surface : Object
    {
    
        public Surface(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class SubSurface : Object
    {
        public Pointer<System.Graphics.Surface> baseSurface
        {
            get
            {
                return new Pointer<System.Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> x
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> y
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public SubSurface(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ShiftedSurface : Object
    {
        public Pointer<System.Graphics.Surface> baseSurface
        {
            get
            {
                return new Pointer<System.Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<short> x
        {
            get
            {
                return new Value<short>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<short> y
        {
            get
            {
                return new Value<short>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public ShiftedSurface(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}

namespace Debugger.Wrappers.System.Interface
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
    
    public class Element : Object
    {
        public Graphics.Point position
        {
            get
            {
                return new Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Point size
        {
            get
            {
                return new Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 backColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> enabled
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> visible
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Outline margin
        {
            get
            {
                return new Graphics.Outline(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> pointed
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent PositionChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent SizeChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent EnabledChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent VisibleChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent BackColorChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent DockChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent MarginChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerMove
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerScroll
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerIn
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerOut
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerDown
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event PointerUp
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event ButtonDown
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event ButtonUp
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Element(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Control : Object
    {
        public Pointer<Graphics.Surface> surface
        {
            get
            {
                return new Pointer<Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Graphics.Surface> Surface
        {
            get
            {
                return new Pointer<Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Event Redrawn
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Control(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Container : Object
    {
        public List containers
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List controls
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Outline border
        {
            get
            {
                return new Graphics.Outline(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 borderColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent BorderChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 BorderColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Event Refreshed
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Container(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Window : Object
    {
        public Pointer<System.Interface.Button> minimize
        {
            get
            {
                return new Pointer<System.Interface.Button>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Interface.Button> close
        {
            get
            {
                return new Pointer<System.Interface.Button>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Interface.Mover> mover
        {
            get
            {
                return new Pointer<System.Interface.Mover>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> title
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Graphics.Surface> cachedSurface
        {
            get
            {
                return new Pointer<Graphics.Surface>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Title
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Event StateChanged
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event LayerChanged
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
        public Event Closed
        {
            get
            {
                return new Event(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Window(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Mover : Object
    {
        public Pointer<System.Interface.Window> window
        {
            get
            {
                return new Pointer<System.Interface.Window>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Mover(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Tab : Object
    {
        public Value<string> title
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Title
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Tab(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class Button : Object
    {
        public Value<string> text
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference image
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference font
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 color
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 overColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 downColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 borderColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Outline border
        {
            get
            {
                return new Graphics.Outline(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Alignment alignment
        {
            get
            {
                return new Graphics.Alignment(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Outline padding
        {
            get
            {
                return new Graphics.Outline(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent ImageChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent TextChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent FontChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent StyleChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent BorderChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Button(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
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
    
    public class WindowsManager : Object
    {
    
        public WindowsManager(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ScrollContainer : Object
    {
        public Point2 view
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 content
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
    
        public ScrollContainer(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public enum ColumnWidthType
    {
        Absolute,
        Relative,
        Fill,
    }
    
    public class Grid : Object
    {
        public List columns
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List columnsOrder
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List rowsOrder
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference font
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> showHeaders
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> showIndices
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> cellHeight
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 alternateBackColor
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> autoSize
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public List Columns
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> ShowHeaders
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference Font
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 AlternateBackColor
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Grid(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Table : Object
    {
    
        public Table(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Graph : Object
    {
        public List curves
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> segmentSize
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<int> minimum
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<int> maximum
        {
            get
            {
                return new Value<int>(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Point gridSize
        {
            get
            {
                return new Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> gridShift
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> fillBelow
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> SegmentSize
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Graphics.Point GridSize
        {
            get
            {
                return new Graphics.Point(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<ushort> GridShift
        {
            get
            {
                return new Value<ushort>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> FillBelow
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Graph(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Image : Object
    {
        public Reference bitmap
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 color
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 Color
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Image(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ListViewItem : Object
    {
    
        public ListViewItem(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class ListView : Object
    {
    
        public ListView(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class Menu : Object
    {
    
        public Menu(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public enum TextStyle
    {
        Normal,
        Bold,
        Italic,
        Strike,
        Underline,
    }
    
    public class TextBox : Object
    {
        public Pointer<System.Interface.TextBox.TextSelection> currentSelection
        {
            get
            {
                return new Pointer<System.Interface.TextBox.TextSelection>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<System.Interface.TextBox.TextSquareSelection> currentSquareSelection
        {
            get
            {
                return new Pointer<System.Interface.TextBox.TextSquareSelection>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> shift
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> control
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> alt
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> pointerDown
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference font
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 backColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 selectionColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> readOnly
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> multiLine
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Pointer<Debugger.Wrappers.System.Interface.TextBox.character> buffer
        {
            get
            {
                return new Pointer<Debugger.Wrappers.System.Interface.TextBox.character>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> length
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> capacity
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public List lines
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List selections
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public List blocks
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 view
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Point2 pointerPosition
        {
            get
            {
                return new Point2(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Text
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent TextChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public Reference Font
        {
            get
            {
                return new Reference(memory, (ulong)((long)Address + 0));
            }
        }
        public ChangeEvent FontChanged
        {
            get
            {
                return new ChangeEvent(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> ReadOnly
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<bool> MultiLine
        {
            get
            {
                return new Value<bool>(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 BackColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public Color32 SelectionColor
        {
            get
            {
                return new Color32(memory, (ulong)((long)Address + 0));
            }
        }
        public List Selections
        {
            get
            {
                return new List(memory, (ulong)((long)Address + 0));
            }
        }
    
        public TextBox(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}

namespace Debugger.Wrappers.System.Objects
{
    public class Entity : Object
    {
        public Value<uint> id
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<uint> Id
        {
            get
            {
                return new Value<uint>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public Entity(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
    
    public class User : Object
    {
        public Value<string> name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
        public Value<string> Name
        {
            get
            {
                return new Value<string>(memory, (ulong)((long)Address + 0));
            }
        }
    
        public User(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}
namespace Debugger.Wrappers.Types
{
}
namespace Debugger.Wrappers.Values
{
}
namespace Debugger.Wrappers.std
{
}
namespace Debugger.Wrappers.Colors
{
    public class System : Object
    {
        public Color24 Color
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 ActiveBackground
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 InactiveBackground
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 Border
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 Menu
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 ActiveTab
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 InactiveTab
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 ActiveSubtab
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
        public Color24 InactiveSubtab
        {
            get
            {
                return new Color24(memory, (ulong)((long)Address + 0));
            }
        }
    
        public System(GdbStub.GdbMemory memory, ulong address) : base(memory, address)
        {
        }
    }
}
