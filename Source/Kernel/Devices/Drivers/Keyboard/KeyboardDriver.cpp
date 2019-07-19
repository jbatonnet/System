#include <Kernel/Devices/DeviceManager.h>

#include "KeyboardDriver.h"
#include "KeyboardDevice.h"
#include "Keyboard.h"

using namespace System::Devices;

KeyboardDriver::KeyboardDriver()
{
}

void KeyboardDriver::Load()
{
    Device* device = new KeyboardDevice();
    DeviceManager::AddDevice(device);
}
void KeyboardDriver::Unload()
{
}