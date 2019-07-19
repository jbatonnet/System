#ifndef _KERNEL_AMDNETDEVICE_H_
#define _KERNEL_AMDNETDEVICE_H_

#include <System/Common.h>
#include <Kernel/Devices/Drivers/PCI/PCIDevice.h>
#include <System/Devices/Communication/NetworkDevice.h>

class AMDNetDevice : public System::Devices::PCIDevice, public System::Devices::NetworkDevice
{
public:
	AMDNetDevice(u8 bus, u8 device);

    string GetVendor() { return "Dju'"; }
    string GetName() { return "AMD PCnet Lance Network Device"; }

    void Load() override;
    void Unload() override;
};

#endif