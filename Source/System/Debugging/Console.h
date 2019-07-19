#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <System/Common.h>
#include <System/IO/Streams/TextStream.h>
#include <System/Devices/Input/InputManager.h>

shared class ConsoleStream : public System::IO::Stream
{
public:
    ConsoleStream() { }

    u64 GetLength() { return (u64)-1; }

    virtual u32 Read(void* buffer, u32 count)
    {
        return Read(buffer, count, false);
    }
    virtual u32 Read(void* buffer, u32 count, bool intercept) = 0;
    virtual void Write(void* buffer, u32 count) = 0;
};

enum class ConsoleColor : u8
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
    White
};

/// <summary>
/// Provides methods to write on the screen
/// </summary>
shared class Console
{
public:
    static ConsoleStream* BaseConsoleStream;
    static System::IO::TextStream* BaseStream;

public:
    static ConsoleColor Color;
    static ConsoleColor BackColor;

    /// <summary>
    /// Clears the screen
    /// </summary>
    shared static void Clear();

    /// <summary>
    /// Read a character from the console input
    /// </summary>
    /// <param name="intercept">Choose whether the character is displayed or not</param>
    /// <returns>The character read from the console input</returns>
    static char Read(bool intercept = false)
    {
        if (!BaseConsoleStream)
            return 0;

        char result = 0;
        BaseConsoleStream->Read(&result, 1, intercept);
        return result;
    }
    /// <summary>
    /// Read a key from the console input
    /// </summary>
    /// <returns>The key read from the console input</returns>
    static System::Devices::Buttons ReadKey()
    {
        //if (!BaseConsoleStream)
            return System::Devices::Buttons::Unknown;

        //char result = 0;
        //BaseConsoleStream->Read(&result, 1, intercept);
        //return result;
    }
    /// <summary>
    /// Reads a line from the console input
    /// </summary>
    /// <returns>The line read from the console input</returns>
    static string ReadLine()
    {
        if (!BaseStream)
            return String::Null;
        return BaseStream->ReadLine();
    }

    /// <summary>
    /// Writes a text on the screen
    /// </summary>
    /// <param name="format">The text to write</param>
    static void Write(const string& format)
    {
        if (BaseStream)
            BaseStream->Write(format);
    }
    /// <summary>
    /// Formats and writes a text on the screen
    /// </summary>
    /// <param name="format">The text to be formatted</param>
    /// <param name="parameters">The parameters to be formatted</param>
    template<typename... Args> static void Write(const string& format, Args... parameters)
    {
        if (BaseStream)
            BaseStream->Write(format, parameters...);
    }
    
    /// <summary>
    /// Writes an empty line on the screen
    /// </summary>
    static void WriteLine()
    {
        if (BaseStream)
            BaseStream->WriteLine();
    }
    /// <summary>
    /// Writes a text on the screen
    /// </summary>
    /// <param name="format">The text to write</param>
    static void WriteLine(const string& format)
    {
        if (BaseStream)
            BaseStream->WriteLine(format);
    }
    /// <summary>
    /// Formats and writes a text on the screen
    /// </summary>
    /// <param name="format">The text to be formatted</param>
    /// <param name="parameters">The parameters to be formatted</param>
    template<typename... Args> static void WriteLine(const string& format, Args... parameters)
    {
        if (BaseStream)
            BaseStream->WriteLine(format, parameters...);
    }
};

#endif