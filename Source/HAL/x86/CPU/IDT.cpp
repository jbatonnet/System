#include "IDT.h"
#include "GDT.h"

#ifdef X86

static IDT_Descriptor idt[IDT_MAX_INTERRUPTS];
static IDT_Data idt_data;

void IDT_Install()
{
    _asm lidt [idt_data]
}

void IDT_InstallIR(u32 i, u16 flags, u16 selector, IDT_InterruptHandler irq)
{
    if (i >= IDT_MAX_INTERRUPTS)
        return;
    if (!irq)
        return;

    // Get base address of interrupt handler
    u32 uiBase = (u32)&(*irq);

    // Store base address into idt
    idt[i].HandlerLo = u16(uiBase & 0xffff);
    idt[i].HandlerHi = u16((uiBase >> 16) & 0xffff);
    idt[i].Reserved = 0;
    idt[i].Flags = u8(flags);
    idt[i].GDTSelector = selector;
}
IDT_Descriptor* IDT_GetIR(u32 i)
{
    if (i > IDT_MAX_INTERRUPTS)
        return null;

    return &idt[i];
}

void  _declspec(naked) IDT_DefaultHandler()
{
    //_asm pushad

    //IRQ_EOI(0);

    //_asm popad
    _asm iretd
}

void IDT_Initialize()
{
    // Set up idt_data for processor
    idt_data.Limit = sizeof(IDT_Descriptor) * IDT_MAX_INTERRUPTS - 1;
    idt_data.Base = (u32)&idt[0];

    // Null out the idt
    u8* idtBytes = (u8*)&idt[0];
    for (u32 i = 0; i < sizeof(IDT_Descriptor) * IDT_MAX_INTERRUPTS - 1; i++)
        idtBytes[i] = 0;

    // Register default handlers
    //for (int i = 0; i < IDT_MAX_INTERRUPTS; i++)
    //    IDT_InstallIR(i, IDT_DESC_PRESENT | IDT_DESC_BIT32, GDT_KERNEL_CODE_SEGMENT, (IDT_InterruptHandler)IDT_DefaultHandler);
    
    // Install our idt
    IDT_Install();
}

#endif