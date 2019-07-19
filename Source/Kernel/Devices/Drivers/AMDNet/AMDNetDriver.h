#ifndef _KERNEL_AMDNETDRIVER_H_
#define _KERNEL_AMDNETDRIVER_H_

#include <System/Common.h>
#include <Kernel/Devices/Drivers/Driver.h>
#include <Kernel/Devices/Drivers/PCI/PCIDriver.h>

class AMDNetDriver : public System::Devices::Driver
{
public:
	AMDNetDriver();

	void Load();
	void Unload();
};

#endif