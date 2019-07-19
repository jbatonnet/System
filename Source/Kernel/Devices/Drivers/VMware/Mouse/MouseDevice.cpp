#include "MouseDevice.h"
#include "Mouse.h"

#include <HAL/Interrupts.h>
#include <System/Maths/Maths.h>

#include <System/Devices/Input/InputManager.h>
#include <Kernel/Devices/Drivers/VMware/Tools/Backdoor.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace System::Devices;

MouseDevice* mouse;

u8 mouseBytes[4], lastMouseBytes[4];
Backdoor_MousePacket mousePacket, lastMousePacket;
PointerMoveEvent pointerMoveEvent;

void Mouse_InterruptHandler()
{
    static u8 step = 0;

    switch (step++)
    {
        case 0: mouseBytes[0] = IO_Read8(KEYBOARD_PORT); break;
        case 1: mouseBytes[1] = IO_Read8(KEYBOARD_PORT); break;
        case 2: mouseBytes[2] = IO_Read8(KEYBOARD_PORT); break;
        case 3: mouseBytes[3] = IO_Read8(KEYBOARD_PORT); break;
    }
    step %= 3;

    if (!step)
    {
        Backdoor_MouseGetPacket(&mousePacket);

        pointerMoveEvent.Index = 0;
        pointerMoveEvent.X = 0;
        pointerMoveEvent.Y = 0;

        if (mouse->Loaded)
        {
            InputManager::PointerPosition.X = mousePacket.X * SCREEN_WIDTH / 65535;
            InputManager::PointerPosition.Y = mousePacket.Y * SCREEN_HEIGHT / 65535;

            mouse->PointerMove(mouse, pointerMoveEvent);

            if (!Flag::Test(lastMouseBytes[0], 1) && Flag::Test(mouseBytes[0], 1))
                mouse->PointerDown(mouse, pointerMoveEvent);
            if (Flag::Test(lastMouseBytes[0], 1) && !Flag::Test(mouseBytes[0], 1))
                mouse->PointerUp(mouse, pointerMoveEvent);
        }

        Memory::Copy(mouseBytes, lastMouseBytes, 4);
    }
}

MouseDevice::MouseDevice()
{
    mouse = this;

    Mouse_Enable();
    Backdoor_MouseInitialize();

    Interrupt_AddRequestHandler(0x0C, Mouse_InterruptHandler);
}

void MouseDevice::Load()
{
    loaded = true;
}
void MouseDevice::Unload()
{
    loaded = false;
}