#include <HAL/Interrupts.h>
#include <Kernel/Kernel.h>
#include <Kernel/Devices/DeviceManager.h>

#include "ATADriver.h"
#include "ATADevice.h"
#include "ATA.h"

using namespace System::Devices;

ATADriver::ATADriver()
{
    //devices = new List<Device*>();
}

void ATADriver::Load()
{
    Interrupt_Disable();

    for (int drive = 0; drive < 1; drive++) // < 2
    {
        bool master = !drive;

        // Identification of ATA devices
        // TODO: Handle errors
        // TODO: Check if the device is present
        ATA_IdentifyData identifyData;
        ATA_Identify(IO_PRIMARY, master, &identifyData);

        // Add the device
        ATADevice* device = new ATADevice(IO_PRIMARY, master);
        DeviceManager::AddDevice(device);
    }

    Interrupt_Enable();
}
void ATADriver::Unload()
{

}