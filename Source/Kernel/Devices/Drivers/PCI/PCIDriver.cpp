#include <Kernel/Devices/DeviceManager.h>

#include "PCIDriver.h"
#include "PCIController.h"
#include "PCI.h"

using namespace System::Devices;

PCIDriver::PCIDriver()
{
}

void PCIDriver::Load()
{
    controller = new PCIController();
    DeviceManager::AddDevice(controller);
}
void PCIDriver::Unload()
{
    DeviceManager::RemoveDevice(controller);
}