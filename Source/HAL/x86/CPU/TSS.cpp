#include <HAL/HAL.h>
#include "TSS.h"
#include "GDT.h"

static TSS_Entry tss;

void _declspec(naked) TSS_Flush()
{
    _asm
    {
        mov ax, 0x2B
        ltr ax
    }
}

void TSS_SetStack(void* stack)
{
    tss.esp0 = (u32)stack;
}

void TSS_Install(u32 id, u16 ss, u32 esp)
{
    u32 base = (u32)&tss;
    GDT_SetDescriptor(id, base, base + sizeof(tss), GDT_Flags::TSS, GDT_Granularity::TSS);

    u8* tssBytes = (u8*)&tss;
    for (u32 i = 0; i < sizeof(TSS_Entry); i++)
        tssBytes[i] = 0;

    tss.ss0 = ss;
    tss.esp0 = esp;
    tss.iomap_base = sizeof(TSS_Entry) - 8192;
}