#include <System/Debugging/Console.h>
#include <Kernel/Devices/DeviceManager.h>

#include "PCIController.h"

using namespace System::Devices;

List<PCIDeviceConstructor*> PCIController::deviceConstructors;

Reference<Iterator<Device*>> PCIController::GetIterator() const
{
    return devices.Select<Device*>([](DeviceMapping d) -> Device* { return d.Device; })->GetIterator();
}

void PCIController::Load()
{
    Scan();
}
void PCIController::Unload()
{
}

void PCIController::Scan()
{
    for (u32 bus = 0; bus < 1; bus++)
        ScanBus(bus);
}
void PCIController::ScanBus(u8 bus)
{
    for (u32 slot = 0; slot < 32; slot++)
        ScanDevice(bus, slot);
}
void PCIController::ScanDevice(u8 bus, u8 device)
{
    PCI_Address baseAddress(bus, device, 0);
    PCI_ConfigDevice configDevice = PCI_ReadDevice(baseAddress);

    //Console::WriteLine("  - Device 0x{0:x2}", device);

    byte config[0x40];
    PCI_ConfigHeader* configHeader = (PCI_ConfigHeader*)config;
    PCI_ConfigType0* configType0 = (PCI_ConfigType0*)config;
    PCI_ConfigType1* configType1 = (PCI_ConfigType1*)config;

    PCI_ReadConfig(baseAddress, config);

    u8 functionCount = 1;// configHeader->MultipleFunctions ? 8 : 1;
    for (u8 function = 0; function < functionCount; function++)
    {
        PCI_Address address(bus, device, function);

        if (function)
            configDevice = PCI_ReadDevice(address);

        if (configDevice.VendorId == 0xFFFF)
            continue;

        //Console::WriteLine("{0:x2}.{1:x2}.{2:x2}", bus, device, function);

        if (function)
            PCI_ReadConfig(address, config);

        //string vendorName = db->QueryValue("SELECT name FROM pci_vendors WHERE id = {0}", configDevice.VendorId);
        //string deviceName = db->QueryValue("SELECT name FROM pci_devices WHERE vendor_id = {0} AND device_id = {1}", configDevice.VendorId, configDevice.DeviceId);
        //Console::WriteLine("{0:x2}.{1:x2}.{2:x2} - {3:x4}.{4:x4} - {5} {6}", bus, device, function, configDevice.VendorId, configDevice.DeviceId, vendorName, deviceName);

        PCIDeviceConstructor* pciDeviceConstructor = deviceConstructors.First([&](PCIDeviceConstructor* c) -> bool { return c->VendorId == configDevice.VendorId && c->DeviceId == configDevice.DeviceId; });
        if (pciDeviceConstructor)
        {
            PCIDevice* pciDevice = pciDeviceConstructor->Constructor(bus, device);
            DeviceManager::AddDevice(pciDevice);
        }
        
        switch (configHeader->HeaderType)
        {
            case 0:
                break;

            case 1:
                ScanBus(configType1->SecondaryBus);
                break;

            default:
                Console::WriteLine("HeaderType: {0}", configHeader->HeaderType);
                break;
        }
    }
}