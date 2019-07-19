#include <System/IO/Streams/TextStream.h>

using namespace System::IO;

static char* eol = "\r\n";

TextStream::TextStream(Stream* baseStream) : baseStream(baseStream) { }

u64 TextStream::GetPosition()
{
    return baseStream->GetPosition();
}
u64 TextStream::GetLength()
{
    return baseStream->GetLength();
}

u32 TextStream::Read(void* buffer, u32 count)
{
    return baseStream->Read(buffer, count);
}
void TextStream::Write(void* buffer, u32 count)
{
    baseStream->Write(buffer, count);
}
void TextStream::Seek(u64 position, SeekOrigin origin)
{
    baseStream->Seek(position, origin);
}

string TextStream::Read(u32 length)
{
    char* data = new char[length + 1];
    baseStream->Read(data, length);
    data[length] = 0;
    return string(data, length);
}
string TextStream::ReadLine()
{
    if (baseStream->EndOfStream)
        return String::Empty;

    char data[0x400];
    char* ptr = data;

    char c;
    do
    {
        baseStream->Read(&c, 1);

        switch (c)
        {
            case '\b': if (ptr > data) *--ptr = ' '; break;
            default: *ptr++ = c;
        }
    }
    while (c && c != '\n' && !baseStream->EndOfStream);

    while (*(ptr - 1) == '\n' || *(ptr - 1) == '\r')
        ptr--;
    *ptr = 0;

    string result(data);
    return result;
}
string TextStream::ReadAll()
{
    char data[0x1000];
    char* ptr = data;

    char c;
    do
    {
        baseStream->Read(&c, 1);
        *ptr++ = c;
    }
    while (!baseStream->EndOfStream);

    *ptr = 0;

    string result(data);
    return result;
}

/*void TextStream::Write(const string& value)
{
    Write(value.characters, value.Length);
    Write((char*)(eol + 2), (u32)1);
}
void TextStream::WriteLine(const string& value)
{
    Write(value.characters, value.Length);
    Write((char*)eol, (u32)3);
}*/