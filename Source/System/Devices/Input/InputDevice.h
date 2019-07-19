#ifndef _SYSTEM_INPUTDEVICE_H_
#define _SYSTEM_INPUTDEVICE_H_

#include <System/Devices/Device.h>

namespace System
{
    namespace Devices
    {
        enum class InputType : u8
        {
            Button,  // Down, Up
            Pointer, // Move
            Stick,   // Change
        };

        enum class InputDeviceType : u8
        {
            Keyboard,
            Mouse,
            Touch,
            Pad,
        };

        class InputDevice : public Device
        {
        };
    }
}

#endif