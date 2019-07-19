#include "BasicFontFamily.h"

#include <System/System.h>
#include <[Libraries]/ZLib/DeflateStream.h>

using namespace System::Graphics;
using namespace System::IO;

Reference<Font> BasicFontFamily::GetFont(u8 size, FontAttribute attributes)
{
    FontIndex* fontIndex = null;
    for (u16 i = 0; i < indexCount; i++)
        if (index[i].Attribute == attributes && index[i].Size == size)
            fontIndex = &index[i];
    if (!fontIndex)
        return Reference<Font>::Invalid;

    stream->Seek(fontIndex->Position);
    //stream = new DeflateStream(stream, CompressionMode::Decompress);
    DataStream* data = new DataStream(stream);

    BasicFont* font = new BasicFont();
    font->family = this;
    font->size = size;
    font->attributes = attributes;

    // Metrics
    u16 width = data->Read<u16>();
    u16 height = data->Read<u16>();
    font->baseline = data->Read<u16>();

    // Positions index
    u16* positions = new u16[256];
    data->Read((char*)positions, 256 * sizeof(u16));
    font->positions[0] = 0;
    Memory::Copy<u16>(positions, font->positions + 1, 256);
    delete[] positions;

    // Cache
    u8* cacheBuffer = Memory::Allocate<u8>(width * height);
    data->Read(cacheBuffer, width * height);

    // Translate cache to colors
    Color32* colorBuffer = Memory::Allocate<Color32>(width * height);
    for (u32 y = 0; y < height; y++)
        for (u32 x = 0; x < width; x++)
            colorBuffer[y * width + x] = Color32(255 - cacheBuffer[y * width + x], 0, 0, 0);

    Memory::Free(cacheBuffer);
    font->cache = new Bitmap(colorBuffer, width, height);

    return font;
}
BasicFontFamily* BasicFontFamily::Load(Stream* stream)
{
    //DeflateStream* deflateStream = new DeflateStream(stream, CompressionMode::Decompress);
    DataStream dataStream(stream);

    string header = dataStream.ReadString(4);
    if (header != "Font")
        return null;
    Exception::Assert(header == "Font", "This stream is not a valid font");

    u8 versionMajor = dataStream.Read<u8>();
    u8 versionMinor = dataStream.Read<u8>();

    // Font informations
    BasicFontFamily* fontFamily = new BasicFontFamily();
    fontFamily->stream = stream;
    fontFamily->name = dataStream.Read<string>();
    fontFamily->type = dataStream.Read<FontType>();

    //Console::WriteLine("{ Version: {0}.{1}, Name: {2}, Type: {3} }", versionMajor, versionMinor, fontFamily->name, (u32)fontFamily->type);

    // Font index
    fontFamily->indexCount = dataStream.Read<u16>();
    fontFamily->index = new FontIndex[fontFamily->indexCount];
    for (u16 i = 0; i < fontFamily->indexCount; i++)
    {
        fontFamily->index[i].Attribute = dataStream.Read<FontAttribute>();
        fontFamily->index[i].Size = dataStream.Read<u8>();
        fontFamily->index[i].Position = dataStream.Read<u32>();

        //Console::WriteLine("- { Attribute: {0}, Size: {1}, Position: {2} }", (u32)fontFamily->index[i].Attribute, fontFamily->index[i].Size, fontFamily->index[i].Position);
    }

    return fontFamily;
}

void BasicFont::Draw(Surface* surface, const string& text, u16 x, u16 y, Color32 color, Alignment alignment)
{
    u32 length = text.Length;
    s32 left = x, top = y;
    Point2 size = Measure(text);

    if (Flag::Test(alignment, Alignment::Center))     left -= size.X / 2;
    else if (Flag::Test(alignment, Alignment::Right)) left -= size.X;
    else if (Flag::Test(alignment, Alignment::Left));

    if (Flag::Test(alignment, Alignment::Middle))        top -= baseline / 2;
    else if (Flag::Test(alignment, Alignment::Baseline)) top -= baseline;
    else if (Flag::Test(alignment, Alignment::Bottom))   top -= cache->Size.Y;
    else if (Flag::Test(alignment, Alignment::Top));

    for (u32 i = 0; i < length && left < surface->Size.X; i++)
    {
        char c = text.Buffer[i];// -32;
        if ((u8)c > 128)
            continue;

        u16 cacheX = positions[c];
        u16 width = positions[c + 1] - cacheX;

        surface->DrawBitmap(cacheX, 0, left, top, width, cache->Size.Y, cache, color);

        left += width;
    }
}
Point2 BasicFont::Measure(const string& text)
{
    u32 length = text.Length;
    u32 width = 0;

    for (u32 i = 0; i < length; i++)
    {
        s8 c = text[i];
        if (c >= 32)
            width += positions[c + 1] - positions[c];
    }

    return Point2(width, cache->Size.Y);
}
Point2 BasicFont::Measure(char character)
{
    s8 c = character;

    if (c >= 32)
        return Point2(positions[c + 1] - positions[c], cache->Size.Y);
    else
        return Point2(0, cache->Size.Y);
}