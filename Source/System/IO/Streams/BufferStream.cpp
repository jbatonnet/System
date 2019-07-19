#include <System/IO/Streams/BufferStream.h>
#include <System/Maths/Maths.h>

using namespace System::IO;

BufferStream::BufferStream(u32 limit) : length(0), limit(limit)
{
    indexesCapacity = 4;
    indexes = Memory::Allocate<byte*>(indexesCapacity);

    bufferCapacity = 512;
    buffer = Memory::Allocate<byte>(bufferCapacity);

    for (u32 i = 0; i < indexesCapacity; i++)
        indexes[i] = buffer + i * BUFFERSTREAM_BLOCK;
}

uint32 BufferStream::Read(void* buffer, uint32 count)
{
    uint8* data = (uint8*)buffer;

    // TODO: Wait if no data available

    for (uint32 i = 0; i < count; i++)
        data[i] = queue.Dequeue();

    return count;
}
void BufferStream::Write(void* buffer, u32 count)
{
    byte* data = (byte*)buffer;

    u32 beginning = Maths::Min(count, BUFFERSTREAM_BLOCK - position);
    Memory::Copy()
}