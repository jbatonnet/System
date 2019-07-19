#ifndef _KERNEL_MOUSEDEVICE_H_
#define _KERNEL_MOUSEDEVICE_H_

#include <System/Devices/Input/PointerDevice.h>

class MouseDevice : public System::Devices::PointerDevice
{
    friend void Mouse_InterruptHandler();

public:
    MouseDevice();

    string GetName() override { return "Mouse"; }
    string GetVendor() override { return "Dju'"; }

    void Load() override { }
    void Unload() override { }
};

#endif