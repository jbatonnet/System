#include "PCI.h"
#include <HAL/IO.h>

// IO
u8 PCI_Read8(PCI_Address address, u32 reg)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    return IO_Read8(PCI_CONFIG_DATA + (reg & 0x03));
}
u16 PCI_Read16(PCI_Address address, u32 reg)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    return IO_Read16(PCI_CONFIG_DATA + (reg & 0x02));
}
u32 PCI_Read32(PCI_Address address, u32 reg)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    return IO_Read32(PCI_CONFIG_DATA);
}
void PCI_Write8(PCI_Address address, u32 reg, u8 value)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    IO_Write8(PCI_CONFIG_DATA + (reg & 0x03), value);
}
void PCI_Write16(PCI_Address address, u32 reg, u16 value)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    IO_Write16(PCI_CONFIG_DATA + (reg & 0x02), value);
}
void PCI_Write32(PCI_Address address, u32 reg, u32 value)
{
    IO_Write32(PCI_CONFIG_ADDRESS, address.Value | (reg & 0xFC));
    IO_Write32(PCI_CONFIG_DATA, value);
}

// Devices and configuration
PCI_ConfigDevice PCI_ReadDevice(PCI_Address address)
{
    u32 value = PCI_Read32(address, 0);
    return *(PCI_ConfigDevice*)&value;
}
void PCI_ReadConfig(PCI_Address address, void* configData)
{
    u32* buffer = (u32*)configData;

    for (int i = 0; i < 16; i++)
        buffer[i] = PCI_Read32(address, i * 4);
}
PCI_Address PCI_FindDevice(u16 vendorId, u16 deviceId)
{
    for (u32 bus = 0; bus < 256; bus++)
        for (u32 slot = 0; slot < 32; slot++)
            for (u32 function = 0; function < 8; function++)
            {
				PCI_Address address(bus, slot, function);
                PCI_ConfigDevice configDevice = PCI_ReadDevice(address);

                if (configDevice.VendorId == vendorId && configDevice.DeviceId == deviceId)
                    return address;
            }

    return PCI_Address(0, 0, 0, false);
}
void PCI_EnableMemory(PCI_Address address, bool enable)
{
   u16 command = PCI_Read16(address, 6);

   if (enable)
      command |= 0x0007;
   else
      command &= ~0x0007;

   PCI_Write16(address, 6, command);
}