#include <System/Interface/Controls/Control.h>

using namespace System::Graphics;
using namespace System::Interface;

Control::Control()
{
    size = Point(40, 40);
    surface = new System::Graphics::Surface(size);
}
Control::Control(u16 width, u16 height)
{
    size = Point(width, height);
    surface = new System::Graphics::Surface(size);
}
Control::Control(Point size)
{
    this->size = size;
    surface = new System::Graphics::Surface(size);
}

void Control::SetSize(Point value)
{
    if (value == size)
        return;

    size = value;
    surface->Resize(size);

    Redraw();
}