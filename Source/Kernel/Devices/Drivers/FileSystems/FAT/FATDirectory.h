#ifndef _KERNEL_FATDIRECTORY_H_
#define _KERNEL_FATDIRECTORY_H_

#include <Kernel/Kernel.h>

#include "FAT.h"
#include "FATStream.h"
#include "FATFile.h"

using namespace System::Devices;
using namespace System::IO;

template<typename T> class FATDirectory : public Directory
{
protected:
    string name;
    Directory* parent;

    FAT<T>* fileSystem;
    T cluster;
    u64 size;

    List<Directory*> directories;
    List<File*> files;

    bool cached;

    void Cache(bool force = false)
    {
        if (cached && !force)
            return;

        directories.Clear();
        files.Clear();

        FATStream<T> stream(fileSystem, cluster, 0xFFFFFFFF);
        u8 entryBytes[sizeof(FAT_DirectoryEntry)];

        FAT_LongDirectoryEntry* longEntries = new FAT_LongDirectoryEntry[0x50];
        Memory::Clear<FAT_LongDirectoryEntry>(longEntries, 0x50);

        for (;;)
        {
            if (!stream.Read((char*)entryBytes, sizeof(FAT_DirectoryEntry)))
                return;

            //for (int i = 0; i < sizeof(FAT_DirectoryEntry); i++)
            //    Console::Write("{0:X2}", entryBytes[i]);
            //Console::WriteLine();

            FAT_DirectoryEntry* entry = (FAT_DirectoryEntry*)entryBytes;
            FAT_LongDirectoryEntry* longEntry = (FAT_LongDirectoryEntry*)entryBytes;

            if (longEntry->Order == 0xE5)
                continue;
            if (longEntry->Order == 0x00)
                break;

            if (entry->Attributes == FAT_DirectoryAttribute::LongName)
            {
                longEntries[longEntry->Order] = *longEntry;
                continue;
            }

            char* name = new char[256];
            char* pointer = name;
            for (int j = 0; j < 0x50; j++)
            {
                if (!longEntries[j].Order)
                    continue;

                *pointer++ = (char)longEntries[j].Name1[0];
                *pointer++ = (char)longEntries[j].Name1[1];
                *pointer++ = (char)longEntries[j].Name1[2];
                *pointer++ = (char)longEntries[j].Name1[3];
                *pointer++ = (char)longEntries[j].Name1[4];
                *pointer++ = (char)longEntries[j].Name2[0];
                *pointer++ = (char)longEntries[j].Name2[1];
                *pointer++ = (char)longEntries[j].Name2[2];
                *pointer++ = (char)longEntries[j].Name2[3];
                *pointer++ = (char)longEntries[j].Name2[4];
                *pointer++ = (char)longEntries[j].Name2[5];
                *pointer++ = (char)longEntries[j].Name3[0];
                *pointer++ = (char)longEntries[j].Name3[1];
            }
            *pointer = 0;

            /*string sName(name);

            WriteLine("Name : %s", name);
            Console::WriteLine("Name : {0}", sName);*/

            Memory::Clear<FAT_LongDirectoryEntry>(longEntries, 0x50);

            if ((u8)entry->Attributes & (u8)FAT_DirectoryAttribute::Directory && *name)
                directories.Add(new FATDirectory<T>(name, this, fileSystem, entry->ClusterHi << 16 | entry->ClusterLo));
            else if (!((u8)entry->Attributes & (u8)FAT_DirectoryAttribute::VolumeID) && *name)
                files.Add(new FATFile<T>(name, fileSystem, entry->ClusterHi << 16 | entry->ClusterLo, entry->Size));

            delete[] name;
        }

        delete[] longEntries;
        cached = true;
    }

public:
    FATDirectory(string name, Directory* parent, FAT<T>* fileSystem, T cluster) : fileSystem(fileSystem), cluster(cluster), size(0), cached(false), name(name), parent(parent)
    {
        directories.Clear();
        files.Clear();
    }

    virtual string GetName() const override
    {
        return name;
    }
    virtual Directory* GetParent() override
    {
        return parent;
    }
    virtual string GetFullPath() override
    {
        return parent ? (parent->Parent ? (parent->FullPath + "/") : "/") + Name : "/";
    }

    virtual void AddDirectory(Directory* directory) override
    {
        Exception::NotImplemented();
    }
    virtual void AddFile(File* file) override
    {
        Exception::NotImplemented();
    }
    virtual Directory* GetDirectory(const string& path) override
    {
        if (!path.Length)
            return this;
        if (path[0] == '/')
            return Root->GetDirectory(path.SubString(1));

        Cache();

        if (path.Contains('/'))
        {
            string name = path.Before('/');
            string rest = path.After('/');

            for (int i = 0; i < directories.Count; i++)
                if (directories[i]->Name == name)
                    return directories[i]->GetDirectory(rest);

            return null;
        }
        else
        {
            for (int i = 0; i < directories.Count; i++)
                if (directories[i]->Name == path)
                    return directories[i];

            return null;
        }
    }
    virtual File* GetFile(string path) override
    {
        if (!path.Length)
            return null;
        if (path[0] == '/')
            return Root->GetFile(path.SubString(1));

        Cache();

        if (path.Contains('/'))
        {
            string name = path.Before('/');
            string rest = path.After('/');

            for (int i = 0; i < directories.Count; i++)
                if (directories[i]->Name == name)
                    return directories[i]->GetFile(rest);

            return null;
        }
        else
        {
            for (int i = 0; i < files.Count; i++)
                if (files[i]->Name == path)
                    return files[i];

            return null;
        }
    }

    virtual Reference<Collection<Directory*>> GetDirectories() override
    {
        if (!cached)
            Cache();
        return directories;
    }
    virtual Reference<Collection<File*>> GetFiles() override
    {
        if (!cached)
            Cache();
        return files;
    }
};

#endif