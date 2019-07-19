#ifndef _KERNEL_VESADRIVER_H_
#define _KERNEL_VESADRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class VESADriver : public System::Devices::Driver
{
public:
    VESADriver();

    void Load() override;
    void Unload() override;

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic VESA driver based on VBE"; }
};

#endif