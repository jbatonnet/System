#include <System/Debugging/Serial.h>

using namespace System::IO;

TextStream* Serial::BaseStream = new TextStream(Stream::GetSerialStream());