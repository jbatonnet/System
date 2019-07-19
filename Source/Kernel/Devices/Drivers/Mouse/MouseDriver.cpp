#include <Kernel/Devices/DeviceManager.h>

#include "MouseDriver.h"
#include "MouseDevice.h"
#include "Mouse.h"

using namespace System::Devices;

MouseDriver::MouseDriver()
{
}

void MouseDriver::Load()
{
    Device* device = new MouseDevice();
    DeviceManager::AddDevice(device);
}
void MouseDriver::Unload()
{
}