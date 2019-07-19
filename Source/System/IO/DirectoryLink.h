#ifndef _SYSTEM_FILES_H_
#define _SYSTEM_FILES_H_

#include <System/Common.h>
#include <System/IO/Directory.h>

namespace System
{
    namespace IO
    {
        class DirectoryLink : public Directory
        {
        private:
            Directory* target;

        public:
            DirectoryLink(string name, Directory* parent, Directory* target);

            // Accessors
            _declspec(property(get = GetTarget)) Directory* Target;
            virtual Directory* GetTarget() { return target; }
            virtual Reference<Collection<Directory*>> GetDirectories() override { return target->GetDirectories(); }
            virtual Reference<Collection<File*>> GetFiles() override { return target->GetFiles(); }

            // Methods
            virtual void AddDirectory(Directory* directory) override { target->AddDirectory(directory); }
            virtual void AddFile(File* file) override { target->AddFile(file); }
            virtual Directory* GetDirectory(const string& path) override { return target->GetDirectory(path); }
            virtual File* GetFile(string path) override { return target->GetFile(path); }
        };
    }
}

#endif