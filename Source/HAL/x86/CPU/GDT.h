#if !defined(_GDT_H_) && defined(X86)
#define _GDT_H_

#include <HAL/HAL.h>

// Maximum number of descriptors
#define GDT_MAX_DESCRIPTORS 6

// Default segments
#define GDT_KERNEL_CODE_SEGMENT 0x08
#define GDT_KERNEL_DATA_SEGMENT 0x10
#define GDT_USER_CODE_SEGMENT 0x18
#define GDT_USER_DATA_SEGMENT 0x20

// Access flags
enum class GDT_Flags : u8
{
    Access     = 0x01,
    Writable   = 0x02,
    Expansion  = 0x04,
    Code       = 0x08,
    Use32Bit   = 0x08,
    NotTSS     = 0x10,
    Ring3      = 0x60,
    Memory     = 0x80,

    KernelCode = Writable | Code | NotTSS | Memory,
    KernelData = Writable | NotTSS | Memory,
    UserCode   = Code | NotTSS | Ring3 | Memory,
    UserData   = Writable | NotTSS | Ring3 | Memory,

    TSS        = Access | Use32Bit | Ring3 | Memory,
};

// Granularity flags
enum class GDT_Granularity : u8
{
    None      = 0x00,
    Available = 0x01,
    Use32Bit  = 0x04,
    Use4K     = 0x08,
    LimitMask = 0xF0,

    Kernel    = Use32Bit | Use4K,
    User      = Available | Use32Bit | Use4K,
    TSS       = None,
};

typedef struct GDT_Descriptor
{
    u16 LimitLo : 16;
    u16 BaseLo  : 16;
    u8  BaseMi  : 8;

    GDT_Flags Flags : 8;

    u8 LimitHi : 4;

    GDT_Granularity Granularity : 4;

    u8 BaseHi : 8;
} GDT_Descriptor;
typedef struct GDT_Data
{
    u16 Limit;
    GDT_Descriptor* Base;
} GDT_Data;

GDT_Descriptor* GDT_GetDescriptor(u32 i);
void GDT_SetDescriptor(u32 i, u32 base, u32 limit, GDT_Flags flags, GDT_Granularity granularity);

void GDT_Initialize();

#endif