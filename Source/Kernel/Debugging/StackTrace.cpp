#include <Kernel/Debugging/StackTrace.h>
#include <System/Structures/Collections/Dictionary.h>
#include <System/IO/File.h>
#include <System/IO/Streams/TextStream.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Log.h>
#include <Kernel/Devices/Screen/Screen.h>

using namespace System::IO;

Dictionary<u32, string>* kernelMap = null;

void StackTrace_Initialize()
{
    //Console::WriteLine("StackTrace_Initialize");

    kernelMap = new Dictionary<u32, string>();
    
    char* buffer = Memory::Allocate<char>(4096);
    u16 index = 0;
    u16 maximum;

    //maximum = stream->Read(buffer, 4096);






    //TextStream* textStream = new TextStream(fileStream);

    // Skip first lines
    //for (u32 i = 0; i < 24; i++)
    //    textStream->ReadLine();

    /*u32 i = 0;
    while (!textStream->EndOfStream)
    {
        string line = textStream->ReadLine();

        Log::WriteLine(Log::Debug, "Length: {0}", line.Length);

        if (line.Length < 21)
            break;*/

        /*string rawName = line.SubString(21).Before(' ');
        Log::WriteLine(Log::Debug, rawName);

        // Skip non functions
        if (rawName.Length < 2 || rawName[1] == '?')
            continue;

        string addressText = line.SubString(21).SubString(rawName.Length).TrimLeft().Before(' ');
        string file = line.AfterLast(' ');

        //Log::WriteLine(Log::Debug, "Line: {0}", line);
        //Console::WriteLine("RawName: {0}", rawName);
        //Console::WriteLine("AddressText: {0}", addressText);
        //Console::WriteLine("File: {0}", file);

        string fullName = rawName.SubString(1);
        u32 address = addressText.To<u32>(16);

        //Console::WriteLine("FullName: {0}", fullName);
        //Console::WriteLine("Address: {0:x8}", address);

        Log::WriteLine(Log::Debug, "- {0} at 0x{1:x8}", fullName, address);

        kernelMap->Add(address, rawName);*/
    //}
}

void StackTrace_Test()
{
    if (!kernelMap)
        StackTrace_Initialize();

    u32* stack;
    _asm mov [stack], ebp

    Console::WriteLine("Stack trace");

    while (*stack / 0x100000 == 3) // TODO: Detect stack bottom
    {
        u32 ebp = *stack++;
        u32 ret = *stack;

        Pair<u32, string>* method = kernelMap->Last([&](Pair<u32, string>* p) -> bool { return p->Key < ret; });
        Console::WriteLine("- {0} at 0x{1:x8} (+0x{2:x8})", method->Value, method->Key, ret - method->Key);

        stack = (u32*)ebp;
    }
}
void StackTrace_Test_3(u32 a)
{
    //StackTrace_Test_4();
}
void StackTrace_Test_2(u8 a)
{
    StackTrace_Test_3(1111111111);
}
void StackTrace_Test_1()
{
    StackTrace_Test_2(1);
}
void StackTrace_Test__()
{
    StackTrace_Test_1();
}