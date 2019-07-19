#ifndef _KERNEL_AMDNETDEVICE_H_
#define _KERNEL_AMDNETDEVICE_H_

#include <System/Common.h>
#include <System/Devices/Communication/NetworkDevice.h>

class AMDNetDevice : public System::Devices::NetworkDevice
{
public:
	AMDNetDevice();

	string GetName() { return "AMD PCnet Lance Network Device"; }
};

#endif