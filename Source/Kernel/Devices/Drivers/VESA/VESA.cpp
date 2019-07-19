#include "VESA.h"

#pragma optimize("", off)

bool VESA_Call(u8 function, u16 b, u16 c, u16 d, u16 destination)
{
    u16 a = 0x4F << 8 | function;

    _asm
    {
        mov ax, [a]
        mov bx, [b]
        mov cx, [c]
        mov dx, [d]
        mov di, [destination]

        int INTERRUPT_VIRTUAL + 0x10

        mov [a], ax
    }

    return a == 0x004F;
}

VbeInfo VESA_GetInformations()
{
    if (!VESA_Call(0x00))
        Write("VESA: Error while getting VBE informations\n");

    VbeInfo informations;
    Memory::Copy<VbeInfo>((void*)0x90000, &informations);

    return informations;
}
VbeModeInfo VESA_GetModeInformations(u16 mode)
{
    if (!VESA_Call(0x01, 0x00, mode))
        Write("VESA: Error while getting VBE mode informations\n");

    VbeModeInfo modeInformations;
    Memory::Copy<VbeModeInfo>((void*)0x90000, &modeInformations);

    return modeInformations;
}
void VESA_SetMode(u16 mode)
{
    if (!VESA_Call(0x02, mode | 0x4000))
        Write("VESA: Error while changing VBE mode\n");
}

#pragma optimize("", on)