#ifndef _SYSTEM_MOVER_H_
#define _SYSTEM_MOVER_H_

#include <System/Interface/Containers/Container.h>

namespace System
{
    namespace Interface
    {
        class Window;

        class Mover : public Container
        {
        private:
            Window* window;

        public:
            Mover(Window* window);

            virtual void OnPointerMove(void* origin, Devices::PointerPositionEvent pointerPositionEvent) override;
            virtual void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent) override;
        };
    }
}

#endif