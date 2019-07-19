#include <System/Interface/Containers/TabContainer.h>
#include <System/Maths/Maths.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;

/*
    Colors
    - Header background: 0xE4E9EB
    - Active tab: 0xFFFFFF
    - Active tab border: 0xBECACE
    - Inactive tab: 0xEFF2F3
    - Inactive tab border: 0xD7DFE1
    - Tab title: 0x364E55
*/

TabContainer::TabContainer() : currentIndex(-1), currentTab(null), orientation(Orientation::RightToLeft)
{
    Container::Add(header = new StackContainer());
    header->BackColor = 0xE4E9EB;
    header->BorderColor = 0xBECACE;

    SetOrientation(Orientation::Horizontal);
}

void TabContainer::SetCurrentTab(Tab* value)
{
    if (currentTab == value)
        return;

    u32 index = 0;
    for (index = 0; index < tabs.Count; index++)
        if (tabs.At(index)->Key == value)
            break;

    if (index >= tabs.Count)
        return;

    Button* button;

    if (currentIndex >= 0)
    {
        button = tabs.At(currentIndex)->Value;
        button->BackColor = 0xEFF2F3;
    }

    button = tabs.At(index)->Value;
    button->BackColor = 0xFFFFFF;

    currentIndex = index;
    currentTab = value;
}
Orientation TabContainer::SetOrientation(System::Graphics::Orientation value)
{
    if (value == orientation)
        return orientation;
    if (value != Orientation::Horizontal && value != Orientation::Vertical)
        return orientation;

    //OrientationChanged(this, orientation, value);
    orientation = value;
    header->Orientation = value;

    if (orientation == Orientation::Horizontal)
    {
        header->Size = Point(size.X, 40);
        header->Dock = DockStyle::TopFull;
        header->Border = Outline(0, 0, 1, 0);
    }
    else if (orientation == Orientation::Vertical)
    {
        header->Size = Point(192, size.Y);
        header->Dock = DockStyle::LeftFull;
        header->Border = Outline(0, 1, 0, 0);
    }

    return orientation;
}

/*void TabContainer::Initialize()
{
    Container::Initialize();

    for (u32 i = 0; i < tabs.Count; i++)
        tabs.At(i)->Key->Initialize();

    if (!currentTab && tabs.Count > 0)
        CurrentTab = tabs.At(0)->Key;
}*/
void TabContainer::Add(Tab* tab)
{
    tab->Position = Point2::Zero;
    tab->Size = Point(size.X, size.Y - header->Size.Y);
    tab->Dock = DockStyle::Full;

    Button* button = new Button(tab->Title);
    button->Tag = tab;

    if (orientation == Orientation::Horizontal)
    {
        button->Size = Point(96, header->Size.Y - 1);
        button->Dock = DockStyle::LeftFull;
    }
    else if (orientation == Orientation::Vertical)
    {
        button->Size = Point(header->Size.X - 1, 40);
        button->Dock = DockStyle::TopFull;
    }

    header->Add(button);
    tabs.Add(tab, button);

    // Events
    button->PointerDown += Event<PointerEvent>::Callback(this, &TabContainer::Tab_PointerDown);
}
void TabContainer::Redraw(Surface* surface, Rectangle rectangle)
{
    Container::Redraw(surface, rectangle);

    if (currentIndex < 0)
        return;

    if (orientation == Orientation::Horizontal)
    {
        rectangle.Position.Y += header->Size.Y;
        rectangle.Size.Y -= header->Size.Y;
    }
    else if (orientation == Orientation::Vertical)
    {
        rectangle.Position.X += header->Size.X;
        rectangle.Size.X -= header->Size.X;
    }

    SubSurface subSurface(surface, rectangle.Position.X, rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y);

    if (orientation == Orientation::Horizontal)
        rectangle.Position.Y -= header->Size.Y;
    else if (orientation == Orientation::Vertical)
        rectangle.Position.X -= header->Size.X;

    currentTab->Redraw(&subSurface, rectangle);
}

void TabContainer::Tab_PointerDown(void* origin, PointerEvent e)
{
    Button* button = (Button*)origin;
    CurrentTab = (Tab*)button->Tag;
}