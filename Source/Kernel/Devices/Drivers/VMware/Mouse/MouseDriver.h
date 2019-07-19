#ifndef _KERNEL_MOUSEDRIVER_H_
#define _KERNEL_MOUSEDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>
#include "MouseDevice.h"

class MouseDriver : public System::Devices::Driver
{
private:
    MouseDevice* mouse;

public:
    MouseDriver();

    _declspec(property(get = GetMouse)) MouseDevice* Mouse;
    MouseDevice* GetMouse() { return mouse; }
    
    void Load();
    void Unload();

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "VMWare mouse driver"; }
};

#endif