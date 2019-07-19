#include <System/Graphics/Bitmap.h>
#include <System/IO/ResourceLoader.h>

using namespace System::Graphics;
using namespace System::IO;

template<typename T> Reference<Bitmap> Bitmap::Load(Stream* stream)
{
    return T::Load(stream);
}
Reference<Bitmap> Bitmap::Load(File* file)
{
    if (!file)
        return Reference<Bitmap>::Invalid;

    return ResourceLoaderBase<Bitmap>::Load(file);
}
Reference<Bitmap> Bitmap::Load(const string& path)
{
    return Load(File::Open(path));
}

#define Bitmap(name, path) Dynamic<Bitmap> Bitmaps::name([] { return Bitmap::Load(path); })

Bitmap(Cursors::Normal, "/System/Images/Cursors/Normal.png");

Bitmap(Icons::Close, "/System/Images/Icons/Close.png");
Bitmap(Icons::Plus, "/System/Images/Icons/Plus.png");

Bitmap(Icons::Up, "/System/Images/Icons/Up.png");
Bitmap(Icons::Right, "/System/Images/Icons/Right.png");
Bitmap(Icons::Down, "/System/Images/Icons/Down.png");
Bitmap(Icons::Left, "/System/Images/Icons/Left.png");