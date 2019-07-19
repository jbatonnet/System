#include "SerialDriver.h"
#include "SerialDevice.h"

#include <Kernel/Devices/DeviceManager.h>
#include <System/Debugging/Serial.h>
#include <System/IO/Streams/TextStream.h>

using namespace System::Devices;
using namespace System::IO;

SerialDriver::SerialDriver()
{
}

void SerialDriver::Load()
{
    for (u8 i = 0; i < 1; i++)
    {
        SerialDevice* device = new SerialDevice(i);
        DeviceManager::AddDevice(device);

        Serial::BaseStream = new TextStream(device->Stream);
    }
}
void SerialDriver::Unload()
{
}