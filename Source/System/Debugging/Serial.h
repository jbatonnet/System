#ifndef _SYSTEM_SERIAL_LOG_H_
#define _SYSTEM_SERIAL_LOG_H_

#include <System/Common.h>
#include <System/IO/Streams/TextStream.h>

class Serial
{
public:
    static System::IO::TextStream* BaseStream;

    static void Write(const string& base)
    {
        if (BaseStream)
            BaseStream->Write(base);
    }
    template<typename... Args> static void Write(const string& base, Args... parameters)
    {
        if (BaseStream)
            BaseStream->Write(base, parameters...);
    }
    
    static void WriteLine()
    {
        if (BaseStream)
            BaseStream->WriteLine();
    }
    static void WriteLine(const string& base)
    {
        if (BaseStream)
            BaseStream->WriteLine(base);
    }
    template<typename... Args> static void WriteLine(const string& base, Args... parameters)
    {
        if (BaseStream)
            BaseStream->WriteLine(base, parameters...);
    }
};

#endif