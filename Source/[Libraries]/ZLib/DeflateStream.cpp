#include "DeflateStream.h"
#include <System/Debugging/Console.h>

#include "zlib-1.2.8/zlib.h"

#define BUFFER_SIZE 1024

using namespace System::IO;

void* AllocFunc(void* opaque, u32 items, u32 size)
{
    //Console::WriteLine("Memory::Allocate({0})", items * size);
    return Memory::Allocate(items * size);
}
void FreeFunc(void* opaque, void* address)
{
    //Console::WriteLine("Memory::Free({0})", address);
    Memory::Free(address);
}

DeflateStream::DeflateStream(Stream* baseStream, CompressionMode mode) : baseStream(baseStream), mode(mode)
{
    handle = Memory::Allocate<z_stream>(1, 0);

    z_stream* stream = (z_stream*)handle;
    stream->zalloc = AllocFunc;
    stream->zfree = FreeFunc;
    stream->opaque = null;

    int result = Z_OK;

    if (Flag::Test(mode, CompressionMode::Compress))
    {
    }
    else
    {
        stream->avail_in = 0;
        stream->next_in = null;

        result = inflateInit(stream);
    }

    if (result != Z_OK)
        Console::WriteLine("Result: {0}", result); // TODO: Exception
}
DeflateStream::~DeflateStream()
{
    z_stream* stream = (z_stream*)handle;
    inflateEnd(stream);

    Memory::Free(stream);
}

u64 DeflateStream::GetPosition()
{
    return 0;
}
u64 DeflateStream::GetLength()
{
    Exception::Assert("DeflateStream: Can't calculate length of a deflated stream");
    return 0;
}
bool DeflateStream::IsEndOfStream()
{
    return baseStream->IsEndOfStream();
}

u32 DeflateStream::Read(void* data, u32 count)
{
    //Console::WriteLine("DeflateStream::Read({0}, {1})", data, count);

    byte buffer[BUFFER_SIZE];
    u32 result = Z_OK;

    // ZLib stream
    z_stream* stream = (z_stream*)handle;
    stream->avail_out = count;
    stream->next_out = (byte*)data;

    // Decompress the specified amount of data
    do
    {
        stream->avail_in = baseStream->Read(buffer, 1);
        if (stream->avail_in == 0)
            break;
        stream->next_in = buffer;

        //Console::WriteLine("In: { Next: {0}, Count: {1} }, Out: { Next: {2}, Count: {3} }", stream.next_in, stream.avail_in, stream.next_out, stream.avail_out);

        result = inflate(stream, Z_NO_FLUSH);
        switch (result)
        {
            case Z_NEED_DICT:
                result = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(stream); // TODO: Exception
                return result;
        }
    }
    while (stream->avail_out > 0 && result != Z_STREAM_END);

    // Free everything
    //inflateEnd(stream);
    return count - stream->avail_out;
}
void DeflateStream::Write(void* buffer, u32 count)
{
}
void DeflateStream::Seek(u64 position, SeekOrigin origin)
{
    if (origin == SeekOrigin::Current)
        position += Position;
    else if (origin == SeekOrigin::End)
        position = Length - position;

    if (position == Position)
        return;

    if (position < Position)
    {
        baseStream->Seek(0);
        this->position = 0;
    }

    byte buffer[BUFFER_SIZE];
    byte temp[BUFFER_SIZE];

    int result = Z_OK;

    // ZLib stream
    z_stream* stream = (z_stream*)handle;
    stream->avail_out = position - Position;

    // Decompress the specified amount of data
    do
    {
        stream->avail_in = baseStream->Read(buffer, 1);
        if (stream->avail_in == 0)
            break;

        stream->next_in = buffer;
        stream->next_out = temp;

        //Console::WriteLine("In: { Next: {0}, Count: {1} }, Out: { Next: {2}, Count: {3} }", stream.next_in, stream.avail_in, stream.next_out, stream.avail_out);

        result = inflate(stream, Z_NO_FLUSH);
        switch (result)
        {
        case Z_NEED_DICT:
            result = Z_DATA_ERROR;
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            inflateEnd(stream); // TODO: Exception
            return;
        }
    }
    while (stream->avail_out > 0 && result != Z_STREAM_END);
}