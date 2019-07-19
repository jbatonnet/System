#ifndef _SYSTEM_TEESTREAM_H_
#define _SYSTEM_TEESTREAM_H_

#include <System/Common.h>
#include <System/IO/Streams/Stream.h>

namespace System
{
    namespace IO
    {
        class TeeStream : public Stream
        {
        protected:
            List<Stream*> streams;
            u32 length;

        public:
            TeeStream(Stream* stream);
            TeeStream(Stream* stream1, Stream* stream2);
            TeeStream(Stream* stream1, Stream* stream2, Stream* stream3);
            TeeStream(Stream* stream1, Stream* stream2, Stream* stream3, Stream* stream4);

            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);
        };
    }
}

#endif