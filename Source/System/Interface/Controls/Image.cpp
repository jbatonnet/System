#include <System/Interface/Controls/Image.h>

using namespace System::Interface;
using namespace System::Graphics;

Image::Image(Reference<Bitmap> bitmap) : bitmap(bitmap), color(Colors::Transparent), Control(bitmap->Size)
{
    backColor = Colors::Transparent;
    Redraw();
}
Image::Image(u16 width, u16 height) : color(Colors::Transparent), Control(width, height)
{
    backColor = Colors::White;
    Redraw();
}

void Image::Redraw()
{
    surface->Clear(backColor);

    if (bitmap.Valid)
    {
        if (color.Alpha < 0xFF)
            surface->DrawBitmap(Point2::Zero, Point2::Zero, size, &*bitmap, color);
        else
            surface->DrawBitmap(Point2::Zero, Point2::Zero, size, &*bitmap, true);
    }

    Redrawn(this, Rectangle(position, size));
}