#ifndef _KERNEL_VMWARE_MOUSEDEVICE_H_
#define _KERNEL_VMWARE_MOUSEDEVICE_H_

#include <System/Devices/Input/PointerDevice.h>

class MouseDevice : public System::Devices::PointerDevice
{
    friend void Mouse_InterruptHandler();

public:
    MouseDevice();

    string GetVendor() override { return "Generic"; }
    string GetName() override { return "Mouse"; }

    void Load() override;
    void Unload() override;
};

#endif