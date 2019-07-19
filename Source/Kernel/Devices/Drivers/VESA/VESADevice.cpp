#include "VESADevice.h"
#include "VESA.h"

#include <Kernel/Runtime/Threading/Thread.h>

using namespace System::Graphics;
using namespace System::Runtime;

#pragma optimize("", off)

VbeModeInfo modeInformations;
VESADevice* vesaDevice;
Thread* vSyncThread;

void VESADevice_VSyncThread()
{
    for (;;)
    {
        while (IO_Read8(0x03DA) & 0x08);
        while (!(IO_Read8(0x03DA) & 0x08));

        vesaDevice->vSync->Send();
    }
}

VESADevice::VESADevice(VbeInfo* informations)
{
    // Listing all video modes
    u16* modes = (u16*)(informations->VideoModes[1] << 4 | informations->VideoModes[0]);
    for (u16 i = 0; modes[i] != 0xFFFF; i++)
    {
        modeInformations = VESA_GetModeInformations(modes[i]);

        VESADisplayMode* displayMode = new VESADisplayMode();
        displayMode->Id = modes[i];
        displayMode->Width = modeInformations.Width;
        displayMode->Height = modeInformations.Height;
        displayMode->Pitch = modeInformations.Pitch;
        displayMode->Bpp = modeInformations.Bpp;
        displayMode->Address = modeInformations.Address;
        
        displayModes.Add(displayMode);
    }

    // VSync
    vesaDevice = this;
    //vSync = new Signal();
    //vSyncThread = new Thread(&VESADevice_VSyncThread);
    //vSyncThread->Start();
}
void VESADevice::SetDisplayMode(System::Devices::DisplayMode* displayMode)
{
	displayMode = null;// displayModes.First([&](System::Devices::DisplayMode* m) { return m->Id == displayMode->Id; });
    Exception::Assert(displayMode, "Invalid display mode for this device");

    VESADisplayMode* vesaDisplayMode = (VESADisplayMode*)displayMode;
    VESA_SetMode(vesaDisplayMode->Id);

    //VMM_InitializeVideo((void*)vesaDisplayMode->Address);

    display = new System::Graphics::Surface((void*)vesaDisplayMode->Address, vesaDisplayMode->Width, vesaDisplayMode->Height, vesaDisplayMode->Pitch - vesaDisplayMode->Width * 4);
}

#pragma optimize("", on)