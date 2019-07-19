#ifndef _KERNEL_FATFILESYSTEM_H_
#define _KERNEL_FATFILESYSTEM_H_

#include <Kernel/Kernel.h>

#include "FAT.h"

using namespace System::Devices;

template<typename T>
class FAT : public FileSystem
{
protected:
    FAT_BootSector bootSector;
    T* fat;

    u64 firstCluster;
    u32 clusterSize;

    void Initialize();

public:
    _declspec(property(get = GetClusterSize)) u32 ClusterSize;
    u32 GetClusterSize() { return clusterSize; }
    
    FAT(StorageDevice* device, u64 position)
    {
        this->device = device;
        this->position = position;

        device->Read((char*)&bootSector, position, 512);

        clusterSize = bootSector.Bpb.SectorsPerCluster * bootSector.Bpb.BytesPerSector;
        firstCluster = bootSector.Bpb.ReservedSectors * bootSector.Bpb.BytesPerSector +
                       bootSector.Bpb.Fats * bootSector.Bpb.SectorsPerFat16 * bootSector.Bpb.BytesPerSector -
                       clusterSize;

        Initialize();
    }
    virtual ~FAT() { }

    // Clusters
    u32 ReadCluster(char* buffer, T cluster)
    {
        return device->Read(buffer, position + firstCluster + cluster * clusterSize, clusterSize);
    }
    void WriteCluster(char* source, T cluster)
    {
        device->Write(source, position + firstCluster + cluster * clusterSize, clusterSize);
    }
    T NextCluster(T cluster)
    {
        return fat[cluster];
    }
    void FreeCluster(T cluster)
    {

    }
};

#endif