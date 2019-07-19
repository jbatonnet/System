#include "SerialDevice.h"
#include "SerialStream.h"
#include "SerialFunctions.h"

#include <HAL/Interrupts.h>

#include <System/Debugging/Console.h>

using namespace System::Devices;

#define SERIALDEVICE_BUFFER_SIZE 4096

SerialDevice* devices[4] = { null };

void Serial_InterruptHandler()
{
    Console::WriteLine("Serial_InterruptHandler");

    u8 line = 0;
    SerialDevice* device = devices[line];

    while (Serial_AvailableToRead(line));
    {
        device->buffer[device->writeIndex] = Serial_ReadByte(line);
        ++device->writeIndex %= SERIALDEVICE_BUFFER_SIZE;
    }
}

SerialDevice::SerialDevice(u8 line) : line(line), CommunicationDevice()
{
    devices[line] = this;

    Serial_Initialize(line);
    stream = new SerialStream(this);

    buffer = Memory::Allocate<byte>(SERIALDEVICE_BUFFER_SIZE);
    readIndex = writeIndex = 0;

    Console::WriteLine("SerialDevice::SerialDevice");

    //Interrupt_AddRequestHandler(0x04, Serial_InterruptHandler);
}