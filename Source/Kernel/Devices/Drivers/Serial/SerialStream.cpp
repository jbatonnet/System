#include "SerialStream.h"
#include "SerialDevice.h"
#include "SerialFunctions.h"

#include <Kernel/Runtime/Threading/Task.h>

using namespace System::Runtime;

#define SERIALDEVICE_BUFFER_SIZE 4096

SerialStream::SerialStream(SerialDevice* device) : device(device) { }

u32 SerialStream::Read(void* buffer, u32 count)
{
    u8* data = (u8*)buffer;

    for (u32 i = 0; i < count; i++)
    {
        if (device->readIndex == device->writeIndex)
            return i;

        data[i] = device->buffer[device->readIndex];
        ++device->readIndex %= SERIALDEVICE_BUFFER_SIZE;
    }

    return count;
}
void SerialStream::Write(void* buffer, u32 count)
{
    u8* data = (u8*)buffer;

    lock (spinLock)
    {
        for (u32 i = 0; i < count; i++)
            Serial_WriteByte(device->line, data[i]);
    }
}