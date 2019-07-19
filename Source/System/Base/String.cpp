#include <System/Base/String.h>

#include <System/Memory/Memory.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Log.h>

#include <System/Runtime/Debugging/Debugger.h>
#include <System/Runtime/Debugging/Profiler.h>

static char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

using namespace System::Runtime;

constexpr u32 len(const char* text)
{
    return *text ? 1 + len(text + 1) : 0;
}
void String::Load(String& other)
{
    value = other.value;
    other.value = 0;
}
#define ctor(...) Load(String(__VA_ARGS__))
#define up(c) ((c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c)
#define low(c) ((c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c)

// Static
String String::Null;
String String::Empty = "";
String String::NewLine = "\r\n";
String String::Separator = "/";

// Constructors
String::String() : value(0), allocated(false)
{
}
String::String(char* pointer, u32 length, bool copy) : value(0), allocated(copy), length(length)
{
    if (copy)
    {
        this->pointer = new char[length];
        Memory::Copy(pointer, this->pointer, length);
    }
    else
        this->pointer = pointer;
}
String::String(const String& other) : value(0), allocated(true), length(other.length)
{
    pointer = new char[length];
    Memory::Copy(other.pointer, pointer, length);
}
String::~String()
{
    if (allocated)// && !embedded)
        delete[] pointer;
}

// Converters
String::String(char* other) : value(0), allocated(true)
{
    length = len(other);
    pointer = new char[length];
    Memory::Copy(other, pointer, length);
}
String::String(const char* other) : value(0), allocated(false), length(len(other)), pointer((char*)other)
{
}
String::String(char value, u32 count) : value(0), allocated(true), length(count)
{
    pointer = new char[length];
    Memory::Clear(pointer, length, value);
}
String::String(s32 value, u8 base, u8 length) : value(0), allocated(true)
{
    if (base < 2 || base > 16)
    {
        length = 0;
        return;
    }

    char result[34];
    s8 i = 0;
    bool sign = value >= 0;

    if (value < 0) value = -value;
    if (!length) length = 1;

    for (; value; i++)
    {
        result[i] = digits[value % base];
        value /= base;
    }

    while (i < length)
        result[i++] = '0';
    if (!sign)
        result[i++] = '-';
    this->length = i;

    pointer = new char[i];
    while (i--)
        pointer[i] = result[this->length - 1 - i];
}
String::String(u32 value, const String& format) : value(0), allocated(true)
{
    u32 length = 1;

    if (format.length == 2)
    {
        length = format[1] - '0';
        Exception::Assert(length > 0 && length <= 9, "String::String(u32 value, const String& format)");
    }
    else if (format.length > 2)
        Exception::Assert("String::String(u32 value, const String& format)");

    switch (format[0])
    {
        case 'x': ctor(value, 16, length); return;
        case 'X': ctor(value, 16, length); return;
        case 'd':
        case 'D': ctor(value, 10, length); return;
        case 'o':
        case 'O': ctor(value, 8, length); return;
        case 'b':
        case 'B': ctor(value, 2, length); return;
    }

    Exception::Assert("String::String(u32 value, const String& format) : Unrecognized format");
}
String::String(u32 value, u8 base, u8 length) : value(0), allocated(true)
{
    if (base < 2 || base > 16)
    {
        length = 0;
        return;
    }

    char result[34];
    s8 i = 0;

    if (!length) length = 1;

    for (; value; i++)
    {
        result[i] = digits[value % base];
        value /= base;
    }

    while (i < length)
        result[i++] = '0';
    this->length = i;

    pointer = new char[i];
    while (i--)
        pointer[i] = result[this->length - 1 - i];
}
String::String(s64 value, u8 base, u8 length) : value(0), allocated(true)
{
    /*if (base < 2 || base > 16)
    {
        length = 0;
        return;
    }

    char result[66];
    s8 i = 0;
    bool sign = value >= 0;

    if (value < 0) value = -value;
    if (!length) length = 1;

    for (; value; i++)
    {
        result[i] = digits[value % base];
        value /= base;
    }

    while (i < length)
        result[i++] = '0';
    if (!sign)
        result[i++] = '-';
    this->length = i;

    pointer = new char[i];
    while (i--)
        pointer[i] = result[this->length - 1 - i];*/
}
String::String(u64 value, u8 base, u8 length) : value(0), allocated(true)
{
    /*if (base < 2 || base > 16)
    {
        length = 0;
        return;
    }

    char result[66];
    s8 i = 0;

    if (!length) length = 1;

    for (; value; i++)
    {
        result[i] = digits[value % base];
        value /= base;
    }

    while (i < length)
        result[i++] = '0';
    this->length = i;

    pointer = new char[i + 1];
    while (i--)
        pointer[i] = result[this->length - 1 - i];*/
}
String::String(bool value) : value(0), allocated(true)// : value(value ? 0x4100000065757274 : 0x51000065736c6166)
{
    // true: 74 72 75 65
    // false: 66 61 6c 73 65

    length = value ? 4 : 5;
    pointer = new char[length];
    Memory::Copy(value ? "true" : "false", pointer, value ? 4 : 5);
}
String::String(float value, u8 digits, bool strip) : value(0), allocated(true)
{
    char integerChars[16];
    char decimalChars[16];

    Exception::Assert(digits <= sizeof(decimalChars), "Too many digits for a floating point number");
        
    u32 integer = (u32)value;
    s8 i = 0;
    for (; integer; i++)
    {
        integerChars[i] = '0' + (integer % 10);
        integer /= 10;
    }

    u8 decimal;
    u8 d = 0;
    for (; d < digits; d++)
    {
        value *= 10.f;
        decimal = (u32)value % 10;
        decimalChars[d] = '0' + decimal;
    }

    bool sign = value >= 0;
    
    if (strip)
        for (; d > 0 && decimalChars[d - 1] == '0'; d--);

    length = !sign + i + !!d + d;
    pointer = new char[length];

    u8 r = 0;

    if (value < 0)
        pointer[r++] = '-';
    
    for (; i > 0; i--)
        pointer[r++] = integerChars[i - 1];
    if (!d)
        return;

    pointer[r++] = '.';
    for (i = 0; i <= d; i++)
        pointer[r++] = decimalChars[i];
}
String::String(double value) : value(0), allocated(true)
{
    Exception::NotImplemented();
}
String::String(void* pointer) : value(0), allocated(true), length(10)
{
    u32 value = (u32)pointer;

    this->pointer = new char[10];
    this->pointer[0] = '0';
    this->pointer[1] = 'x';
    this->pointer[2] = digits[value >> 28];
    this->pointer[3] = digits[(value >> 24) & 0xF];
    this->pointer[4] = digits[(value >> 20) & 0xF];
    this->pointer[5] = digits[(value >> 16) & 0xF];
    this->pointer[6] = digits[(value >> 12) & 0xF];
    this->pointer[7] = digits[(value >> 8) & 0xF];
    this->pointer[8] = digits[(value >> 4) & 0xF];
    this->pointer[9] = digits[value & 0xF];
}
String::String(void* pointer, const String& format)
{
    ctor((u32)pointer, format);
}
String::String(Object& other)
{
    ctor(other.ToString());
}
String::String(Object& other, const String& format)
{
    ctor(other.ToString(), format);
}
String::String(Object* other)
{
    ctor(other->ToString());
}
String::String(Object* other, const String& format)
{
    ctor(other->ToString(), format);
}
String::String(const String& other, const String& format)
{
    if (format.Length == 1)
    {
        switch (format[0])
        {
            case 'l': ctor(other.ToLower()); return;
            case 'u': ctor(other.ToUpper()); return;
            case 'w': ctor(other.ToCasing(Casing::Words)); return;
            case 's': ctor(other.ToCasing(Casing::Sentence)); return;
        }
    }

    ctor(other);
}

String& String::operator=(const String& other)
{
    delete[] pointer;

    length = other.length;
    pointer = new char[length];
    Memory::Copy(other.pointer, pointer, length);

    return *this;
}
String& String::operator=(String&& other)
{
    length = other.length;
    pointer = other.pointer;

    other.pointer = null;

    return *this;
}

// Accessors
char& String::operator[](s32 index) const
{
    if (index < 0)
        index = Length + index;
    Exception::Assert(index >= 0 && (u32)index < Length, "String::operator[] : Out of bounds");

    return Buffer[index];
}

// String methods
String String::After(const String& other) const
{
    s32 index = IndexOf(other);

    if (index < 0)
        return *this;
    else
        return SubString(index);
}
String String::AfterLast(const String& other) const
{
    s32 index = IndexOfLast(other);

    if (index < 0)
        return *this;
    else
        return SubString(index);
}
String String::Before(const String& other) const
{
    s32 index = IndexOf(other);

    if (index < 0)
        return *this;
    else
        return SubString(0, index);
}
String String::BeforeLast(const String& other) const
{
    s32 index = IndexOfLast(other);

    if (index < 0)
        return *this;
    else
        return SubString(0, index);
}
bool String::Contains(const String& other) const
{
    return IndexOf(other) >= 0;
}
s32 String::IndexOf(const String& other, u32 from) const
{
    if (other.length > length)
        return -1;

    u16 i = from;
    for (; i <= length - other.length; i++)
        if (Memory::Compare(pointer + i, other.pointer, other.length))
            return i;

    return -1;
}
s32 String::IndexOfLast(const String& other, u32 from) const
{
    if (other.length > length)
        return -1;

    u32 i = length - other.length - 1;
    for (; i > from; i--)
        if (Memory::Compare(pointer + i, other.pointer, other.length))
            return i;

    return -1;
}

// Methods with chars
String String::After(char character) const
{
    s32 index = IndexOf(character);

    if (index < 0)
        return *this;
    else
        return SubString(index + 1);
}
String String::AfterLast(char character) const
{
    s32 index = IndexOfLast(character);

    if (index < 0)
        return *this;
    else
        return SubString(index + 1);
}
String String::Before(char character) const
{
    s32 index = IndexOf(character);

    if (index < 0)
        return *this;
    else
        return SubString(0, index);
}
String String::BeforeLast(char character) const
{
    s32 index = IndexOfLast(character);

    if (index < 0)
        return *this;
    else
        return SubString(0, index);
}
bool String::Contains(char character) const
{
    return IndexOf(character) >= 0;
}
s32 String::IndexOf(char character, u32 from) const
{
    for (u32 i = from; i < length; i++)
        if (pointer[i] == character)
            return i;
    return -1;
}
s32 String::IndexOfLast(char character, u32 from) const
{
    for (u32 i = length - 1; i > from; i--)
        if (pointer[i] == character)
            return i;
    return -1;
}

// Other methods
String String::Replace(const String& value, const String& replacement, u32 count) const
{
    Exception::Assert(count < 10, "String::Replace() : Unable to replace more than 10 items");

    if (value.length > length)
        return *this;

    u32 positions[10],
           index = 0;

    for (u32 i = 0; i < length - value.length && index < count; i++)
        if (Memory::Compare(pointer + i, value.pointer, value.length))
        {
            positions[index] = i;
            index++;
        }

    if (!index)
        return *this;

    String result;
    result.length = length - index * value.length + index * replacement.length;
    result.pointer = new char[result.length];

    u32 lastSource = 0,
           lastDestination = 0;

    for (u32 i = 0; i < index; i++)
    {
        u32 source = positions[i],
               destination = positions[i] - i * value.length + i * replacement.length;

        Memory::Copy(pointer + lastSource, result.pointer + lastDestination, source - lastSource);
        Memory::Copy(replacement.pointer, result.pointer + destination, replacement.length);

        lastSource = source;
        lastDestination = destination;
    }
    
    Memory::Copy(pointer + lastSource, result.pointer + lastDestination, length - lastSource);

    return result;
}
String String::SubString(s32 position) const
{
    if (position < 0)
        position = length - position;
    if (position < 0 || position >= length)
        Exception::Assert("String::SubString() : Position out of bounds");

    return String(pointer + position, length - position, allocated);
}
String String::SubString(s32 position, s32 length) const
{
    if (position < 0)
        position = this->length + position;
    if (length < 0)
        length = this->length + length - position;
    if (position < 0 || position + length > this->length)
        Exception::Assert("String::SubString() : Position out of bounds");

    return String(pointer + position, length, allocated);
}
String String::ToLower() const
{
    String result = *this;
    
    for (u32 i = 0; i < result.length; i++)
        result.pointer[i] = low(result.pointer[i]);

    return result;
}
String String::ToUpper() const
{
    String result = *this;
    
    for (u32 i = 0; i < result.length; i++)
        result.pointer[i] = up(result.pointer[i]);

    return result;
}
String String::ToCasing(Casing casing) const
{
    String result = *this;

    bool upper = Flag::Test(casing, Casing::Upper);
    bool lower = Flag::Test(casing, Casing::Lower);
    bool wordsUpper = upper || Flag::Test(casing, Casing::WordsUpper);
    bool firstUpper = wordsUpper || Flag::Test(casing, Casing::FirstUpper);
    
    bool newWord = true;
    for (u32 i = 0; i < result.length; i++)
    {
        char& c = result[i];

        if ((!i && firstUpper) || (newWord && wordsUpper) || upper)
            c = up(c);
        else if (lower)
            c = low(c);

        newWord = c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    return result;
}
String String::Trim(const String& characters) const
{
    return TrimLeft(characters).TrimRight(characters);
}
String String::TrimLeft(const String& characters) const
{
    if (!characters.length)
        return *this;

    u32 count = 0;
    for (u32 i = 0; i < length; i++)
    {
        bool found = false;
        for (u32 j = 0; j < characters.length; j++)
            if (pointer[i] == characters.pointer[j])
            {
                found = true;
                break;
            }

        if (!found)
            break;
        count++;
    }

    return SubString(count);
}
String String::TrimRight(const String& characters) const
{
    if (!characters.length)
        return *this;

    u32 count = 0;
    for (u32 i = length - 1; i >= 0; i--)
    {
        bool found = false;
        for (u32 j = 0; j < characters.length; j++)
            if (pointer[i] == characters.pointer[j])
            {
                found = true;
                break;
            }

        if (!found)
            break;
        count++;
    }

    return SubString(0, characters.length - count);
}

// Operators
bool String::operator!=(const String& other) const
{
    if (length != other.length)
        return true;

    return !Memory::Compare(pointer, other.pointer, length);
}
bool String::operator!=(char* other) const
{
    u32 l = len(other);
    if (length != l)
        return true;

    return !Memory::Compare(pointer, other, length);
}
bool String::operator==(const String& other) const
{
    if (length != other.length)
        return false;

    return Memory::Compare(pointer, other.pointer, length);
}
bool String::operator==(char* other) const
{
    if (!other)
        return false;

    u32 l = len(other);
    if (length != l)
        return false;

    return Memory::Compare(pointer, other, length);
}
String String::operator+(String& other) const
{
    String result;
    result.length = length + other.length;
    result.pointer = new char[result.length];

    Memory::Copy(pointer, result.pointer, result.length);
    Memory::Copy(other.pointer, result.pointer + length, other.length);

    return result;
}
String String::operator+(char* other) const
{
    u32 otherLength = len(other);

    String result;
    result.length = length + otherLength;
    result.pointer = new char[result.length];

    Memory::Copy(pointer, result.pointer, length);
    Memory::Copy(other, result.pointer + length, otherLength);

    return result;
}
String String::operator+(bool value) const
{
    return operator+(String(value));
}
String String::operator+(char value) const
{
    String result;
    result.length = length + 1;
    result.pointer = new char[result.length];

    Memory::Copy(pointer, result.pointer, result.length);
    result.pointer[result.length - 1] = value;

    return result;
}
String String::operator+(void* pointer) const
{
    return operator+(String(pointer));
}
String String::operator+(s32 value) const
{
    return operator+(String(value));
}
String String::operator+(u32 value) const
{
    return operator+(String(value));
}
String String::operator+(s64 value) const
{
    return operator+(String(value));
}
String String::operator+(u64 value) const
{
    return operator+(String(value));
}
String String::operator+(float value) const
{
    return operator+(String(value));
}
String String::operator+(double value) const
{
    return operator+(String(value));
}
String operator+(char* value1, const String& value2)
{
    u32 otherLength = len(value1);

    String result;
    result.length = otherLength + value2.length;
    result.pointer = new char[result.length];

    Memory::Copy(value1, result.pointer, otherLength);
    Memory::Copy(value2.pointer, result.pointer + otherLength, value2.length);

    return result;
}

// Converters
bool String::ToBool()
{
    if (*this == "0")
        return false;
    else if (*this == "1")
        return true;
    else if (*this == "true")
        return true;
    else if (*this == "false")
        return false;

    return false;
}
u32 String::ToUnsigned(u32 base)
{
    for (u32 i = 0; i < length; i++)
        Exception::Assert((pointer[i] >= '0' && pointer[i] <= '9') || (pointer[i] >= 'a' && pointer[i] <= 'f') || (pointer[i] >= 'A' && pointer[i] <= 'F'), "String::To() : Unable to convert this string to numeric value");
    Exception::Assert(base >= 2 && base <= 16, "Base should be between 2 and 16");

    char* pointer = this->pointer;
    u32 result = *pointer++ - '0';

    while (pointer < this->pointer + length)
    {
        result *= base;

        if (*pointer >= 'a' && *pointer <= 'f')
            result += *pointer++ + 10 - 'a';
        else if (*pointer >= 'A' && *pointer <= 'F')
            result += *pointer++ + 10 - 'A';
        else
            result += *pointer++ - '0';
    }

    return result;
}
s32 String::ToSigned(u32 base)
{
    for (u32 i = 0; i < length; i++)
        if (i == 0)
            Exception::Assert(pointer[i] == '-' || (pointer[i] >= '0' && pointer[i] <= '9') || (pointer[i] >= 'a' && pointer[i] <= 'f') || (pointer[i] >= 'A' && pointer[i] <= 'F'), "String::To() : Unable to convert this string to numeric value");
        else
            Exception::Assert((pointer[i] >= '0' && pointer[i] <= '9') || (pointer[i] >= 'a' && pointer[i] <= 'f') || (pointer[i] >= 'A' && pointer[i] <= 'F'), "String::To() : Unable to convert this string to numeric value");
    Exception::Assert(base >= 2 && base <= 16, "Base should be between 2 and 16");

    char* pointer = this->pointer;

    s32 sign = *pointer == '-' ? -1 : 1;
    if (sign < 0)
        pointer++;

    s32 result = *pointer++ - '0';

    while (pointer < this->pointer + length)
    {
        result *= base;

        if (*pointer >= 'a' && *pointer <= 'f')
            result += *pointer++ + 10 - 'a';
        else if (*pointer >= 'A' && *pointer <= 'F')
            result += *pointer++ + 10 - 'A';
        else
            result += *pointer++ - '0';
    }

    return result * sign;
}