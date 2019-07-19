#ifndef _KERNEL_SERIALDEVICE_H_
#define _KERNEL_SERIALDEVICE_H_

#include <System/Devices/Communication/CommunicationDevice.h>
#include "SerialStream.h"

class SerialDevice : public System::Devices::CommunicationDevice
{
    friend class SerialStream;
    friend void Serial_InterruptHandler();

protected:
    u8 line;
    SerialStream* stream;

    byte* buffer;
    u32 readIndex, writeIndex;

public:
    SerialDevice(u8 line);

    string GetVendor() override { return "Generic"; }
    string GetName() override { return "Serial"; }

    void Load() override { }
    void Unload() override { }

    _declspec(property(get = GetStream)) SerialStream* Stream;
    SerialStream* GetStream() { return stream; }
};

#endif