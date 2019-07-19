#include <System/Interface/Containers/ScrollContainer.h>

using namespace System::Devices;
using namespace System::Graphics;
using namespace System::Interface;

ScrollContainer::ScrollContainer() : view(0, 0)
{
}

void ScrollContainer::OnPointerMove(void* origin, PointerPositionEvent pointerPositionEvent)
{
    pointerPositionEvent.X += view.X;
    pointerPositionEvent.Y += view.Y;

    Container::OnPointerMove(origin, pointerPositionEvent);
}
void ScrollContainer::OnPointerScroll(void* origin, PointerScrollEvent pointerScrollEvent)
{
    view.Y += pointerScrollEvent.Delta * 32;
    view.Y = Maths::Clamp(view.Y, 0, Maths::Max(0, content.Y - size.Y));

    Refreshed(this, Rectangle(position, size));
}
void ScrollContainer::Redraw(Surface* surface, Rectangle rectangle)
{
    surface->FillRectangle(rectangle.Position, rectangle.Size, backColor);

    // Borders
    surface->FillRectangle(0, 0, size.X, border.Top, borderColor);
    surface->FillRectangle(size.X - border.Right, 0, border.Right, rectangle.Size.Y, borderColor);
    surface->FillRectangle(0, size.Y - border.Bottom, size.X, border.Bottom, borderColor);
    surface->FillRectangle(0, 0, border.Left, size.Y, borderColor);

    // Subcontainers
    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        if (!container->Visible)
            continue;

        Rectangle r = Rectangle(container->Position, container->Size);

        r.Position.X = Maths::Max(r.Position.X, rectangle.Position.X);
        r.Size.X = Maths::Min(r.Position.X + r.Size.X, rectangle.Position.X + rectangle.Size.X) - r.Position.X;
        r.Position.Y = Maths::Max(r.Position.Y, rectangle.Position.Y);
        r.Size.Y = Maths::Min(r.Position.Y + r.Size.Y, rectangle.Position.Y + rectangle.Size.Y) - r.Position.Y;

        SubSurface subSurface(surface, r.Position.X, r.Position.Y, r.Size.X, r.Size.Y);
        ShiftedSurface shiftedSurface(&subSurface, -view.X, -view.Y);

        r.Position.X -= container->Position.X;
        r.Position.Y -= container->Position.Y;

        container->Redraw(&shiftedSurface, r);
    }

    // Subcontrols
    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        if (!control || !control->Visible)
            continue;

        //if (control->Position.X > rectangle.Position.X + rectangle.Size.X) continue;
        //if (control->Position.X + control->Size.X < rectangle.Position.X) continue;
        //if (control->Position.Y > rectangle.Position.Y + rectangle.Size.Y) continue;
        //if (control->Position.Y + control->Size.Y < rectangle.Position.Y) continue;

        if (control->BackColor.Alpha)
            surface->FillRectangle(control->Position, control->Size, backColor);

        surface->DrawBitmap(Point2::Zero, control->Position, control->Size, control->Surface, true);
    }

    // Vertical scrollbar
    if (content.Y > size.Y)
    {
        u16 ySize = Maths::Max<u16>(16, size.Y * size.Y / content.Y);
        u16 yPosition = view.Y * size.Y / content.Y;

        surface->FillRectangle(size.X - 6, yPosition, 6, ySize, 0xA0000000);
    }
}

void ScrollContainer::Add(Container* container)
{
    container->SizeChanged += ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_SizeChanged);
    container->PositionChanged += ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_PositionChanged);
    container->VisibleChanged += ChangeEvent<bool>::Callback(this, &ScrollContainer::Element_VisibleChanged);

    Container::Add(container);
    RefreshSizes();
}
void ScrollContainer::Add(Control* control)
{
    control->SizeChanged += ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_SizeChanged);
    control->PositionChanged += ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_PositionChanged);
    control->VisibleChanged += ChangeEvent<bool>::Callback(this, &ScrollContainer::Element_VisibleChanged);

    Container::Add(control);
    RefreshSizes();
}
void ScrollContainer::Remove(Container* container)
{
    container->SizeChanged -= ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_SizeChanged);
    container->PositionChanged -= ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_PositionChanged);
    container->VisibleChanged -= ChangeEvent<bool>::Callback(this, &ScrollContainer::Element_VisibleChanged);

    Container::Remove(container);
    RefreshSizes();
}
void ScrollContainer::Remove(Control* control)
{
    control->SizeChanged -= ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_SizeChanged);
    control->PositionChanged -= ChangeEvent<Point>::Callback(this, &ScrollContainer::Element_PositionChanged);
    control->VisibleChanged -= ChangeEvent<bool>::Callback(this, &ScrollContainer::Element_VisibleChanged);

    Container::Remove(control);
    RefreshSizes();
}

void ScrollContainer::Element_SizeChanged(void* control, ChangeEventParameter<Point> parameter)
{
    RefreshSizes();
}
void ScrollContainer::Element_PositionChanged(void* control, ChangeEventParameter<Point> parameter)
{
    RefreshSizes();
}
void ScrollContainer::Element_VisibleChanged(void* control, ChangeEventParameter<bool> parameter)
{
    RefreshSizes();
}

void ScrollContainer::RefreshSizes()
{
    u16 xMax = 0,
        yMax = 0;

    // Subcontainers
    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        if (!container->Visible)
            continue;

        xMax = Maths::Max<u16>(xMax, container->Position.X + container->Size.X);
        yMax = Maths::Max<u16>(yMax, container->Position.Y + container->Size.Y);
    }

    // Subcontrols
    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        if (!control || !control->Visible)
            continue;

        xMax = Maths::Max<u16>(xMax, control->Position.X + control->Size.X);
        yMax = Maths::Max<u16>(yMax, control->Position.Y + control->Size.Y);
    }

    // Refresh if needed
    if (xMax != content.X || yMax != content.Y)
    {
        content = Point2(xMax, yMax);
        Refreshed(this, Rectangle(position, size));
    }
}