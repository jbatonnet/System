#include "GDT.h"
#include "IDT.h"
#include "CPU.h"
#ifdef X86

void CPU_EnableSSE()
{
    // Modify CR0
    _asm
    {
        mov eax, cr0
        and ax, 0xFFFB // Disable coprocessor emulation CR0.EM
        or ax, 0x2     // Enable coprocessor monitoring CR0.MP
        mov cr0, eax
    }

    // Modify CR4
    _asm
    {
        _emit 0x0F // mov eax, cr4
        _emit 0x20
        _emit 0xE0

        or ax, 3 << 9

        _emit 0x0F // mov cr4, eax
        _emit 0x22
        _emit 0xE0
    }
}

void CPU_Initialize()
{
    GDT_Initialize();
    IDT_Initialize();

    CPU_EnableSSE();
}
void CPU_Shutdown()
{
}

#endif