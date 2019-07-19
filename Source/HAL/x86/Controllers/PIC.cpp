#include <HAL/HAL.h>
#include "PIC.h"
#ifdef X86

inline u8 PIC_ReadData(u8 picNum)
{
    if (picNum > 1)
        return 0;
    return IO_Read8(picNum ? PIC2_REG_DATA : PIC1_REG_DATA);
}
inline void PIC_SendData(u8 data, u8 picNum)
{
    if (picNum > 1)
        return;
    IO_Write8(picNum ? PIC2_REG_DATA : PIC1_REG_DATA, data);
}
inline void PIC_SendCommand(u8 command, u8 picNum)
{
    if (picNum > 1)
        return;
    IO_Write8(picNum ? PIC2_REG_COMMAND : PIC1_REG_COMMAND, command);
}

void PIC_Initialize(u8 base0, u8 base1)
{
    u8 icw = 0;

    _asm cli

    // Initialization of PIC
    icw = (icw & ~PIC_ICW1_MASK_INIT) | PIC_ICW1_INIT_YES;
    icw = (icw & ~PIC_ICW1_MASK_IC4) | PIC_ICW1_IC4_EXPECT;
    PIC_SendCommand(icw, 0);
    PIC_SendCommand(icw, 1);

    // Initialization Control Word 2
    PIC_SendData(base0, 0);
    PIC_SendData(base1, 1);

    // Initialization Control Word 3
    PIC_SendData(0x04, 0);
    PIC_SendData(0x02, 1);

    // Initialization Control Word 4
    icw = (icw & ~PIC_ICW4_MASK_UPM) | PIC_ICW4_UPM_86MODE;
    PIC_SendData(icw, 0);
    PIC_SendData(icw, 1);
}
void PIC_EOI(u8 irq)
{
    if (irq > 16)
        return;
    if (irq >= 8)
        PIC_SendCommand(PIC_OCW2_MASK_EOI, 1);
    PIC_SendCommand(PIC_OCW2_MASK_EOI, 0);
}

#endif