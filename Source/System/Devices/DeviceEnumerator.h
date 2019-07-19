#ifndef _SYSTEM_DEVICEENUMERATOR_H_
#define _SYSTEM_DEVICEENUMERATOR_H_

#include <System/Devices/Device.h>

namespace System
{
	namespace Devices
	{
		class DeviceEnumerator : public Device, public Collection<Device*>
		{
        };
	}
}

#endif