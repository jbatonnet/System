#include <System/System.h>

using namespace System::IO;

Directory* Directory::GetRootDirectory()
{
    return null;
}

class KernelDirectory : public Directory
{
private:
    u64 id;

    string name;
    Directory* parent;

    Reference<List<Directory*>> directories;
    Reference<List<File*>> files;

public:
    KernelDirectory()
    {
        directories = new List<Directory*>();
        files = new List<File*>();
    }

    virtual string GetName() const override
    {
        return name;
    }
    virtual Directory* GetParent() override
    {
        return parent;
    }
    virtual Reference<Collection<Directory*>> GetDirectories() override
    {
        return &*directories;
    }
    virtual Reference<Collection<File*>> GetFiles() override
    {
        return &*files;
    }
    virtual string GetFullPath() override
    {
        return Parent ? (Parent->Parent ? (Parent->FullPath + "/") : "/") + Name : "/";
    }

    virtual void AddDirectory(Directory* directory) override
    {
        directories->Add(directory);
    }
    virtual void AddFile(File* file) override
    {
        files->Add(file);
    }
    virtual Directory* GetDirectory(const string& path) override
    {
        if (!path.Length)
            return this;
        if (path[0] == '/')
            return Root->GetDirectory(path.SubString(1));

        if (path.Contains('/'))
        {
            string name = path.Before('/');
            string rest = path.After('/');

            for (int i = 0; i < directories->Count; i++)
                if (directories->At(i)->Name == name)
                    return directories->At(i)->GetDirectory(rest);

            return null;
        }
        else
        {
            for (int i = 0; i < directories->Count; i++)
                if (directories->At(i)->Name == path)
                    return directories->At(i);

            return null;
        }
    }
    virtual File* GetFile(string path) override
    {
        if (!path.Length)
            return null;
        if (path[0] == '/')
            return Root->GetFile(path.SubString(1));

        if (path.Contains('/'))
        {
            string name = path.Before('/');
            string rest = path.After('/');

            for (int i = 0; i < directories->Count; i++)
                if (directories->At(i)->Name == name)
                    return directories->At(i)->GetFile(rest);

            return null;
        }
        else
        {
            for (int i = 0; i < files->Count; i++)
                if (files->At(i)->Name == path)
                    return files->At(i);

            return null;
        }
    }
};

class KernelDirectoryLink : public DirectoryLink
{
private:
    Directory* target;

public:
    virtual Directory* GetTarget() override
    {
        return target;
    }
    virtual Reference<Collection<Directory*>> GetDirectories() override
    {
        return target->GetDirectories();
    }
    virtual Reference<Collection<File*>> GetFiles() override
    {
        return target->GetFiles();
    }

    virtual void AddDirectory(Directory* directory) override
    {
        target->AddDirectory(directory);
    }
    virtual void AddFile(File* file) override
    {
        target->AddFile(file);
    }
    virtual Directory* GetDirectory(const string& path) override
    {
        return target->GetDirectory(path);
    }
    virtual File* GetFile(string path) override
    {
        return target->GetFile(path);
    }
};