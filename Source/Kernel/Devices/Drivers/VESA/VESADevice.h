#ifndef _KERNEL_VESADEVICE_H_
#define _KERNEL_VESADEVICE_H_

#include <System/Common.h>
#include <System/Devices/Display/DisplayDevice.h>

struct VbeInfo;

struct VESADisplayMode : System::Devices::DisplayMode
{
    u16 Pitch;
    u32 Address;
};

class VESADevice : public System::Devices::DisplayDevice
{
    friend void VESADevice_VSyncThread();

protected:
	System::Graphics::Surface* display;
	List<System::Devices::DisplayMode*> displayModes;
	System::Runtime::Signal* vSync;

public:
    VESADevice(VbeInfo* informations);

	System::Runtime::Signal* GetVSync() override { return vSync; }
	void SetDisplayMode(System::Devices::DisplayMode* displayMode) override;

    string GetName() { return "VESA Display"; }
    string GetVendor() { return "Dju'"; }
};

#endif