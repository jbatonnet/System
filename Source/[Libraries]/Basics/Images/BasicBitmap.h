#ifndef _BASICBITMAP_H_
#define _BASICBITMAP_H_

#include <System/Graphics/Bitmap.h>
#include <System/IO/Streams/Stream.h>

class BasicBitmap : public System::Graphics::Bitmap
{
private:
    BasicBitmap(u16 width, u16 height, void* data) : Bitmap(data, width, height) { }

public:
    static BasicBitmap* Load(System::IO::Stream* stream);
};

#endif