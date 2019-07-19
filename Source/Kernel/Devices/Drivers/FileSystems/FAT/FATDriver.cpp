#include <System/Devices/Storage/FileSystem.h>

#include "FATDriver.h"
#include "FATFileSystem.h"

using namespace System::Devices;

FATDriver::FATDriver()
{
}

void FATDriver::Load()
{
    FileSystem::Register<FAT<u16>>(FileSystemType::Fat16);
    FileSystem::Register<FAT<u32>>(FileSystemType::Fat32);
}
void FATDriver::Unload()
{
}