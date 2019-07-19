#ifndef _SYSTEM_STORAGEDEVICE_H_
#define _SYSTEM_STORAGEDEVICE_H_

#include <System/Common.h>
#include <System/Devices/Device.h>
#include <System/Structures/Collections/List.h>

namespace System
{
    namespace Devices
    {
        class FileSystem;

        class StorageDevice : public Device
        {
        protected:
            List<FileSystem*>* fileSystems;

        public:
            StorageDevice()
            {
                fileSystems = new List<FileSystem*>();
            }
    
            _declspec(property(get = GetFileSystems)) List<FileSystem*>* FileSystems;
            List<FileSystem*>* GetFileSystems() { return fileSystems; }

            virtual u32 Read(void* buffer, u64 position, u32 count) = 0;
            virtual void Write(void* source, u64 position, u32 count) = 0;
        };
    }
}

#endif