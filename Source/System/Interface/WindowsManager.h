#ifndef _SYSTEM_WINDOWSMANAGER_H_
#define _SYSTEM_WINDOWSMANAGER_H_

#include <System/Common.h>
#include <System/Interface/Window.h>

namespace System
{
    namespace Interface
    {
        class WindowsManager : public Object
        {
        public:
            static void Initialize();

            static void Add(Window* window);
            static void Remove(Window* window);
        };
    }
}

#endif