#ifndef _KERNEL_MOUSE_H_
#define _KERNEL_MOUSE_H_

#include <System/Common.h>

#define KEYBOARD_PORT 0x60
#define MOUSE_PORT    0x64

#define MOUSE_COMMAND 0xD4
#define MOUSE_ENABLE  0xA8

#define MOUSE_TIMEOUT 1000

void Mouse_WaitData();
void Mouse_WaitSignal();

void Mouse_Write(u8 data);
u8 Mouse_Read();

void Mouse_Enable();

#endif