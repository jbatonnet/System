#ifndef _KERNEL_ATADRIVER_H_
#define _KERNEL_ATADRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class ATADriver : public System::Devices::Driver
{
public:
    ATADriver();

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic ATA driver to handle hard drives"; }

    void Load() override;
    void Unload() override;
};

#endif