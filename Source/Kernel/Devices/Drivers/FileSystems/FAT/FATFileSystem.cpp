#include "FATFileSystem.h"
#include "FATDirectory.h"

template<> void FAT<u16>::Initialize()
{
    // Label
    u32 length = 0;
    for (; length < 11 && bootSector.Informations.FAT16.Label[length] != ' '; length++);

    char* name = new char[length];
    this->name = string(bootSector.Informations.FAT16.Label, length);
    delete[] name;

    // FAT
    u32 fatSize = bootSector.Bpb.SectorsPerFat16 * bootSector.Bpb.BytesPerSector;
    u32 fatPosition = bootSector.Bpb.ReservedSectors * bootSector.Bpb.BytesPerSector;

    fat = new u16[fatSize];
    device->Read((char*)fat, position + fatPosition, fatSize);

    // Root directory
    root = new FATDirectory<u16>("Root", null, this, 1);
}
template<> void FAT<u32>::Initialize()
{
    /* TODO: Check and test
    // Label
    int length = 0;
    for (; length < 11 && bootSector.Informations.FAT32.Label[length] != ' '; length++);

    char* name = new char[length + 1];
    this->name = string(bootSector.Informations.FAT32.Label, length);
    delete[] name;

    // FAT
    u32 fatSize = bootSector.Bpb.SectorsPerFat16 * bootSector.Bpb.BytesPerSector;
    u32 fatPosition = bootSector.Bpb.ReservedSectors * bootSector.Bpb.BytesPerSector;

    fat = new u32[fatSize];
    device->Read((char*)fat, 0, position + fatPosition, fatSize);

    // Root directory
    root = new FATDirectory<u32>("Root", null, this, bootSector.Informations.FAT32.RootCluster); // FIXME: Use FAT
    */
}