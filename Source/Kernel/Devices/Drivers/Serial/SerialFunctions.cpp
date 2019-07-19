#include "SerialFunctions.h"

#include <HAL/IO.h>
#include <Kernel/Runtime/Threading/Task.h>
#include <System/Utilities/Time/Timer.h>

#include <Kernel/Devices/Screen/Screen.h>

u16 Serial_BasePorts[] = { 0x03F8, 0x02F8, 0x03E8, 0x02E8 };

u8 Serial_ReadRegister(u8 line, u8 offset)
{
    Exception::Assert(line < 4, "Only 4 serial lines are supported");
    return IO_Read8(Serial_BasePorts[line] + offset);
}
void Serial_WriteRegister(u8 line, u8 offset, u8 value)
{
    Exception::Assert(line < 4, "Only 4 serial lines are supported");
    IO_Write8(Serial_BasePorts[line] + offset, value);
}

void Serial_SetBaudRate(u8 line, Serial_BaudRateDivisor rate)
{
    Exception::Assert(line < 4, "Only 4 serial lines are supported");
    Task::BeginCritical();

    Serial_SetLineControl(line, Serial_LineControl::DLAB);
    Serial_WriteRegister(line, 0, rate);
    Serial_WriteRegister(line, 1, 0);

    Task::EndCritical();
}
void Serial_SetLineControl(u8 line, Serial_LineControl control)
{
    Serial_WriteRegister(line, SERIAL_OFFSET_LINE_CONTROL, control);
}
void Serial_SetInterruptEnable(u8 line, Serial_InterruptEnable enable);

bool Serial_AvailableToRead(u8 line)
{
    return Serial_ReadRegister(line, SERIAL_OFFSET_LINE_STATUS) & 1;
}
bool Serial_AvailableToWrite(u8 line)
{
    return Serial_ReadRegister(line, SERIAL_OFFSET_LINE_STATUS) & 0x20;
}

u8 Serial_ReadByte(u8 line)
{
    while (!Serial_AvailableToRead(line));
    return Serial_ReadRegister(line, 0);
}
void Serial_WriteByte(u8 line, u8 value)
{
    while (!Serial_AvailableToWrite(line));
    Serial_WriteRegister(line, 0, value);
}

void Serial_Initialize(u8 line, Serial_BaudRateDivisor rate, Serial_LineControl control)
{
    Exception::Assert(line < 4, "Only 4 serial lines are supported");

    // Disable interrupts
    //Serial_SetBaudRate(line, rate);
    //Serial_SetLineControl(line, control);
    // Enable FIFO
    // Enable interrupts

    IO_Write8(Serial_BasePorts[line] + 1, 0x00); // Disable all interrupts
    IO_Write8(Serial_BasePorts[line] + 3, 0x80); // Enable DLAB (set baud rate divisor)
    IO_Write8(Serial_BasePorts[line] + 0, 0x01); // Set divisor to 1 (lo byte) 115200 baud
    IO_Write8(Serial_BasePorts[line] + 1, 0x00); //                  (hi byte)
    IO_Write8(Serial_BasePorts[line] + 3, 0x03); // 8 bits, no parity, one stop bit
    IO_Write8(Serial_BasePorts[line] + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    IO_Write8(Serial_BasePorts[line] + 4, 0x0B); // IRQs enabled, RTS/DSR set

    IO_Write8(Serial_BasePorts[line] + 1, 0x01); // Enable all interrupts
}