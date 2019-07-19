#ifndef _KERNEL_EXCEPTIONS_H_
#define _KERNEL_EXCEPTIONS_H_

#include "Devices/Screen/Screen.h"

#include <Kernel/Debugging/StackTrace.h>
#include <System/IO/Streams/DataStream.h>
#include <System/Runtime/Debugging/Debugger.h>

using namespace System::IO;

void Exception_Dump(string message, const InterruptHandlerRegisters& registers)
{
    Log::WriteLine(Log::Error);
    Log::WriteLine(Log::Error, "-- SystemException --");
    Log::WriteLine(Log::Error, message);

    // Break early in case of memory allocation exception
    System::Runtime::Debugger::Break();

    Log::WriteLine(Log::Error, "Context: { eip: 0x{0:x8}, esp: 0x{1:x8} }", registers.eip, registers.esp);

    Timer::Sleep(200);

    DataStream dataStream(Serial::BaseStream);
    dataStream.Write((u8)0xEE);

    u32 esp = registers.esp;
    void* stack = (void*)esp;

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

        dataStream.Write(ret);
        if (ret == 0)
            break;

        //Console::WriteLine("{ ebp: 0x{0:x8}, ret: 0x{1:x8} }", ebp, ret);

        stack = (void*)ebp;
    }
}

void Exception_GeneralProtectionFault(InterruptHandlerParameters parameters, u32 irq, u32 gpf, InterruptHandlerRegisters registers)
{
    // V86 Monitor
    if (registers.cs & 0xF000)
        return;

    Exception_Dump("General Protection Fault", registers);
    for (;;);
}
void Exception_DivideByZero(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    Exception_Dump("Divide by Zero", registers);
    for (;;);
}
void Exception_BoundsCheck(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    Exception_Dump("Bounds Check", registers);
    for (;;);
}
void Exception_InvalidOPCode(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    Exception_Dump("Invalid OPCode", registers);
    for (;;);
}

void Exception_SingleStep()
{
    Log::WriteLine(Log::Error, "-- Single Step --");

    for (;;);
}
void Exception_NMI()
{
    Log::WriteLine(Log::Error, "-- Non Maskable Interrupt --");

    for (;;);
}
void Exception_Breakpoint()
{
    System::Runtime::Debugger::Break();
}
void Exception_Overflow()
{
    Log::WriteLine(Log::Error, "-- Overflow --");

    for (;;);
}
void Exception_NoDevice()
{
    Log::WriteLine(Log::Error, "-- No Device --");

    for (;;);
}
void Exception_DoubleFault()
{
    Log::WriteLine(Log::Error, "-- Double Fault --");

    for (;;);
}
void Exception_InvalidTSS()
{
    Log::WriteLine(Log::Error, "-- Invalid Task State Segment --");

    for (;;);
}
void Exception_NoSegment()
{
    Log::WriteLine(Log::Error, "-- Invalid Segment --");

    for (;;);
}
void Exception_StackFault()
{
    Log::WriteLine(Log::Error, "-- Stack Fault --");

    for (;;);
}
void Exception_FPUFault()
{
    Log::WriteLine(Log::Error, "-- Floating Point Unit Fault --");

    for (;;);
}
void Exception_AlignmentCheck()
{
    Log::WriteLine(Log::Error, "-- Alignment Check --");

    for (;;);
}
void Exception_MachineCheck()
{
    Log::WriteLine(Log::Error, "-- Machine Check --");

    for (;;);
}
void Exception_SimdFPUFault()
{
    Log::WriteLine(Log::Error, "-- SIMD Fault --");

    for (;;);
}

void Exception_PageFault()
{
    /*_asm cli
    _asm sub ebp, 4
    _asm popad
    _asm sti
    _asm iret*/

    //Clear();
    //WriteLine("Page fault");
    //for (;;);
}

#endif