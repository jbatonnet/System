#ifndef _KERNEL_VFS_H_
#define _KERNEL_VFS_H_

#include <System/Common.h>
#include <System/Devices/Storage/FileSystem.h>

using namespace System::Devices;

namespace System
{
    namespace Devices
    {
        namespace Drivers
        {
            class VFS : public FileSystem
            {
            protected:
                IO::Directory *_system, *storage, *temp, *users, *apps;

            public:
                VFS();
                virtual ~VFS() { }

                // Accessors
                __declspec(property(get = GetSystem)) IO::Directory* System;
                IO::Directory* GetSystem() { return _system; }
                __declspec(property(get = GetStorage)) IO::Directory* Storage;
                IO::Directory* GetStorage() { return storage; }

                // Methods
                IO::File* GetFile(string path) { return null; }
            };
        }
    }
}

#endif