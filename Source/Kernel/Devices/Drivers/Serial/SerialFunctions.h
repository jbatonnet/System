#ifndef _KERNEL_SERIAL_H_
#define _KERNEL_SERIAL_H_

#include <System/Common.h>

#define SERIAL_OFFSET_DATA         0
#define SERIAL_OFFSET_INTERRUPT    1
#define SERIAL_OFFSET_LINE_CONTROL 3
#define SERIAL_OFFSET_LINE_STATUS  5

u16 Serial_BasePorts[];

enum Serial_BaudRateDivisor
{
    Rate115200 = 1,
    Rate57600  = 2,
    Rate38400  = 3,
};

enum Serial_LineControl
{
    // Character length
    CharLength5 = 0x00,
    CharLength6 = 0x01,
    CharLength7 = 0x02,
    CharLength8 = 0x03,

    // Stop bits
    StopBits1 = 0x00,
    StopBits2 = 0x04,

    // Parity
    ParityNone  = 0x00,
    ParityOdd   = 0x08,
    ParityEven  = 0x18,
    ParityMark  = 0x28,
    ParitySpace = 0x38,

    // Other
    DLAB = 0x80,

    // Protocol
    Protocol8N1 = CharLength8 | StopBits1 | ParityNone,
    Default = Protocol8N1
};

enum class Serial_InterruptEnable : u8
{
    DataAvailable    = 0,
    TransmitterEmpty = 1,
    Break            = 2,
    StatusChange     = 3
};

enum class Serial_LineStatus : u8
{
    ReceiverFull     = 0x01,
    OverrunError     = 0x02,
    ParityError      = 0x04,
    FramingError     = 0x08,
    Break            = 0x10,
    TransmitterEmpty = 0x20,
    FIFOError        = 0x80
};

u8 Serial_ReadRegister(u8 line, u8 offset);
void Serial_WriteRegister(u8 line, u8 offset, u8 value);

void Serial_SetBaudRate(u8 line, Serial_BaudRateDivisor rate = Serial_BaudRateDivisor::Rate115200);
void Serial_SetLineControl(u8 line, Serial_LineControl control);
void Serial_SetInterruptEnable(u8 line, Serial_InterruptEnable enable);

bool Serial_AvailableToRead(u8 line);
bool Serial_AvailableToWrite(u8 line);

u8 Serial_ReadByte(u8 line);
void Serial_WriteByte(u8 line, u8 value);

void Serial_Initialize(u8 line, Serial_BaudRateDivisor rate = Serial_BaudRateDivisor::Rate115200, Serial_LineControl control = Serial_LineControl::Default);

#endif