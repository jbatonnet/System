#include <System/IO/Streams/Stream.h>

using namespace System::IO;

class NullStream : public Stream
{
    virtual u32 Read(void * buffer, u32 count)
    {
        return 0;
    }
    virtual void Write(void * buffer, u32 count)
    {
    }
};

Stream* Stream::Null = new NullStream();