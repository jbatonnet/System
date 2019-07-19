#ifndef _SYSTEM_DIRECTORY_H_
#define _SYSTEM_DIRECTORY_H_

#include <System/Common.h>
#include <System/IO/File.h>
#include <System/Structures/Collections/Collection.h>

namespace System
{
    namespace IO
    {
        /// <summary>
        /// Represents a directory in a filesystem, and allows to manipulate it
        /// </summary>
        shared class Directory : public Object
        {
        protected:
            Directory() { }

        public:
            /// <summary>
            /// Get this directory's name
            /// </summary>
            _declspec(property(get = GetName)) string Name;
            virtual string GetName() const = 0;

            /// <summary>
            /// Get this directory's parent
            /// </summary>
            _declspec(property(get = GetParent)) Directory* Parent;
            virtual Directory* GetParent() = 0;

            /// <summary>
            /// Get this directory's child directories
            /// </summary>
            _declspec(property(get = GetDirectories)) Reference<Collection<Directory*>> Directories;
            virtual Reference<Collection<Directory*>> GetDirectories() = 0;

            /// <summary>
            /// Get this directory's child files
            /// </summary>
            _declspec(property(get = GetFiles)) Reference<Collection<File*>> Files;
            virtual Reference<Collection<File*>> GetFiles() = 0;

            /// <summary>
            /// Get this directory's full path
            /// </summary>
            _declspec(property(get = GetFullPath)) string FullPath;
            virtual string GetFullPath() = 0;

            // Methods
            virtual void AddDirectory(Directory* directory) = 0;
            virtual void AddFile(File* file) = 0;
            virtual Directory* GetDirectory(const string& path) = 0;
            virtual File* GetFile(string path) = 0;

            // Static
            static Directory* Open(const string& path);
            static Directory* Root;
            static Directory* Current;
            shared static Directory* GetRootDirectory();
        };
    }
}

#endif