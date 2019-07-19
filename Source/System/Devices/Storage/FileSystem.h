#ifndef _SYSTEM_FILESYSTEM_H_
#define _SYSTEM_FILESYSTEM_H_

#include <System/Common.h>
#include <System/Structures/Collections/Dictionary.h>

namespace System
{
    namespace IO
    {
        class Directory;
        class File;
        class FileStream;
    };

    namespace Devices
    {
        class StorageDevice;
        class FileSystem;

        struct FileSystemConstructorBase
        {
            virtual FileSystem* operator()(StorageDevice* device, u64 position) = 0;
        };
        template<typename T> struct FileSystemConstructor : public FileSystemConstructorBase
        {
            FileSystem* operator()(StorageDevice* device, u64 position)
            {
                return new T(device, position);
            }
        };

        enum class FileSystemType : u8
        {
            None  = 0x00,
            Fat16 = 0x06,
            ExFat = 0x07,
            Fat32,
        };

        class FileSystem
        {
        private:
            static FileSystemConstructorBase* fileSystems[256];

        protected:
            StorageDevice* device; // Not here ...
            u64 position;
            IO::Directory* root;
            string name;

            FileSystem() { }

        public:
            // Accessors
            _declspec(property(get = GetRoot)) IO::Directory* Root;
            IO::Directory* GetRoot() { return root; }
            _declspec(property(get = GetName)) string Name;
            virtual string GetName() { return name; }

            // Methods
            //virtual File* GetFile(string path);
            //virtual File* CreateFile(Directory* directory, string name) = 0;
            //virtual File* MoveFile(File* file, Directory* destination, string name = null) = 0;

            // Static
            template<typename T> static void Register(FileSystemType type)
            {
                fileSystems[(u8)type] = new FileSystemConstructor<T>();
            }
            static FileSystem* Create(FileSystemType type, StorageDevice* device, u64 position);

            u32 Read(char* buffer, u32 offset, u64 position, u32 count);
            void Write(char* source, u32 offset, u64 position, u32 count);
        };
    }
}

#endif