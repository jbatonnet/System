#ifndef _SYSTEM_BUTTONSDEVICE_H_
#define _SYSTEM_BUTTONSDEVICE_H_

#include <System/Devices/Device.h>

namespace System
{
    namespace Devices
    {   
        enum class Buttons : u16
        {
            Unknown,

            // Characters
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Digit0, Digit1, Digit2, Digit3, Digit4, Digit5, Digit6, Digit7, Digit8, Digit9,

            // Modifiers
            CapsLock, NumLock,
            Shift, LeftShift, RightShift,
            Control, LeftControl, RightControl,
            Alt, LeftAlt, RightAlt,

            // Control
            Escape, Space, Enter, Backspace, Start, Select, Menu, Tab,

            // Moves
            Up, Right, Down, Left,
            Insert, Delete, PageUp, PageDown, Origin, End,

            // Others
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

            // Oem
            Oem1, Oem2, Oem3,                // ² ) =
            Oem4, Oem5,                      // ^ $
            Oem6, Oem7,                      // ù *
            Oem8, Oem9, Oem10, Oem11, Oem12, // < , ; : !

            Count
        };
        struct RawButtonEvent
        {
            Buttons Button;
        };
        struct ButtonEvent
        {
            Buttons Button;
            char Character;
        };

        struct ButtonsMapping
        {
        private:
            Buttons map[0xFF];

        public:
            ButtonsMapping()
            {
                Memory::Clear<Buttons>(map, 0xFF);
            }
            Buttons& operator[](u8 code)
            {
                return map[code];
            }
        };
        struct CharactersMapping
        {
        private:
            char map[(u32)Buttons::Count];

        public:
            CharactersMapping()
            {
                Memory::Clear(map, (u16)Buttons::Count);
            }
            char& operator[](Buttons button)
            {
                return map[(u16)button];
            }
        };
        struct ButtonsState
        {
        private:
            bool state[(u32)Buttons::Count];

        public:
            ButtonsState()
            {
                Memory::Clear<bool>(state, false);
            }
            bool& operator[](Buttons button)
            {
                return state[(u16)button];
            }
        };

        class ButtonsDevice : public Device
        {
        protected:
            ButtonsMapping buttonsMapping;

        public:
            Event<RawButtonEvent> ButtonDown, ButtonUp;
        };
    }
}

#endif