#ifndef _KERNEL_DEVICEMANAGER_H_
#define _KERNEL_DEVICEMANAGER_H_

#include <System/Common.h>
#include <System/Debugging/Log.h>
#include <System/Structures/Collections/List.h>
#include <Kernel/Devices/Drivers/Driver.h>

namespace System
{
	namespace Devices
	{
		class Device;

        class DeviceManager
        {
		private:
			static List<Driver*> drivers;
            static List<Device*> devices;

            static void RegisterDriver(Driver* driver);
            static void UnregisterDriver(Driver* driver);

		public:
            /// <summary>
            /// Registers and loads a new driver in the kernel
            /// </summary>
			template<typename T> static void RegisterDriver()
			{
                T* driver = new T();
                RegisterDriver(driver);
			}
            template<typename T> static void UnregisterDriver()
            {
                foreach (Driver*, driver, drivers)
                {
                    if (driver->Is<T>())
                    {
                        UnregisterDriver(driver);
                        return;
                    }
                }
            }

            /// <summary>
            /// Adds a new device in the system
            /// </summary>
            static void AddDevice(Device* device);

            /// <summary>
            /// Adds a new device in the system
            /// </summary>
            static void RemoveDevice(Device* device);

            template<typename T> static T* GetDevice()
            {
                for (int i = 0; i < devices.Count; i++)
                    if (devices[i]->Is<T>())
                        return devices[i]->As<T>();

                return null;
            }
        };
	}
}

#endif