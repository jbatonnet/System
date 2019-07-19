#include <System/Interface/Containers/StackContainer.h>

#include <System/Debugging/Serial.h>

using namespace System::Graphics;
using namespace System::Interface;

StackContainer::StackContainer() : orientation(Orientation::Horizontal), autoSize(false)
{
    SetSize(Point2(40, 40));
}

void StackContainer::Add(Container* container)
{
    Container::Add(container);
    elements.Add(container);

    Refresh(container);

    container->SizeChanged += ChangeEvent<Point>::Callback(this, &StackContainer::Element_SizeChanged);
    container->PositionChanged += ChangeEvent<Point>::Callback(this, &StackContainer::Element_PositionChanged);
    container->VisibleChanged += ChangeEvent<bool>::Callback(this, &StackContainer::Element_VisibleChanged);
    container->MarginChanged += ChangeEvent<Outline>::Callback(this, &StackContainer::Element_MarginChanged);
}
void StackContainer::Add(Control* control)
{
    Container::Add(control);
    elements.Add(control);

    Refresh(control);

    control->SizeChanged += ChangeEvent<Point>::Callback(this, &StackContainer::Element_SizeChanged);
    control->PositionChanged += ChangeEvent<Point>::Callback(this, &StackContainer::Element_PositionChanged);
    control->VisibleChanged += ChangeEvent<bool>::Callback(this, &StackContainer::Element_VisibleChanged);
    control->MarginChanged += ChangeEvent<Outline>::Callback(this, &StackContainer::Element_MarginChanged);
}
void StackContainer::Remove(Container* container)
{
    Container::Remove(container);
    elements.Remove(container);

    container->SizeChanged -= ChangeEvent<Point>::Callback(this, &StackContainer::Element_SizeChanged);
    container->PositionChanged -= ChangeEvent<Point>::Callback(this, &StackContainer::Element_PositionChanged);
    container->VisibleChanged -= ChangeEvent<bool>::Callback(this, &StackContainer::Element_VisibleChanged);
    container->MarginChanged -= ChangeEvent<Outline>::Callback(this, &StackContainer::Element_MarginChanged);

    Refresh();
}
void StackContainer::Remove(Control* control)
{
    Container::Remove(control);
    elements.Remove(control);

    control->SizeChanged -= ChangeEvent<Point>::Callback(this, &StackContainer::Element_SizeChanged);
    control->PositionChanged -= ChangeEvent<Point>::Callback(this, &StackContainer::Element_PositionChanged);
    control->VisibleChanged -= ChangeEvent<bool>::Callback(this, &StackContainer::Element_VisibleChanged);
    control->MarginChanged -= ChangeEvent<Outline>::Callback(this, &StackContainer::Element_MarginChanged);

    Refresh();
}
void StackContainer::Clear()
{
    Container::Clear();
    elements.Clear();

    Refresh();
}

void StackContainer::Refresh(Element* element)
{
    u32 position = 0;
    s32 index = 0;

    if (orientation == Orientation::Horizontal)
        position = padding.Left;
    else if (orientation == Orientation::Vertical)
        position = padding.Top;

    if (element)
    {
        index = elements.IndexOf(element);
        Exception::Assert(index >= 0, "The specified element is not part of this container");

        if (index > 0)
        {
            Element* element = elements[index - 1];

            if (orientation == Orientation::Horizontal)
                position = element->Position.X + element->Margin.Left + element->Size.X + element->Margin.Right;
            else if (orientation == Orientation::Vertical)
                position = element->Position.Y + element->Margin.Top + element->Size.Y + element->Margin.Bottom;
        }
    }

    for (; index < elements.Count; index++)
    {
        Element* element = elements[index];
        if (!element->Visible)
            continue;

        if (orientation == Orientation::Horizontal)
        {
            position += element->Margin.Left;
            element->Position = Point(position, padding.Top + element->Margin.Top);
            position += element->Size.X + element->Margin.Right;
        }
        else if (orientation == Orientation::Vertical)
        {
            position += element->Margin.Top;
            element->Position = Point(padding.Left + element->Margin.Left, position);
            position += element->Size.Y + element->Margin.Bottom;
        }
    }

    if (autoSize)
    {
        if (orientation == Orientation::Horizontal && !Flag::Test(dock, DockStyle::LeftRight))
            Size = Point(position + padding.Right, size.Y);
        else if (orientation == Orientation::Vertical && !Flag::Test(dock, DockStyle::TopBottom))
            Size = Point(size.X, position + padding.Bottom);
    }

    Refreshed(this, Rectangle(this->position, size));
}

void StackContainer::Element_SizeChanged(void* element, ChangeEventParameter<Point> parameter)
{
    Refresh((Element*)element);
}
void StackContainer::Element_PositionChanged(void* element, ChangeEventParameter<Point> parameter)
{
    Refresh((Element*)element);
}
void StackContainer::Element_VisibleChanged(void* element, ChangeEventParameter<bool> parameter)
{
    Refresh((Element*)element);
}
void StackContainer::Element_MarginChanged(void* element, ChangeEventParameter<Outline> parameter)
{
    //Serial::WriteLine("StackContainer::Element_MarginChanged");
    Refresh((Element*)element);
}