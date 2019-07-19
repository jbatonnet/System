#ifdef WINDOWS

#include <System/System.h>

using namespace System;
using namespace System::Runtime;
using namespace System::Objects;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Interface;
using namespace System::Graphics;

#undef using
#define _INITIALIZER_LIST_

#include <Windows.h>
#include <Shlwapi.h>
#include <iostream>

#define MAX_PATH_LENGTH 512

const char* rootDirectories[3] = { "Root", "Source", "Tools" };

bool DirectoryExists(const string& path)
{
    char fullPath[MAX_PATH_LENGTH];
    u32 length = path.Length;

    Exception::Assert(length < sizeof(fullPath) - 1, "This path is too long");

    memcpy(fullPath, path.Buffer, length);
    fullPath[length] = 0;

    for (int i = 0; fullPath[i]; i++)
        if (fullPath[i] == '/')
            fullPath[i] = '\\';

    if (fullPath[length - 1] == '\\')
        fullPath[--length] = 0;

    DWORD attributes = GetFileAttributes(fullPath);
    return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

class WindowsFileStream : public Stream
{
private:
    FILE* handle;

public:
    WindowsFileStream(FILE* handle) : handle(handle)
    {
    }

    virtual u64 GetPosition() override
    {
        return ftell(handle);
    }
    virtual u64 GetLength() override
    {
        u64 position = ftell(handle);

        fseek(handle, 0, SEEK_END);
        u64 length = ftell(handle);

        fseek(handle, position, SEEK_SET);

        return length;
    }
    virtual bool IsEndOfStream() override
    {
        return feof(handle);
    }
    virtual u32 Read(void* buffer, u32 count) override
    {
        byte* bytes = (byte*)buffer;
        int i = 0;

        for (; i < count && !feof(handle); i++)
            bytes[i] = fgetc(handle);

        return i;
    }
    virtual void Write(void* buffer, u32 count) override
    {
        byte* bytes = (byte*)buffer;

        for (int i = 0; i < count; i++)
            fputc(bytes[i], handle);
    }
    virtual void Seek(u64 offset, SeekOrigin origin = SeekOrigin::Begin) override
    {
        switch (origin)
        {
        case SeekOrigin::Begin: fseek(handle, offset, SEEK_SET); break;
        case SeekOrigin::Current: fseek(handle, offset, SEEK_CUR); break;
        case SeekOrigin::End: fseek(handle, offset, SEEK_END); break;
        }
    }
};
class WindowsFile : public File
{
private:
    string path;
    string name;

public:
    WindowsFile(const char* path)
    {
        DWORD attributes = GetFileAttributes(path);
        Exception::Assert(attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY), "Could not find specified file");

        char fullPath[MAX_PATH_LENGTH];

        u32 length = strlen(path);
        Exception::Assert(length < sizeof(fullPath) - 1, "This path is too long");

        memcpy(fullPath, path, length + 1);

        for (int i = 0; fullPath[i]; i++)
            if (fullPath[i] == '/')
                fullPath[i] = '\\';

        char* filePart;
        GetFullPathName(fullPath, sizeof(fullPath), fullPath, &filePart);

        for (int i = 0; fullPath[i]; i++)
            if (fullPath[i] == '\\')
                fullPath[i] = '/';

        this->path = fullPath;
        this->name = filePart;
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
        u32 extensionSeparator = name.IndexOfLast('.');
        if (extensionSeparator == -1)
            return "";

        return name.SubString(extensionSeparator + 1);
    }
    virtual u64 GetSize() override
    {
        char fullPath[MAX_PATH_LENGTH] = { 0 };

        memcpy(fullPath, path.Buffer, path.Length);
        for (int i = 0; fullPath[i]; i++)
            if (fullPath[i] == '/')
                fullPath[i] = '\\';

        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (!GetFileAttributesEx(fullPath, GetFileExInfoStandard, &fad))
            return -1;

        LARGE_INTEGER size;
        size.HighPart = fad.nFileSizeHigh;
        size.LowPart = fad.nFileSizeLow;

        return size.QuadPart;
    }

    virtual Stream* GetStream() override
    {
        char buffer[MAX_PATH_LENGTH] = { 0 };
        memcpy(buffer, path.Buffer, path.Length);

        FILE* handle = fopen(buffer, "rb");
        return handle ? new WindowsFileStream(handle) : null;
    }
};
class WindowsDirectory : public Directory
{
private:
    string path;
    string name;

public:
    WindowsDirectory(const char* path)
    {
        char fullPath[MAX_PATH_LENGTH];

        u32 length = strlen(path);
        Exception::Assert(length < sizeof(fullPath) - 1, "This path is too long");

        memcpy(fullPath, path, length + 1);

        for (int i = 0; fullPath[i]; i++)
            if (fullPath[i] == '/')
                fullPath[i] = '\\';

        if (fullPath[length - 1] == '\\')
            fullPath[--length] = 0;

        char* filePart;
        GetFullPathName(fullPath, sizeof(fullPath), fullPath, &filePart);

        for (int i = 0; fullPath[i]; i++)
            if (fullPath[i] == '\\')
                fullPath[i] = '/';

        this->path = fullPath;
        this->name = filePart ? filePart : string::Empty;

        DWORD attributes = GetFileAttributes(fullPath);
        Exception::Assert(attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY), "Could not find specified directory");
    }

    virtual string GetName() const override
    {
        return name;
    }
    virtual Directory* GetParent() override
    {
        char buffer[MAX_PATH_LENGTH] = { 0 };

        string fullPath = path + "\\..";

        memcpy(buffer, fullPath.Buffer, fullPath.Length);
        for (int i = 0; buffer[i]; i++)
            if (buffer[i] == '/')
                buffer[i] = '\\';

        return new WindowsDirectory(buffer);
    }
    virtual Reference<Collection<Directory*>> GetDirectories() override
    {
        char buffer[MAX_PATH_LENGTH] = { 0 };
        HANDLE hFile;
        WIN32_FIND_DATA findData;
        List<Directory*>* result = new List<Directory*>();

        string pattern = path + "\\*";

        memcpy(buffer, pattern.Buffer, pattern.Length);
        for (int i = 0; buffer[i]; i++)
            if (buffer[i] == '/')
                buffer[i] = '\\';

        hFile = FindFirstFile(buffer, &findData);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (findData.cFileName[0] == '.')
                    continue;

                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    result->Add(GetDirectory(findData.cFileName));
            }
            while (FindNextFile(hFile, &findData) == TRUE);

            FindClose(hFile);
        }

        return result;
    }
    virtual Reference<Collection<File*>> GetFiles() override
    {
        char buffer[MAX_PATH_LENGTH] = { 0 };
        HANDLE hFile;
        WIN32_FIND_DATA findData;
        List<File*>* result = new List<File*>();

        string pattern = path + "\\*";

        memcpy(buffer, pattern.Buffer, pattern.Length);
        for (int i = 0; buffer[i]; i++)
            if (buffer[i] == '/')
                buffer[i] = '\\';

        hFile = FindFirstFile(buffer, &findData);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (findData.cFileName[0] == '.')
                    continue;

                if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    result->Add(GetFile(findData.cFileName));
            } while (FindNextFile(hFile, &findData) == TRUE);

            FindClose(hFile);
        }

        return result;
    }
    virtual string GetFullPath() override
    {
        return path;
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

        char buffer[MAX_PATH_LENGTH] = { 0 };

        if (path.Contains('/'))
        {
            string name = path.Before('/');
            string rest = path.After('/');

            string subPath = this->path + "/" + name;

            if (DirectoryExists(subPath))
            {
                memcpy(buffer, subPath.Buffer, subPath.Length);
                for (int i = 0; buffer[i]; i++)
                    if (buffer[i] == '/')
                        buffer[i] = '\\';

                return (new WindowsDirectory(buffer))->GetDirectory(rest);
            }

            return null;
        }
        else
        {
            string subPath = this->path + "/" + (string&)path;

            if (DirectoryExists(subPath))
            {
                memcpy(buffer, subPath.Buffer, subPath.Length);
                for (int i = 0; buffer[i]; i++)
                    if (buffer[i] == '/')
                        buffer[i] = '\\';

                return new WindowsDirectory(buffer);
            }

            return null;
        }
    }
    virtual File* GetFile(string path) override
    {
        char buffer[MAX_PATH_LENGTH] = { 0 };
        memcpy(buffer, path.Buffer, path.Length);

        bool rooted = !PathIsRelative(buffer);
        if (rooted)
            return new WindowsFile(buffer);
        else
        {
            u32 length = this->path.Length;

            memcpy(buffer, this->path.Buffer, length);
            buffer[length] = '\\';
            memcpy(buffer + length + 1, path.Buffer, path.Length);

            for (u32 i = 0; buffer[i]; i++)
                if (buffer[i] == '/')
                    buffer[i] = '\\';

            return new WindowsFile(buffer);
        }
    }
};

Directory* rootDirectory = null;
Directory* Directory::GetRootDirectory()
{
    if (rootDirectory != null)
        return rootDirectory;

    char currentDirectory[MAX_PATH_LENGTH];
    GetCurrentDirectory(MAX_PATH_LENGTH, currentDirectory);

    Directory* directory = new WindowsDirectory(currentDirectory);

    for (;;)
    {
        bool found = true;

        for (u32 i = 0; i < sizeof(rootDirectories) / sizeof(char*); i++)
        {
            Directory* subDirectory = directory->GetDirectory(rootDirectories[i]);

            if (subDirectory == null)
            {
                found = false;
                break;
            }
            else
                delete subDirectory;
        }

        if (found)
            break;
        else
        {
            Directory* parentDirectory = directory->Parent;
            delete directory;
            directory = parentDirectory;
        }
    }

    rootDirectory = directory->GetDirectory("Root");
    delete directory;

    return rootDirectory;
}

#endif