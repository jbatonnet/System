#ifndef _KERNEL_PCI_H_
#define _KERNEL_PCI_H_

#include <System/Common.h>

// I/O
#define PCI_CONFIG_ADDRESS 0x0CF8
#define PCI_CONFIG_DATA    0x0CFC

// Headers
#define PCI_TYPE_MULTIFUNCTION  0x80
#define PCI_TYPE_GENERIC        0x00
#define PCI_TYPE_PCI_BRIDGE     0x01
#define PCI_TYPE_CARDBUS_BRIDGE 0x02

// Configuration registers
#define PCI_CONFIG_VENDOR_ID      0x00
#define PCI_CONFIG_DEVICE_ID      0x02
#define PCI_CONFIG_COMMAND        0x04
#define PCI_CONFIG_STATUS         0x06
#define PCI_CONFIG_REVISION_ID    0x08
#define PCI_CONFIG_PROG_INTF      0x09
#define PCI_CONFIG_SUBCLASS       0x0A
#define PCI_CONFIG_CLASS_CODE     0x0B
#define PCI_CONFIG_CACHELINE_SIZE 0x0C
#define PCI_CONFIG_LATENCY        0x0D
#define PCI_CONFIG_HEADER_TYPE    0x0E
#define PCI_CONFIG_BIST           0x0F

// Structures
struct PCI_Address
{
	union
	{
		u32 Value;

		struct
		{
			u8 __Unused_0;
			u8 Function : 3;
			u8 Device : 5;
			u8 Bus;
			u8 __Unused_1 : 7;
			bool Enabled : 1;
		};
	};

    PCI_Address() : Value(0) { }
	PCI_Address(u8 bus, u8 device, u8 function) : Enabled(true), Bus(bus), Device(device), Function(function), __Unused_0(0), __Unused_1(0) { }
	PCI_Address(u8 bus, u8 device, u8 function, bool enabled) : Enabled(enabled), Bus(bus), Device(device), Function(function), __Unused_0(0), __Unused_1(0) { }
};

enum class PCI_BaseAddressType : u8
{
	Memory = 0,
	IO = 1
};
enum class PCI_BaseAddressMemoryType : u8
{
	Space32Bit = 0,
	Space64Bit = 2
};


union PCI_MemoryBaseAddress
{
	u32 Address;

	struct
	{
		bool __Unused_0 : 1;
		PCI_BaseAddressMemoryType Type : 2;
		bool Prefetchable : 1;
	};
};
struct PCI_IOBaseAddress
{
	u32 Address;
};

struct PCI_BaseAddress
{
	union
	{
		u32 Value;

		struct
		{
			PCI_BaseAddressType Type : 1;
			u8 _Unused_0 : 7;
			u8 _Unused_1[3];
		};

		PCI_MemoryBaseAddress Memory;
		PCI_IOBaseAddress IO;
	};
};

struct PCI_ConfigDevice
{
    u16 VendorId;
    u16 DeviceId;
};
struct PCI_ConfigHeader
{
    PCI_ConfigDevice Device;

    u16 Command;
    u16 Status;

    u8 RevisionId;
    u8 Interface;
    u8 SubClass;
    u8 Class;

    u8 Cache;
    u8 Latency;
    struct
    {
        u8 HeaderType : 7;
        u8 MultipleFunctions : 1;
    };
	u8 BIST;
};

struct PCI_ConfigType0
{
    PCI_ConfigHeader Header;
    PCI_BaseAddress BaseAddress0;
    PCI_BaseAddress BaseAddress1;
    PCI_BaseAddress BaseAddress2;
    PCI_BaseAddress BaseAddress3;
    PCI_BaseAddress BaseAddress4;
    PCI_BaseAddress BaseAddress5;
    u32 Cardbus;
    PCI_ConfigDevice SubSystem;
    u32 ROMBaseAddress;
    u8  _Unused_0[3];
    u32 Capabilities;
    u32 _Unused_1;
    u8  MaxLatency;
    u8  Grant;
    u8  InterruptPin;
    u8  InterruptLine;
};
struct PCI_ConfigType1
{
	PCI_ConfigHeader Header;

	u32 BaseAddress0;
	u32 BaseAddress1;

	u8 PrimaryBus;
	u8 SecondaryBus;
	u8 SubordinateBus;
	u8 SecondaryLatency;

	u8 IOBase;
	u8 IOLimit;
	u16 SecondaryStatus;

	u16 MemoryBase;
	u16 MemoryLimit;

	u16 PrefetchableMemoryBase;
	u16 PrefetchableMemoryLimit;

	u32 PrefetchableBaseUpper;
	u32 PrefetchableLimitUpper;

	u16 IOBaseUpper;
	u16 IOLimitUpper;

	u8 CapabilityPointer;
	u8 _Unused_0[3];

	u32 ExpansionBaseAddress;

	u8 InterruptLine;
	u8 InterruptPin;
	u16 BridgeControl;
};

// General
#define PCI_EnableBit 0x80000000
#define PCI_MakeAddress(bus, slot, function) (PCI_EnableBit | ((bus) << 16) | ((slot) << 11) | ((function) << 8))

// IO
u8 PCI_Read8(PCI_Address address, u32 reg);
u16 PCI_Read16(PCI_Address address, u32 reg);
u32 PCI_Read32(PCI_Address address, u32 reg);
void PCI_Write8(PCI_Address address, u32 reg, u8 value);
void PCI_Write16(PCI_Address address, u32 reg, u16 value);
void PCI_Write32(PCI_Address address, u32 reg, u32 value);

// Devices and configuration
PCI_ConfigDevice PCI_ReadDevice(PCI_Address address);
void PCI_ReadConfig(PCI_Address address, void* configData);
PCI_Address PCI_FindDevice(u16 vendorId, u16 deviceId);
void PCI_EnableMemory(PCI_Address address, bool enable);

#endif