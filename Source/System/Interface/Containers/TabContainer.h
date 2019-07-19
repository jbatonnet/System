#ifndef _SYSTEM_TABCONTAINER_H_
#define _SYSTEM_TABCONTAINER_H_

#include <System/Interface/Containers/Tab.h>
#include <System/Interface/Containers/StackContainer.h>
#include <System/Interface/Controls/Label.h>
#include <System/Interface/Controls/Button.h>
#include <System/Devices/Input/PointerDevice.h>

namespace System
{
    namespace Interface
    {
        class TabContainer : public Container
        {
            struct TabVisuals
            {
                Container *Back;
                Container *Left, *Right, *Bottom;
                Label *Title;
            };

        protected:
            StackContainer* header;
            Dictionary<Tab*, Button*> tabs;
            Graphics::Orientation orientation;

            s32 currentIndex;
            Tab* currentTab;

            void Tab_PointerDown(void* origin, Devices::PointerEvent e);

        public:
            TabContainer();

            // Accessors
            Tab* GetCurrentTab() const { return currentTab; }
            virtual void SetCurrentTab(Tab* value);
            _declspec(property(get = GetCurrentTab, put = SetCurrentTab)) Tab* CurrentTab;
            Graphics::Orientation GetOrientation() const { return orientation; }
            virtual Graphics::Orientation SetOrientation(Graphics::Orientation value);
            _declspec(property(get = GetOrientation, put = SetOrientation)) Graphics::Orientation Orientation;

            // Methods
            virtual void Add(Tab* tab);
            virtual void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
        };
    }
}

#endif