#ifndef _SYSTEM_SCROLLCONTAINER_H_
#define _SYSTEM_SCROLLCONTAINER_H_

#include <System/Interface/Containers/Container.h>

namespace System
{
    namespace Interface
    {
        class ScrollContainer : public Container
        {
        private:
            Point2 view;
            Point2 content;
            //void Buttons_ButtonDown(void* origin, Devices::ButtonEvent e);

        public:
            ScrollContainer();

            virtual void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent) override;
            virtual void OnPointerScroll(void* origin, Devices::PointerScrollEvent pointerScrollEvent) override;
            virtual void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle) override;

            virtual void Add(Container* container) override;
            virtual void Add(Control* control) override;
            virtual void Remove(Container* container) override;
            virtual void Remove(Control* control) override;

        protected:
            virtual void Element_SizeChanged(void* control, ChangeEventParameter<Graphics::Point> parameter);
            virtual void Element_PositionChanged(void* control, ChangeEventParameter<Graphics::Point> parameter);
            virtual void Element_VisibleChanged(void* control, ChangeEventParameter<bool> parameter);

            void RefreshSizes();
        };
    }
}

#endif