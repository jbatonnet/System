#ifndef _KERNEL_FATSTREAM_H_
#define _KERNEL_FATSTREAM_H_

#include <Kernel/Kernel.h>

#include "FAT.h"

template<typename T> class FATStream : public System::IO::Stream
{
protected:
    FAT<T>* fileSystem;
    List<T> clusters;

    char* cache;
    T cacheIndex;
    bool autoExpand;

public:
    FATStream(FAT<T>* fileSystem, T cluster, u64 length, bool autoExpand = false) : fileSystem(fileSystem), autoExpand(autoExpand)
    {
        this->length = length;
        this->position = 0;

        for (; cluster != (T)0xFFFFFFFF; cluster = fileSystem->NextCluster(cluster))
            clusters.Add(cluster);

        cache = Memory::Allocate<char>(fileSystem->ClusterSize);
    }
    virtual ~FATStream() { }

    u32 Read(void* buffer, u32 count)
    {
        if (position + count > length)
            count = length - position;
        if (!count)
            return 0;

        u32 clusterSize  = fileSystem->ClusterSize;
        u32 firstIndex = position / clusterSize;
        u32 lastIndex  = (position + count - 1) / clusterSize;

        // Proceed with the first cluster
        if (cacheIndex != clusters[firstIndex])
        {
            fileSystem->ReadCluster(cache, clusters[firstIndex]);
            cacheIndex = clusters[firstIndex];
        }
        u32 num = clusterSize - position % clusterSize;
        Memory::Copy(cache + position % clusterSize, buffer, count < num ? count : num);

        // Proceed with the middle clusters
        u32 i = 0;
        if (lastIndex - firstIndex > 1)
        {
            for (; i < lastIndex - firstIndex - 1; i++)
            {
                fileSystem->ReadCluster(cache, clusters[firstIndex + 1 + i]);
                cacheIndex = clusters[firstIndex + 1 + i];
                Memory::Copy(cache, (char*)buffer + num + i * clusterSize, clusterSize);
            }
        }

        // Proceed with the last cluster
        if (lastIndex != firstIndex)
        {
            fileSystem->ReadCluster(cache, clusters[lastIndex]);
            cacheIndex = clusters[lastIndex];
            Memory::Copy(cache, (char*)buffer + num + i * clusterSize, (position + count) % clusterSize);
        }

        position += count;
        return count;
    }
    void Write(void* buffer, u32 count)
    {
    }
};

#endif