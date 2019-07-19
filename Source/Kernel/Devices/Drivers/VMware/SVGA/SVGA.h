#ifndef _KERNEL_SVGA_H_
#define _KERNEL_SVGA_H_

#include <System/Common.h>

enum class SVGA_VersionId : u32
{
    Version0 = 0x90000000,
    Version1 = 0x90000001,
    Version2 = 0x90000002,

    Invalid  = 0xFFFFFFFF
};
enum class SVGA_Register : u32
{
   Id = 0,
   Enable = 1,
   Width = 2,
   Height = 3,
   MaxWidth = 4,
   MaxHeight = 5,
   Depth = 6,
   BitsPerPixel = 7, // Current bpp in the guest
   PseudoColor = 8,
   RedMask = 9,
   GreenMask = 10,
   BlueMask = 11,
   BytesPerLine = 12,
   FrameBufferStart = 13, // Deprecated
   FrameBufferOffset = 14,
   VRAMSize = 15,
   FrameBufferSize = 16,

   /* ID 0 implementation only had the above registers, then the palette */

   Capabilities = 17,
   MemoryStart = 18,           /* (Deprecated) */
   MemorySize = 19,
   ConfigDone = 20,         /* Set when memory area configured */
   Sync = 21,                /* See "FIFO Synchronization Registers" */
   Busy = 22,                /* See "FIFO Synchronization Registers" */
   GuestId = 23,            /* Set guest OS identifier */
   CursorId = 24,           /* (Deprecated) */
   CursorX = 25,            /* (Deprecated) */
   CursorY = 26,            /* (Deprecated) */
   CursorOn = 27,           /* (Deprecated) */
   HOST_BITS_PER_PIXEL = 28, /* (Deprecated) */
   SCRATCH_SIZE = 29,        /* Number of scratch registers */
   MEM_REGS = 30,            /* Number of FIFO registers */
   NUM_DISPLAYS = 31,        /* (Deprecated) */
   PITCHLOCK = 32,           /* Fixed pitch for all modes */
   IRQMask = 33,             /* Interrupt mask */

   /* Legacy multi-monitor support */
   NUM_GUEST_DISPLAYS = 34,/* Number of guest displays in X/Y direction */
   DISPLAY_ID = 35,        /* Display ID for the following display attributes */
   DISPLAY_IS_PRIMARY = 36,/* Whether this is a primary display */
   DISPLAY_POSITION_X = 37,/* The display position x */
   DISPLAY_POSITION_Y = 38,/* The display position y */
   DISPLAY_WIDTH = 39,     /* The display's width */
   DISPLAY_HEIGHT = 40,    /* The display's height */

   /* See "Guest memory regions" below. */
   GMR_ID = 41,
   GMR_DESCRIPTOR = 42,
   GMR_MAX_IDS = 43,
   GMR_MAX_DESCRIPTOR_LENGTH = 44,

   TRACES = 45,            /* Enable trace-based updates even when FIFO is on */
   GMRS_MAX_PAGES = 46,    /* Maximum number of 4KB pages for all GMRs */
   MEMORY_SIZE = 47,       /* Total dedicated device memory excluding FIFO */
   TOP = 48,               /* Must be 1 more than the last register */

   SVGA_PALETTE_BASE = 1024,        /* Base of SVGA color map */
   /* Next 768 (== 256*3) registers exist for colormap */

   //SVGA_SCRATCH_BASE = SVGA_PALETTE_BASE + SVGA_NUM_PALETTE_REGS
};
enum class SVGA_Port : u8
{
    Index = 0,
    Value = 1,
    Bios = 2,
    IRQStatus = 8
};

struct SVGA_Fifo
{
	u32 Minimum;
	u32 Maximum; // At least 10k
	u32 Next;
	u32 Stop;

	/*
	* Block 2 (extended registers): Mandatory registers for the extended
	* FIFO.  These exist if the SVGA caps register includes
	* SVGA_CAP_EXTENDED_FIFO; some of them are valid only if their
	* associated capability bit is enabled.
	*
	* Note that when originally defined, SVGA_CAP_EXTENDED_FIFO implied
	* support only for (FIFO registers) CAPABILITIES, FLAGS, and FENCE.
	* This means that the guest has to test individually (in most cases
	* using FIFO caps) for the presence of registers after this; the VMX
	* can define "extended FIFO" to mean whatever it wants, and currently
	* won't enable it unless there's room for that set and much more.
	*/
	struct
	{
		u32 Capabilities;
		u32 Flags;
		u32 Fence;
	} Extended;

	struct
	{
		u32 SVGA_FIFO_3D_HWVERSION;       /* See SVGA3dHardwareVersion in svga3d_reg.h */
		// Valid with SVGA_FIFO_CAP_PITCHLOCK:
		u32 SVGA_FIFO_PITCHLOCK;

		// Valid with SVGA_FIFO_CAP_CURSOR_BYPASS_3:
		u32 CursorVisible;    // Cursor bypass 3 show/hide register
		u32 CursorX;          // Cursor bypass 3 x register
		u32 CursorY;          // Cursor bypass 3 y register
		u32 CursorUpdate;     // Incremented when any of the other 3 change
		u32 LastCursorUpdate; // Last time the host updated the cursor

		// Valid with SVGA_FIFO_CAP_RESERVE:
		u32 Reserved;           /* Bytes past NEXT_CMD with real contents */

		/*
		* Valid with SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2:
		*
		* By default this is SVGA_ID_INVALID, to indicate that the cursor
		* coordinates are specified relative to the virtual root. If this
		* is set to a specific screen ID, cursor position is reinterpreted
		* as a signed offset relative to that screen's origin.
		*/
		u32 CursorScreen;

		/*
		* Valid with SVGA_FIFO_CAP_DEAD
		*
		* An arbitrary value written by the host, drivers should not use it.
		*/
		u32 SVGA_FIFO_DEAD;

		/*
		* Valid with SVGA_FIFO_CAP_3D_HWVERSION_REVISED:
		*
		* Contains 3D HWVERSION (see SVGA3dHardwareVersion in svga3d_reg.h)
		* on platforms that can enforce graphics resource limits.
		*/
		u32 SVGA_FIFO_3D_HWVERSION_REVISED;
	};
};
enum {
	/*
	* XXX: The gap here, up until SVGA_FIFO_3D_CAPS, can be used for new
	* registers, but this must be done carefully and with judicious use of
	* capability bits, since comparisons based on SVGA_FIFO_MIN aren't
	* enough to tell you whether the register exists: we've shipped drivers
	* and products that used SVGA_FIFO_3D_CAPS but didn't know about some of
	* the earlier ones.  The actual order of introduction was:
	* - PITCHLOCK
	* - 3D_CAPS
	* - CURSOR_* (cursor bypass 3)
	* - RESERVED
	* So, code that wants to know whether it can use any of the
	* aforementioned registers, or anything else added after PITCHLOCK and
	* before 3D_CAPS, needs to reason about something other than
	* SVGA_FIFO_MIN.
	*/

	/*
	* 3D caps block space; valid with 3D hardware version >=
	* SVGA3D_HWVERSION_WS6_B1.
	*/
	SVGA_FIFO_3D_CAPS = 32,
	SVGA_FIFO_3D_CAPS_LAST = 32 + 255,

	/*
	* End of VMX's current definition of "extended-FIFO registers".
	* Registers before here are always enabled/disabled as a block; either
	* the extended FIFO is enabled and includes all preceding registers, or
	* it's disabled entirely.
	*
	* Block 3b (truly optional extended registers): Additional registers for
	* the extended FIFO, which the VMX already knows how to enable and
	* disable with correct granularity.
	*
	* Registers after here exist if and only if the guest SVGA driver
	* sets SVGA_FIFO_MIN high enough to leave room for them.
	*/

	// Valid if register exists:
	SVGA_FIFO_GUEST_3D_HWVERSION, /* Guest driver's 3D version */
	SVGA_FIFO_FENCE_GOAL,         /* Matching target for SVGA_IRQFLAG_FENCE_GOAL */
	SVGA_FIFO_BUSY,               /* See "FIFO Synchronization Registers" */

	/*
	* Always keep this last.  This defines the maximum number of
	* registers we know about.  At power-on, this value is placed in
	* the SVGA_REG_MEM_REGS register, and we expect the guest driver
	* to allocate this much space in FIFO memory for registers.
	*/
	SVGA_FIFO_NUM_REGS
};




u32 SVGA_ReadRegister(u16 base, SVGA_Register index);
void SVGA_WriteRegister(u16 base, SVGA_Register index, u32 value);
u32 SVGA_GetVersion(u16 base);

#endif