#ifndef _KERNEL_FATFILE_H_
#define _KERNEL_FATFILE_H_

#include <Kernel/Kernel.h>

#include "FAT.h"
#include "FATStream.h"

using namespace System::IO;

template<typename T> class FATFile : public virtual File
{
protected:
    u64 id;

    string path;
    string name;
    string extension;

    FileAttributes attributes;

    FAT<T>* fileSystem;
    T cluster;
    u64 size;

public:
    FATFile(string name, FAT<T>* fileSystem, T cluster, u64 size) : fileSystem(fileSystem), cluster(cluster), size(size), name(name)
    {
        extension = name.AfterLast('.');
    }

    virtual string GetPath() const override
    {
        return path;
    }
    virtual string GetName() const override
    {
        return name;
    }
    virtual string GetExtension() const override
    {
        return extension;
    }
    virtual u64 GetSize() override
    {
        return size;
    }

    virtual Stream* GetStream() override
    {
        return new FATStream<T>(fileSystem, cluster, size);
    }
};

#endif