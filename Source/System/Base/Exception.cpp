#include <System/System.h>
#include <System/Runtime/Debugging/Debugger.h>

using namespace System::IO;
using namespace System::Runtime;

void Exception::ExtractFrames()
{
    u32 stack = 0;
    _asm mov[stack], esp
    ExtractFrames((void*)stack);
}
void Exception::ExtractFrames(void* stack)
{
    u32 esp = (u32)stack;

    // Search first frame
    while (true)
    {
        // We found a stack pointer
        if ((*(u32*)stack & 0xFFFF0000) == (esp & 0xFFFF0000))
            // And this stack pointer leads to another one
            if ((**(u32**)stack & 0xFFFF0000) == (esp & 0xFFFF0000))
                // Then stop, this should be the one :)
                break;

        stack = (void*)((u32)stack + 1);
    }

    // Decode frames
    while (true)
    {
        u32 ebp = ((u32*)stack)[0];
        u32 ret = ((u32*)stack)[1];

        if (ret == 0)
            break;

        frames.Add((void*)ret);
        stack = (void*)ebp;
    }
}

void AssertInternal()
{
    Timer::Sleep(200);

    DataStream dataStream(Serial::BaseStream);
    dataStream.Write((u8)0xEE);

    u32 stackPointer = 0;
    _asm mov[stackPointer], ebp
    void* stack = (void*)stackPointer;

    // Show stack
    //for (s32 i = 20; i >= 0; i--)
    //    Console::WriteLine("At {0}: 0x{1:x8}", (u32*)((u32)stack + i * 4), *(u32*)((u32)stack + i * 4));

    // Search first frame
    while (true)
    {
        // We found a stack pointer
        if ((*(u32*)stack & 0xFFFF0000) == (stackPointer & 0xFFFF0000))
            // And this stack pointer leads to another one
            if ((**(u32**)stack & 0xFFFF0000) == (stackPointer & 0xFFFF0000))
                // Then stop, this should be the one :)
                break;

        stack = (void*)((u32)stack + 1);
    }

    // Decode frames
    while (true)
    {
        u32 ebp = ((u32*)stack)[0];
        u32 ret = ((u32*)stack)[1];

        dataStream.Write(ret);
        if (ret == 0)
            break;

        //Console::WriteLine("{ ebp: 0x{0:x8}, ret: 0x{1:x8} }", ebp, ret);

        stack = (void*)ebp;
    }

    loop
    _asm int 0x0D
}

void Exception::Assert()
{
    Debugger::Break();

    Log::WriteLine(Log::Error);
    Log::WriteLine(Log::Error, "-- AssertException --");

    AssertInternal();

    // TODO: Throw AssertException
}
void Exception::Assert(const char* message)
{
    Debugger::Break();

    Log::WriteLine(Log::Error);
    Log::WriteLine(Log::Error, "-- AssertException --");
    Log::WriteLine(Log::Error, "Message: {0}", message);

    AssertInternal();

    // TODO: Throw AssertException
}
void Exception::Assert(const string& message)
{
    Debugger::Break();

    Log::WriteLine(Log::Error);
    Log::WriteLine(Log::Error, "-- AssertException --");
    Log::WriteLine(Log::Error, "Message: {0}", message);

    AssertInternal();

    // TODO: Throw AssertException
}