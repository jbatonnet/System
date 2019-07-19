#include <System/Debugging/Log.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>

using namespace System::IO;

class LogStream : public Stream
{
private:
    ConsoleColor color;

public:
    LogStream(ConsoleColor color) : color(color) { }

    u32 Read(void* buffer, u32 count) override { return 0; }
    void Write(void* buffer, u32 count) override
    {
        ConsoleColor backup = Console::Color;
        
        Console::Color = color;
        Console::BaseConsoleStream->Write(buffer, count);
        Console::Color = backup;

        if (Serial::BaseStream)
            Serial::BaseStream->Write(buffer, count);
    }
};

Stream* Log::Trace = new LogStream(ConsoleColor::DarkGray);
Stream* Log::Debug = new LogStream(ConsoleColor::DarkGray);
Stream* Log::Info = new LogStream(ConsoleColor::Gray);
Stream* Log::Warning = new LogStream(ConsoleColor::DarkYellow);
Stream* Log::Error = new LogStream(ConsoleColor::DarkRed);