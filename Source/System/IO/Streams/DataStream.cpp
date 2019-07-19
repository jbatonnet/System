#include <System/IO/Streams/DataStream.h>

using namespace System::IO;

DataStream::DataStream(Stream* baseStream) : baseStream(baseStream)
{
    buffer = new char[16];
}

u64 DataStream::GetPosition()
{
    return baseStream->GetPosition();
}
void DataStream::SetPosition(u64 position)
{
    baseStream->SetPosition(position);
}
u64 DataStream::GetLength()
{
    return baseStream->GetLength();
}

u32 DataStream::Read(void* buffer, u32 count)
{
    return baseStream->Read(buffer, count);
}
void DataStream::Write(void* buffer, u32 count)
{
    baseStream->Write(buffer, count);
}

string DataStream::ReadString(u32 length)
{
    char* buffer = new char[length];
    baseStream->Read(buffer, length);
    return string(buffer, length);
}
void DataStream::Write(string& value)
{
    Write(value.Buffer, value.Length);
    Write<u8>(0);
}