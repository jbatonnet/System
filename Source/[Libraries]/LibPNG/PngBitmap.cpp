#include "PngBitmap.h"

#include "lpng1616/png.h"

#include <System/IO/Streams/DataStream.h>
#include <System/Debugging/Console.h>

using namespace System::Graphics;
using namespace System::IO;

#define PNG_DEBUG 0

void PngBitmap_Read(png_structp png, png_bytep buffer, png_size_t length)
{
#if PNG_DEBUG
    Console::WriteLine("PngBitmap_Read({0}, {1}, {2})", png, buffer, length);
#endif

    png_voidp pointer = png_get_io_ptr(png);
    Stream* stream = (Stream*)pointer;
    stream->Read(buffer, length);
}

PngBitmap* PngBitmap::Load(System::IO::Stream* stream)
{
#if PNG_DEBUG
    Console::WriteLine("PngBitmap::Load({0})", stream);
#endif

    byte header[8] = { 0x89, 0x50, 0x4E, 0x47, 0x00, 0x00, 0x00, 0x00 };

    stream->Seek(0);
    if (stream->Position == 0)
        stream->Read(header, 8);
    else if (stream->Position == 4)
        stream->Read(header + 4, 4);
    else
        Exception::Assert("[PngBitmap::Load] The specified stream is not seekable");

    Exception::Assert(!png_sig_cmp(header, 0, 8), "[PngBitmap::Load] Stream is not a valid PNG");

    png_struct* png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        Exception::Assert(png, "[PngBitmap::Load] png_create_read_struct failed");
        return null;
    }

    png_info* info = png_create_info_struct(png);
    if (!info)
    {
        Exception::Assert(info, "[PngBitmap::Load] png_create_info_struct failed");
        return null;
    }

    png_set_read_fn(png, (png_voidp)stream, PngBitmap_Read);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    u16 width = png_get_image_width(png, info);
    u16 height = png_get_image_height(png, info);
    u16 bytes = png_get_rowbytes(png, info);
    byte pixel = png_get_color_type(png, info);
    byte depth = png_get_bit_depth(png, info);

#if PNG_DEBUG
    Console::WriteLine("{ Width: {0}, Height: {1}, Depth: {2}, Bytes: {3} }", width, height, depth, bytes);
#endif

    //number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png, info);

    byte* buffer = Memory::Allocate<byte>(height * bytes);
    u32 colorValue;
    byte* color = (byte*)&colorValue;

    for (u16 y = 0; y < height; y++)
    {
        byte* row = buffer + y * bytes;
        png_read_row(png, row, null);

        // Invert alpha
        for (u16 x = 0; x < width; x++)
            row[x * 4 + 3] = 0xFF - row[x * 4 + 3];
    }
    
    return new PngBitmap(buffer, width, height, bytes - width * 4);
}