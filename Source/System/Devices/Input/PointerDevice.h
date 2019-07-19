#ifndef _SYSTEM_POINTERDEVICE_H_
#define _SYSTEM_POINTERDEVICE_H_

#include <System/Devices/Device.h>
#include <System/Graphics/Point.h>

namespace System
{
    namespace Devices
    {
        struct PointerEvent
        {
            u8 Index;
        };

        struct PointerPositionEvent : PointerEvent
        {
            u16 X;
            u16 Y;
        };

        struct PointerMoveEvent : PointerEvent
        {
            s8 X;
            s8 Y;
        };

        // TODO: Refactor this into Jauge ?
        struct PointerScrollEvent : PointerEvent
        {
            s16 Delta;
        };

        class PointerDevice : public Device
        {
        public:
            Event<PointerMoveEvent> PointerMove;
            Event<PointerEvent> PointerDown;
            Event<PointerEvent> PointerUp;

            // TODO: Refactor this into Jauge ?
            Event<PointerScrollEvent> PointerScroll;
        };
    }
}

#endif