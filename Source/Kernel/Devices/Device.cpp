#include <HAL/HAL.h>

#include <System/Devices/Storage/FileSystem.h>
#include <System/Devices/Storage/StorageDevice.h>
#include <System/Devices/Display/DisplayDevice.h>
#include <System/Devices/Communication/CommunicationDevice.h>
#include <System/Devices/Input/InputManager.h>

#include <Kernel/Devices/Screen/Screen.h>

using namespace System::Devices;
using namespace System::IO;

/*List<Device*>* Device::devices = null;

void Device::Register(StorageDevice* device)
{
    if (!devices)
        devices = new List<Device*>();
    devices->Add(device);

    for (u32 i = 0; i < device->FileSystems->Count; i++)
    {
        FileSystem* fileSystem = (*device->FileSystems)[i];

        if (!Directory::Root)
            Directory::Current = Directory::Root = fileSystem->Root;
    }
}
void Device::Register(PointerDevice* device)
{
    if (!devices)
        devices = new List<Device*>();
    devices->Add(device);

    InputManager::AddDevice(device, true);
}
void Device::Register(ButtonsDevice* device)
{
    if (!devices)
        devices = new List<Device*>();
    devices->Add(device);

    InputManager::AddDevice(device);
}
void Device::Register(DisplayDevice* device)
{
    if (!devices)
        devices = new List<Device*>();
    devices->Add(device);
}
void Device::Register(CommunicationDevice* device)
{
    if (!devices)
        devices = new List<Device*>();
    devices->Add(device);
}*/