#include <System/Interface/Controls/Label.h>

#include <System/Debugging/Serial.h>

using namespace System::Graphics;
using namespace System::Interface;

Label::Label() : color(Colors::Black), text(""), autoSize(true), alignment(Alignment::TopLeft)
{
    backColor = Colors::Transparent;
    font = FontFamily::GetDefaultFamily()->GetFont(10);
}
Label::Label(string text) : color(Colors::Black), text(text), autoSize(true), alignment(Alignment::TopLeft)
{
    backColor = Colors::Transparent;
    font = FontFamily::GetDefaultFamily()->GetFont(10);

    UpdateSize();
}

void Label::SetBackColor(Color32 value)
{
    Control::SetBackColor(value);

    Redraw();
}
void Label::SetSize(Point value)
{
    autoSize = false;

    Control::SetSize(value);
}

void Label::Redraw()
{
    surface->Clear(backColor);

    u16 x = 0,
        y = 0;

    if (Flag::Test(alignment, Alignment::Center))     x = size.X / 2;
    else if (Flag::Test(alignment, Alignment::Right)) x = size.X;
    else if (Flag::Test(alignment, Alignment::Left))  x = 0;

    if (Flag::Test(alignment, Alignment::Middle))        y = size.Y / 2;
    else if (Flag::Test(alignment, Alignment::Baseline)) y = size.Y / 2;
    else if (Flag::Test(alignment, Alignment::Bottom))   y = size.Y;
    else if (Flag::Test(alignment, Alignment::Top))      y = 0;

    if (font.Valid)
        surface->DrawText(text, font, x, y, color, alignment);

    Redrawn(this, Rectangle(position, size));
}

void Label::UpdateSize()
{
    if (!autoSize)
        return;

    if (font.Valid)
        Control::SetSize(font->Measure(text));
}