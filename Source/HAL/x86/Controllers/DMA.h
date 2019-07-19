#if !defined(_DMA_H_) && defined(X86)
#define _DMA_H_

#include <HAL/HAL.h>

// DMA0 Ports
#define DMA0_CHANNEL0_ADDRESS 0x00
#define DMA0_CHANNEL0_COUNTER 0x01
#define DMA0_CHANNEL1_ADDRESS 0x02
#define DMA0_CHANNEL1_COUNTER 0x03
#define DMA0_CHANNEL2_ADDRESS 0x04
#define DMA0_CHANNEL2_COUNTER 0x05
#define DMA0_CHANNEL3_ADDRESS 0x06
#define DMA0_CHANNEL3_COUNTER 0x07
#define DMA0_STATUS           0x08
#define DMA0_COMMAND          0x08
#define DMA0_REQUEST          0x09
#define DMA0_CHANNEL_MASK     0x0A
#define DMA0_MODE             0x0B
#define DMA0_CLEAR_FLIPFLOP   0x0C
#define DMA0_TEMP             0x0D
#define DMA0_MASTER_CLEAR     0x0D
#define DMA0_CLEAR_MASK       0x0E
#define DMA0_MASK             0x0F

// DMA1 Ports
#define DMA1_CHANNEL4_ADDRESS 0xC0
#define DMA1_CHANNEL4_COUNTER 0xC2
#define DMA1_CHANNEL5_ADDRESS 0xC4
#define DMA1_CHANNEL5_COUNTER 0xC6
#define DMA1_CHANNEL6_ADDRESS 0xC8
#define DMA1_CHANNEL6_COUNTER 0xCA
#define DMA1_CHANNEL7_ADDRESS 0xCC
#define DMA1_CHANNEL7_COUNTER 0xCE
#define DMA1_STATUS           0xD0
#define DMA1_COMMAND          0xD0
#define DMA1_REQUEST          0xD2
#define DMA1_CHANNEL_MASK     0xD4
#define DMA1_MODE             0xD6
#define DMA1_CLEAR_FLIPFLOP   0xD8
#define DMA1_INTER            0xDA
#define DMA1_UNMASK_ALL       0xDC
#define DMA1_MASK             0xDE

// DMA Externel Page Ports
#define DMA_PAGE_EXTRA0         0x80
#define DMA_PAGE_CHANNEL2_ADDR2 0x81
#define DMA_PAGE_CHANNEL3_ADDR2 0x82
#define DMA_PAGE_CHANNEL1_ADDR2 0x83
#define DMA_PAGE_EXTRA1         0x84
#define DMA_PAGE_EXTRA2         0x85
#define DMA_PAGE_EXTRA3         0x86
#define DMA_PAGE_CHANNEL6_ADDR2 0x87
#define DMA_PAGE_CHANNEL7_ADDR2 0x88
#define DMA_PAGE_CHANNEL5_ADDR2 0x89
#define DMA_PAGE_EXTRA4         0x8C
#define DMA_PAGE_EXTRA5         0x8D
#define DMA_PAGE_EXTRA6         0x8E
#define DMA_PAGE_DRAM_REFRESH   0x8F

// DMA Modes
#define DMA_MODE_MASK_SEL          0x03
#define DMA_MODE_MASK_TRA          0x0C
#define DMA_MODE_SELF_TEST         0x00
#define DMA_MODE_READ_TRANSFER     0x04
#define DMA_MODE_WRITE_TRANSFER    0x08
#define DMA_MODE_MASK_AUTO         0x10
#define DMA_MODE_MASK_IDEC         0x20
#define DMA_MODE_MASK              0xC0
#define DMA_MODE_TRANSFER_ONDEMAND 0x00
#define DMA_MODE_TRANSFER_SINGLE   0x40
#define DMA_MODE_TRANSFER_BLOCK    0x80
#define DMA_MODE_TRANSFER_CASCADE  0xC0

// DMA Commands
#define DMA_CMD_MEM_TO_MEM         0x01
#define DMA_CMD_CHANNEL0_ADD_RHOLD 0x02
#define DMA_CMD_ENABLE             0x04
#define DMA_CMD_TIMING             0x08
#define DMA_CMD_PRIORITY           0x10
#define DMA_CMD_WRITE_SEL          0x20
#define DMA_CMD_DREQ               0x40
#define DMA_CMD_DACK               0x80

void DMA_MaskChannel(u8 channel);
void DMA_UnmaskChannel(u8 channel);
void DMA_UnmaskAllChannels();
void DMA_Reset();
void DMA_ResetFlipFlop(u32 dma);
void DMA_SetAddress(u8 channel, u16 address);
void DMA_SetCounter(u8 channel, u16 counter);
void DMA_SetMode(u8 channel, u8 mode);
void DMA_SetExternalPageRegister(u8 reg, u8 value);

#define DMA_MODE_MASK_SEL          0x03
#define DMA_MODE_MASK_TRA          0x0C
#define DMA_MODE_SELF_TEST         0x00
#define DMA_MODE_READ_TRANSFER     0x04
#define DMA_MODE_WRITE_TRANSFER    0x08
#define DMA_MODE_MASK_AUTO         0x10
#define DMA_MODE_MASK_IDEC         0x20
#define DMA_MODE_MASK              0xC0
#define DMA_MODE_TRANSFER_ONDEMAND 0x00
#define DMA_MODE_TRANSFER_SINGLE   0x40
#define DMA_MODE_TRANSFER_BLOCK    0x80
#define DMA_MODE_TRANSFER_CASCADE  0xC0

#define DMA_SetRead(channel) DMA_SetMode(channel, DMA_MODE_READ_TRANSFER | DMA_MODE_TRANSFER_SINGLE)
#define DMA_SetWrite(channel) DMA_SetMode(channel, DMA_MODE_WRITE_TRANSFER | DMA_MODE_TRANSFER_SINGLE)

#endif