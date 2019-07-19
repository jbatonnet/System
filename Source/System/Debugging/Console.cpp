#include <System/Debugging/Console.h>

using namespace System::IO;

//ConsoleColor Console::Color = ConsoleColor::Gray;
//ConsoleColor Console::BackColor = ConsoleColor::Black;

ConsoleStream* Console::BaseConsoleStream = Stream::GetConsoleStream();
TextStream* Console::BaseStream = new TextStream(Console::BaseConsoleStream);