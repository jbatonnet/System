#include <System/IO/Streams/TeeStream.h>
#include <System/Maths/Maths.h>

using namespace System::IO;

TeeStream::TeeStream(Stream* stream)
{
    streams.Add(stream);
}
TeeStream::TeeStream(Stream* stream1, Stream* stream2)
{
    streams.Add(stream1);
    streams.Add(stream2);
}
TeeStream::TeeStream(Stream* stream1, Stream* stream2, Stream* stream3)
{
    streams.Add(stream1);
    streams.Add(stream2);
    streams.Add(stream3);
}
TeeStream::TeeStream(Stream* stream1, Stream* stream2, Stream* stream3, Stream* stream4)
{
    streams.Add(stream1);
    streams.Add(stream2);
    streams.Add(stream3);
    streams.Add(stream4);
}

u32 TeeStream::Read(void* buffer, u32 count)
{
    u32 result = -1;

    for (u32 i = 0; i < streams.Count; i++)
        result = Maths::Min(result, streams[i]->Read(buffer, count));

    return result;
}
void TeeStream::Write(void* buffer, u32 count)
{
    for (u32 i = 0; i < streams.Count; i++)
        streams[i]->Write(buffer, count);
}