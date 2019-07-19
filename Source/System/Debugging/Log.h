#ifndef _SYSTEM_LOG_H_
#define _SYSTEM_LOG_H_

#include <System/Common.h>
#include <System/IO/Streams/TextStream.h>

/// <summary>
/// Provides methods to log
/// </summary>
shared class Log
{
public:
    static System::IO::Stream* Trace;
    static System::IO::Stream* Debug;
    static System::IO::Stream* Info;
    static System::IO::Stream* Warning;
    static System::IO::Stream* Error;
    
    /// <summary>
    /// Writes an empty line on the specified log
    /// </summary>
    static void WriteLine(System::IO::Stream* log)
    {
        if (!log)
            return;

        System::IO::TextStream textStream(log);
        textStream.WriteLine();
    }
    /// <summary>
    /// Writes a text on the specified log
    /// </summary>
    /// <param name="format">The text to write</param>
    static void WriteLine(System::IO::Stream* log, const string& format)
    {
        if (!log)
            return;

        System::IO::TextStream textStream(log);
        textStream.WriteLine(format);
    }
    /// <summary>
    /// Formats and writes a text on the specified log
    /// </summary>
    /// <param name="format">The text to be formatted</param>
    /// <param name="parameter">The parameter to be formatted</param>
    template<typename... Args> static void WriteLine(System::IO::Stream* log, const string& format, Args... parameters)
    {
        if (!log)
            return;

        System::IO::TextStream textStream(log);
        textStream.WriteLine(format, parameters...);
    }
};

#endif