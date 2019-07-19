#include <System/System.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;

Button::Button(const string& text) : text(text), color(Colors::Black), overColor(0x80FFFFFF), downColor(0x80000000), style(ButtonStyle::Text), state(ButtonState::Idle), alignment(Alignment::MiddleCenter), Control(40, 40)
{
    backColor = Colors::Transparent;
    font = FontFamily::GetDefaultFamily()->GetFont(10);

    Redraw();
}
Button::Button(const Reference<Bitmap>& bitmap) : image(bitmap), color(Colors::Transparent), overColor(0x80FFFFFF), downColor(0x80000000), style(ButtonStyle::Image), state(ButtonState::Idle), alignment(Alignment::MiddleCenter), Control(40, 40)
{
    backColor = Colors::Transparent;
    font = FontFamily::GetDefaultFamily()->GetFont(10);

    Redraw();
}

void Button::Redraw()
{
    surface->Clear(backColor);

    switch (state)
    {
        case ButtonState::Over: surface->FillRectangle(Point2::Zero, size, overColor); break;
        case ButtonState::Down: surface->FillRectangle(Point2::Zero, size, downColor); break;
    }

    if (border.Top > 0) surface->FillRectangle(0, 0, size.X, border.Top, borderColor);
    if (border.Right > 0) surface->FillRectangle(size.X - border.Right, 0, border.Right, size.Y, borderColor);
    if (border.Bottom > 0) surface->FillRectangle(0, size.Y - border.Bottom, size.X, border.Bottom, borderColor);
    if (border.Left > 0) surface->FillRectangle(0, 0, border.Left, size.Y, borderColor);

    if (style == ButtonStyle::Text)
    {
        u32 x = padding.Left, y = padding.Top;

        if (Flag::Test(alignment, Alignment::Center))     x = padding.Left + (size.X - padding.Left - padding.Right) / 2;
        else if (Flag::Test(alignment, Alignment::Right)) x = size.X - padding.Right;
        else if (Flag::Test(alignment, Alignment::Left));

        if (Flag::Test(alignment, Alignment::Middle) || Flag::Test(alignment, Alignment::Baseline)) y = padding.Top + (size.Y - padding.Top - padding.Bottom) / 2;
        else if (Flag::Test(alignment, Alignment::Bottom))                                          y = size.Y - padding.Bottom;
        else if (Flag::Test(alignment, Alignment::Top));

        surface->DrawText(text, font, x, y, color, alignment);
    }
    else if (style == ButtonStyle::Image && image.Valid)
    {
        if (color.Alpha < 0xFF)
            surface->DrawBitmap(Point2::Zero, Point2((size.X - image->Size.X) / 2, (size.Y - image->Size.Y) / 2), Point2(image->Size.X, image->Size.Y), &*image, color);
        else
            surface->DrawBitmap(Point2::Zero, Point2((size.X - image->Size.X) / 2, (size.Y - image->Size.Y) / 2), Point2(image->Size.X, image->Size.Y), &*image, true);
    }

    Redrawn(this, Rectangle(position, size));
}

void Button::OnPointerIn(void* origin, PointerEvent pointerEvent)
{
    state = ButtonState::Over;
    Redraw();

    Element::OnPointerIn(origin, pointerEvent);
}
void Button::OnPointerOut(void* origin, PointerEvent pointerEvent)
{
    state = ButtonState::Idle;
    Redraw();

    Element::OnPointerOut(origin, pointerEvent);
}
void Button::OnPointerDown(void* origin, PointerEvent pointerEvent)
{
    state = ButtonState::Down;
    Redraw();

    Element::OnPointerDown(origin, pointerEvent);
}
void Button::OnPointerUp(void* origin, PointerEvent pointerEvent)
{
    state = pointed ? ButtonState::Over : ButtonState::Idle;
    Redraw();

    Element::OnPointerUp(origin, pointerEvent);
}