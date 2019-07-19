#ifndef _SYSTEM_BUFFERSTREAM_H_
#define _SYSTEM_BUFFERSTREAM_H_

#include <System/Common.h>
#include <System/IO/Streams/Stream.h>

#define BUFFERSTREAM_BLOCK 128

namespace System
{
    namespace IO
    {
        class BufferStream : public Stream
        {
        protected:
            byte** indexes;
            u32 indexesCapacity;

            byte* buffer;
            u32 bufferCapacity;

            u32 position;
            u32 length;
            u32 limit;

        public:
            BufferStream(u32 limit = 4096);

            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
        };
    }
}

#endif