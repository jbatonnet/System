#include <System/IO/Streams/Stream.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>

using namespace System::IO;

ConsoleStream* Stream::GetConsoleStream()
{
    return null;//Console::BaseConsoleStream;
}
Stream* Stream::GetSerialStream()
{
    return Serial::BaseStream;
}