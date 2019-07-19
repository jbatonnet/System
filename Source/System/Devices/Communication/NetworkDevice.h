#ifndef _SYSTEM_NETWORKDEVICE_H_
#define _SYSTEM_NETWORKDEVICE_H_

#include <System/Common.h>
#include <System/Devices/Device.h>
#include <System/Devices/Communication/CommunicationDevice.h>

namespace System
{
	namespace Devices
	{
		class NetworkDevice : public CommunicationDevice
		{
		protected:

		public:
			NetworkDevice();
		};
	}
}

#endif