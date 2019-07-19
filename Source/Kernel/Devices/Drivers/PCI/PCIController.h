#ifndef _KERNEL_PCICONTROLLER_H_
#define _KERNEL_PCICONTROLLER_H_

#include <Kernel/Devices/Drivers/PCI/PCIDevice.h>
#include <System/Devices/DeviceEnumerator.h>

struct PCIDeviceConstructor
{
    u16 VendorId;
    u16 DeviceId;
    Function<System::Devices::PCIDevice*, u8, u8> Constructor;
};

class PCIController : public System::Devices::DeviceEnumerator
{
    struct DeviceMapping
    {
        PCI_Address Address;
        bool Loaded;
        System::Devices::PCIDevice* Device;

        DeviceMapping() { }
        bool operator==(const DeviceMapping& other)
        {
            return Address.Value == other.Address.Value;
        }
    };

private:
    static List<PCIDeviceConstructor*> deviceConstructors;
    List<DeviceMapping> devices;

public:
    template<typename T> static void RegisterDevice(u16 vendorId, u16 deviceId)
    {
        PCIDeviceConstructor* deviceConstructor = new PCIDeviceConstructor();

        deviceConstructor->VendorId = vendorId;
        deviceConstructor->DeviceId = deviceId;
        deviceConstructor->Constructor = [](u8 bus, u8 device) -> System::Devices::PCIDevice* { return new T(bus, device); };

        deviceConstructors.Add(deviceConstructor);
    }

public:
    Reference<Iterator<Device*>> GetIterator() const override;

    string GetVendor() override { return "Generic"; }
    string GetName() override { return "PCI Controller"; }

    void Load() override;
    void Unload() override;

    void Scan();
    void ScanBus(u8 bus);
    void ScanDevice(u8 bus, u8 device);
};

#endif