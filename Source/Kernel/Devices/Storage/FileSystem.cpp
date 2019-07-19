#include <System/Devices/Storage/FileSystem.h>
#include <System/IO/Directory.h>

using namespace System::Devices;
using namespace System::IO;

/*File* FileSystem::Open(const char* path)
{
    char* str = (char*)path;
    if (*str == '/')
        str++;
    return root->GetFile(str);
    // The filesystem should resolve it instead of Vfs
}*/

FileSystemConstructorBase* FileSystem::fileSystems[256];

FileSystem* FileSystem::Create(FileSystemType type, StorageDevice* device, u64 position)
{
    FileSystemConstructorBase* constructor = fileSystems[(u8)type];
    return constructor ? (*constructor)(device, position) : null;
}

u32 FileSystem::Read(char* buffer, u32 offset, u64 position, u32 count)
{
    // TODO: Check if position in partition
    //return device->Read(buffer, offset, this->position + position, count);
    return 0;
}
void FileSystem::Write(char* source, u32 offset, u64 position, u32 count)
{
}
