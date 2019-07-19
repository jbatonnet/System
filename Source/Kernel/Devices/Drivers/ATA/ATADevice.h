#ifndef _KERNEL_ATADEVICE_H_
#define _KERNEL_ATADEVICE_H_

#include <System/Common.h>
#include <System/Devices/Storage/StorageDevice.h>

class ATADevice : public System::Devices::StorageDevice
{
private:
    u16 bus;
    bool master;

public:
    ATADevice(u16 bus, bool master);

    string GetVendor() override { return "Generic"; }
    string GetName() override { return "Hard drive"; }

    void Load() override { }
    void Unload() override { }

    u32 Read(void* buffer, u64 position, u32 count);
    void Write(void* buffer, u64 position, u32 count);
};

#endif