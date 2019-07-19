#ifndef _KERNEL_MOUSEDRIVER_H_
#define _KERNEL_MOUSEDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class MouseDriver : public System::Devices::Driver
{
public:
    MouseDriver();

    void Load() override;
    void Unload() override;

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic mouse driver"; }
};

#endif