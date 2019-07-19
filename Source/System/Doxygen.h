typedef ... s8;

typedef ... u8;

typedef ... s16;

typedef ... u16;

typedef ... s32;

typedef ... u32;

typedef ... s64;

typedef ... u64;

typedef ... byte;

class Flag
{
public:
    static bool Test(T value, U flag);
    static U Get(T value, U mask);
};

class type_info
{
public:
    void* data;
    signed char name;
    type_info(type_info& );
    type_info();
    bool operator==(type_info& );
    bool operator!=(type_info& );
};

typedef ... RTTI_TypeDescriptor;

struct RTTI_ClassHierarchyDescriptor
{
    u32 Signature;
    u32 Attributes;
    u32 BaseClassesCount;
    RTTI_BaseClassDescriptor** BaseClasses;
};

struct RTTI_PMD
{
    s32 MemberOffset;
    s32 VTableOffset;
    s32 vdisp;
};

struct RTTI_BaseClassDescriptor
{
    type_info* Type;
    u32 BaseClassesCount;
    RTTI_PMD Pmd;
    u32 Attributes;
    RTTI_ClassHierarchyDescriptor* Hierarchy;
};

struct RTTI_CompleteObjectLocator
{
    u32 Signature;
    u32 Offset;
    u32 CdOffset;
    type_info* Type;
    RTTI_ClassHierarchyDescriptor* Hierarchy;
};

struct String
{
    u32 Length;
    s8* Buffer;
    String Null;
    String Empty;
    String NewLine;
    String Separator;
    String();
    String(s8* buffer, u32 length, bool copy);
    String(String& other);
    String(String& other, String& format);
    String();
    String(s8* other);
    String(s8* other);
    String(signed char character, u32 count);
    String(s32 value, u8 base, u8 length);
    String(u32 value, String& format);
    String(u32 value, u8 base, u8 length);
    String(s64 value, u8 base, u8 length);
    String(u64 value, u8 base, u8 length);
    String(bool value);
    String(float value, u8 digits, bool strip);
    String(double value);
    String(void* pointer);
    String(void* pointer, String& format);
    String(Object& other);
    String(Object& other, String& format);
    String(Object* other);
    String(Object* other, String& format);
    String& operator=(String& other);
    String& operator=(String& other);
    String(Month month, String& format);
    String(Day day, String& format);
    u32 GetLength();
    s8* GetBuffer();
    s8& operator[](s32 index);
    String After(String& other);
    String AfterLast(String& other);
    String Before(String& other);
    String BeforeLast(String& other);
    bool Contains(String& other);
    s32 IndexOf(String& other, u32 from);
    s32 IndexOfLast(String& other, u32 from);
    String After(signed char character);
    String AfterLast(signed char character);
    String Before(signed char character);
    String BeforeLast(signed char character);
    bool Contains(signed char character);
    s32 IndexOf(signed char character, u32 from);
    s32 IndexOfLast(signed char character, u32 from);
    String Replace(String& value, String& replacement, u32 count);
    String SubString(s32 position);
    String SubString(s32 position, s32 length);
    String ToLower();
    String ToUpper();
    String ToCasing(Casing casing);
    String Trim(String& characters);
    String TrimLeft(String& characters);
    String TrimRight(String& characters);
    bool operator==(String& s);
    bool operator==(s8* c);
    bool operator!=(String& s);
    bool operator!=(s8* c);
    String operator+(String& other);
    String operator+(s8* other);
    String operator+(bool other);
    String operator+(signed char other);
    String operator+(void* other);
    String operator+(s32 other);
    String operator+(u32 other);
    String operator+(s64 other);
    String operator+(u64 other);
    String operator+(float other);
    String operator+(double other);
    bool ToBool();
    u32 ToUnsigned(u32 base);
    s32 ToSigned(u32 base);
    T To(u32 base);
    String To(u32 base);
    bool To(u32 );
    u8 To(u32 base);
    u16 To(u32 base);
    u32 To(u32 base);
    s8 To(u32 base);
    s16 To(u32 base);
    s32 To(u32 base);
    static String FormatInternal(String& base, u32 index, T parameter);
    static String FormatInternal(String& base, u32 index, First parameter, Other parameters);
    static String Format(String& base, Args parameters);
    static String Format(String& base);
};

class Object
{
public:
    Object();
    String ToString();
    u32 Hash();
    System::Runtime::Type* GetType();
    bool Is();
    T* As();
};

enum class Month
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
};

enum class Day
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
};

enum class Casing
{
    Upper,
    Lower,
    FirstUpper,
    WordsUpper,
    Words,
    Sentence,
};

typedef ... string;

enum class MemoryType
{
    Heap,
    Stack,
};

class Memory
{
public:
    static void Copy(void* source, void* destination, u32 count);
    static void Copy(void* source, void* destination, u32 count);
    static void Clear(void* address, u32 count, u8 value);
    static void Clear(void* address, u32 count, u8 value);
    static void Set(void* address, T& value, u32 count);
    static bool Compare(void* address1, void* address2, u32 count);
    static bool Compare(void* address1, void* address2, u32 count);
    static T* Allocate(u32 count, s16 value);
    static T* Allocate(u32 count, MemoryType type, s16 value);
    static void* Allocate(u32 count, s16 value);
    static void* Allocate(u32 count, MemoryType type, s16 value);
    static void Free(void* address);
};

struct Function
{
    enum class 
    {
        Size,
    };
    Function();
    Function(Function& function);
    Function(Function& function);
    Function(Result* action);
    void Function<Result, Args...>(T* object, Result* action);
    void Function<Result, Args...>(T& object, Result* action);
    void Function<Result, Args...>(T& callable);
    Function& operator=(Function& function);
    Result operator()(Args parameters);
    bool operator==(Function& function);
    void* GetPointer();
};

struct Pointer
{
    bool Valid;
    Pointer();
    Pointer(T* pointer);
    Pointer(T& object);
    Pointer(Pointer& other);
    Pointer(Pointer& other);
    bool GetValid();
    T* operator->();
    T& operator*();
    bool operator==(Pointer& other);
};

struct Dynamic
{
    Dynamic(Function& loader);
    T* operator->();
    T& operator*();
    void Load();
};

struct Reference
{
    Reference Invalid;
    bool Valid;
    Reference();
    Reference(T* pointer);
    Reference(T* pointer);
    Reference(Reference& other);
    Reference(Reference& other);
    Reference(Pointer& other);
    Reference(Pointer& other);
    Reference(Dynamic& other);
    Reference(Dynamic& other);
    Reference();
    bool GetValid();
    Reference& operator=(Reference& other);
};

struct Unit
{
    Unit();
    Unit(float value);
    Unit(double value);
    Unit(bool value);
    Unit(s32 value);
    Unit operator+(Unit other);
    Unit operator-(Unit other);
    Unit operator*(Unit other);
    Unit operator!();
};

typedef ... unit;

struct Parameters
{
    Parameters(T& arg);
    T& GetValue(u32 i);
    T* GetPointer();
};

struct Iterator
{
    T Current;
    Iterator();
    T GetCurrent();
    bool Next();
};

struct Collection
{
    struct FilteredCollection
    {
        class FilteredIterator
        {
        public:
            FilteredIterator(Reference iterator, Function& filter);
            T GetCurrent();
            bool Next();
        };
        FilteredCollection(Collection* collection, Function& filter);
        Reference GetIterator();
    };
    
    struct ProjectedCollection
    {
        class ProjectedIterator
        {
        public:
            ProjectedIterator(Reference iterator, Function& projection);
            To GetCurrent();
            bool Next();
        };
        ProjectedCollection(Reference collection, Function& projection);
        Reference GetIterator();
    };
    
    struct ConcatenedCollection
    {
        class ConcatenedIterator
        {
        public:
            ConcatenedIterator(Reference iterator);
            T GetCurrent();
            bool Next();
        };
        ConcatenedCollection(Reference collections);
        ConcatenedCollection(Reference collection1, Reference collection2);
        Reference GetIterator();
    };
    Collection();
    Reference GetIterator();
    T First();
    T Last();
    T At(u32 index);
    bool Any();
    u32 Count();
    Reference Where(Function& filter);
    Reference OfType();
    T First(Function& filter);
    T Last(Function& filter);
    bool Any(Function& filter);
    u32 Count(Function& filter);
    Reference Select(Function& projection);
    Reference SelectMany(Function& projection);
    Reference Concat(Reference other);
};

struct RangeIterator
{
    RangeIterator();
    RangeIterator(Reference& iterator);
    T GetCurrent();
    bool Next();
    bool operator!=(RangeIterator iterator);
    void operator++();
    T operator*();
};

struct ILockable
{
    bool Lock(u32 timeout);
    void Unlock();
};

struct LockableLocker
{
    ILockable* lockable;
    LockableLocker(ILockable* lockable);
    LockableLocker(ILockable& lockable);
    LockableLocker();
};

struct List
{
    class ListIterator
    {
    public:
        ListIterator(T* pointer, u32 count);
        bool IsEnd();
        T GetCurrent();
        bool Next();
    };
    u32 Count;
    List(InitializerCollection& items);
    List(u32 limit);
    List(List& other);
    List();
    u32 GetCount();
    void Add(T item);
    void Add(Reference items);
    void Remove(T item);
    void Remove(Reference items);
    void Clear();
    List& operator=(List& other);
    List& operator=(List& other);
    T operator[](u32 index);
    T At(u32 index);
    void Move(u32 from, u32 to);
    void Swap(u32 from, u32 to);
    void BringToFront(u32 index);
    void SendToBack(u32 index);
    Reference GetIterator();
    T First();
    T Last();
    bool Any();
    s32 IndexOf(T element);
    T First(Function& filter);
    T Last(Function& filter);
    bool Any(Function& filter);
    T Sum();
    List* Where(Func& predicate);
};

struct Tuple
{
};

struct Event
{
    void operator+=(& callback);
    void operator-=(& callback);
    void operator()(void* origin, T parameter);
};

struct ChangeEventParameter
{
    T& OldValue;
    T& NewValue;
    ChangeEventParameter(T& oldValue, T& newValue);
};

struct ChangeEvent
{
    void operator()(void* origin, T& oldValue, T& newValue);
};

class Exception
{
public:
    String Message;
    Collection* Frames;
    Exception();
    Exception(String message);
    String GetMessage();
    Collection* GetFrames();
    static void NotImplemented();
    static void Assert();
    static void Assert(bool condition);
    static void Assert(void* pointer);
    static void Assert(s8* message);
    static void Assert(String& message);
    static void Assert(bool condition, s8* message);
    static void Assert(void* pointer, s8* message);
    static void Assert(bool condition, String& message, Args parameters);
    static void Assert(void* pointer, String& message, Args parameters);
};

struct DefaultValue
{
    static T Get();
    static bool Get();
    static u8 Get();
    static u16 Get();
    static u32 Get();
    static u64 Get();
    static s8 Get();
    static s16 Get();
    static s32 Get();
    static s64 Get();
    static float Get();
    static double Get();
    static Unit Get();
};

class AssertException
{
public:
    AssertException();
};

class ConsoleStream
{
public:
    ConsoleStream();
    u64 GetLength();
    u32 Read(void* buffer, u32 count);
    u32 Read(void* buffer, u32 count, bool intercept);
    void Write(void* buffer, u32 count);
};

class Maths
{
public:
    static T Max(T& left, T& right);
    static T Max(T& value1, T& value2, T& value3);
    static T Min(T& left, T& right);
    static T Min(T& value1, T& value2, T& value3);
    static T Clamp(T& value, T& minimum, T& maximum);
    static T Abs(T& val);
    static T Sign(T& val);
    static void Swap(T& value1, T& value2);
    static T Map(T& value, T& fromMin, T& fromMax, T& toMin, T& toMax);
    static float Round(float value);
    static float Ceil(float value);
    static float Floor(float value);
    static float Lerp(float start, float end, float value);
    static float Sqrt(float value);
    static float Pow(float value, float power);
    static float Sin(float value);
    static float Cos(float value);
    static float Tan(float value);
    static float Atan2(float x, float y);
};

struct Matrix3
{
    union 
    {
        struct 
        {
            float c11;
            float c12;
            float c13;
            float c21;
            float c22;
            float c23;
            float c31;
            float c32;
            float c33;
        };
        float* components;
    };
    Matrix3 Identity;
    Matrix3();
    Matrix3(Matrix3& matrix);
    Matrix3(float c11, float c12, float c13, float c21, float c22, float c23, float c31, float c32, float c33);
    float Determinant();
    Matrix3& Transpose();
    void Normalize();
    static Matrix3& Normalize(Matrix3& matrix);
    static Matrix3& CreateRotation(float pitch, float yaw, float roll);
    static Matrix3& CreateRotation(float x, float y, float z, float angle);
    static Matrix3& CreateRotation(Vector3& vector, float angle);
    static Matrix3& CreateRotation(Quaternion& quaternion);
    static Matrix3& CreateTranslation(float x, float y, float z);
    static Matrix3& CreateTranslation(Vector3& vector);
    static Matrix3& CreateScale(float x, float y, float z);
    static Matrix3& CreateScale(Vector3& vector);
    Matrix3& operator+=(Matrix3& matrix);
    Matrix3& operator-=(Matrix3& matrix);
    Matrix3& operator*=(Matrix3& matrix);
    Matrix3& operator/=(Matrix3& matrix);
    Matrix3& operator+(Matrix3& matrix);
    Matrix3& operator-(Matrix3& matrix);
    Matrix3& operator*(Matrix3& matrix);
    Vector3& operator*(Vector3& vector);
    Matrix3& operator/(Matrix3& matrix);
};

struct Point2
{
    s32 X;
    s32 Y;
    Point2 Zero;
    Point2 One;
    Point2();
    Point2(s32 n);
    Point2(s32 x, s32 y);
    bool operator==(Point2& point);
    bool operator!=(Point2& point);
    Point2& operator+=(Point2& point);
    Point2& operator-=(Point2& point);
    Point2 operator+(Point2& point);
    Point2 operator-(Point2& point);
};

struct Point3
{
    s32 X;
    s32 Y;
    s32 Z;
    Point3 Zero;
    Point3 One;
    Point3();
    Point3(s32 n);
    Point3(s32 x, s32 y, s32 z);
    bool operator==(Point3& point);
    bool operator!=(Point3& point);
};

struct Vector2
{
    float X;
    float Y;
    Vector2 Zero;
    Vector2 One;
    Vector2 Left;
    Vector2 Up;
    Vector2 Right;
    Vector2 Down;
    Vector2();
    Vector2(Vector2& vector);
    Vector2(float n);
    Vector2(float x, float y);
    Vector2(Point2& point);
    float Length();
    static Vector2 Lerp(Vector2& v1, Vector2& v2, float c);
    static float Dot(Vector2& v1, Vector2& v2);
    static Vector2 Normalize(Vector2& vector);
    static float Angle(Vector2& v1, Vector2& v2);
    static float Distance(Vector2& v1, Vector2& v2);
    bool operator==(Vector2& vector);
    bool operator!=(Vector2& vector);
    Vector2& operator+=(Vector2& vector);
    Vector2& operator-=(Vector2& vector);
    Vector2& operator*=(float factor);
    Vector2& operator*=(Vector2& vector);
    Vector2& operator/=(float factor);
    Vector2& operator/=(Vector2& vector);
    Vector2 operator+(Vector2& vector);
    Vector2 operator-(Vector2& vector);
    Vector2 operator*(float factor);
    Vector2 operator*(Vector2& vector);
    Vector2 operator/(float factor);
    Vector2 operator/(Vector2& vector);
};

struct Vector3
{
    float X;
    float Y;
    float Z;
    Vector3 Zero;
    Vector3 One;
    Vector3 Backward;
    Vector3 Forward;
    Vector3 Left;
    Vector3 Right;
    Vector3 Down;
    Vector3 Up;
    Vector3();
    Vector3(Vector3& vector);
    Vector3(float n);
    Vector3(float x, float y, float z);
    Vector3(Vector2& vector, float z);
    float Length();
    static Vector3 Lerp(Vector3& v1, Vector3& v2, float c);
    static Vector3 Cross(Vector3& v1, Vector3& v2);
    static float Dot(Vector3& v1, Vector3& v2);
    static Vector3 Normalize(Vector3& vector);
    static float Distance(Vector3& v1, Vector3& v2);
    bool operator==(Vector3& vector);
    bool operator!=(Vector3& vector);
    Vector3& operator+=(Vector3& vector);
    Vector3& operator-=(Vector3& vector);
    Vector3& operator*=(float factor);
    Vector3& operator*=(Vector3& vector);
    Vector3& operator/=(float factor);
    Vector3 operator+(Vector3& vector);
    Vector3 operator-(Vector3& vector);
    Vector3 operator*(float factor);
    Vector3 operator*(Vector3& vector);
    Vector3 operator/(float factor);
    Vector3 operator^(Vector3& vector);
};

struct Quaternion
{
    union 
    {
        float W;
        float Angle;
    };
    float X;
    float Y;
    float Z;
    Quaternion Identity;
    Quaternion();
    Quaternion(float x, float y, float z, float angle);
    Quaternion(Vector3 vector, float angle);
    static Quaternion& Lerp(Quaternion& q1, Quaternion& q2, float c);
};

struct UnitGroup
{
    enum class Units
    {
    };
};

struct Units
{
    struct Size
    {
        enum class Units
        {
            Pixel,
            Point,
            Centimeter,
            Inch,
            Count,
            Default,
        };
        float* Values;
    };
    
    struct Temperature
    {
        enum class Units
        {
            Celsius,
            Fareneight,
            Count,
            Default,
        };
        float* Factors;
        float* Deltas;
    };
    
    struct FileSize
    {
        enum class Units
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
        };
        u32* Factors;
    };
    static s32 Convert(s32 value, T from, T to);
    static float Convert(float value, T from, T to);
};

typedef ... SizeUnit;

typedef ... TemperatureUnit;

typedef ... FileSizeUnit;

enum class ConsoleColor
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
};

class Console
{
public:
    ConsoleStream* BaseConsoleStream;
    System::IO::TextStream* BaseStream;
    ConsoleColor Color;
    ConsoleColor BackColor;
    static void Clear();
    static signed char Read(bool intercept);
    static System::Devices::Buttons ReadKey();
    static String ReadLine();
    static void Write(String& format);
    static void Write(String& format, Args parameters);
    static void WriteLine();
    static void WriteLine(String& format);
    static void WriteLine(String& format, Args parameters);
};

class Log
{
public:
    System::IO::Stream* Trace;
    System::IO::Stream* Debug;
    System::IO::Stream* Info;
    System::IO::Stream* Warning;
    System::IO::Stream* Error;
    static void WriteLine(System::IO::Stream* log);
    static void WriteLine(System::IO::Stream* log, String& format);
    static void WriteLine(System::IO::Stream* log, String& format, Args parameters);
};

class Serial
{
public:
    System::IO::TextStream* BaseStream;
    static void Write(String& base);
    static void Write(String& base, Args parameters);
    static void WriteLine();
    static void WriteLine(String& base);
    static void WriteLine(String& base, Args parameters);
};

struct Color24
{
    union 
    {
        struct 
        {
            u8 Blue;
            u8 Green;
            u8 Red;
            u8 __Unused;
        };
        u32 Value;
    };
    Color24();
    Color24(u32 value);
    Color24(u8 red, u8 green, u8 blue);
    bool operator==(Color24& other);
};

struct Color32
{
    union 
    {
        struct 
        {
            u8 Blue;
            u8 Green;
            u8 Red;
            u8 Alpha;
        };
        u32 Value;
    };
    Color32();
    Color32(u32 value);
    Color32(u8 red, u8 green, u8 blue);
    Color32(u8 alpha, u8 red, u8 green, u8 blue);
    Color32(Color24 color, u8 alpha);
    bool operator==(Color32& other);
};

struct Pair
{
    TKey Key;
    TValue Value;
    Pair(TKey key, TValue value);
    Pair(u32 );
};

struct Dictionary
{
    Dictionary(u32 limit);
    Dictionary();
    void Add(TKey key, TValue value);
    void Remove(TKey key);
    TValue& Get(TKey& key);
};

struct ArrayIterator
{
    ArrayIterator(T* pointer, u32 count);
    bool IsEnd();
    T GetCurrent();
    bool Next();
};

struct Array
{
    u32 Count;
    Array();
    Array(Array& other);
    Array(Array& other);
    u32 GetCount();
    T& operator[](s32 index);
    Reference GetIterator();
};

struct ObservableList
{
    struct Change
    {
        u32 NewItemsIndex;
        Array NewItems;
        u32 OldItemsIndex;
        Array OldItems;
        Change();
    };
    Event Changed;
    void Add(T item);
    void Add(Reference items);
    void Remove(T item);
    void Clear();
};

struct Matrix4
{
    union 
    {
        struct 
        {
            float c11;
            float c12;
            float c13;
            float c14;
            float c21;
            float c22;
            float c23;
            float c24;
            float c31;
            float c32;
            float c33;
            float c34;
            float c41;
            float c42;
            float c43;
            float c44;
        };
        float* components;
    };
    Matrix4 Identity;
    Matrix4();
    Matrix4(float c11, float c12, float c13, float c14, float c21, float c22, float c23, float c24, float c31, float c32, float c33, float c34, float c41, float c42, float c43, float c44);
    Matrix4(Matrix3& matrix);
    Matrix4& Transpose();
    float Determinant();
    static Matrix4& CreateTransformation(Vector3& translation, Matrix3& rotation, Vector3& scale);
    static Matrix4& CreateView(Vector3& position, Vector3& target, Vector3& up);
    static Matrix4& CreateProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
    Matrix4& operator*(Matrix4& matrix);
};

class Application
{
public:
    void Start(String parameters);
};

class Game
{
public:
    void Initialize();
    void Load();
    void Update(u64 lastTime, u64 time);
    void Draw(u64 lastTime, u64 time);
    void Unload();
    void Start(String parameters);
};

struct LinkedList
{
    LinkedList();
    void Add(T item);
};

struct OrderedCollection
{
    class OrderedIterator
    {
    public:
        OrderedIterator(Reference list, Function& comparer);
        T GetCurrent();
        bool Next();
    };
    OrderedCollection(Reference collection, Function& comparer);
    Reference GetIterator();
};

struct Queue
{
    u32 Count;
    Queue(u32 limit);
    Queue();
    u32 GetCount();
    void Enqueue(T& item);
    T& Dequeue();
    void Clear();
};

struct Stack
{
    Stack(u32 limit);
    Stack();
    void Push(T& item);
    T& Pop();
    void Clear();
};

struct TreeNode
{
    T Element;
    TreeNode(T& element);
};

struct Tree
{
};

class Timer
{
public:
    u64 Ticks;
    static u64 Time();
    static void Sleep(u64 milliseconds);
};

class RandomStream
{
public:
    RandomStream(u32 seed);
    u32 Read(void* buffer, u32 count);
    void Write(void* buffer, u32 count);
};

class Random
{
public:
    Random();
    Random(u32 seed);
    T Generate();
};

class TimeSpan
{
public:
    bool sign;
    u32 days;
    u32 milliseconds;
    u16 Days;
    u8 Hours;
    u8 Minutes;
    u8 Seconds;
    u16 Milliseconds;
    TimeSpan(s32 milliseconds);
    TimeSpan(u16 days, u16 hours, u16 minutes, u16 seconds, u16 milliseconds);
    u16 GetDays();
    u8 GetHours();
    u8 GetMinutes();
    u8 GetSeconds();
    u16 GetMilliseconds();
    String ToString();
    TimeSpan operator-(TimeSpan& other);
};

class DateTime
{
public:
    u16 Year;
    Month Month;
    u8 Day;
    u8 Hours;
    u8 Minutes;
    u8 Seconds;
    u16 Milliseconds;
    Day DayOfWeek;
    DateTime Date;
    DateTime Time;
    String DateFormat;
    String TimeFormat;
    String DateTimeFormat;
    String LongDateFormat;
    String LongTimeFormat;
    String LongDateTimeFormat;
    DateTime Now;
    DateTime(u8 hours, u8 minutes, u8 seconds, u16 milliseconds);
    DateTime(u16 year, Month month, u8 day);
    DateTime(u16 year, Month month, u8 day, u8 hours, u8 minutes, u8 seconds, u16 milliseconds);
    u16 GetYear();
    void SetYear(u16 value);
    Month GetMonth();
    void SetMonth(Month value);
    u8 GetDay();
    void SetDay(u8 value);
    u8 GetHours();
    void SetHours(u8 value);
    u8 GetMinutes();
    void SetMinutes(u8 value);
    u8 GetSeconds();
    void SetSeconds(u8 value);
    u16 GetMilliseconds();
    void SetMilliseconds(u16 value);
    Day GetDayOfWeek();
    DateTime GetDate();
    DateTime GetTime();
    String ToString();
    String ToLongDate();
    bool operator>(DateTime& other);
    bool operator<(DateTime& other);
    bool operator==(DateTime& other);
    TimeSpan operator-(DateTime& other);
    DateTime operator+(TimeSpan& other);
};
namespace System
{
    namespace Runtime
    {
        class Type
        {
        public:
            String RawName;
            String Name;
            String FullName;
            List BaseTypes;
            static System::Runtime::Type* Get();
            static System::Runtime::Type* Get(void* pointer);
            String& GetRawName();
            String& GetName();
            String& GetFullName();
            List& GetBaseTypes();
        };
        
        class Mutex
        {
        public:
            Mutex();
            Mutex(bool locked);
            bool Lock(u32 timeout);
            void Unlock();
        };
        
        class Process
        {
        public:
            Collection& Threads;
            Collection& GetThreads();
            void Start();
            void Kill();
            static System::Runtime::Process* GetCurrent();
        };
        
        class Dispatcher
        {
        public:
            bool bufferIndex;
            List frameBuffer1;
            List frameBuffer2;
            System::Runtime::Spinlock invokeLock;
            System::Runtime::Spinlock flushLock;
            Dispatcher();
            void Invoke(Action& invokation, Args parameters);
            void Invoke(System::Runtime::Dispatcher::BaseFrame* frame);
            void Flush();
            static System::Runtime::Dispatcher* GetCurrent();
        };
        
        class Thread
        {
        public:
            u32 Id;
            String Name;
            System::Runtime::Process* Process;
            System::Runtime::Dispatcher* Dispatcher;
            System::Runtime::Process* GetProcess();
            System::Runtime::Dispatcher* GetDispatcher();
            void SetDispatcher(System::Runtime::Dispatcher* value);
            void Start();
            void Kill();
            static System::Runtime::Thread* GetCurrent();
            static System::Runtime::Thread* Create(Action& function, String& name);
            static System::Runtime::Thread* Start(Action& function, String& name);
        };
        
        class Spinlock
        {
        public:
            Spinlock();
            bool Lock(u32 timeout);
            bool TryLock();
            void Unlock();
        };
        
        class Signal
        {
        public:
            Signal();
            void Send();
            bool Wait(u32 timeout);
        };
        
        class Debugger
        {
        public:
            static void Break();
        };
        
        class Profiler
        {
        public:
            static void Trace();
            static void Trace(s8* tag);
        };
        
        enum class AccessibilityModifier
        {
            Public,
            Protected,
            Private,
            Static,
        };
        
        class Symbol
        {
        public:
            String Name;
            String GetName();
            String ToString();
        };
        
        class Constructor
        {
        public:
            static System::Runtime::Constructor* Load(void* address, String rawName);
        };
        
        enum class VirtualizationModifier
        {
            None,
            Abstract,
            Virtual,
        };
        
        class Method
        {
        public:
            static System::Runtime::Method& AddFunction(String& name, System::Runtime::Type& parent, void* );
            static System::Runtime::Method* Load(void* address, String rawName);
        };
        
        class Reflection
        {
        public:
        };
        
        class Namespace
        {
        public:
        };
        
        class Property
        {
        public:
            static System::Runtime::Property& Add(String& name, System::Runtime::Type& parent, System::Runtime::Method& getter);
            static System::Runtime::Property& AddProperty(String& name, System::Runtime::Type& parent, System::Runtime::Method& getter, System::Runtime::Method& setter);
        };
        
        class Serializer
        {
        public:
        };
        
        class Executable
        {
        public:
            System::Runtime::Process* CreateProcess();
            static System::Runtime::Executable* Load(String& path);
            static System::Runtime::Executable* Load(IO::File* file);
            static System::Runtime::Executable* Load(IO::Stream* stream);
        };
    }
    
    namespace Data
    {
        class Record
        {
        public:
            String GetString(u32 index);
            bool GetBool(u32 index);
            u8 GetU8(u32 index);
            u16 GetU16(u32 index);
            u32 GetU32(u32 index);
            u64 GetU64(u32 index);
            s8 GetS8(u32 index);
            s16 GetS16(u32 index);
            s32 GetS32(u32 index);
            s64 GetS64(u32 index);
            float GetFloat(u32 index);
            double GetDouble(u32 index);
            T Get(u32 index);
            String Get(u32 index);
            bool Get(u32 index);
            u8 Get(u32 index);
            u16 Get(u32 index);
            u32 Get(u32 index);
            u64 Get(u32 index);
            s8 Get(u32 index);
            s16 Get(u32 index);
            s32 Get(u32 index);
            s64 Get(u32 index);
            float Get(u32 index);
            double Get(u32 index);
        };
        
        class Table
        {
        public:
        };
        
        class Database
        {
        public:
            System::Data::Database* Default;
            u32 Execute(String& query);
            Reference QueryTable(String& query);
            u32 Execute(String& format, First parameter, Other parameters);
            Reference QueryTable(String& query, First parameter, Other parameters);
            Reference QueryRecord(String& query, Args parameters);
            T QueryValue(String& query, Args parameters);
        };
    }
    
    namespace IO
    {
        enum class SeekOrigin
        {
            Begin,
            Current,
            End,
        };
        
        class Stream
        {
        public:
            u64 Position;
            u64 Length;
            bool EndOfStream;
            System::IO::Stream* Null;
            u64 GetPosition();
            void SetPosition(u64 value);
            u64 GetLength();
            bool IsEndOfStream();
            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
            void Seek(u64 offset, System::IO::SeekOrigin origin);
            static ConsoleStream* GetConsoleStream();
            static System::IO::Stream* GetSerialStream();
        };
        
        class TextStream
        {
        public:
            TextStream(System::IO::Stream* baseStream);
            u64 GetPosition();
            u64 GetLength();
            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
            void Seek(u64 offset, System::IO::SeekOrigin origin);
            String Read(u32 length);
            String ReadLine();
            String ReadAll();
            void Write(String& base);
            void Write(String& base, Args parameters);
            void WriteLine();
            void WriteLine(String& base);
            void WriteLine(String& base, Args parameters);
        };
        
        class BufferStream
        {
        public:
            BufferStream(u32 limit);
            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
        };
        
        enum class FileAttributes
        {
            None,
            Hidden,
            System,
        };
        
        class File
        {
        public:
            String Path;
            String Name;
            String Extension;
            u64 Size;
            String GetPath();
            String GetName();
            String GetExtension();
            u64 GetSize();
            System::IO::Stream* GetStream();
            static System::IO::File* Open(String path);
            static System::IO::Stream* OpenStream(String path);
        };
        
        class Directory
        {
        public:
            String Name;
            System::IO::Directory* Parent;
            Reference Directories;
            Reference Files;
            String FullPath;
            System::IO::Directory* Root;
            System::IO::Directory* Current;
            String GetName();
            System::IO::Directory* GetParent();
            Reference GetDirectories();
            Reference GetFiles();
            String GetFullPath();
            void AddDirectory(System::IO::Directory* directory);
            void AddFile(System::IO::File* file);
            System::IO::Directory* GetDirectory(String& path);
            System::IO::File* GetFile(String path);
            static System::IO::Directory* Open(String& path);
            static System::IO::Directory* GetRootDirectory();
        };
        
        class FileStream
        {
        public:
        };
        
        class DirectoryLink
        {
        public:
            System::IO::Directory* Target;
            DirectoryLink(String name, System::IO::Directory* parent, System::IO::Directory* target);
            System::IO::Directory* GetTarget();
            Reference GetDirectories();
            Reference GetFiles();
            void AddDirectory(System::IO::Directory* directory);
            void AddFile(System::IO::File* file);
            System::IO::Directory* GetDirectory(String& path);
            System::IO::File* GetFile(String path);
        };
        
        struct ResourceLoaderBase
        {
            Reference LoadInternal(System::IO::File* file);
            static void Register(String& extension, ResourceLoaderBase* loader);
            static Reference Load(System::IO::File* file);
        };
        
        struct ResourceLoader
        {
            ResourceLoader(String& extension);
            Reference LoadInternal(System::IO::File* file);
        };
        
        class AsyncStream
        {
        public:
        };
        
        class DataStream
        {
        public:
            DataStream(System::IO::Stream* baseStream);
            u64 GetPosition();
            void SetPosition(u64 value);
            u64 GetLength();
            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
            T Read();
            T* Read(u32 count);
            void Read(T* buffer);
            void Write(T& value);
            u8 ReadByte();
            u8 ReadU8();
            u16 ReadU16();
            u32 ReadU32();
            u64 ReadU64();
            s8 ReadS8();
            s16 ReadS16();
            s32 ReadS32();
            s64 ReadS64();
            float ReadFloat();
            double ReadDouble();
            signed char ReadChar();
            void Write(u8 value);
            void Write(u16 value);
            void Write(u32 value);
            void Write(u64 value);
            void Write(s8 value);
            void Write(s16 value);
            void Write(s32 value);
            void Write(s64 value);
            void Write(float value);
            void Write(double value);
            String Read();
            String ReadString(u32 length);
            void Write(String& value);
        };
        
        class TeeStream
        {
        public:
            TeeStream(System::IO::Stream* stream);
            TeeStream(System::IO::Stream* stream1, System::IO::Stream* stream2);
            TeeStream(System::IO::Stream* stream1, System::IO::Stream* stream2, System::IO::Stream* stream3);
            TeeStream(System::IO::Stream* stream1, System::IO::Stream* stream2, System::IO::Stream* stream3, System::IO::Stream* stream4);
            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
        };
    }
    
    namespace Devices
    {
        class Device
        {
        public:
            bool Loaded;
            String GetVendor();
            String GetName();
            void Load();
            void Unload();
        };
        
        struct PointerEvent
        {
            u8 Index;
        };
        
        struct PointerPositionEvent
        {
            u16 X;
            u16 Y;
        };
        
        struct PointerMoveEvent
        {
            s8 X;
            s8 Y;
        };
        
        struct PointerScrollEvent
        {
            s16 Delta;
        };
        
        class PointerDevice
        {
        public:
            Event PointerMove;
            Event PointerDown;
            Event PointerUp;
            Event PointerScroll;
        };
        
        enum class Buttons
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
        };
        
        struct RawButtonEvent
        {
            System::Devices::Buttons Button;
        };
        
        struct ButtonEvent
        {
            System::Devices::Buttons Button;
            signed char Character;
        };
        
        struct ButtonsMapping
        {
            ButtonsMapping();
            System::Devices::Buttons& operator[](u8 code);
        };
        
        struct CharactersMapping
        {
            CharactersMapping();
            s8& operator[](System::Devices::Buttons button);
        };
        
        struct ButtonsState
        {
            ButtonsState();
            bool& operator[](System::Devices::Buttons button);
        };
        
        class ButtonsDevice
        {
        public:
            Event ButtonDown;
            Event ButtonUp;
        };
        
        enum class Jauges
        {
            LeftStickX,
            LeftStickY,
            RightStickX,
            RightStickY,
            LeftTrigger,
            RightTrigger,
        };
        
        struct JaugeEvent
        {
            System::Devices::Jauges Jauge;
            float Value;
        };
        
        class InputManager
        {
        public:
            Event PointerMove;
            Event PointerDown;
            Event PointerUp;
            Point2 PointerPosition;
            Event ButtonDown;
            Event ButtonUp;
            Event JaugeChange;
            static void Initialize();
            static void AddDevice(System::Devices::PointerDevice* pointer, bool );
            static void SetDefaultPointer(System::Devices::PointerDevice* pointer);
            static void AddDevice(System::Devices::ButtonsDevice* button);
            static bool IsButtonDown(System::Devices::Buttons button);
        };
        
        class DeviceEnumerator
        {
        public:
        };
        
        class CommunicationDevice
        {
        public:
            List* Streams;
            CommunicationDevice();
            List* GetStreams();
        };
        
        class NetworkDevice
        {
        public:
            NetworkDevice();
        };
        
        struct DisplayMode
        {
            u16 Id;
            u16 Width;
            u16 Height;
            u8 Bpp;
        };
        
        class DisplayOverlay
        {
        public:
            bool Visible;
            Point2 Position;
            Graphics::Bitmap* Bitmap;
            Graphics::Bitmap* GetBitmap();
            void SetBitmap(Graphics::Bitmap* surface);
        };
        
        class DisplayDevice
        {
        public:
            Graphics::Surface* Surface;
            Runtime::Signal* VSync;
            System::Devices::DisplayOverlay* Overlay;
            System::Devices::DisplayMode* DisplayMode;
            Graphics::Surface* GetSurface();
            Runtime::Signal* GetVSync();
            System::Devices::DisplayOverlay* GetOverlay();
            System::Devices::DisplayMode* FindDisplayMode(u16 width, u16 height, u8 bpp, bool exact);
            System::Devices::DisplayMode* GetDisplayMode();
            void SetDisplayMode(System::Devices::DisplayMode* displayMode);
            void Update();
            void Update(u16 x, u16 y, u16 width, u16 height);
        };
        
        enum class InputType
        {
            Button,
            Pointer,
            Stick,
        };
        
        enum class InputDeviceType
        {
            Keyboard,
            Mouse,
            Touch,
            Pad,
        };
        
        class InputDevice
        {
        public:
        };
        
        class StorageDevice
        {
        public:
            List* FileSystems;
            StorageDevice();
            List* GetFileSystems();
            u32 Read(void* buffer, u64 position, u32 count);
            void Write(void* source, u64 position, u32 count);
        };
        
        class FileSystem
        {
        public:
            IO::Directory* Root;
            String Name;
            IO::Directory* GetRoot();
            String GetName();
            static void Register(System::Devices::FileSystemType type);
            static System::Devices::FileSystem* Create(System::Devices::FileSystemType type, System::Devices::StorageDevice* device, u64 position);
            u32 Read(s8* buffer, u32 offset, u64 position, u32 count);
            void Write(s8* source, u32 offset, u64 position, u32 count);
        };
        
        struct FileSystemConstructorBase
        {
            System::Devices::FileSystem* operator()(System::Devices::StorageDevice* device, u64 position);
        };
        
        struct FileSystemConstructor
        {
            System::Devices::FileSystem* operator()(System::Devices::StorageDevice* device, u64 position);
        };
        
        enum class FileSystemType
        {
            None,
            Fat16,
            ExFat,
            Fat32,
        };
    }
    
    namespace Graphics
    {
        struct Point
        {
            Units::Size::Units Unit;
            Point();
            Point(Point2 point, Units::Size::Units unit);
            Point(s32 x, s32 y, Units::Size::Units unit);
        };
        
        struct Rectangle
        {
            System::Graphics::Point Position;
            System::Graphics::Point Size;
            Rectangle();
            Rectangle(System::Graphics::Point position, System::Graphics::Point size);
            Rectangle(s32 x, s32 y, u32 w, u32 h);
            Rectangle(s32 x, s32 y, u32 w, u32 h, Units::Size::Units unit);
            bool operator==(System::Graphics::Rectangle& rectangle);
            System::Graphics::Rectangle Expand(s32 size);
        };
        
        struct Outline
        {
            u32 Top;
            u32 Right;
            u32 Bottom;
            u32 Left;
            Outline();
            Outline(System::Graphics::Outline& outline);
            Outline(u32 value);
            Outline(u32 top, u32 right, u32 bottom, u32 left);
            bool operator==(System::Graphics::Outline& outline);
        };
        
        enum class Alignment
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
        };
        
        enum class Orientation
        {
            LeftToRight,
            RightToLeft,
            TopToBottom,
            BottomToTop,
            Horizontal,
            Vertical,
        };
        
        enum class Direction
        {
            Left,
            Up,
            Right,
            Down,
        };
        
        struct BitmapLoaderBase
        {
        };
        
        class Bitmap
        {
        public:
            void* Data;
            Point2 Size;
            Bitmap();
            Bitmap(void* data, u16 width, u16 height, u16 padding);
            Bitmap(void* data, Point2 size, u16 padding);
            void* GetData();
            static Reference Load(IO::Stream* stream);
            static Reference Load(IO::File* file);
            static Reference Load(String& path);
            String ToString();
        };
        
        struct Bitmaps
        {
            struct Cursors
            {
                Dynamic Normal;
            };
            
            struct Icons
            {
                Dynamic Close;
                Dynamic Plus;
                Dynamic Up;
                Dynamic Right;
                Dynamic Down;
                Dynamic Left;
            };
        };
        
        class Font
        {
        public:
            Reference Family;
            u8 Size;
            System::Graphics::FontAttribute Attributes;
            Reference GetFamily();
            u8 GetSize();
            System::Graphics::FontAttribute GetAttributes();
            void Draw(s32* surface, String& text, Point2 position, Color32 color, System::Graphics::Alignment alignment);
            void Draw(s32* surface, String& text, u16 x, u16 y, Color32 color, System::Graphics::Alignment alignment);
            Point2 Measure(String& text);
            Point2 Measure(signed char character);
        };
        
        enum class FontType
        {
            None,
            Serif,
            Monospace,
        };
        
        enum class FontAttribute
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
        };
        
        class FontFamily
        {
        public:
            String Name;
            System::Graphics::FontType Type;
            String GetName();
            System::Graphics::FontType GetType();
            Reference GetFont(u8 size, System::Graphics::FontAttribute attributes);
            static Reference Load(IO::Stream* stream);
            static Reference Load(String& path);
            static Reference Load(IO::File* file);
            static Reference GetFamily(String& name);
            static Reference GetDefaultFamily(System::Graphics::FontType type);
        };
        
        class Surface
        {
        public:
            Surface(void* data, u16 width, u16 height, u16 padding);
            Surface(void* data, Point2 size, u16 padding);
            Surface(u16 width, u16 height);
            Surface(Point2 size);
            void Clear(Color32 color);
            void Resize(Point2 size);
            void DrawPoint(s16 x, s16 y, Color32 color);
            void DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased);
            void DrawRectangle(Point2 position, Point2 size, Color32 color);
            void DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);
            void FillRectangle(Point2 position, Point2 size, Color32 color);
            void FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);
            void DrawBitmap(System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(Point2 position, System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(s16 x, s16 y, System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(Point2 source, Point2 destination, Point2 size, System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(Point2 source, Point2 destination, Point2 size, System::Graphics::Bitmap* bitmap, Color32 color);
            void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, System::Graphics::Bitmap* bitmap, Color32 color);
            void DrawText(String& text, Reference font, Point2 position, Color32 color, System::Graphics::Alignment alignment);
            void DrawText(String& text, Reference font, s16 x, s16 y, Color32 color, System::Graphics::Alignment alignment);
            void Darken(s16 x, s16 y, u16 width, u16 height, u16 multiplier, u16 divisor);
        };
        
        class SubSurface
        {
        public:
            SubSurface(System::Graphics::Surface* surface, s16 x, s16 y, u16 width, u16 height);
            SubSurface(System::Graphics::Surface* surface, Point2 position, Point2 size);
            void Resize(Point2 newSize);
        };
        
        class ShiftedSurface
        {
        public:
            ShiftedSurface(System::Graphics::Surface* surface, s16 x, s16 y);
            ShiftedSurface(System::Graphics::Surface* surface, Point2 position);
            void DrawPoint(s16 x, s16 y, Color32 color);
            void DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased);
            void DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);
            void FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);
            void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, System::Graphics::Bitmap* bitmap, bool alpha);
            void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, System::Graphics::Bitmap* bitmap, Color32 color);
            void DrawText(String& text, Reference font, s16 x, s16 y, Color32 color, System::Graphics::Alignment alignment);
        };
    }
    
    namespace Interface
    {
        enum class DockStyle
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
        };
        
        class Element
        {
        public:
            bool pointed;
            ChangeEvent PositionChanged;
            Graphics::Point Position;
            ChangeEvent SizeChanged;
            Graphics::Point Size;
            ChangeEvent EnabledChanged;
            bool Enabled;
            ChangeEvent VisibleChanged;
            bool Visible;
            ChangeEvent BackColorChanged;
            Color32 BackColor;
            ChangeEvent DockChanged;
            System::Interface::DockStyle Dock;
            ChangeEvent MarginChanged;
            Graphics::Outline Margin;
            void* Tag;
            Event PointerMove;
            Event PointerScroll;
            Event PointerIn;
            Event PointerOut;
            Event PointerDown;
            Event PointerUp;
            Event ButtonDown;
            Event ButtonUp;
            Element();
            Element();
            void* GetTag();
            void SetTag(void* value);
        };
        
        class Control
        {
        public:
            Graphics::Surface* Surface;
            Event Redrawn;
            Control();
            Control(u16 width, u16 height);
            Control(Graphics::Point size);
            Control();
            Graphics::Surface* GetSurface();
            void SetSize(Graphics::Point value);
            void Redraw();
        };
        
        class Container
        {
        public:
            ChangeEvent BorderChanged;
            Graphics::Outline Border;
            Color32 BorderColor;
            Pointer Containers;
            Pointer Controls;
            Event Refreshed;
            void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent);
            void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerScroll(void* origin, Devices::PointerScrollEvent pointerScrollEvent);
            void OnButtonDown(void* origin, Devices::ButtonEvent buttonEvent);
            void OnButtonUp(void* origin, Devices::ButtonEvent buttonEvent);
            void Container_Refreshed(void* container, Graphics::Rectangle rectangle);
            void Control_Redrawn(void* control, Graphics::Rectangle rectangle);
            Container();
            Color32 GetBorderColor();
            void SetBorderColor(Color32 value);
            void SetSize(Graphics::Point value);
            void SetBackColor(Color32 value);
            void Add(System::Interface::Container* container);
            void Add(System::Interface::Control* control);
            void Remove(System::Interface::Container* container);
            void Remove(System::Interface::Control* control);
            void Clear();
            void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
        };
        
        class Window
        {
        public:
            Graphics::Surface* cachedSurface;
            String Title;
            System::Interface::WindowState State;
            System::Interface::WindowLayer Layer;
            Event StateChanged;
            Event LayerChanged;
            Event Closed;
            Window(String& title, bool buttons, bool moveable);
            void Initialize();
            String GetTitle();
            void SetTitle(String& value);
            System::Interface::WindowState GetState();
            void SetState(System::Interface::WindowState value);
            System::Interface::WindowLayer GetLayer();
            void SetLayer(System::Interface::WindowLayer value);
            void SetBackColor(Color32 value);
        };
        
        class Mover
        {
        public:
            Mover(System::Interface::Window* window);
            void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent);
            void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent);
            void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent);
        };
        
        class Tab
        {
        public:
            String Title;
            Tab(String& title);
            String& GetTitle();
            void SetTitle(String& value);
        };
        
        enum class ButtonStyle
        {
            None,
            Text,
            Image,
        };
        
        enum class ButtonState
        {
            Idle,
            Over,
            Down,
        };
        
        class Button
        {
        public:
            ChangeEvent ImageChanged;
            Reference Image;
            ChangeEvent TextChanged;
            String Text;
            ChangeEvent FontChanged;
            Reference Font;
            ChangeEvent StyleChanged;
            System::Interface::ButtonStyle Style;
            ChangeEvent BorderChanged;
            Graphics::Outline Border;
            Graphics::Alignment Alignment;
            Graphics::Outline Padding;
            Color32 Color;
            Color32 BorderColor;
            Color32 OverColor;
            Color32 DownColor;
            Button(String& text);
            Button(Reference& bitmap);
            void SetBackColor(Color32 value);
            void Redraw();
        };
        
        enum class WindowState
        {
            Normal,
            Maximized,
            Hidden,
            Docked,
        };
        
        enum class WindowLayer
        {
            Bottom,
            Normal,
            Top,
        };
        
        class WindowsManager
        {
        public:
            static void Initialize();
            static void Add(System::Interface::Window* window);
            static void Remove(System::Interface::Window* window);
        };
        
        class ScrollContainer
        {
        public:
            ScrollContainer();
            void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent);
            void OnPointerScroll(void* origin, Devices::PointerScrollEvent pointerScrollEvent);
            void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
            void Add(System::Interface::Container* container);
            void Add(System::Interface::Control* control);
            void Remove(System::Interface::Container* container);
            void Remove(System::Interface::Control* control);
        };
        
        class Label
        {
        public:
            Color32 Color;
            String Text;
            Reference Font;
            bool AutoSize;
            Graphics::Alignment Alignment;
            Label();
            Label(String text);
            Color32 GetColor();
            void SetColor(Color32 value);
            String GetText();
            void SetText(String value);
            Reference GetFont();
            void SetFont(Reference value);
            bool GetAutoSize();
            void SetAutoSize(bool value);
            Graphics::Alignment GetAlignment();
            void SetAlignment(Graphics::Alignment value);
            void SetBackColor(Color32 value);
            void SetSize(Graphics::Point value);
            void Redraw();
        };
        
        enum class ColumnWidthType
        {
            Absolute,
            Relative,
            Fill,
        };
        
        class Grid
        {
        public:
            class Column
            {
            public:
                String Title;
                System::Interface::Grid::ColumnWidth Width;
                Reference Cells;
                Column(System::Interface::Grid* grid);
                Column(System::Interface::Grid* grid, String& title);
                Column(System::Interface::Grid* grid, String& title, System::Interface::Grid::ColumnWidth width);
                Column(System::Interface::Grid* grid, String& title, Graphics::Alignment alignment);
                Column(System::Interface::Grid* grid, String& title, System::Interface::Grid::ColumnWidth width, Graphics::Alignment alignment);
                String GetTitle();
                void SetTitle(String& value);
                System::Interface::Grid::ColumnWidth GetWidth();
                void SetWidth(System::Interface::Grid::ColumnWidth value);
                System::Interface::Grid::Cell* AddCell();
                System::Interface::Grid::Cell* AddCell(String& title);
                System::Interface::Grid::Cell* AddCell(System::Interface::Grid::Cell* cell);
            };
            
            struct ColumnWidth
            {
                u32 Size;
                System::Interface::ColumnWidthType Type;
                ColumnWidth();
                ColumnWidth(u32 size);
                ColumnWidth(u32 size, System::Interface::ColumnWidthType type);
                ColumnWidth(System::Interface::ColumnWidthType type);
            };
            
            class Cell
            {
            public:
                System::Interface::Control* Control;
                Graphics::Alignment Alignment;
                Cell(System::Interface::Grid::Column* column, u32 row);
                Cell(System::Interface::Grid::Column* column, u32 row, String& text);
                Cell(System::Interface::Grid::Column* column, u32 row, System::Interface::Control* control);
                Interface::Control* GetControl();
                void SetControl(Interface::Control* value);
                Graphics::Alignment GetAlignment();
                void SetAlignment(Graphics::Alignment value);
                void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
            };
            
            class Row
            {
            public:
            };
            List Columns;
            bool ShowHeaders;
            Reference Font;
            Color24 AlternateBackColor;
            bool AutoSize;
            Grid();
            List& GetColumns();
            bool GetShowHeaders();
            bool SetShowHeaders(bool value);
            Reference GetFont();
            void SetFont(Reference value);
            Color24& GetAlternateBackColor();
            Color24& SetAlternateBackColor(Color24& value);
            void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
            void Clear();
            void UpdateSize();
            System::Interface::Grid::Column* AddColumn();
            System::Interface::Grid::Column* AddColumn(System::Interface::Grid::Column* column);
            System::Interface::Grid::Column* AddColumn(String& title);
            System::Interface::Grid::Column* AddColumn(String& title, System::Interface::Grid::ColumnWidth width);
            System::Interface::Grid::Column* AddColumn(String& title, Graphics::Alignment alignment);
            System::Interface::Grid::Column* AddColumn(String& title, System::Interface::Grid::ColumnWidth width, Graphics::Alignment alignment);
            System::Interface::Grid::Row* AddRow();
            System::Interface::Grid::Row* AddRow(System::Interface::Grid::Row* row);
            System::Interface::Grid::Row* AddRow(System::Interface::Control* control1, System::Interface::Control* control2, System::Interface::Control* control3, System::Interface::Control* control4, System::Interface::Control* control5, System::Interface::Control* control6, System::Interface::Control* control7, System::Interface::Control* control8);
            System::Interface::Grid::Row* AddRow(String& value1, String& value2, String& value3, String& value4, String& value5, String& value6, String& value7, String& value8);
        };
        
        class StackContainer
        {
        public:
            Graphics::Orientation Orientation;
            bool AutoSize;
            Graphics::Outline Padding;
            Pointer Elements;
            StackContainer();
            void Add(System::Interface::Container* container);
            void Add(System::Interface::Control* control);
            void Remove(System::Interface::Container* container);
            void Remove(System::Interface::Control* control);
            void Clear();
        };
        
        class TabContainer
        {
        public:
            System::Interface::Tab* CurrentTab;
            Graphics::Orientation Orientation;
            TabContainer();
            System::Interface::Tab* GetCurrentTab();
            void SetCurrentTab(System::Interface::Tab* value);
            void Add(System::Interface::Tab* tab);
            void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
        };
        
        class Table
        {
        public:
        };
        
        class Graph
        {
        public:
            class Curve
            {
            public:
                Color24 Color;
                s32* Values;
                Curve(System::Interface::Graph* graph);
                void AddValue(s32 value);
                void Clear(s32 value);
            };
            u16 SegmentSize;
            Graphics::Point GridSize;
            u16 GridShift;
            bool FillBelow;
            Graph();
            u16 GetSegmentSize();
            u16& SetSegmentSize(u16 value);
            Graphics::Point GetGridSize();
            Graphics::Point& SetGridSize(Graphics::Point value);
            u16 GetGridShift();
            u16& SetGridShift(u16 value);
            bool GetFillBelow();
            bool& SetFillBelow(bool value);
            System::Interface::Graph::Curve* AddCurve(Color24 color);
            void Redraw();
            void Redraw(bool fullRedraw);
        };
        
        class Image
        {
        public:
            Color32 Color;
            Image(Reference bitmap);
            Image(u16 width, u16 height);
            Color32 GetColor();
            void SetColor(Color32 value);
            void SetBackColor(Color32 value);
            void Redraw();
        };
        
        class ListViewItem
        {
        public:
        };
        
        class ListView
        {
        public:
        };
        
        class Menu
        {
        public:
            class Item
            {
            public:
                Item(String& text);
            };
            Menu();
            void Add(System::Interface::Menu::Item* item);
        };
        
        enum class TextStyle
        {
            Normal,
            Bold,
            Italic,
            Strike,
            Underline,
        };
        
        class TextBox
        {
        public:
            typedef ... character;
            
            typedef ... TextPoint;
            
            struct TextSpan
            {
                u32 Begin;
                u32 End;
                u32 First();
                u32 Last();
                bool Empty();
                u32 Length();
            };
            
            struct TextSelection
            {
                s8** Buffer;
                u32 LastColumn;
            };
            
            struct TextBlock
            {
                Color32 Color;
                System::Interface::TextStyle Style;
                System::Interface::TextBox::TextBlock* Previous;
                System::Interface::TextBox::TextBlock* Next;
            };
            
            struct TextSquareSelection
            {
                Point2 Position;
                Point2 Size;
                Point2 First();
                Point2 Last();
            };
            String Text;
            ChangeEvent TextChanged;
            Reference Font;
            ChangeEvent FontChanged;
            bool ReadOnly;
            bool MultiLine;
            Color32 BackColor;
            Color32 SelectionColor;
            List Selections;
            TextBox();
            String GetText();
            void SetText(String value);
            Reference GetFont();
            void SetFont(Reference value);
            bool GetReadOnly();
            void SetReadOnly(bool value);
            bool GetMultiLine();
            void SetMultiLine(bool value);
            Color32 GetBackColor();
            void SetBackColor(Color32 value);
            Color32 GetSelectionColor();
            void SetSelectionColor(Color32 value);
            List& GetSelections();
            void Redraw();
            u32 GetIndexAtPosition(Point2 position);
            u32 GetIndexAtView(Point2 view);
            Point2 GetViewAtIndex(u32 index);
        };
    }
    
    namespace Objects
    {
        class Entity
        {
        public:
            u32 Id;
            Entity();
            u32 GetId();
        };
        
        class User
        {
        public:
            String Name;
            User(String name);
            String GetName();
        };
    }
}
namespace Types
{
    struct If
    {
    };
    
    struct Equals
    {
        enum class 
        {
            Value,
        };
    };
    
    struct Nth
    {
    };
    
    struct SizeOf
    {
        enum class 
        {
            Value,
        };
    };
    
    struct Count
    {
        enum class 
        {
            Value,
        };
    };
}
namespace Values
{
    struct If
    {
        enum class 
        {
            Value,
        };
    };
    
    struct Min
    {
        enum class 
        {
            Condition,
            Value,
        };
    };
    
    struct Max
    {
        enum class 
        {
            Condition,
            Value,
        };
    };
}
namespace std
{
    struct initializer_list
    {
        class InitializerCollectionIterator
        {
        public:
            InitializerCollectionIterator(T* first, T* last);
            bool IsEnd();
            T GetCurrent();
            bool Next();
        };
        initializer_list(T* first, T* last);
        T* begin();
        T* end();
        Reference GetIterator();
    };
}
namespace Colors
{
    struct System
    {
        Color24 Color;
        Color24 ActiveBackground;
        Color24 InactiveBackground;
        Color24 Border;
        Color24 Menu;
        Color24 ActiveTab;
        Color24 InactiveTab;
        Color24 ActiveSubtab;
        Color24 InactiveSubtab;
    };
}
