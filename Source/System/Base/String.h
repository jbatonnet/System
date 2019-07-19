#ifndef _SYSTEM_STRING_H_
#define _SYSTEM_STRING_H_

#include <System/Base/Types.h>
#include <System/Base/Object.h>
//#include <System/Structures/List.h>

#include <System/Utilities/Time/Enums.h>
void WriteLine(char* format, ...);

enum class Casing
{
    Upper = 1,
    Lower = 2,
    FirstUpper = 4,
    WordsUpper = 8,
    Words = Lower | WordsUpper,
    Sentence = Lower | FirstUpper
};

/// <summary>
/// Represents text as a series of characters
/// </summary>
struct String
{
private:
    union
    {
        u64 value;

        struct
        {
            /*union
            {
                char buffer[7];
                */
                struct
                {
                    char* pointer;
                    u16 length;
                };
            //};

            struct
            {
                //bool embedded : 1;
                bool allocated : 1;

                //u8 unused : 2;
                //u8 bufferLength : 4;
            };
        };
    };

    void Load(String& other);

public:
    String();
    String(char* buffer, u32 length, bool copy = false);
    String(const String& other);
    String(const String& other, const String& format);
    ~String();

    // Converters
    String(char* other);
    String(const char* other);
    String(char character, u32 count = 1);
    String(s32 value, u8 base = 10, u8 length = 1);
    String(u32 value, const String& format);
    String(u32 value, u8 base = 10, u8 length = 1);
    String(s64 value, u8 base = 10, u8 length = 1);
    String(u64 value, u8 base = 10, u8 length = 1);
    String(bool value);
    String(float value, u8 digits = 7, bool strip = true);
    String(double value);
    String(void* pointer);
    String(void* pointer, const String& format);
    String(Object& other);
    String(Object& other, const String& format);
    String(Object* other);
    String(Object* other, const String& format);
    String& operator=(const String& other);
    String& operator=(String&& other);

    // Enums
    String(Month month, const String& format = String::Empty);
    String(Day day, const String& format = String::Empty);

    // Accessors
    _declspec(property(get = GetLength)) u32 Length;
    u32 GetLength() const { return (u32)length; } // embedded ? (u32)bufferLength : (u32)length; }
    _declspec(property(get = GetBuffer)) char* Buffer;
    char* GetBuffer() const { return pointer; } // embedded ? (char*)buffer : pointer; }
    char& operator[](s32 index) const;

    // String methods
    String After(const String& other) const;
    String AfterLast(const String& other) const;
    String Before(const String& other) const;
    String BeforeLast(const String& other) const;
    bool Contains(const String& other) const;
    s32 IndexOf(const String& other, u32 from = 0) const;
    s32 IndexOfLast(const String& other, u32 from = 0) const;

    // Char methods
    String After(char character) const;
    String AfterLast(char character) const;
    String Before(char character) const;
    String BeforeLast(char character) const;
    bool Contains(char character) const;
    s32 IndexOf(char character, u32 from = 0) const;
    s32 IndexOfLast(char character, u32 from = 0) const;

    // Other methods
    String Replace(const String& value, const String& replacement, u32 count = 0) const;
    //List<String>* Split(const String& characters) const;
    String SubString(s32 position) const;
    String SubString(s32 position, s32 length) const;
    String ToLower() const;
    String ToUpper() const;
    String ToCasing(Casing casing) const;
    String Trim(const String& characters = " ") const;
    String TrimLeft(const String& characters = " ") const;
    String TrimRight(const String& characters = " ") const;

    // Operators
    bool operator==(const String& s) const;
    bool operator==(char* c) const;
    bool operator!=(const String& s) const;
    bool operator!=(char* c) const;
    String operator+(String& other) const;
    String operator+(char* other) const;
    String operator+(bool other) const;
    String operator+(char other) const;
    String operator+(void* other) const;
    String operator+(s32 other) const;
    String operator+(u32 other) const;
    String operator+(s64 other) const;
    String operator+(u64 other) const;
    String operator+(float other) const;
    String operator+(double other) const;
    friend String operator+(char* value1, const String& value2);

    // Converters
    bool ToBool();
    u32 ToUnsigned(u32 base);
    s32 ToSigned(u32 base);
    template<typename T> T To(u32 base = 10);
    template<> String To<String>(u32 base)
    {
        return *this;
    }
    template<> bool To<bool>(u32)
    {
        return ToBool();
    }
    template<> u8 To<u8>(u32 base)
    {
        return (u8)ToUnsigned(base);
    }
    template<> u16 To<u16>(u32 base)
    {
        return (u16)ToUnsigned(base);
    }
    template<> u32 To<u32>(u32 base)
    {
        return ToUnsigned(base);
    }
    template<> s8 To<s8>(u32 base)
    {
        return (s8)ToSigned(base);
    }
    template<> s16 To<s16>(u32 base)
    {
        return (s16)ToSigned(base);
    }
    template<> s32 To<s32>(u32 base)
    {
        return (s32)ToSigned(base);
    }

    // Formatters
    template<typename T> static String FormatInternal(const String& base, u32 index, T parameter)
    {
        //WriteLine("Index: %d", index);

        char buffer[0x100];
        s32 start = -1,
            end = -1,
            cursor = 0;

        char tag[0x10] = "{";
        s32 indexLength = 0;

        // Build tag
        if (index < 10) { tag[1] = '0' + index; tag[2] = 0; indexLength = 1; }
        else if (index < 100) { tag[1] = '0' + index / 10; tag[2] = '0' + index % 10; tag[3] = 0; indexLength = 2; }
        else
            Exception::Assert("FormatInternal with index >= 100");

        //WriteLine("Tag: %s", tag);

        // Find the tag
        cursor = start = base.IndexOf(tag);
        if (start < 0)
            return base;

        //WriteLine("Start: %d", start);

        end = base.IndexOf('}', (u32)(start + 2));
        if (end < 0)
            return base;

        //WriteLine("End: %d", end);

        // Copy up to start
        Memory::Copy<char>(base.pointer, buffer, (u32)start);

        // Copy the parameter without custom formatting
        if (end - start == indexLength + 1)
        {
            String parameterString(parameter);

            Memory::Copy<char>(parameterString.pointer, buffer + cursor, parameterString.length);
            cursor += parameterString.length;
        }

        // Format the parameter and copy it
        else if (base[start + indexLength + 1] == ':')
        {
            String format(base.pointer + start + indexLength + 2, end - start - indexLength - 2);
            String replacement(parameter, format);

            Memory::Copy<char>(replacement.pointer, buffer + cursor, replacement.length);
            cursor += replacement.length;
        }

        // Copy the remaining static string
        Memory::Copy<char>(base.pointer + end + 1, buffer + cursor, base.length - end - 1);
        cursor += base.length - end - 1;
        buffer[cursor++] = 0;

        return String(buffer);
    }
    template<typename First, typename... Other> static String FormatInternal(const String& base, u32 index, First parameter, Other... parameters)
    {
        String result = FormatInternal(base, index, parameter);
        return FormatInternal(result, index + 1, parameters...);
    }
    template<typename... Args> static String Format(const String& base, Args... parameters)
    {
        return FormatInternal(base, 0, parameters...);
    }
    template<> static String Format(const String& base)
    {
        return base;
    }

    /// <summary>
    /// Represents a null string without any buffer
    /// </summary>
    static String Null;

    /// <summary>
    /// Represents an empty string containing no characters
    /// </summary>
    static String Empty;

    /// <summary>
    /// Represents the new line character sequence
    /// </summary>
    static String NewLine;

    /// <summary>
    /// Represents the directory separator character
    /// </summary>
    static String Separator;
};

/// <summary>
/// Represents text as a series of characters
/// </summary>
typedef String string;

#endif