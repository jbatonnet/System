#include "AMDNetDevice.h"

#include <System/System.h>

// "00:0c:29:14:38:08"
AMDNetDevice::AMDNetDevice(u8 bus, u8 device) : PCIDevice(bus, device, 0)
{
	Console::WriteLine("AMDNetDevice found at address 0x{0:X8}", address.Value);
	Console::WriteLine();

	Console::WriteLine("HeaderType: {0}", header.Base.HeaderType);

	u16 ioBase = header.Type0.BaseAddress0.IO.Address & 0xFFF0;
	Console::WriteLine("IOBase: 0x{0:X4}", ioBase);

	u8 val = PCI_Read8(address, ioBase);
	Console::WriteLine("Val: 0x{0:X2}", val);




	//configDevice = PCI_ReadDevice()

    loop
}

void AMDNetDevice::Load()
{

}
void AMDNetDevice::Unload()
{

}

/*

this.hardwareResources = hardwareResources;
base.name = "AMDPCNet_0x" + hardwareResources.GetIOPortRegion(0).BaseIOPort.ToString("X");

ioProm1 = hardwareResources.GetIOPort(0, 0x0);
ioProm4 = hardwareResources.GetIOPort(0, 0x4);
rdp = hardwareResources.GetIOPort(0, 0x10);
rap = hardwareResources.GetIOPort(0, 0x14);
bdp = hardwareResources.GetIOPort(0, 0x1C);

initBlock = hardwareResources.GetMemory(0);
txDescriptor = hardwareResources.GetMemory(1);
rxDescriptor = hardwareResources.GetMemory(2);
buffers = hardwareResources.GetMemory(3);

bufferSize = 2048;
uint len = (ushort)(~bufferSize);
len = (len + 1) & 0x0FFF | 0x8000F000;

physicalBufferAddress = HAL.GetPhysicalAddress(buffers);

for (uint index = 0; index < 16; index++)
{
uint offset = index * 4;
rxDescriptor.Write32((offset + 1) * 4, len);
rxDescriptor.Write32((offset + 2) * 4, physicalBufferAddress + (bufferSize * index));
txDescriptor.Write32((offset + 2) * 4, physicalBufferAddress + (bufferSize * (index + 16)));
}

nextTXDesc = 0;

*/