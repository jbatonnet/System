#include <System/Interface/Containers/Container.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>
#include <System/Maths/Maths.h>

#include <System/Debugging/Log.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;

void Container::SetSize(Point value)
{
    if (value == size)
        return;

    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        if (container->Dock == DockStyle::None)
            continue;

        if (Flag::Test(container->Dock, DockStyle::Right))
        {
            if (Flag::Test(container->Dock, DockStyle::Left))
                container->Size = Point(container->Size.X + value.X - size.X, container->Size.Y);
            else
                container->Position.X += value.X - size.X;
        }

        if (Flag::Test(container->Dock, DockStyle::Bottom))
        {
            if (Flag::Test(container->Dock, DockStyle::Left))
                container->Size = Point(container->Size.X, container->Size.Y + value.Y - size.Y);
            else
                container->Position.Y += value.Y - size.Y;
        }
    }

    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        if (control->Dock == DockStyle::None)
            continue;

        if (Flag::Test(control->Dock, DockStyle::Right))
        {
            if (Flag::Test(control->Dock, DockStyle::Left))
                control->Size = Point(control->Size.X + value.X - size.X, control->Size.Y);
            else
                control->Position.X += value.X - size.X;
        }

        if (Flag::Test(control->Dock, DockStyle::Bottom))
        {
            if (Flag::Test(control->Dock, DockStyle::Left))
                control->Size = Point(control->Size.X, control->Size.Y + value.Y - size.Y);
            else
                control->Position.Y += value.Y - size.Y;
        }
    }

    Maths::Swap(size, value);
    SizeChanged(this, value, size);

    Refreshed(this, Rectangle(position, size));
}
void Container::SetBackColor(Color32 value)
{
    if (backColor.Value == value.Value)
        return;

    backColor = value;

    Refreshed(this, Rectangle(Point2::Zero, size));
}
void Container::SetBorderColor(Color32 value)
{
    if (borderColor == value)
        return;

    borderColor = value;
    if (!border.Top && !border.Right && !border.Bottom && !border.Left)
        SetBorder(Outline(1));

    Refreshed(this, Rectangle(Point2::Zero, size));
}

void Container::Add(Container* container)
{
    containers.Add(container);
    container->Refreshed += Event<Rectangle>::Callback(this, &Container::Container_Refreshed);
}
void Container::Add(Control* control)
{
    controls.Add(control);
    control->Redrawn += Event<Rectangle>::Callback(this, &Container::Control_Redrawn);
}
void Container::Remove(Container* container)
{
    containers.Remove(container);
    container->Refreshed -= Action<void*, Rectangle>(this, &Container::Container_Refreshed);
}
void Container::Remove(Control* control)
{
    controls.Remove(control);
    control->Redrawn -= Action<void*, Rectangle>(this, &Container::Control_Redrawn);
}
void Container::Clear()
{
    while (containers.Count > 0)
        Remove(containers[0]);

    while (controls.Count > 0)
        Remove(controls[0]);
}

void Container::OnPointerMove(void* origin, PointerPositionEvent pointerPositionEvent)
{
    bool found = false;

    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        bool wasPointed = container->pointed;
        bool isPointed = !(pointerPositionEvent.X < container->Position.X || pointerPositionEvent.X >= container->Position.X + container->Size.X || pointerPositionEvent.Y < container->Position.Y || pointerPositionEvent.Y >= container->Position.Y + container->Size.Y);

        PointerPositionEvent pointerSubPositionEvent = pointerPositionEvent;
        pointerSubPositionEvent.X -= container->Position.X;
        pointerSubPositionEvent.Y -= container->Position.Y;

        if (!wasPointed && isPointed)
        {
            container->OnPointerIn(container, pointerPositionEvent);
            container->OnPointerMove(container, pointerSubPositionEvent);
        }
        else if (wasPointed && isPointed)
            container->OnPointerMove(container, pointerSubPositionEvent);
        else if (wasPointed && !isPointed)
            container->OnPointerOut(container, pointerPositionEvent);

        container->pointed = isPointed;
        found |= isPointed;
    }

    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        bool wasPointed = control->pointed;
        bool isPointed = !(pointerPositionEvent.X < control->Position.X || pointerPositionEvent.X >= control->Position.X + control->Size.X || pointerPositionEvent.Y < control->Position.Y || pointerPositionEvent.Y >= control->Position.Y + control->Size.Y);

        PointerPositionEvent pointerSubPositionEvent = pointerPositionEvent;
        pointerSubPositionEvent.X -= control->Position.X;
        pointerSubPositionEvent.Y -= control->Position.Y;

        if (!wasPointed && isPointed)
        {
            control->OnPointerIn(control, pointerPositionEvent);
            control->OnPointerMove(control, pointerSubPositionEvent);
        }
        else if (wasPointed && isPointed)
            control->OnPointerMove(control, pointerSubPositionEvent);
        else if (wasPointed && !isPointed)
            control->OnPointerOut(control, pointerPositionEvent);

        control->pointed = isPointed;
        found |= isPointed;
    }

    if (!found)
        PointerMove(origin, pointerPositionEvent);
}
void Container::OnPointerIn(void* origin, PointerEvent pointer)
{
    
}
void Container::OnPointerOut(void* origin, PointerEvent pointer)
{
    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        if (!container->pointed)
            continue;

        container->OnPointerOut(container, pointer);
        container->pointed = false;
    }

    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        if (!control->pointed)
            continue;

        control->OnPointerOut(control, pointer);
        control->pointed = false;
    }

    if (pointed)
        PointerOut(origin, pointer);
}
void Container::OnPointerDown(void* origin, PointerEvent pointerEvent)
{
    bool found = false;

    for (s32 i = containers.Count - 1; i >= 0; i--)
    {
        Container* container = containers[i];

        if (!found && container->pointed)
        {
            container->OnPointerDown(container, pointerEvent);
            found = true;
        }
    }

    for (s32 i = controls.Count - 1; i >= 0; i--)
    {
        Control* control = controls[i];

        if (!found && control->pointed)
        {
            control->OnPointerDown(control, pointerEvent);
            found = true;
        }
    }

    if (!found)
        PointerDown(origin, pointerEvent);
}
void Container::OnPointerUp(void* origin, PointerEvent pointerEvent)
{
    bool found = false;

    for (s32 i = containers.Count - 1; i >= 0; i--)
    {
        Container* container = containers[i];

        if (!found && container->pointed)
        {
            container->OnPointerUp(container, pointerEvent);
            found = true;
        }
    }

    for (s32 i = controls.Count - 1; i >= 0; i--)
    {
        Control* control = controls[i];

        if (!found && control->pointed)
        {
            control->OnPointerUp(control, pointerEvent);
            found = true;
        }
    }

    if (!found)
        PointerUp(origin, pointerEvent);
}
void Container::OnPointerScroll(void* origin, PointerScrollEvent pointerScrollEvent)
{
    bool found = false;

    for (s32 i = containers.Count - 1; i >= 0; i--)
    {
        Container* container = containers[i];

        if (!found && container->pointed)
        {
            container->OnPointerScroll(container, pointerScrollEvent);
            found = true;
        }
    }

    for (s32 i = controls.Count - 1; i >= 0; i--)
    {
        Control* control = controls[i];

        if (!found && control->pointed)
        {
            control->OnPointerScroll(control, pointerScrollEvent);
            found = true;
        }
    }

    if (!found)
        PointerScroll(origin, pointerScrollEvent);
}

void Container::OnButtonDown(void* origin, ButtonEvent buttonEvent)
{
    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        //if (container->pointed)
            container->OnButtonDown(container, buttonEvent);
    }

    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        //if (control->pointed)
            control->OnButtonDown(control, buttonEvent);
    }
}
void Container::OnButtonUp(void* origin, ButtonEvent buttonEvent)
{
    for (u32 i = 0; i < containers.Count; i++)
    {
        Container* container = containers[i];
        //if (container->pointed)
            container->OnButtonUp(container, buttonEvent);
    }

    for (u32 i = 0; i < controls.Count; i++)
    {
        Control* control = controls[i];
        //if (control->pointed)
            control->OnButtonUp(control, buttonEvent);
    }
}

void Container::Container_Refreshed(void* container, Rectangle rectangle)
{
    rectangle.Position.X += position.X;
    rectangle.Position.Y += position.Y;

    Refreshed(this, rectangle);
}
void Container::Control_Redrawn(void* origin, Rectangle rectangle)
{
    rectangle.Position.X += position.X;
    rectangle.Position.Y += position.Y;

    Refreshed(this, rectangle);
}

void Container::Redraw(Surface* surface, Rectangle rectangle)
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

        r.Position.X -= container->Position.X;
        r.Position.Y -= container->Position.Y;

        container->Redraw(&subSurface, r);
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

        if (control->backColor.Alpha)
            surface->FillRectangle(control->Position, control->Size, backColor);

        surface->DrawBitmap(Point2::Zero, control->Position, control->Size, control->surface, true);
    }
}