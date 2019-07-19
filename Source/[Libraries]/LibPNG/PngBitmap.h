#ifndef _LIBPNG_PNGBITMAP_H_
#define _LIBPNG_PNGBITMAP_H_

#include <System/Graphics/Bitmap.h>

//#include "lpng1616/png.h"

class PngBitmap : public System::Graphics::Bitmap
{
private:
    void* png;
    void* info;

    PngBitmap(void* data, u16 width, u16 height, u16 padding) : Bitmap(data, width, height) { }

public:
    static PngBitmap* Load(System::IO::Stream* stream);
};

#endif