#include "SVGADevice.h"
#include "SVGA.h"

#include <HAL/IO.h>
#include <HAL/Interrupts.h>
#include <System/System.h>

using namespace System::Devices;
using namespace System::Graphics;
using namespace System::Runtime;

u32 SVGA_ClearIRQ()
{
	u32 flags = 0;
	//Atomic_Exchange(gSVGA.irq.pending, flags);
	return flags;
}

void SVGA_InterruptHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
	Log::WriteLine(Log::Debug, "SVGA_InterruptHandler");

	/*
	* The SVGA_IRQSTATUS_PORT is a separate I/O port, not a register.
	* Reading from it gives us the set of IRQ flags which are
	* set. Writing a '1' to any bit in this register will clear the
	* corresponding flag.
	*
	* Here, we read then clear all flags.
	*/

	/*u16 port = ioBase + SVGA_IRQSTATUS_PORT;
	u32 irqFlags = IO_In32(port);
	IO_Out32(port, irqFlags);

	gSVGA.irq.count++;

	if (!irqFlags) {
		SVGA_Panic("Spurious SVGA IRQ");
	}

	Atomic_Or(gSVGA.irq.pending, irqFlags);

	if (gSVGA.irq.switchContext) {
		memcpy((void*)&gSVGA.irq.oldContext, context, sizeof *context);
		memcpy(context, (void*)&gSVGA.irq.newContext, sizeof *context);
		gSVGA.irq.switchContext = FALSE;
	}*/
}



SVGAOverlay::SVGAOverlay(SVGADevice* device) : device(device), visible(false), position(0, 0), bitmap(null) { }

void SVGAOverlay::SetVisible(bool visible)
{
	this->visible = visible;

	if (true) //SVGA_HasFIFOCap(SVGA_FIFO_CAP_SCREEN_OBJECT))
	{
		device->fifo->CursorScreen = 0xFFFFFFFF;
	}

	if (true) //SVGA_HasFIFOCap(SVGA_FIFO_CAP_CURSOR_BYPASS_3))
	{
		device->fifo->CursorVisible = visible;
		device->fifo->CursorUpdate++;
	}
}
void SVGAOverlay::SetPosition(Point2 position)
{
	this->position = position;

	if (true) //SVGA_HasFIFOCap(SVGA_FIFO_CAP_SCREEN_OBJECT))
	{
		device->fifo->CursorScreen = 0xFFFFFFFF;
	}

	if (true) //SVGA_HasFIFOCap(SVGA_FIFO_CAP_CURSOR_BYPASS_3))
	{
		device->fifo->CursorX = position.X;
		device->fifo->CursorY = position.Y;
		device->fifo->CursorUpdate++;
	}
}
void SVGAOverlay::SetBitmap(System::Graphics::Bitmap* bitmap)
{
	this->bitmap = bitmap;

	struct SVGAFifoCmdDefineAlphaCursor
	{
		u32 id;
		u32 hotspotX;
		u32 hotspotY;
		u32 width;
		u32 height;
	};

	u32 size = bitmap->Size.X * bitmap->Size.Y * 4;
	//SVGAFifoCmdDefineAlphaCursor *cmd = SVGA_FIFOReserveCmd(SVGA_CMD_DEFINE_ALPHA_CURSOR,
	//	sizeof *cmd + size);
	//*cmd = *cursorInfo;
	//*data = (void*)(cmd + 1);

	//SVGAFifoCmdDefineAlphaCursor* cmd = (SVGAFifoCmdDefineAlphaCursor*)device->ReserveCmd(SVGA_CMD_DEFINE_ALPHA_CURSOR, sizeof(SVGAFifoCmdDefineAlphaCursor));
	//cmd->id = 0;
	//cmd->hotspotX = 0;
	//cmd->hotspotY = 0;
	//cmd->width = bitmap->Size.X;
	//cmd->height = bitmap->Size.Y;

	// Add Cursor Info
	// Add BGRA buffer

	device->CommitAll();
}



SVGADevice::SVGADevice(u8 bus, u8 device) : PCIDevice(bus, device, 0)
{
	//Log::WriteLine(Log::Debug, "SVGADevice::Initialize");

	PCI_EnableMemory(address, true);

	//Console::WriteLine("Status: 0x{0:X4}", Header.Base.Status);
	//Console::WriteLine("Command: 0x{0:X4}", Header.Base.Command);
	//Console::WriteLine("Class: 0x{0:X2}", Header.Base.Class);
	//Console::WriteLine("Subclass: 0x{0:X2}", Header.Base.SubClass);
	//Console::WriteLine("Header: 0x{0:X2}", Header.Base.HeaderType);

	ioBase = (u16)(header.Type0.BaseAddress0.IO.Address & 0xFFFC);
	fbMemory = (byte*)(header.Type0.BaseAddress1.Memory.Address & 0xFFFFFFF0);
	fifoMemory = (u32*)(header.Type0.BaseAddress2.Memory.Address & 0xFFFFFFF0);

	version = SVGA_GetVersion(ioBase);

	vramSize = SVGA_ReadRegister(ioBase, SVGA_Register::VRAMSize);
	fbSize = SVGA_ReadRegister(ioBase, SVGA_Register::FrameBufferSize);
	fifoSize = SVGA_ReadRegister(ioBase, SVGA_Register::MemorySize);

	//Console::WriteLine("ioBase: 0x{0:X}", ioBase);
	//Console::WriteLine("fbMemory: {0}", fbMemory);
	//Console::WriteLine("fifoMemory: {0}", fifoMemory);
	//Console::WriteLine("version: 0x{0:X8}", version);
	//Console::WriteLine("vramSize: 0x{0:X}", vramSize);
	//Console::WriteLine("fbSize: 0x{0:X}", fbSize);
	//Console::WriteLine("fifoSize: 0x{0:X}", fifoSize);

	capabilities = SVGA_ReadRegister(ioBase, SVGA_Register::Capabilities);

	#define SVGA_CAP_IRQMASK            0x00040000
	#define SVGA_IRQSTATUS_PORT     0x8

	if (capabilities & SVGA_CAP_IRQMASK)
	{
		u8 irq = header.Type0.InterruptLine;

		/* Start out with all SVGA IRQs masked */
		SVGA_WriteRegister(ioBase, SVGA_Register::IRQMask, 0);

		/* Clear all pending IRQs stored by the device */
		IO_Write32(ioBase + SVGA_IRQSTATUS_PORT, 0xFF);

		/* Clear all pending IRQs stored by us */
		SVGA_ClearIRQ();

		/* Enable the IRQ */
		Interrupt_AddHandler(irq, (InterruptHandler)SVGA_InterruptHandler);
	}

    fifo->Minimum = sizeof(SVGA_Fifo);
    fifo->Maximum = fifoSize;
    fifo->Next = fifo->Minimum;
    fifo->Stop = fifo->Minimum;

    //Console::WriteLine("fifoMinimum: 0x{0:X}", fifo->Minimum);
    //Console::WriteLine("fifoMaximum: 0x{0:X}", fifo->Maximum);
}

void SVGADevice::Load()
{
    //Log::WriteLine(Log::Debug, "SVGADevice::Load");

    //SVGA_WriteRegister(ioBase, SVGA_Register::Enable, true);
    SVGA_WriteRegister(ioBase, SVGA_Register::ConfigDone, true);

    //Log::WriteLine(Log::Debug, "SVGADevice::SetMode");

    //DisplayMode* displayMode = FindDisplayMode(1280, 720);
    //SetDisplayMode(displayMode);

    //Surface* surface = GetDisplay();

    /*u32 color = 0;
    for (;;)
    {
    color++;

    surface->Clear(color);
    Update(0, 0, 1280, 720);

    Timer::Sleep(0);
    }*/

    //Device::Register(this);


    //Console::WriteLine("loop");
    //loop*/
}
void SVGADevice::Unload()
{
    Log::WriteLine(Log::Debug, "SVGADevice::Unload");

    SVGA_WriteRegister(ioBase, SVGA_Register::Enable, false);
    SVGA_WriteRegister(ioBase, SVGA_Register::ConfigDone, false);
}

void* SVGADevice::Reserve(u32 bytes)
{
	u32 min = fifo->Minimum;
	u32 max = fifo->Maximum;
	u32 next = fifo->Next;
	bool reserveable = false;// SVGA_HasFIFOCap(SVGA_FIFO_CAP_RESERVE);

	/*
	* This example implementation uses only a statically allocated
	* buffer.  If you want to support arbitrarily large commands,
	* dynamically allocate a buffer if and only if it's necessary.
	*/
	if (bytes > sizeof _fifo.bounceBuffer || bytes > (max - min))
		Exception::Assert(false, "FIFO command too large");
	if (bytes % 4)
		Exception::Assert(false, "FIFO command length not 32-bit aligned");
	if (_fifo.reservedSize != 0)
		Exception::Assert(false, "FIFOReserve before FIFOCommit");

	_fifo.reservedSize = bytes;

	for (;;)
	{
		u32 stop = fifo->Stop;
		bool reserveInPlace = false;
		bool needBounce = false;

		/*
		* Find a strategy for dealing with "bytes" of data:
		* - reserve in place, if there's room and the FIFO supports it
		* - reserve in bounce buffer, if there's room in FIFO but not
		*   contiguous or FIFO can't safely handle reservations
		* - otherwise, sync the FIFO and try again.
		*/

		if (next >= stop)
		{
			/* There is no valid FIFO data between nextCmd and max */

			if (next + bytes < max || (next + bytes == max && stop > min))
			{
				/*
				* Fastest path 1: There is already enough contiguous space
				* between nextCmd and max (the end of the buffer).
				*
				* Note the edge case: If the "<" path succeeds, we can
				* quickly return without performing any other tests. If
				* we end up on the "==" path, we're writing exactly up to
				* the top of the FIFO and we still need to make sure that
				* there is at least one unused DWORD at the bottom, in
				* order to be sure we don't fill the FIFO entirely.
				*
				* If the "==" test succeeds, but stop <= min (the FIFO
				* would be completely full if we were to reserve this
				* much space) we'll end up hitting the FIFOFull path below.
				*/

				reserveInPlace = true;
			}
			else if ((max - next) + (stop - min) <= bytes)
			{
				/*
				* We have to split the FIFO command into two pieces,
				* but there still isn't enough total free space in
				* the FIFO to store it.
				*
				* Note the "<=". We need to keep at least one DWORD
				* of the FIFO free at all times, or we won't be able
				* to tell the difference between full and empty.
				*/

				Exception::Assert(false, "SVGAFIFOFull");
				//SVGAFIFOFull();
			}
			else
			{
				/*
				* Data fits in FIFO but only if we split it.
				* Need to bounce to guarantee contiguous buffer.
				*/

				needBounce = true;
			}
		}
		else
		{
			/* There is FIFO data between nextCmd and max */

			if (next + bytes < stop)
			{
				/*
				* Fastest path 2: There is already enough contiguous space
				* between nextCmd and stop.
				*/

				reserveInPlace = true;
			}
			else
			{
				/*
				* There isn't enough room between nextCmd and stop.
				* The FIFO is too full to accept this command.
				*/

				Exception::Assert(false, "SVGAFIFOFull");
				//SVGAFIFOFull();
			}
		}

		/*
		* If we decided we can write directly to the FIFO, make sure
		* the VMX can safely support this.
		*/
		if (reserveInPlace)
		{
			if (reserveable || bytes <= 4)
			{
				_fifo.usingBounceBuffer = false;
				if (reserveable)
					fifo->Reserved = bytes;
				return next + (u8*)fifoMemory;
			}
			else
			{
				/*
				* Need to bounce because we can't trust the VMX to safely
				* handle uncommitted data in FIFO.
				*/
				needBounce = true;
			}
		}

		/*
		* If we reach here, either we found a full FIFO, called
		* SVGAFIFOFull to make more room, and want to try again, or we
		* decided to use a bounce buffer instead.
		*/
		if (needBounce)
		{
			_fifo.usingBounceBuffer = true;
			return _fifo.bounceBuffer;
		}
	}
}
void* SVGADevice::ReserveCmd(u32 type, u32 bytes)
{
	u32* cmd = (u32*)Reserve(bytes + 4);
	cmd[0] = type;
	return cmd + 1;
}
void SVGADevice::Commit(u32 bytes)
{
	u32 min = fifo->Minimum;
	u32 max = fifo->Maximum;
	u32 next = fifo->Next;
	bool reserveable = false;// SVGA_HasFIFOCap(SVGA_FIFO_CAP_RESERVE);

	if (_fifo.reservedSize == 0)
		Exception::Assert(false, "FIFOCommit before FIFOReserve");

	_fifo.reservedSize = 0;

	if (_fifo.usingBounceBuffer)
	{
		/*
		* Slow paths: copy out of a bounce buffer.
		*/
		u8* buffer = _fifo.bounceBuffer;

		if (reserveable)
		{
			/*
			* Slow path: bulk copy out of a bounce buffer in two chunks.
			*
			* Note that the second chunk may be zero-length if the reserved
			* size was large enough to wrap around but the commit size was
			* small enough that everything fit contiguously into the FIFO.
			*
			* Note also that we didn't need to tell the FIFO about the
			* reservation in the bounce buffer, but we do need to tell it
			* about the data we're bouncing from there into the FIFO.
			*/

			u32 chunkSize = Maths::Min(bytes, max - next);
			fifo->Reserved = bytes;

			Memory::Copy(buffer, (u8*)fifoMemory + next, chunkSize);
			Memory::Copy(buffer + chunkSize, (u8*)fifoMemory + min, bytes - chunkSize);

			//memcpy(nextCmd + (uint8*)fifo, buffer, chunkSize);
			//memcpy(min + (uint8*)fifo, buffer + chunkSize, bytes - chunkSize);

		}
		else
		{
			/*
			* Slowest path: copy one dword at a time, updating NEXT_CMD as
			* we go, so that we bound how much data the guest has written
			* and the host doesn't know to checkpoint.
			*/

			u32* dword = (u32*)buffer;

			while (bytes > 0)
			{
				fifoMemory[next / 4] = *dword++;
				next += 4;

				if (next == max)
					next = min;

				fifo->Next = next;
				bytes -= 4;
			}
		}
	}

	/*
	* Atomically update NEXT_CMD, if we didn't already
	*/
	if (!_fifo.usingBounceBuffer || reserveable)
	{
		next += bytes;
		if (next >= max)
			next -= max - min;

		fifo->Next = next;
	}

	/*
	* Clear the reservation in the FIFO.
	*/
	if (reserveable)
		fifo->Reserved = 0;
}
void SVGADevice::CommitAll()
{
	Commit(_fifo.reservedSize);
}

System::Devices::DisplayMode* SVGADevice::FindDisplayMode(u16 width, u16 height, u8 bpp, bool exact)
{
	System::Devices::DisplayMode* displayMode = new System::Devices::DisplayMode();

	displayMode->Id = 0;
	displayMode->Width = width;
	displayMode->Height = height;
	displayMode->Bpp = bpp;

	return displayMode;
}
void SVGADevice::SetDisplayMode(System::Devices::DisplayMode* displayMode)
{
	if (!displayMode)
	{
		SVGA_WriteRegister(ioBase, SVGA_Register::Enable, false);
		return;
	}

	// Setup the adapter
    SVGA_WriteRegister(ioBase, SVGA_Register::Width, displayMode->Width);
    SVGA_WriteRegister(ioBase, SVGA_Register::Height, displayMode->Height);
    SVGA_WriteRegister(ioBase, SVGA_Register::BitsPerPixel, displayMode->Bpp);

	// Setup the surface
	if (surface)
		delete surface;

	u32 pitch = SVGA_ReadRegister(ioBase, SVGA_Register::BytesPerLine);
	surface = new System::Graphics::Surface(fbMemory, displayMode->Width, displayMode->Height);

	// Enable display mode
	SVGA_WriteRegister(ioBase, SVGA_Register::Enable, true);
}

void SVGADevice::Update()
{
	if (!surface)
		return;

	Update(0, 0, surface->Size.X, surface->Size.Y);
}
void SVGADevice::Update(u16 x, u16 y, u16 width, u16 height)
{
	struct SVGAFifoCmdUpdate
	{
		u32 x;
		u32 y;
		u32 width;
		u32 height;
	};

	#define SVGA_CMD_UPDATE 1

	SVGAFifoCmdUpdate* cmd = (SVGAFifoCmdUpdate*)ReserveCmd(SVGA_CMD_UPDATE, sizeof(SVGAFifoCmdUpdate));
	cmd->x = x;
	cmd->y = y;
	cmd->width = width;
	cmd->height = height;

	CommitAll();
}