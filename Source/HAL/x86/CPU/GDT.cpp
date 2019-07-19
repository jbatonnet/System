#include "TSS.h"
#include "GDT.h"
#include <../Kernel/Config.h>

#ifdef X86

static GDT_Descriptor gdt[GDT_MAX_DESCRIPTORS];
static GDT_Data gdt_data;

static void GDT_Install()
{
    _asm
    {
        mov byte ptr jump, 0xEA
        lgdt [gdt_data]
        
        // Far jump to CS = 0x08
        jump:
            push reload
            _emit GDT_KERNEL_CODE_SEGMENT
            _emit 0x00

        // Reload segments
        reload:
            mov ax, GDT_KERNEL_DATA_SEGMENT
            mov ds, ax
            mov es, ax
            mov fs, ax
            mov gs, ax
            mov ss, ax
    }
}

void GDT_SetDescriptor(u32 i, u32 base, u32 limit, GDT_Flags flags, GDT_Granularity granularity)
{
    if (i >= GDT_MAX_DESCRIPTORS)
        return;

    // Null out the descriptor
    u8* gdtBytes = (u8*)&gdt[i];
    for (u32 j = 0; j < sizeof(GDT_Descriptor); j++)
        gdtBytes[j] = 0;

    // Set base address and limit
    gdt[i].BaseLo      = base & 0xFFFF;
    gdt[i].BaseMi      = (base >> 16) & 0xFF;
    gdt[i].BaseHi      = (base >> 24) & 0xFF;
    gdt[i].LimitLo     = limit & 0xFFFF;
    gdt[i].LimitHi     = (limit >> 16) & 0x0F;

    // Set flags and granularity
    gdt[i].Flags = flags;
    gdt[i].Granularity = granularity;
}
GDT_Descriptor* GDT_GetDescriptor(u32 i)
{
    if (i > GDT_MAX_DESCRIPTORS)
        return null;

    return &gdt[i];
}

void GDT_Initialize()
{
    gdt_data.Limit = (sizeof(GDT_Descriptor) * GDT_MAX_DESCRIPTORS) - 1;
    gdt_data.Base = gdt;

    // Set null descriptor
    GDT_SetDescriptor(0, 0, 0, (GDT_Flags)0, (GDT_Granularity)0);

    // Set default kernel descriptors
    GDT_SetDescriptor(1, 0, 0xFFFFFFFF, GDT_Flags::KernelCode, GDT_Granularity::Kernel);
    GDT_SetDescriptor(2, 0, 0xFFFFFFFF, GDT_Flags::KernelData, GDT_Granularity::Kernel);

    // Set default user descriptors
    GDT_SetDescriptor(3, 0, 0xFFFFFFFF, GDT_Flags::UserCode, GDT_Granularity::User);
    GDT_SetDescriptor(4, 0, 0xFFFFFFFF, GDT_Flags::UserData, GDT_Granularity::User);

    // Install TSS
    u32 stack = 0;
    _asm mov [stack], esp
    TSS_Install(5, 0x10, KERNEL_STACK);

    // Install the Global Descriptor Table
    GDT_Install();

    _asm mov ax, 0x2B
    _asm ltr ax
}

u32 HAL_Test(u32 param)
{
    return sizeof(GDT_Descriptor);
}

#endif