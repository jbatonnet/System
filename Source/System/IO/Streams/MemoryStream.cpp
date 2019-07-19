#include <System/IO/Streams/MemoryStream.h>
#include <System/Memory/Memory.h>
#include <System/Debugging/Debug.h>

using namespace System::IO;

MemoryStream::MemoryStream(void* buffer, uint32 length) : buffer((uint8*)buffer), length(length), position(0), expand(!length) { }

uint64 MemoryStream::GetPosition()
{
    return position;
}
uint64 MemoryStream::GetLength()
{
    return length;
}

uint32 MemoryStream::Read(void* buffer, uint32 count)
{
    if (length && position + count > length)
        count = length - position;

    Memory::Copy(this->buffer + position, buffer, count);
    position += count;

    return count;
}
void MemoryStream::Write(void* buffer, uint32 count)
{
    Debug::Assert(expand || position + count <= length, "MemoryStream : Unable to write data after stream end");

    Memory::Copy(buffer, this->buffer + position, count);
    position += count;

    if (position > length)
        length = position;
}
void MemoryStream::Seek(uint64 position, SeekOrigin origin)
{
    Debug::Assert(position <= length, "Cannot set stream position out of bounds");
    Stream::Seek(position, origin);
}
