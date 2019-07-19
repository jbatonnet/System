#include "VESADriver.h"
#include "VESADevice.h"
#include "VESA.h"

VbeInfo informations;

VESADriver::VESADriver()
{
}

void VESADriver::Load()
{
    // Get VBE informations
    informations = VESA_GetInformations();

    // Register VESA device
    //VESADevice* device = new VESADevice(&informations);
    //devices->Add(device);
    //Device::Register(device);
}
void VESADriver::Unload() { }