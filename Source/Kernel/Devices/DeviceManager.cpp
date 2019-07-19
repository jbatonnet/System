#include <Kernel/Devices/DeviceManager.h>

#include <System/Devices/Device.h>
#include <System/Devices/Storage/StorageDevice.h>
#include <System/Devices/Communication/CommunicationDevice.h>
#include <System/Devices/Display/DisplayDevice.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>
#include <System/Devices/Input/InputManager.h>

#include <System/IO/Directory.h>
#include <System/Runtime/Reflection/Type.h>
#include <System/Devices/Storage/FileSystem.h>

using namespace System::Devices;
using namespace System::IO;

List<Driver*> DeviceManager::drivers;
List<Device*> DeviceManager::devices;

void DeviceManager::RegisterDriver(Driver* driver)
{
    if (!driver)
        return;

    //Log::WriteLine(Log::Trace, "DeviceManager::RegisterDriver({0})", driver->GetType()->FullName);

    drivers.Add(driver);
    driver->Load();
}
void DeviceManager::UnregisterDriver(Driver* driver)
{
    if (!driver)
        return;

    drivers.Remove(driver);
    driver->Unload();
}

void DeviceManager::AddDevice(Device* device)
{
    if (!device)
        return;

    //Log::WriteLine(Log::Trace, "DeviceManager::AddDevice({0})", device->GetType()->FullName);

    devices.Add(device);
    device->Load();

    StorageDevice* storageDevice = device->As<StorageDevice>();
    if (storageDevice)
    {
        if (Directory::Root == null)
        {
            Exception::Assert(storageDevice->FileSystems->Count > 0, "A storage device must have at least one filesystem");

            FileSystem* fileSystem = storageDevice->FileSystems->First();
            Directory* root = fileSystem->Root;

            //Log::WriteLine(Log::Debug, "Setting root directory on {0}, {1}", device->Name, fileSystem->Name);

            Directory::Current = Directory::Root = root;
        }
    }

    CommunicationDevice* communicationDevice = device->As<CommunicationDevice>();
    if (communicationDevice)
    {
    }

    DisplayDevice* displayDevice = device->As<DisplayDevice>();
    if (displayDevice)
    {
    }

    PointerDevice* pointerDevice = device->As<PointerDevice>();
    if (pointerDevice)
        InputManager::AddDevice(pointerDevice);

    ButtonsDevice* buttonsDevice = device->As<ButtonsDevice>();
    if (buttonsDevice)
        InputManager::AddDevice(buttonsDevice);
}
void DeviceManager::RemoveDevice(Device* device)
{
    if (!device)
        return;

    devices.Remove(device);
    device->Unload();
}