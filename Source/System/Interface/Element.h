#ifndef _SYSTEM_ELEMENT_H_
#define _SYSTEM_ELEMENT_H_

#include <System/Common.h>
#include <System/Graphics/Point.h>
#include <System/Graphics/Colors.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>

#include <System/Debugging/Serial.h>

namespace System
{
    namespace Interface
    {
        enum class DockStyle : u8
        {
            None   = 0x00,

            Left   = 0x11,
            Right  = 0x22,
            Top    = 0x44,
            Bottom = 0x88,

            TopLeft = Top | Left,
            TopRight = Top | Right,
            BottomLeft = Bottom | Left,
            BottomRight = Bottom | Right,

            LeftFull = Left | Top | Bottom,
            RightFull = Right | Top | Bottom,
            TopFull = Top | Left | Right,
            BottomFull = Bottom | Left | Right,

            LeftRight = Left | Right,
            TopBottom = Top | Bottom,
            
            Full = Left | Right | Top | Bottom
        };

        class Element : public Object
        {
            friend class WindowsManager;
            friend class Container;

        protected:
            DockStyle dock;
            Graphics::Point position, size;
            Color32 backColor;
            bool enabled, visible;
            Graphics::Outline margin;
            void* tag;

            virtual void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent) { PointerMove(origin, pointerPositionEvent); }
            virtual void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent) { PointerIn(origin, pointerEvent); }
            virtual void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent) { PointerOut(origin, pointerEvent); }
            virtual void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent) { PointerDown(origin, pointerEvent); }
            virtual void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent) { PointerUp(origin, pointerEvent); }
            virtual void OnPointerScroll(void* origin, Devices::PointerScrollEvent pointerScrollEvent) { PointerScroll(origin, pointerScrollEvent); }

            virtual void OnButtonDown(void* origin, Devices::ButtonEvent buttonEvent) { ButtonDown(origin, buttonEvent); }
            virtual void OnButtonUp(void* origin, Devices::ButtonEvent buttonEvent) { ButtonUp(origin, buttonEvent); }

        public:
            bool pointed;

            Element() : enabled(true), visible(true), backColor(Colors::White), dock(DockStyle::None) { }
            //Element(Element&& element) = delete;
            virtual ~Element() { }

            // Accessors
            ChangeEvent<Graphics::Point> PositionChanged;
            Graphics::Point& GetPosition() { return position; }
            virtual void SetPosition(Graphics::Point value) { if (position == value) return; Maths::Swap(position, value); PositionChanged(this, value, position); }
            _declspec(property(get = GetPosition, put = SetPosition)) Graphics::Point Position;

            ChangeEvent<Graphics::Point> SizeChanged;
            Graphics::Point& GetSize() { return size; }
            virtual void SetSize(Graphics::Point value) { if (size == value) return; Maths::Swap(size, value); SizeChanged(this, value, size); }
            _declspec(property(get = GetSize, put = SetSize)) Graphics::Point Size;

            ChangeEvent<bool> EnabledChanged;
            bool GetEnabled() { return enabled; }
            virtual void SetEnabled(bool value) { if (enabled == value) return; Maths::Swap(enabled, value); EnabledChanged(this, value, enabled); }
            _declspec(property(get = GetEnabled, put = SetEnabled)) bool Enabled;

            ChangeEvent<bool> VisibleChanged;
            bool GetVisible() { return visible; }
            virtual void SetVisible(bool value) { if (visible == value) return; Maths::Swap(visible, value); VisibleChanged(this, value, visible); }
            _declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

            ChangeEvent<Color32> BackColorChanged;
            Color32& GetBackColor() { return backColor; }
            virtual void SetBackColor(Color32 value) { if (backColor == value) return; Maths::Swap(backColor, value); BackColorChanged(this, value, backColor); }
            _declspec(property(get = GetBackColor, put = SetBackColor)) Color32 BackColor;

            ChangeEvent<DockStyle> DockChanged;
            DockStyle GetDock() { return dock; }
            virtual void SetDock(DockStyle value) { if (dock == value) return; Maths::Swap(dock, value); DockChanged(this, value, dock); }
            _declspec(property(get = GetDock, put = SetDock)) DockStyle Dock;

            ChangeEvent<Graphics::Outline> MarginChanged;
            Graphics::Outline GetMargin() { return margin; }
            virtual void SetMargin(Graphics::Outline value) { if (margin == value) return; Maths::Swap(margin, value); MarginChanged(this, value, margin); }
            _declspec(property(get = GetMargin, put = SetMargin)) Graphics::Outline Margin;

            void* GetTag() { return tag; }
            virtual void SetTag(void* value) { tag = value; }
            _declspec(property(get = GetTag, put = SetTag)) void* Tag;

            // Events
            Event<Devices::PointerPositionEvent> PointerMove;
            Event<Devices::PointerScrollEvent> PointerScroll;
            Event<Devices::PointerEvent> PointerIn, PointerOut, PointerDown, PointerUp;
            Event<Devices::ButtonEvent> ButtonDown, ButtonUp;
        };
    }
}

#endif