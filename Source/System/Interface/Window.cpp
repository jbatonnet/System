#include <System/Interface/Window.h>
#include <System/Interface/WindowsManager.h>
#include <System/Utilities/Random.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;

Window::Window(const string& title, bool buttons, bool moveable) : title(title), layer(WindowLayer::Normal)
{
    Size = Point(96, 96);

    if (moveable)
    {
        // Mover
        Add(mover = new Mover(this));
        mover->Size = Point(Size.X - 40, 40);
        mover->Position = Point::Zero;
        mover->Dock = DockStyle::TopFull;
    }

    if (buttons)
    {
        // Close
        Add(close = new Button(Bitmaps::Icons::Close));
        close->Size = Point(40, 39);
        close->Position = Point(size.X - close->Size.X, 0);
        close->Dock = DockStyle::TopRight;
        close->BackColor = BackColor;
        close->OverColor = 0xE0000000;
        close->DownColor = 0xC0000000;
        close->PointerUp += Event<PointerEvent>::Callback(this, &Window::Close_PointerUp);
    }
}

void Window::Initialize()
{
}

void Window::Close_PointerUp(void* origin, PointerEvent e)
{
    WindowsManager::Remove(this);
}

void Window::SetBackColor(Color32 value)
{
    Container::SetBackColor(value);
    close->BackColor = value;
}