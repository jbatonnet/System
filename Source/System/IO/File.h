#ifndef _SYSTEM_FILE_H_
#define _SYSTEM_FILE_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>
#include <System/IO/Streams/Stream.h>

namespace System
{
    namespace IO
    {
        enum class FileAttributes : u8
        {
            None   = 0x00,
            Hidden = 0x01,
            System = 0x02,
        };

        /// <summary>
        /// Represents a file in a filesystem, and allows to manipulate it
        /// </summary>
        shared class File : public Object
        {
        protected:
            File() { }

        public:
            /// <summary>
            /// Gets this file's path
            /// </summary>
            _declspec(property(get = GetPath)) string Path;
            virtual string GetPath() const = 0;

            /// <summary>
            /// Gets this file's name
            /// </summary>
            _declspec(property(get = GetName)) string Name;
            virtual string GetName() const = 0;

            /// <summary>
            /// Gets this file's extension
            /// </summary>
            _declspec(property(get = GetExtension)) string Extension;
            virtual string GetExtension() const = 0;

            /// <summary>
            /// Gets this file's size
            /// </summary>
            _declspec(property(get = GetSize)) u64 Size;
            virtual u64 GetSize() = 0;

            // Streams
            virtual Stream* GetStream() = 0;

            /// <summary>
            /// Opens a file from the specified path
            /// </summary>
            /// <param name="path">The path of the file to load</param>
            /// <returns>The open file, or null if the path was not found</returns>
            static File* Open(string path);

            /// <summary>
            /// Opens a file stream from the specified path
            /// </summary>
            /// <param name="path">The path of the file to load</param>
            /// <returns>The file stream, or null if the path was not found</returns>
            static Stream* OpenStream(string path);
        };
    }
}

#endif