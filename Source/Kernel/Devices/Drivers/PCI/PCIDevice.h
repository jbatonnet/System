#ifndef _KERNEL_PCIDEVICE_H_
#define _KERNEL_PCIDEVICE_H_

#include <System/Common.h>
#include <System/Devices/DeviceEnumerator.h>

#include "PCI.h"

namespace System
{
    namespace Devices
    {
        class PCIDevice : public Device
        {
        protected:
            PCI_Address address;
            
			union
			{
				u8 Raw[0x40];
				PCI_ConfigHeader Base;
				PCI_ConfigType0 Type0;
				PCI_ConfigType1 Type1;
			} header;

        public:
            PCIDevice(u8 bus, u8 device, u8 function);

            virtual u16 GetVendorId() { return header.Base.Device.VendorId; }
			_declspec(property(get = GetVendorId)) u16 VendorId;

			virtual u16 GetDeviceId() { return header.Base.Device.DeviceId; }
			_declspec(property(get = GetDeviceId)) u16 DeviceId;
		};
    }
}

#endif