#include <Kernel/Devices/Drivers/PCI/PCIDevice.h>
#include <System/Data/Database.h>

using namespace System::Data;
using namespace System::Devices;

PCIDevice::PCIDevice(u8 bus, u8 slot, u8 function) : address(bus, slot, function)
{
	PCI_ReadConfig(address, header.Raw);
}

/*string PCIDevice::GetName()
{
    Database* db = Database::Default;
    return db->QueryValue("SELECT name FROM pci_devices WHERE vendor_id = {0} AND id = {1}", configDevice.VendorId, configDevice.DeviceId);
}
string PCIDevice::GetVendor()
{
    Database* db = Database::Default;
    return db->QueryValue("SELECT name FROM pci_vendors WHERE id = {0}", configDevice.VendorId);
}*/