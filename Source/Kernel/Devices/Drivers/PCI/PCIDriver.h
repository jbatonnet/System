#ifndef _KERNEL_PCIDRIVER_H_
#define _KERNEL_PCIDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

namespace System
{
	namespace Devices
	{
		class PCIDevice;
	}
}

class PCIController;

class PCIDriver : public System::Devices::Driver
{
private:
    PCIController* controller;

public:
    PCIDriver();

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic PCI driver"; }

    void Load() override;
    void Unload() override;
};

#endif