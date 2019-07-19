#include <System/Graphics/Bitmap.h>

#include <[Libraries]/Basics/Images/BasicBitmap.h>
#include <[Libraries]/LibPNG/PngBitmap.h>

#include <System/Debugging/Console.h>

using namespace System::Graphics;
using namespace System::IO;

template<typename T>
Reference<Bitmap> Bitmap::Load(Stream* stream)
{
    return BasicBitmap::Load(stream);
}
Reference<Bitmap> Bitmap::Load(File* file)
{
    Stream* stream = file->GetStream();
    if (!stream)
        return Reference<Bitmap>::Invalid;

    if (file->Extension == "image")
        return BasicBitmap::Load(stream);
    if (file->Extension == "png")
        return PngBitmap::Load(stream);

    return Load(file->GetStream());
}
Reference<Bitmap> Bitmap::Load(const string& path)
{
    File* file = File::Open(path);
    if (!file)
        return Reference<Bitmap>::Invalid;

    return Load(file);
}