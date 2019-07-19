#ifndef _KERNEL_SVGADEVICE_H_
#define _KERNEL_SVGADEVICE_H_

#include <System/Common.h>
#include <Kernel/Devices/Drivers/PCI/PCIDevice.h>
#include <System/Devices/Display/DisplayDevice.h>

#include "SVGA.h"

class SVGADevice;

class SVGAOverlay : public System::Devices::DisplayOverlay
{
private:
	SVGADevice* device;
	bool visible;
	Point2 position;
	System::Graphics::Bitmap* bitmap;

public:
	SVGAOverlay(SVGADevice* device);

	bool GetVisible() override { return visible; }
	void SetVisible(bool visible) override;

	Point2 GetPosition() override { return position; }
	void SetPosition(Point2 position) override;

	System::Graphics::Bitmap* GetBitmap() override { return bitmap; }
	void SetBitmap(System::Graphics::Bitmap* bitmap) override;
};

class SVGADevice : public System::Devices::PCIDevice, public System::Devices::DisplayDevice
{
	friend class SVGAOverlay;

private:
	u32 ioBase;

	union
	{
		u32* fifoMemory;
		SVGA_Fifo* fifo;
	};
	u32 fifoSize;

	byte* fbMemory;
	u32 fbSize;

	u32 vramSize;

	u32 version;
	u32 capabilities;

	u32 width;
	u32 height;
	u32 bpp;
	u32 pitch;

	struct
	{
		u32  reservedSize;
		bool    usingBounceBuffer;
        u8   bounceBuffer[1024];// 1024 * 1024];
		u32  nextFence;
	} _fifo;

	volatile struct
	{
		u32        pending;
		u32        switchContext;
		//IntrContext   oldContext;
		//IntrContext   newContext;
		u32        count;
	} _irq;

	void* Reserve(u32 count);
	void* ReserveCmd(u32 type, u32 bytes);

	void Commit(u32 count);
	void CommitAll();

	System::Graphics::Surface* surface;
	System::Devices::DisplayMode* displayMode;
	System::Runtime::Signal* vSync;
	System::Devices::DisplayOverlay* overlay;

public:
	SVGADevice(u8 bus, u8 device);

    string GetVendor() { return "Dju'"; }
    string GetName() { return "Basic SVGA display device"; }

    void Load() override;
    void Unload() override;

    System::Graphics::Surface* GetSurface() override { return surface; }
	System::Runtime::Signal* GetVSync() override { return vSync; }
	System::Devices::DisplayOverlay* GetOverlay() override { return overlay; }

	System::Devices::DisplayMode* FindDisplayMode(u16 width, u16 height, u8 bpp = 32, bool exact = true) override;
	System::Devices::DisplayMode* GetDisplayMode() override { return displayMode; }
	void SetDisplayMode(System::Devices::DisplayMode* displayMode) override;

	void Update() override;
	void Update(u16 x, u16 y, u16 width, u16 height) override;
};

#endif