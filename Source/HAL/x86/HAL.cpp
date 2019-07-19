#include <HAL/HAL.h>
#include <Kernel/Config.h>

#include "CPU/CPU.h"
#include "CPU/IDT.h"
#include "CPU/GDT.h"
#include "Controllers/PIC.h"
#include "Controllers/PIT.h"

#ifdef X86

void HAL_Load()
{
    CPU_Initialize();
    PIC_Initialize(0x20, 0x28);
    PIT_Initialize();
    PIT_StartCounter(1000 / FRENQUENCY_DIVIDER, PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVEGEN);
}
void HAL_Unload()
{
    CPU_Shutdown();
}

u8 IO_Read8(u16 port)
{
    u8 value;
    _asm
    {
        mov dx, word ptr[port]
        in al, dx
        mov byte ptr[value], al
    }
    return value;
}
u16 IO_Read16(u16 port)
{
    u16 value;
    _asm
    {
        mov dx, word ptr[port]
        in ax, dx
        mov word ptr[value], ax
    }
    return value;
}
u32 IO_Read32(u16 port)
{
    u32 value;
    _asm
    {
        mov dx, word ptr[port]
        in eax, dx
        mov dword ptr[value], eax
    }
    return value;
}
void IO_Write8(u16 port, u8 value)
{
    _asm
    {
        mov al, byte ptr [value]
        mov dx, word ptr [port]
        out dx, al
    }
}
void IO_Write16(u16 port, u16 value)
{
    _asm
    {
        mov ax, word ptr [value]
        mov dx, word ptr [port]
        out dx, ax
    }
}
void IO_Write32(u16 port, u32 value)
{
    _asm
    {
        mov eax, dword ptr [value]
        mov dx, word ptr [port]
        out dx, eax
    }
}

#endif