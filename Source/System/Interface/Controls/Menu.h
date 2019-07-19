#ifndef _SYSTEM_MENU_H_
#define _SYSTEM_MENU_H_

#include <System/Interface/Containers/StackContainer.h>
#include <System/Interface/Controls/Button.h>

namespace System
{
    namespace Interface
    {
        class Menu : public StackContainer
        {
        public:
            class Item : public Button
            {
            public:
                Item(const string& text);
            };

        public:
            Menu();

            void Add(Item* item);
        };
    }
}

#endif
