#ifndef _SYSTEM_DEVICE_H_
#define _SYSTEM_DEVICE_H_

#include <System/Common.h>

namespace System
{
    namespace Devices
    {
        /// <summary>
        /// Represents a device in this system
        /// </summary>
        class Device : public Object
        {
        protected:
            bool loaded;

        public:
            // Accessors
            virtual string GetVendor() = 0;
            __declspec(property(get = GetVendor)) string Vendor;
            virtual string GetName() = 0;
            __declspec(property(get = GetName)) string Name;
            bool GetLoaded() const { return loaded; }
            _declspec(property(get = GetLoaded)) bool Loaded;

            // Methods
            virtual void Load() = 0;
            virtual void Unload() = 0;
           
        };
    }
}

#endif