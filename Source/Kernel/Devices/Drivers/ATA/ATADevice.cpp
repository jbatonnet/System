#include <Kernel/Devices/Drivers/ATA/ATA.h>
#include <Kernel/Devices/Drivers/ATA/ATADevice.h>

#include <System/Devices/Storage/FileSystem.h>
#include <System/Runtime/Threading/Spinlock.h>
#include <Kernel/Runtime/Threading/Task.h>

using namespace System::Devices;
using namespace System::Runtime;

namespace { Spinlock spinlock; }

ATADevice::ATADevice(u16 bus, bool master) : bus(bus), master(master)
{
    ATA_MasterBootRecord mbr;
    Read(&mbr, 0, 512);

    for (int i = 0; i < 4; i++)
    {
        FileSystemType type = (FileSystemType)mbr.Partitions[i].Type;
        FileSystem* fileSystem = FileSystem::Create(type, this, mbr.Partitions[i].LBA * 512);
        if (!fileSystem)
            continue;

        FileSystems->Add(fileSystem);
    }
}

u32 ATADevice::Read(void* buffer, u64 position, u32 count)
{
    char data[512];

    u32 firstBlock = (u32)position / 512;
    u32 lastBlock = ((u32)position + count - 1) / 512;
    u32 i = 0;

    lock (spinlock)
    {
        // Proceed with the first block
        ATA_PIO_Read28(bus, master, firstBlock, 1, data);
        u32 num = 512 - (u32)position % 512;
        Memory::Copy(data + (u32)position % 512, buffer, count < num ? count : num);

        // Proceed with the middle blocks
        for (; i < lastBlock - firstBlock; i++)
        {
            ATA_PIO_Read28(bus, master, firstBlock + 1 + i, 1, data);
            Memory::Copy(data, (char*)buffer + num + i * 512, 512);
        }

        // Proceed with the last block
        if (lastBlock != firstBlock)
        {
            ATA_PIO_Read28(bus, master, lastBlock, 1, data);
            Memory::Copy(data, (char*)buffer + num + i * 512, ((u32)position + count) % 512);
        }
    }

    return count;
}
void ATADevice::Write(void* buffer, u64 position, u32 count)
{
    char data[512];

    u32 firstBlock = (u32)position / 512;
    u32 lastBlock = ((u32)position + count - 1) / 512;
    u32 i = 0;

    lock (spinlock)
    {
        // Proceed with the first block
        u32 num = 512 - (u32)position % 512;
        if (num < 512)
            ATA_PIO_Read28(bus, master, firstBlock, 1, data);
        Memory::Copy(buffer, data + (u32)position % 512, count < num ? count : num);
        ATA_PIO_Write28(bus, master, firstBlock, 1, data);

        // Proceed with the middle blocks
        for (; i < lastBlock - firstBlock; i++)
            ATA_PIO_Write28(bus, master, firstBlock + 1 + i, 1, (char*)buffer + num + i * 512);

        // Proceed with the last block
        if (lastBlock != firstBlock)
        {
            num = ((u32)position + count) % 512;
            if (num < 512)
                ATA_PIO_Read28(bus, master, lastBlock, 1, data);
            Memory::Copy((char*)buffer + num + i * 512, data, ((u32)position + count) % 512);
            ATA_PIO_Write28(bus, master, lastBlock, 1, data);
        }
    }
}