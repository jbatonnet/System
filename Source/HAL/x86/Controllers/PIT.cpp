#include "PIT.h"
#ifdef X86

static bool pit_init = false;

void PIT_SendCommand(u8 cmd)
{
    IO_Write8(PIT_REG_COMMAND, cmd);
}
void PIT_SendData(u8 data, u8 counter)
{
    u8 port = (counter == PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 : 
                   (counter == PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 :
                   PIT_REG_COUNTER2;
    IO_Write8(port, data);
}
u8 PIT_ReadData(u16 counter)
{
    u8 port = (counter == PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 : 
                   (counter == PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 :
                   PIT_REG_COUNTER2;
    return IO_Read8(port);
}

void PIT_StartCounter(u32 freq, u8 counter, u8 mode)
{
    if (!freq)
        return;

    u16 divisor = u16(1193181 / (u16)freq);

    // Send operational command
    u8 ocw = 0;
    ocw = (ocw & ~PIT_OCW_MASK_MODE) | mode;
    ocw = (ocw & ~PIT_OCW_MASK_RL) | PIT_OCW_RL_DATA;
    ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | counter;
    PIT_SendCommand(ocw);

    // Set frequency rate
    PIT_SendData(divisor & 0xff, 0);
    PIT_SendData((divisor >> 8) & 0xff, 0);
}

void PIT_Initialize()
{
    pit_init = true;
}
bool PIT_IsInitialized()
{
    return pit_init;
}

#endif