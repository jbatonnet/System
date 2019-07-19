#include "KeyboardDevice.h"
#include "Keyboard.h"

#include <HAL/Interrupts.h>
#include <System/Debugging/Log.h>

using namespace System::Devices;

KeyboardDevice* keyboard;

void Keyboard_InterruptHandler()
{
    static bool released = false;
    static bool extendedCode = false;

    static bool control = false;
    static bool alt = false;
    static bool shift = false;

    static bool numLock = false;
    static bool capsLock = false;

    //if (IsFlag(KBD_GetStatus(), KBD_STATUS_OUT_BUF))
    {
        u8 scanCode = KBD_ReadBuffer();
        released = Flag::Test(scanCode, 0x80);

        if (scanCode == 0xE0)
            extendedCode = true;
        else
        {
            Buttons button;
            if (extendedCode)
                button = keyboard->buttonsMapping[(scanCode & 0x7F) | 0x80];
            else
                button = keyboard->buttonsMapping[scanCode & 0x7F];

            if ((u16)button == 0 && !released)
                Log::WriteLine(Log::Debug, "Keyboard_InterruptHandler() : { ScanCode: 0x{0:X2}, Extended: {1} }", scanCode, extendedCode, (u16)button);
            extendedCode = false;

            RawButtonEvent e;
            e.Button = button;

            if (keyboard->Loaded)
            {
                if (!keyBuffer[(u16)button] && !released)
                    keyboard->ButtonDown(keyboard, e);
                else if (keyBuffer[(u16)button] && released)
                    keyboard->ButtonUp(keyboard, e);
            }

            keyBuffer[(u16)button] = !released;

            if (button == Buttons::NumLock && !released)
                numLock = !numLock;
            if (button == Buttons::CapsLock && !released)
                capsLock = !capsLock;

            if (button == Buttons::NumLock || button == Buttons::CapsLock)
                KBD_SetLEDs(numLock, capsLock, false);
        }
    }
}
void Keyboard_ButtonsMapping(ButtonsMapping& buttonsMapping)
{
    buttonsMapping[0x01] = Buttons::Escape;

    buttonsMapping[0x3B] = Buttons::F1;
    buttonsMapping[0x3C] = Buttons::F2;
    buttonsMapping[0x3D] = Buttons::F3;
    buttonsMapping[0x3E] = Buttons::F4;
    buttonsMapping[0x3F] = Buttons::F5;
    buttonsMapping[0x40] = Buttons::F6;
    buttonsMapping[0x41] = Buttons::F7;
    buttonsMapping[0x42] = Buttons::F8;
    buttonsMapping[0x43] = Buttons::F9;
    buttonsMapping[0x44] = Buttons::F10;
    buttonsMapping[0x57] = Buttons::F11;
    buttonsMapping[0x58] = Buttons::F12;

    buttonsMapping[0x52] = Buttons::Insert;
    buttonsMapping[0xD3] = Buttons::Delete;
    buttonsMapping[0x47] = Buttons::Origin;
    buttonsMapping[0x4F] = Buttons::End;
    buttonsMapping[0x49] = Buttons::PageUp;
    buttonsMapping[0x51] = Buttons::PageDown;

    buttonsMapping[0x29] = Buttons::Oem1;
    
    buttonsMapping[0x02] = Buttons::Digit1;
    buttonsMapping[0x03] = Buttons::Digit2;
    buttonsMapping[0x04] = Buttons::Digit3;
    buttonsMapping[0x05] = Buttons::Digit4;
    buttonsMapping[0x06] = Buttons::Digit5;
    buttonsMapping[0x07] = Buttons::Digit6;
    buttonsMapping[0x08] = Buttons::Digit7;
    buttonsMapping[0x09] = Buttons::Digit8;
    buttonsMapping[0x0A] = Buttons::Digit9;
    buttonsMapping[0x0B] = Buttons::Digit0;

    buttonsMapping[0x0C] = Buttons::Oem2;
    buttonsMapping[0x0D] = Buttons::Oem3;
    buttonsMapping[0x0E] = Buttons::Backspace;

    buttonsMapping[0x0F] = Buttons::Tab;

    buttonsMapping[0x10] = Buttons::A;
    buttonsMapping[0x11] = Buttons::Z;
    buttonsMapping[0x12] = Buttons::E;
    buttonsMapping[0x13] = Buttons::R;
    buttonsMapping[0x14] = Buttons::T;
    buttonsMapping[0x15] = Buttons::Y;
    buttonsMapping[0x16] = Buttons::U;
    buttonsMapping[0x17] = Buttons::I;
    buttonsMapping[0x18] = Buttons::O;
    buttonsMapping[0x19] = Buttons::P;

    buttonsMapping[0x1A] = Buttons::Oem4;
    buttonsMapping[0x1B] = Buttons::Oem5;
    buttonsMapping[0x1C] = Buttons::Enter;
    buttonsMapping[0x9C] = Buttons::Enter;

    buttonsMapping[0x3A] = Buttons::CapsLock;

    buttonsMapping[0x1E] = Buttons::Q;
    buttonsMapping[0x1F] = Buttons::S;
    buttonsMapping[0x20] = Buttons::D;
    buttonsMapping[0x21] = Buttons::F;
    buttonsMapping[0x22] = Buttons::G;
    buttonsMapping[0x23] = Buttons::H;
    buttonsMapping[0x24] = Buttons::J;
    buttonsMapping[0x25] = Buttons::K;
    buttonsMapping[0x26] = Buttons::L;
    buttonsMapping[0x27] = Buttons::M;

    buttonsMapping[0x28] = Buttons::Oem6;
    buttonsMapping[0x2B] = Buttons::Oem7;

    buttonsMapping[0x2A] = Buttons::LeftShift;
    buttonsMapping[0x56] = Buttons::Oem8;

    buttonsMapping[0x2C] = Buttons::W;
    buttonsMapping[0x2D] = Buttons::X;
    buttonsMapping[0x2E] = Buttons::C;
    buttonsMapping[0x2F] = Buttons::V;
    buttonsMapping[0x30] = Buttons::B;
    buttonsMapping[0x31] = Buttons::N;

    buttonsMapping[0x32] = Buttons::Oem9;
    buttonsMapping[0x33] = Buttons::Oem10;
    buttonsMapping[0x34] = Buttons::Oem11;
    buttonsMapping[0x35] = Buttons::Oem12;
    buttonsMapping[0x36] = Buttons::RightShift;

    buttonsMapping[0x1D] = Buttons::LeftControl;
    buttonsMapping[0xDB] = Buttons::Start;
    buttonsMapping[0x38] = Buttons::LeftAlt;

    buttonsMapping[0x39] = Buttons::Space;

    buttonsMapping[0xB8] = Buttons::RightAlt;
    buttonsMapping[0xDD] = Buttons::Menu;
    buttonsMapping[0x9D] = Buttons::RightControl;

    buttonsMapping[0xC8] = Buttons::Up;
    buttonsMapping[0xCD] = Buttons::Right;
    buttonsMapping[0xD0] = Buttons::Down;
    buttonsMapping[0xCB] = Buttons::Left;

    buttonsMapping[0x45] = Buttons::NumLock;
}

KeyboardDevice::KeyboardDevice()
{
    keyboard = this;

    Keyboard_ButtonsMapping(buttonsMapping);
    Interrupt_AddRequestHandler(0x01, Keyboard_InterruptHandler);
}

void KeyboardDevice::Load()
{
    loaded = true;
}
void KeyboardDevice::Unload()
{
    loaded = false;
}