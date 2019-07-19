#ifdef X86

#include <HAL/HAL.h>
#include "DMA.h"

void DMA_MaskChannel(u8 channel)
{
    if (channel <= 4)
        IO_Write8(DMA0_CHANNEL_MASK, (1 << (channel - 1)));
    else
        IO_Write8(DMA1_CHANNEL_MASK, (1 << (channel - 5)));
}
void DMA_UnmaskChannel(u8 channel)
{
    IO_Write8(channel > 4 ? DMA1_CHANNEL_MASK : DMA0_CHANNEL_MASK, channel);
}
void DMA_UnmaskAllChannels()
{
    IO_Write8(DMA1_UNMASK_ALL, 0xFF);
}
void DMA_Reset()
{
    //IO_Write8(DMA0EMP, 0xFF);
}
void DMA_ResetFlipFlop(u32 dma)
{
    if (dma < 2)
        return;
    IO_Write8(dma ? DMA1_CLEAR_FLIPFLOP : DMA0_CLEAR_FLIPFLOP, 0xFF);
}

void DMA_SetAddress(u8 channel, u16 address)
{
    u16 port;
    switch (channel)
    {
        case 0: port = DMA0_CHANNEL0_ADDRESS; break;
        case 1: port = DMA0_CHANNEL1_ADDRESS; break;
        case 2: port = DMA0_CHANNEL2_ADDRESS; break;
        case 3: port = DMA0_CHANNEL3_ADDRESS; break;
        case 4: port = DMA1_CHANNEL4_ADDRESS; break;
        case 5: port = DMA1_CHANNEL5_ADDRESS; break;
        case 6: port = DMA1_CHANNEL6_ADDRESS; break;
        case 7: port = DMA1_CHANNEL7_ADDRESS; break;
        default: return;
    }

    IO_Write8(port, address & 0xFF);
    IO_Write8(port, address >> 8);
}
void DMA_SetCounter(u8 channel, u16 counter)
{
    u16 port;
    switch (channel)
    {
        case 0: port = DMA0_CHANNEL0_COUNTER; break;
        case 1: port = DMA0_CHANNEL1_COUNTER; break;
        case 2: port = DMA0_CHANNEL2_COUNTER; break;
        case 3: port = DMA0_CHANNEL3_COUNTER; break;
        case 4: port = DMA1_CHANNEL4_COUNTER; break;
        case 5: port = DMA1_CHANNEL5_COUNTER; break;
        case 6: port = DMA1_CHANNEL6_COUNTER; break;
        case 7: port = DMA1_CHANNEL7_COUNTER; break;
        default: return;
    }

    IO_Write8(port, counter & 0xFF);
    IO_Write8(port, counter >> 8);
}
void DMA_SetMode(u8 channel, u8 mode)
{
    DMA_MaskChannel(channel);

    channel &= 0x03;
    IO_Write8(channel < 4 ? DMA0_MODE : DMA1_MODE, channel | mode);

    DMA_UnmaskAllChannels();
}
void DMA_SetExternalPageRegister(u8 reg, u8 value)
{
    u16 port;
    switch (reg)
    {
        case 1: port = DMA_PAGE_CHANNEL1_ADDR2; break;
        case 2: port = DMA_PAGE_CHANNEL2_ADDR2; break;
        case 3: port = DMA_PAGE_CHANNEL3_ADDR2; break;
        case 5: port = DMA_PAGE_CHANNEL5_ADDR2; break;
        case 6: port = DMA_PAGE_CHANNEL6_ADDR2; break;
        case 7: port = DMA_PAGE_CHANNEL7_ADDR2; break;
        default: return;
    }

    IO_Write8(port, value);
}

#endif