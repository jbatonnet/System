#if !defined(_PIT_H_) && defined(X86)
#define _PIT_H_

#include <HAL/HAL.h>

// Operational Command Bit masks
#define PIT_OCW_MASK_BINCOUNT 0x01
#define PIT_OCW_MASK_MODE     0x0E
#define PIT_OCW_MASK_RL       0x30
#define PIT_OCW_MASK_COUNTER  0xC0

// Use when setting binary count mode
#define PIT_OCW_BINCOUNT_BINARY 0
#define PIT_OCW_BINCOUNT_BCD    1

// Use when setting counter mode
#define PIT_OCW_MODE_TERMINALCOUNT 0x00
#define PIT_OCW_MODE_ONESHOT       0x02
#define PIT_OCW_MODE_RATEGEN       0x04
#define PIT_OCW_MODE_SQUAREWAVEGEN 0x06
#define PIT_OCW_MODE_SOFTWARETRIG  0x08
#define PIT_OCW_MODE_HARDWARETRIG  0x0A

// Use when setting data transfer
#define PIT_OCW_RL_LATCH   0x00
#define PIT_OCW_RL_LSBONLY 0x10
#define PIT_OCW_RL_MSBONLY 0x20
#define PIT_OCW_RL_DATA    0x30

// Use when setting the counter we are working with
#define PIT_OCW_COUNTER_0 0x00
#define PIT_OCW_COUNTER_1 0x40
#define PIT_OCW_COUNTER_2 0x80

// Controller Registers
#define PIT_REG_COUNTER0 0x40
#define PIT_REG_COUNTER1 0x41
#define PIT_REG_COUNTER2 0x42
#define PIT_REG_COMMAND  0x43

void PIT_SendCommand(u8 cmd);
void PIT_SendData(u8 data, u8 counter);
u8 PIT_ReadData(u16 counter);

void PIT_StartCounter(u32 freq, u8 counter, u8 mode);
void PIT_Initialize();

#endif