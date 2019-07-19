#include "SVGA.h"

#include <Kernel/Devices/Drivers/PCI/PCI.h>
#include <HAL/IO.h>

#include <System/Debugging/Console.h>

u32 SVGA_ReadRegister(u16 base, SVGA_Register index)
{
    IO_Write32(base + (u8)SVGA_Port::Index, (u32)index);
    return IO_Read32(base + (u8)SVGA_Port::Value);
}
void SVGA_WriteRegister(u16 base, SVGA_Register index, u32 value)
{
    IO_Write32(base + (u8)SVGA_Port::Index, (u32)index);
    IO_Write32(base + (u8)SVGA_Port::Value, value);
}

#define SVGA_MAGIC         0x900000UL
#define SVGA_MAKE_ID(ver)  (SVGA_MAGIC << 8 | (ver))

/* Version 2 let the address of the frame buffer be unsigned on Win32 */
#define SVGA_VERSION_2     2
#define SVGA_ID_2          SVGA_MAKE_ID(SVGA_VERSION_2)

/* Version 1 has new registers starting with SVGA_REG_CAPABILITIES so
PALETTE_BASE has moved */
#define SVGA_VERSION_1     1
#define SVGA_ID_1          SVGA_MAKE_ID(SVGA_VERSION_1)

/* Version 0 is the initial version */
#define SVGA_VERSION_0     0
#define SVGA_ID_0          SVGA_MAKE_ID(SVGA_VERSION_0)

/* "Invalid" value for all SVGA IDs. (Version ID, screen object ID, surface ID...) */
#define SVGA_ID_INVALID    0xFFFFFFFF


u32 SVGA_GetVersion(u16 base)
{
    SVGA_WriteRegister(base, SVGA_Register::Id, SVGA_ID_2);
    if (SVGA_ReadRegister(base, SVGA_Register::Id) == SVGA_ID_2)
        return SVGA_ID_2;

    SVGA_WriteRegister(base, SVGA_Register::Id, SVGA_ID_1);
    if (SVGA_ReadRegister(base, SVGA_Register::Id) == SVGA_ID_1)
        return SVGA_ID_1;

    SVGA_WriteRegister(base, SVGA_Register::Id, SVGA_ID_0);
    if (SVGA_ReadRegister(base, SVGA_Register::Id) == SVGA_ID_0)
        return SVGA_ID_0;

    return SVGA_ID_INVALID;
}

void SVGA_Initialize()
{
	PCI_Address address = PCI_FindDevice(0x15AD, 0x0405);
    Console::WriteLine("Address: 0x{0:X8}", address.Value);

    PCI_EnableMemory(address, true);

    PCI_ConfigType0 config;
    PCI_ReadConfig(address, &config);

    Console::WriteLine("Status: 0x{0:X4}", config.Header.Status);
    Console::WriteLine("Command: 0x{0:X4}", config.Header.Command);
    Console::WriteLine("Class: 0x{0:X2}", config.Header.Class);
    Console::WriteLine("Subclass: 0x{0:X2}", config.Header.SubClass);
    Console::WriteLine("Header: 0x{0:X2}", config.Header.HeaderType);

	//u16 ioBase = (u16)config.BaseAddress0.IO.Address << 2;
    //void* fbMemory = (void*)(config.BaseAddress1.Memory.Address << 4);
    //void* fifoMemory = (void*)(config.BaseAddress2.Memory.Address << 4);

    //Console::WriteLine("ioBase: 0x{0:X}", ioBase);
    //Console::WriteLine("fbMemory: {0}", fbMemory);
    //Console::WriteLine("fifoMemory: {0}", fifoMemory);

    u32 version = SVGA_ID_1;// SVGA_GetVersion(ioBase);
    Console::WriteLine("version: 0x{0:X8}", version);

    //u32 vramSize = SVGA_ReadRegister(ioBase, SVGA_Register::VRAMSize);
    //u32 fbSize = SVGA_ReadRegister(ioBase, SVGA_Register::FrameBufferSize);
    //u32 fifoSize = SVGA_ReadRegister(ioBase, SVGA_Register::MemorySize);

    //Console::WriteLine("vramSize: 0x{0:X}", vramSize);
    //Console::WriteLine("fbSize: 0x{0:X}", fbSize);
    //Console::WriteLine("fifoSize: 0x{0:X}", fifoSize);

    Console::WriteLine("loop");
    loop
}