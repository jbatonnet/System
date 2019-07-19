#ifndef _SYSTEM_STREAM_H_
#define _SYSTEM_STREAM_H_

#include <System/Common.h>
//#include <System/Debugging/Console.h> // FIXME

class ConsoleStream;

namespace System
{
    namespace IO
    {
        enum class SeekOrigin : u8
        {
            Begin,
            Current,
            End
        };

        shared class Stream
        {
        protected:
            // FIXME: Remove these fields, Stream should be fully virtual
            u64 length;
            u64 position;

        public:
            /// <summary>
            /// Gets or sets the current position of this stream
            /// </summary>
            _declspec(property(get = GetPosition, put = SetPosition)) u64 Position;
            // Gets the current position of this stream
            virtual u64 GetPosition() { return position; }
            // Sets the current position of this stream
            virtual void SetPosition(u64 value)
            {
                Seek(value, SeekOrigin::Begin);
            }

            // Gets the length of this stream
            _declspec(property(get = GetLength)) u64 Length;
            // Gets the length of this stream
            virtual u64 GetLength() { return length; }

            _declspec(property(get = IsEndOfStream)) bool EndOfStream;
            virtual bool IsEndOfStream()
            {
                return GetPosition() == GetLength();
            }

            // Reads the specified amount of data from this stream
            virtual u32 Read(void* buffer, u32 count) = 0;
            // Writes the specified data to this stream
            virtual void Write(void* buffer, u32 count) = 0;
            // Seeks the position with the specified length
            virtual void Seek(u64 offset, SeekOrigin origin = SeekOrigin::Begin)
            {
                if (origin == SeekOrigin::Begin)        this->position = offset;
                else if (origin == SeekOrigin::Current) this->position += offset;
                else if (origin == SeekOrigin::End)     this->position = Length - offset;
            }

            // Gets the system console stream
            shared static ConsoleStream* GetConsoleStream();
            // Gets the system serial stream
            shared static Stream* GetSerialStream();

            static Stream* Null;
        };
    }
}

#endif