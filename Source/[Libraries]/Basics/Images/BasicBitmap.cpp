#include "BasicBitmap.h"

#include <System/System.h>
#include <[Libraries]/ZLib/DeflateStream.h>

using namespace System::Graphics;
using namespace System::IO;

//ResourceLoader<Bitmap, BasicBitmap> basicBitmapLoader("image");

BasicBitmap* BasicBitmap::Load(Stream* stream)
{
    stream = new DeflateStream(stream, CompressionMode::Decompress);
    DataStream* data = new DataStream(stream);

    string& tag = data->ReadString(5);
    if (tag != "Image")
    {
        delete data;
        return null;
    }

    u16 width = data->Read<u16>();
    u16 height = data->Read<u16>();

    u32* pixels = Memory::Allocate<u32>(width * height);
    u32 size = stream->Read(pixels, width * height * sizeof(u32));
    if (size != width * height * sizeof(u32))
    {
        delete data;
        delete pixels;
        return null;
    }

    for (u16 y = 0; y < height; y++)
        for (u16 x = 0; x < width; x++)
        {
            u8 alpha = (pixels[y * width + x] >> 24) & 0xFF;
            
            pixels[y * width + x] &= 0x00FFFFFF;
            pixels[y * width + x] |= (0xFF - alpha) << 24;
        }

    BasicBitmap* bitmap = new BasicBitmap(width, height, pixels);

    delete data;
    return bitmap;
}