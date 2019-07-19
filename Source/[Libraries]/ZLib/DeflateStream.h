#ifndef _ZLIB_DEFLATESTREAM_H_
#define _ZLIB_DEFLATESTREAM_H_

#include <System/IO/Streams/Stream.h>

enum class CompressionMode : u8
{
    Compress = 0x10,
    Decompress = 0x20,

    CompressSpeed =  Compress | 1,
    CompressNormal = Compress | 6,
    CompressSize =   Compress | 9
};

class DeflateStream : public System::IO::Stream
{
protected:
    Stream* baseStream;
    CompressionMode mode;

private:
    void* handle;
    u8* buffer;

public:
    DeflateStream(Stream* baseStream, CompressionMode mode);
    ~DeflateStream();

    u64 GetPosition();
    u64 GetLength();
    bool IsEndOfStream();

    u32 Read(void* buffer, u32 count);
    void Write(void* buffer, u32 count);
    void Seek(u64 position, System::IO::SeekOrigin origin = System::IO::SeekOrigin::Begin);
};

#endif