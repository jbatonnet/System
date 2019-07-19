#include "Mouse.h"
#include <HAL/IO.h>

#include <Kernel/Devices/Screen/Screen.h>

inline void Mouse_WaitData()
{
    //u32 timeout = MOUSE_TIMEOUT;
    while (!(IO_Read8(MOUSE_PORT) & 1));// && timeout--);
}
inline void Mouse_WaitSignal()
{
    //u32 timeout = MOUSE_TIMEOUT;
    while ((IO_Read8(MOUSE_PORT) & 2));// && timeout--);
}

inline void Mouse_Write(u8 data)
{
    Mouse_WaitSignal();
    IO_Write8(MOUSE_PORT, MOUSE_COMMAND);

    Mouse_WaitSignal();
    IO_Write8(KEYBOARD_PORT, data);
}
inline u8 Mouse_Read()
{
    Mouse_WaitData();
    return IO_Read8(KEYBOARD_PORT);
}

void Mouse_Enable()
{
    // Enable the mouse
    Mouse_WaitSignal();
    IO_Write8(MOUSE_PORT, MOUSE_ENABLE);

    // Enable the interrupts
    Mouse_WaitSignal();
    IO_Write8(MOUSE_PORT, 0x20);
    Mouse_WaitData();
    u8 status = IO_Read8(KEYBOARD_PORT) | 0x02;

    Mouse_WaitSignal();
    IO_Write8(MOUSE_PORT, 0x60);
    Mouse_WaitSignal();
    IO_Write8(KEYBOARD_PORT, status);
  
    // Use the default settings
    Mouse_Write(0xF6);
    u8 value = Mouse_Read();
  
    // Enable the mouse
    Mouse_Write(0xF4);
    value = Mouse_Read();
}