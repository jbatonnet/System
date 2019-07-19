#include "VMwareDriver.h"

#include <Kernel/Devices/Drivers/PCI/PCIController.h>

#include "Mouse/MouseDevice.h"
#include "SVGA/SVGADevice.h"
#include "AMDNet/AMDNetDevice.h"

using namespace System::Devices;

VMwareDriver::VMwareDriver()
{
}

void VMwareDriver::Load()
{
    //MouseDevice* mouseDevice = new MouseDevice();
    //devices->Add(mouseDevice);
    //Device::Register(mouseDevice);

	// Register PCI devices
	PCIController::RegisterDevice<SVGADevice>(0x15AD, 0x0405);
    //PCIController::RegisterDevice<AMDNetDevice>(0x1022, 0x2000);
}
void VMwareDriver::Unload()
{
}