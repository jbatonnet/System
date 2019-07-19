#include <System/Graphics/Surface.h>
#include <System/Graphics/Colors.h>
#include <System/Graphics/Font.h>
#include <System/Maths/Maths.h>

using namespace System::Graphics;

#define pixel(b, x, y) ((Pixel*)((u32)((b)->data) + (y) * b->_pitch + (x) * sizeof(Pixel)))
#define line(b, y) ((Pixel*)((u32)((b)->data) + (y) * b->_pitch))

#pragma region Alpha blending

#define a(x) ((x) >> 24)
#define r(x) (((x) >> 16) & 0xFF)
#define g(x) (((x) >> 8) & 0xFF)
#define b(x) ((x) & 0xFF)

#define inv(x) (0xFF - (x))
#define mul(x, y) ((x) * (y) / 0xFF)
#define div(x, y) ((x) * 0xFF / (y))

// https://en.wikipedia.org/wiki/Alpha_compositing

// Normal
// out.a = src.a + dst.a * (1 - src.a)
// out.rgb = (src.rgb * src.a + dst.rgb * dst.a * (1 - src.a)) / out.a

// Inverted
// out.a = (1 - src.a) + (1 - dst.a) * src.a
// out.rgb = (src.rgb * (1 - src.a) + dst.rgb * (1 - dst.a) * src.a) / out.a

void Blend(void* destination, void* source, u32 color, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        u32 dst = ((u32*)destination)[i];
        u32 src = ((u32*)source)[i];

        if (!inv(a(src)))
            continue;

        u16 _a = (inv(a(src))) + mul(inv(a(dst)), a(src));
        u16 _r = div(mul(r(color), inv(a(src))) + mul(r(dst), mul(inv(a(dst)), a(src))), _a);
        u16 _g = div(mul(g(color), inv(a(src))) + mul(g(dst), mul(inv(a(dst)), a(src))), _a);
        u16 _b = div(mul(b(color), inv(a(src))) + mul(b(dst), mul(inv(a(dst)), a(src))), _a);

        ((u32*)destination)[i] = (inv(_a) << 24) | (_r << 16) | (_g << 8) | _b;
    }
}
void Blend(void* destination, void* source, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        u32 dst = ((u32*)destination)[i];
        u32 src = ((u32*)source)[i];

        if (!inv(a(src)))
            continue;

        u16 _a = (inv(a(src))) + mul(inv(a(dst)), a(src));
        u16 _r = div(mul(r(src), inv(a(src))) + mul(r(dst), mul(inv(a(dst)), a(src))), _a);
        u16 _g = div(mul(g(src), inv(a(src))) + mul(g(dst), mul(inv(a(dst)), a(src))), _a);
        u16 _b = div(mul(b(src), inv(a(src))) + mul(b(dst), mul(inv(a(dst)), a(src))), _a);

        ((u32*)destination)[i] = (inv(_a) << 24) | (_r << 16) | (_g << 8) | _b;
    }
}
void Blend(void* destination, u32 color, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        u32 dst = ((u32*)destination)[i];

        u16 _a = (inv(a(color))) + mul(inv(a(dst)), a(color));
        u16 _r = div(mul(r(color), inv(a(color))) + mul(r(dst), mul(inv(a(dst)), a(color))), _a);
        u16 _g = div(mul(g(color), inv(a(color))) + mul(g(dst), mul(inv(a(dst)), a(color))), _a);
        u16 _b = div(mul(b(color), inv(a(color))) + mul(b(dst), mul(inv(a(dst)), a(color))), _a);

        ((u32*)destination)[i] = (inv(_a) << 24) | (_r << 16) | (_g << 8) | _b;
    }
}

#undef a
#undef r
#undef g
#undef b

#undef inv
#undef mul
#undef div

#pragma endregion


// Surface

Surface::Surface(void* data, u16 width, u16 height, u16 padding) : Bitmap(data, width, height, padding) { }
Surface::Surface(void* data, Point2 size, u16 padding) : Bitmap(data, size, padding) { }
Surface::Surface(u16 width, u16 height) : Bitmap(null, width, height)
{
    data = Memory::Allocate<Pixel>(width * height);
}
Surface::Surface(Point2 size) : Bitmap(0, size)
{
    data = Memory::Allocate<Pixel>(size.X * size.Y);
}

void Surface::Clear(Color32 color)
{
    if (!padding)
        Memory::Set(data, color, size.X * size.Y);
    else
        for (int y = 0; y < size.Y; y++)
            Memory::Set(line(this, y), color, size.X);
}
void Surface::Resize(Point2 size)
{
    Exception::Assert(size.X >= 1 && size.Y >= 1, "Size can't be zero or negative");

    Pixel* newData = Memory::Allocate<Pixel>(size.X * size.Y, 0);

    // TODO: Copy old data

    Memory::Free(data);
    data = newData;

    this->size = size;
    this->Initialize();
}
void Surface::DrawPoint(s16 x, s16 y, Color32 color)
{
    if (color.Alpha == 0xFF || x < 0 || y < 0 || x >= size.X || y >= size.Y)
        return;

    Blend(pixel(this, x, y), &color, 1);
}
void Surface::DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased)
{
    if (x1 == x2)
    {
        if (y1 == y2)
            return DrawPoint(x1, y1, color);

        FillRectangle(x1, y1, 1, y2 - y1, color);
        return;
    }
    else if (y1 == y2)
    {
        FillRectangle(x1, y1, x2 - x1, 1, color);
        return;
    }
    
    float dx = (s16)x2 - (s16)x1,
          dy = (s16)y2 - (s16)y1;
    bool horizontal = Maths::Abs(dx) >= Maths::Abs(dy);

    if (horizontal)
    {
        if (x1 > x2)
        {
            Maths::Swap(x1, x2);
            Maths::Swap(y1, y2);
        }

        for (s16 x = x1; x <= x2; x++)
        {
            float factor = (x - x1) / dx;
            float y = y1 + dy * factor;

            if (antialiased)
            {
                s16 top = y;
                float position = y - top;

                DrawPoint(x, top, Color32((0xFF - color.Alpha) * position, color.Red, color.Green, color.Blue));
                DrawPoint(x, top + 1, Color32((0xFF - color.Alpha) * (1 - position), color.Red, color.Green, color.Blue));
            }
            else
                DrawPoint(x, y, color);
        }
    }
    else
    {
        if (y1 > y2)
        {
            Maths::Swap(x1, x2);
            Maths::Swap(y1, y2);
        }

        for (s16 y = y1; y <= y2; y++)
        {
            float factor = (y - y1) / dy;
            float x = x1 + dx * factor;

            if (antialiased)
            {
                s16 left = x;
                float position = x - left;

                DrawPoint(left, y, Color32((0xFF - color.Alpha) * position, color.Red, color.Green, color.Blue));
                DrawPoint(left + 1, y, Color32((0xFF - color.Alpha) * (1 - position), color.Red, color.Green, color.Blue));
            }
            else
                DrawPoint(x, y, color);
        }
    }
}
void Surface::DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color)
{
    if (!h || !w)
        return;

    FillRectangle(x, y, 1, h, color);
    FillRectangle(x, y, w, 1, color);
    FillRectangle(x + w - 1, y, 1, h, color);
    FillRectangle(x, y + h - 1, w, 1, color);

    //DrawLine(x, y, x + w, y, color);
    //DrawLine(x + w, y, x + w, y + h, color);
    //DrawLine(x, y + h, x + w, y + h, color);
    //DrawLine(x, y, x, y + h, color);
}
void Surface::FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color)
{
    if (color.Alpha == 0xFF)
        return;
    if (!w || !h)
        return;
    if (w == 1 && h == 1)
        return DrawPoint(x, y, color);

    s16 xPos = Maths::Max<s16>(x, 0),
        xTot = Maths::Min<s16>(w + xPos - x, size.X - xPos),
        yPos = Maths::Max<s16>(y, 0),
        yTot = Maths::Min<s16>(h + yPos - y, size.Y - yPos);

    if (color.Alpha)
    {
        for (y = 0; y < yTot; y++)
            Blend(pixel(this, xPos, yPos + y), color.Value, xTot);
    }
    else
    {
        for (y = 0; y < yTot; y++)
            Memory::Set(pixel(this, xPos, yPos + y), color, xTot);
    }




    /*s16 yMin = Maths::Max<s16>(y, 0),
        yMax = Maths::Min<s16>(y + h, size.Y),
        yTot = yMax - yMin,
        xMin = Maths::Max<s16>(x, 0),
        xMax = Maths::Min<s16>(x + w, size.X),
        xTot = xMax - xMin;

    if (!xTot || !yTot)
        return;
    if (xTot == 1 && yTot == 1)
        return DrawPoint(xMin, yMin, color);
    //if (xTot == 1 || yTot == 1)
    //    return DrawLine(xMin, yMin, xMax, yMax, color);

    if (color.Alpha)
    {
        for (y = yMin; y < yMax; y++)
            Blend(pixel(this, xMin, y), color.Value, xTot);
    }
    else
    {
        for (y = yMin; y < yMax; y++)
            Memory::Set(pixel(this, xMin, y), color, xTot);
    }*/
}
void Surface::DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, bool alpha)
{
    if ((destinationX + w < 0) || (destinationY + h < 0) || (sourceX + w < 0) || (sourceY + h < 0))
        return;
    if (destinationX > size.X || destinationY > size.Y || sourceX > bitmap->Size.X || sourceY > bitmap->Size.Y)
        return;

    s16 xDst = Maths::Max<s16>(destinationX, 0),
        xSrc = sourceX + xDst - destinationX,
        xTot = Maths::Min<s16>(w + xDst - destinationX, size.X - xDst, bitmap->Size.X - xSrc),
        yDst = Maths::Max<s16>(destinationY, 0),
        ySrc = sourceY + yDst - destinationY,
        yTot = Maths::Min<s16>(h + yDst - destinationY, size.Y - yDst, bitmap->Size.Y - ySrc);

    if (alpha)
    {
        for (s16 y = 0; y < yTot; y++)
            Blend(pixel(this, xDst, yDst + y), pixel(bitmap, xSrc, ySrc + y), xTot);
    }
    else
    {
        for (s16 y = 0; y < yTot; y++)
            Memory::Copy<u32>(pixel(bitmap, xSrc, ySrc + y), pixel(this, xDst, yDst + y), xTot);
    }
}
void Surface::DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, Color32 color)
{
    if ((destinationX + w < 0) || (destinationY + h < 0) || (sourceX + w < 0) || (sourceY + h < 0))
        return;
    if (destinationX > size.X || destinationY > size.Y || sourceX > bitmap->Size.X || sourceY > bitmap->Size.Y)
        return;

    s16 yMin = Maths::Max<s16>(destinationY, 0),
        yMax = Maths::Min<s16>(destinationY + h, size.Y),
        yTot = yMax - yMin,
        xMin = Maths::Max<s16>(destinationX, 0),
        xMax = Maths::Min<s16>(destinationX + w, size.X),
        xTot = xMax - xMin,
        srcX = sourceX + destinationX - xMin,
        srcY = sourceY + destinationY - yMin;

    for (s16 y = yMin; y < yMax; y++)
        Blend(pixel(this, xMin, y), pixel(bitmap, srcX, srcY + y - yMin), color.Value, xTot);
}
void Surface::DrawText(const string& text, Reference<Font> font, s16 x, s16 y, Color32 color, Alignment alignment)
{
    font->Draw(this, text, x, y, color, alignment);
}
void Surface::Darken(s16 x, s16 y, u16 width, u16 height, u16 multiplier, u16 divisor)
{
    if (!width || !height)
        return;

    s16 yMin = Maths::Max<s16>(y, 0),
        yMax = Maths::Min<s16>(y + height, size.Y),
        yTot = yMax - yMin,
        xMin = Maths::Max<s16>(x, 0),
        xMax = Maths::Min<s16>(x + width, size.X),
        xTot = xMax - xMin;

    for (y = yMin; y < yMax; y++)
        for (x = xMin; x < xMax; x++)
        {
            Color32 destination = *pixel(this, x, y);

            destination.Red = (u8)((u32)destination.Red * multiplier / divisor);
            destination.Green = (u8)((u32)destination.Green * multiplier / divisor);
            destination.Blue = (u8)((u32)destination.Blue * multiplier / divisor);

            *pixel(this, x, y) = destination;
        }
}


// SubSurface

SubSurface::SubSurface(Surface* surface, s16 x, s16 y, u16 width, u16 height) : x(x), y(y), Surface(pixel(surface, x, y), width, height, (surface->size.X - width) * sizeof(Pixel) + surface->padding) { }
SubSurface::SubSurface(Surface* surface, Point2 position, Point2 size) : x(position.X), y(position.Y), Surface(pixel(surface, position.X, position.Y), size.X, size.Y, (surface->size.X - size.X) * sizeof(Pixel) + surface->padding) { }

void SubSurface::Resize(Point2 size)
{
    Exception::Assert(size.X >= 1 && size.Y >= 1, "Size can't be zero or negative");
    Exception::Assert(x + size.X < baseSurface->size.X && y + size.Y < baseSurface->size.Y, "Size can't exceed base surface size");

    this->size = size;
    padding = (baseSurface->size.X - size.X) * sizeof(Pixel) + baseSurface->padding;
}


// ShiftedSurface

ShiftedSurface::ShiftedSurface(Surface* surface, s16 x, s16 y) : baseSurface(surface), x(x), y(y) { }
ShiftedSurface::ShiftedSurface(Surface* surface, Point2 offset) : baseSurface(surface), x(offset.X), y(offset.Y) { }

void ShiftedSurface::DrawPoint(s16 x, s16 y, Color32 color)
{
    baseSurface->DrawPoint(x + this->x, y + this->y, color);
}
void ShiftedSurface::DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased)
{
    baseSurface->DrawLine(x1 + this->x, y1 + this->y, x2 + this->x, y2 + this->y, color, antialiased);
}
void ShiftedSurface::DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color)
{
    baseSurface->DrawRectangle(x + this->x, y + this->y, w, h, color);
}
void ShiftedSurface::FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color)
{
    baseSurface->FillRectangle(x + this->x, y + this->y, w, h, color);
}
void ShiftedSurface::DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, bool alpha)
{
    baseSurface->DrawBitmap(sourceX, sourceY, destinationX + this->x, destinationY + this->y, w, h, bitmap, alpha);
}
void ShiftedSurface::DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, Color32 color)
{
    baseSurface->DrawBitmap(sourceX, sourceY, destinationX + this->x, destinationY + this->y, w, h, bitmap, color);
}
void ShiftedSurface::DrawText(const string& text, Reference<Font> font, s16 x, s16 y, Color32 color, Alignment alignment)
{
    baseSurface->DrawText(text, font, x + this->x, y + this->y, color, alignment);
}