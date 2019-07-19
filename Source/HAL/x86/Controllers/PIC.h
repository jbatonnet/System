#if !defined(_PIC_H_) && defined(X86)
#define _PIC_H_

#include <HAL/HAL.h>

// PIC 1 register port addresses
#define PIC1_REG_COMMAND 0x20
#define PIC1_REG_STATUS  0x20
#define PIC1_REG_DATA    0x21
#define PIC1_REG_IMR     0x21

// PIC 2 register port addresses
#define PIC2_REG_COMMAND 0xA0
#define PIC2_REG_STATUS  0xA0
#define PIC2_REG_DATA    0xA1
#define PIC2_REG_IMR     0xA1

// PIC 1 IRQs
#define PIC_IRQ_TIMER     0
#define PIC_IRQ_KEYBOARD  1
#define PIC_IRQ_SERIAL2   3
#define PIC_IRQ_SERIAL1   4
#define PIC_IRQ_PARALLEL2 5
#define PIC_IRQ_FLOPPY    6
#define PIC_IRQ_PARALLEL1 7

// PIC 2 IRQs
#define PIC_IRQ_CMOSTIMER  0
#define PIC_IRQ_CGARETRACE 1
#define PIC_IRQ_AUXILIARY  4
#define PIC_IRQ_FPU        5
#define PIC_IRQ_HDC        6

// Initialization Control Word 1
#define PIC_ICW1_MASK_IC4            0x01 // Bit Masks
#define PIC_ICW1_MASK_SNGL           0x02
#define PIC_ICW1_MASK_ADI            0x04
#define PIC_ICW1_MASK_LTIM           0x08
#define PIC_ICW1_MASK_INIT           0x10
#define PIC_ICW1_IC4_EXPECT          0x01 // Control Bits
#define PIC_ICW1_IC4_NO              0x00
#define PIC_ICW1_SNGL_YES            0x02
#define PIC_ICW1_SNGL_NO             0x00
#define PIC_ICW1_ADI_CALLINTERVAL4   0x04
#define PIC_ICW1_ADI_CALLINTERVAL8   0x00
#define PIC_ICW1_LTIM_LEVELTRIGGERED 0x08
#define PIC_ICW1_LTIM_EDGETRIGGERED  0x00
#define PIC_ICW1_INIT_YES            0x10
#define PIC_ICW1_INIT_NO             0x00

// Initialization Control Word 4
#define PIC_ICW4_MASK_UPM        0x01 // Bit Masks
#define PIC_ICW4_MASK_AEOI       0x02
#define PIC_ICW4_MASK_MS         0x04
#define PIC_ICW4_MASK_BUF        0x08
#define PIC_ICW4_MASK_SFNM       0x10
#define PIC_ICW4_UPM_86MODE      0x01 // Control Bits
#define PIC_ICW4_UPM_MCSMODE     0x00
#define PIC_ICW4_AEOI_AUTOEOI    0x02
#define PIC_ICW4_AEOI_NOAUTOEOI  0x00
#define PIC_ICW4_MS_BUFFERMASTER 0x04
#define PIC_ICW4_MS_BUFFERSLAVE  0x00
#define PIC_ICW4_BUF_MODEYES     0x08
#define PIC_ICW4_BUF_MODENO      0x00
#define PIC_ICW4_SFNM_NESTEDMODE 0x10
#define PIC_ICW4_SFNM_NOTNESTED  0x00

// Command Word 2 - Bit Masks
#define PIC_OCW2_MASK_L1     0x01
#define PIC_OCW2_MASK_L2     0x02
#define PIC_OCW2_MASK_L3     0x04
#define PIC_OCW2_MASK_EOI    0x20
#define PIC_OCW2_MASK_SL     0x40
#define PIC_OCW2_MASK_ROTATE 0x80

// Command Word 3 - Bit Masks
#define PIC_OCW3_MASK_RIS    0x01
#define PIC_OCW3_MASK_RIR    0x02
#define PIC_OCW3_MASK_MODE   0x04
#define PIC_OCW3_MASK_SMM    0x20
#define PIC_OCW3_MASK_ESMM   0x40
#define PIC_OCW3_MASK_D7     0x80

u8 PIC_ReadData(u8 picNum);
void PIC_SendData(u8 data, u8 picNum);
void PIC_SendCommand(u8 command, u8 picNum);

void PIC_Initialize(u8 base0, u8 base1);
void PIC_EOI(u8 irq);

#endif