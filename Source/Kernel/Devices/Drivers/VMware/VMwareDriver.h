#ifndef _KERNEL_VMWAREDRIVER_H_
#define _KERNEL_VMWAREDRIVER_H_

#include <System/Common.h>
#include <Kernel/Devices/Drivers/Driver.h>

class VMwareDriver : public System::Devices::Driver
{
public:
    VMwareDriver();

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic VMware driver to use VMware-specific devices"; }

    void Load() override;
    void Unload() override;
};

#endif