#ifndef _KERNEL_KEYBOARDDEVICE_H_
#define _KERNEL_KEYBOARDDEVICE_H_

#include <System/Devices/Input/ButtonsDevice.h>

class KeyboardDevice : public System::Devices::ButtonsDevice
{
    friend void Keyboard_InterruptHandler();

public:
    KeyboardDevice();

    string GetVendor() override { return "Generic"; }
    string GetName() override { return "Keyboard"; }

    void Load() override;
    void Unload() override;
};

#endif