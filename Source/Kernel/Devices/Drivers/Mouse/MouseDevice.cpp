#include "MouseDevice.h"
#include "Mouse.h"

#include <HAL/Interrupts.h>
#include <System/Maths/Maths.h>

using namespace System::Devices;

MouseDevice* mouse;
u8 lastMousePacket[4];
u8 mousePacket[4];

void Mouse_InterruptHandler()
{
    static u8 step = 0;

    switch (step++)
    {
        case 0: mousePacket[0] = IO_Read8(KEYBOARD_PORT); break;
        case 1: mousePacket[1] = IO_Read8(KEYBOARD_PORT); break;
        case 2: mousePacket[2] = IO_Read8(KEYBOARD_PORT); break;
        case 3: mousePacket[3] = IO_Read8(KEYBOARD_PORT); break;
    }
    step %= 3;

    if (!step)
    {
        PointerMoveEvent move;

        move.Index = 0;
        move.X = mousePacket[1];
        move.Y = mousePacket[2];

        mouse->PointerMove(mouse, move);

        if (!Flag::Test(lastMousePacket[0], 1) && Flag::Test(mousePacket[0], 1))
            mouse->PointerDown(mouse, move);
        if (Flag::Test(lastMousePacket[0], 1) && !Flag::Test(mousePacket[0], 1))
            mouse->PointerUp(mouse, move);

        Memory::Copy(mousePacket, lastMousePacket, 4);
    }
}

MouseDevice::MouseDevice()
{
    mouse = this;

    Mouse_Enable();
    Interrupt_AddRequestHandler(0x0C, Mouse_InterruptHandler);
}