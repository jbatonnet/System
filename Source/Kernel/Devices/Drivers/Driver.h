#ifndef _KERNEL_DRIVER_H_
#define _KERNEL_DRIVER_H_

#include <System/Common.h>

namespace System
{
    namespace Devices
    {
        class Device;
		class DeviceInfo;

        class Driver : public Object
        {
        public:
            // Accessors
			virtual string GetEditor() = 0;
			__declspec(property(get = GetEditor)) string Editor;
			virtual string GetName() = 0;
			__declspec(property(get = GetName)) string Name;

            // Methods
			virtual void Load() = 0;
			virtual void Unload() = 0;
			virtual bool CanGetDevice(DeviceInfo* deviceInfo) { return false; }
			virtual Device* TryGetDevice(DeviceInfo* deviceInfo) { return null; }
        };
    }
}

#endif