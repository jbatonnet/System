#ifndef _SYSTEM_INPUTMANAGER_H_
#define _SYSTEM_INPUTMANAGER_H_

#include <System/Common.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>

namespace System
{
    namespace IO
    {
        class BufferStream;
        class TextStream;
    }

    namespace Devices
    {
        enum class Jauges : u8
        {
            LeftStickX, LeftStickY,
            RightStickX, RightStickY,
            LeftTrigger, RightTrigger
        };
        struct JaugeEvent
        {
            Jauges Jauge;
            float Value;
        };

        class InputManager
        {
            friend class Device;

        private:
            InputManager();

            static List<PointerDevice*> pointers;
            static PointerDevice* defaultPointer;

            static List<ButtonsDevice*> buttons;
            static CharactersMapping charactersMappingNormal, charactersMappingShift, charactersMappingAlt;
            static ButtonsState buttonsState;

            static IO::BufferStream* buttonsBuffer;
            static IO::TextStream* buttonsStream;

            static void ButtonsDevice_ButtonDown(void* origin, RawButtonEvent e);
            static void ButtonsDevice_ButtonUp(void* origin, RawButtonEvent e);

        public:
            static void Initialize();

            // Pointers
            static void AddDevice(PointerDevice* pointer, bool default = false);
            static void SetDefaultPointer(PointerDevice* pointer);
            static Event<PointerPositionEvent> PointerMove;
            static Event<PointerEvent> PointerDown, PointerUp;
            static Point2 PointerPosition;

            // Keyboards
            static void AddDevice(ButtonsDevice* button);
            static Event<ButtonEvent> ButtonDown, ButtonUp;
            static bool IsButtonDown(Buttons button);

            // Other
            static Event<JaugeEvent> JaugeChange;
        };
    }
}

#endif