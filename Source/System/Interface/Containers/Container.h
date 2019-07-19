#ifndef _SYSTEM_CONTAINER_H_
#define _SYSTEM_CONTAINER_H_

#include <System/Graphics/Point.h>
#include <System/Interface/Element.h>
#include <System/Interface/Controls/Control.h>
#include <System/Structures/Collections/ObservableList.h>

namespace System
{
    namespace Interface
    {
        class Container : public Element
        {
        protected:
            List<Container*> containers;
            List<Control*> controls;
            Graphics::Outline border;
            Color32 borderColor;

        public: // FIXME
            virtual void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent) override;
            virtual void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerScroll(void* origin, Devices::PointerScrollEvent pointerScrollEvent) override;

            virtual void OnButtonDown(void* origin, Devices::ButtonEvent buttonEvent) override;
            virtual void OnButtonUp(void* origin, Devices::ButtonEvent buttonEvent) override;

            void Container_Refreshed(void* container, Graphics::Rectangle rectangle);
            void Control_Redrawn(void* control, Graphics::Rectangle rectangle);

        public:
            Container() : borderColor(0)
            {
                BackColor = Colors::Transparent;
            }

            // Accessors
            ChangeEvent<Graphics::Outline> BorderChanged;
            Graphics::Outline GetBorder() const { return border; }
            virtual Graphics::Outline& SetBorder(Graphics::Outline& value) { if (border == value) return border; BorderChanged(this, border, value); return border = value; }
            _declspec(property(get = GetBorder, put = SetBorder)) Graphics::Outline Border;

            _declspec(property(get = GetBorderColor, put = SetBorderColor)) Color32 BorderColor;
            Color32 GetBorderColor() const { return borderColor; }
            virtual void SetBorderColor(Color32 value);

            Pointer<Collection<Container*>> GetContainers() { return containers; }
            _declspec(property(get = GetContainers)) Pointer<Collection<Container*>> Containers;

            Pointer<Collection<Control*>> GetControls() { return controls; }
            _declspec(property(get = GetControls)) Pointer<Collection<Control*>> Controls;

            virtual void SetSize(Graphics::Point value);
            virtual void SetBackColor(Color32 value);

            // Events
            Event<Graphics::Rectangle> Refreshed;

            // Methods
            virtual void Add(Container* container);
            virtual void Add(Control* control);
            virtual void Remove(Container* container);
            virtual void Remove(Control* control);
            virtual void Clear();

            virtual void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
        };
    }
}

#endif