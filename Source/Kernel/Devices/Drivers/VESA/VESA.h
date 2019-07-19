#ifndef _KERNEL_VESA_H_
#define _KERNEL_VESA_H_

#include <Kernel/Kernel.h>

struct VbeInfo
{
    char Signature[4];
    
    struct
    {
        u8 Minor;
        u8 Major;
    } Version;
    
    u16 Oem[2];
    u8  Capabilities[4];
    u16 VideoModes[2];
    u16 TotalMemory;
};
struct VbeModeInfo
{
    u16 Attributes;
    u8  WindowA, WindowB;
    u16 Granularity;
    u16 WindowSize;
    u16 SegmentA, SegmentB;
    u16 WindowFunction[2];

    u16 Pitch;
    u16 Width, Height;

    u8 CharacterWidth, CharacterHeight, Planes;
    u8 Bpp;
    u8 Banks;
    u8 PixelFormat, BankSize, ImagePages;
    u8 _Reserved0;
 
    u8 RedMask, RedShift;
    u8 GreenMask, GreenShift;
    u8 BlueMask, BlueShift;

    u8 _ReservedMask, _ReservedShift;
    u8 ColorAttributes;
 
    u32 Address;
    u32 _Reserved1;
    u16 _Reserved2;
};

bool VESA_Call(u8 function, u16 b = 0, u16 c = 0, u16 d = 0, u16 destination = 0);

VbeInfo VESA_GetInformations();
VbeModeInfo VESA_GetModeInformations(u16 mode);
void VESA_SetMode(u16 mode);

#endif