#ifndef _KERNEL_KEYBOARD_H_
#define _KERNEL_KEYBOARD_H_

#include <System/Common.h>

#define KBD_ENCODER_PORT    0x60
#define KBD_CONTROLLER_PORT 0x64

#define KBD_STATUS_OUT_BUF  (1 << 0)
#define KBD_STATUS_IN_BUF   (1 << 1)
#define KBD_STATUS_SYSTEM   (1 << 2)
#define KBD_STATUS_CMD_DATA (1 << 3)
#define KBD_STATUS_LOCKED   (1 << 4)
#define KBD_STATUS_AUX_BUF  (1 << 5)
#define KBD_STATUS_TIMEOUT  (1 << 6)
#define KBD_STATUS_PARITY   (1 << 7)

#define KBD_ENCODER_SET_LEDS                  0xED
#define KBD_ENCODER_ECHO                      0xEE
#define KBD_ENCODER_SCANCODE                  0xF0
#define KBD_ENCODER_KDB_ID                    0xF2
#define KBD_ENCODER_AUTOREPEAT                0xF3
#define KBD_ENCODER_ENABLE                    0xF4
#define KBD_ENCODER_RESET_WAIT                0xF5
#define KBD_ENCODER_RESET_SCAN                0xF6
#define KBD_ENCODER_ALL_AUTOREPEAT            0xF7
#define KBD_ENCODER_ALL_MAKE_BREAK            0xF8
#define KBD_ENCODER_ALL_ONLY_MAKE             0xF9
#define KBD_ENCODER_ALL_AUTOREPEAT_MAKE_BREAK 0xFA
#define KBD_ENCODER_SINGLE_AUTOREPEAT         0xFB
#define KBD_ENCODER_SINGLE_MAKE_BREAK         0xFC
#define KBD_ENCODER_SINGLE_ONLY_BREAK         0xFD
#define KBD_ENCODER_RESEND_LAST               0xFE
#define KBD_ENCODER_RESET_SELFTEST            0xFF

#define KBD_CONTROLLER_READ_CMD       0x20
#define KBD_CONTROLLER_WRITE_CMD      0x60
#define KBD_CONTROLLER_SELFTEST       0xAA
#define KBD_CONTROLLER_INTERFACE_TEST 0xAB
#define KBD_CONTROLLER_DISABLE        0xAD
#define KBD_CONTROLLER_ENABLE         0xAE
#define KBD_CONTROLLER_READ_IN_PORT   0xC0
#define KBD_CONTROLLER_READ_OUT_PORT  0xD0
#define KBD_CONTROLLER_WRITE_OUT_PORT 0xD1
#define KBD_CONTROLLER_READ_TEST_IN   0xE0
#define KBD_CONTROLLER_SYSTEM_RESET   0xFE
#define KBD_CONTROLLER_DISABLE_MOUSE  0xA7
#define KBD_CONTROLLER_ENABLE_MOUSE   0xA8
#define KBD_CONTROLLER_TEST_MOUSE     0xA9
#define KBD_CONTROLLER_WRITE_MOUSE    0xD4

// System key codes
#define KEY_LBUTTON             0x01 // Mouse
#define KEY_RBUTTON             0x02
#define KEY_CANCEL              0x03
#define KEY_MBUTTON             0x04
#define KEY_XBUTTON1            0x05
#define KEY_XBUTTON2            0x06
#define KEY_BACKSPACE           0x08 // Keyboard
#define KEY_TAB                 0x09
#define KEY_CLEAR               0x0C
#define KEY_ENTER               0x0D
#define KEY_SHIFT               0x10
#define KEY_CONTROL             0x11
#define KEY_MENU                0x12
#define KEY_PAUSE               0x13
#define KEY_CAPS                0x14
#define KEY_ESCAPE              0x1B
#define KEY_SPACE               0x20
#define KEY_PRIOR               0x21
#define KEY_NEXT                0x22
#define KEY_END                 0x23
#define KEY_HOME                0x24
#define KEY_LEFT                0x25
#define KEY_UP                  0x26
#define KEY_RIGHT               0x27
#define KEY_DOWN                0x28
#define KEY_SELECT              0x29
#define KEY_PRINT               0x2A
#define KEY_EXECUTE             0x2B
#define KEY_SNAPSHOT            0x2C
#define KEY_INSERT              0x2D
#define KEY_DELETE              0x2E
#define KEY_HELP                0x2F
#define KEY_0                   0x30
#define KEY_1                   0x31
#define KEY_2                   0x32
#define KEY_3                   0x33
#define KEY_4                   0x34
#define KEY_5                   0x35
#define KEY_6                   0x36
#define KEY_7                   0x37
#define KEY_8                   0x38
#define KEY_9                   0x39
#define KEY_SPEC_0				0x3A
#define KEY_SPEC_1				0x3B
#define KEY_SPEC_2				0x3C
#define KEY_SQUARE              0x3F // � (usermade)
#define KEY_A                   0x41
#define KEY_B                   0x42
#define KEY_C                   0x43
#define KEY_D                   0x44
#define KEY_E                   0x45
#define KEY_F                   0x46
#define KEY_G                   0x47
#define KEY_H                   0x48
#define KEY_I                   0x49
#define KEY_J                   0x4A
#define KEY_K                   0x4B
#define KEY_L                   0x4C
#define KEY_M                   0x4D
#define KEY_N                   0x4E
#define KEY_O                   0x4F
#define KEY_P                   0x50
#define KEY_Q                   0x51
#define KEY_R                   0x52
#define KEY_S                   0x53
#define KEY_T                   0x54
#define KEY_U                   0x55
#define KEY_V                   0x56
#define KEY_W                   0x57
#define KEY_X                   0x58
#define KEY_Y                   0x59
#define KEY_Z                   0x5A
#define KEY_LWIN                0x5B
#define KEY_RWIN                0x5C
#define KEY_APPS                0x5D
#define KEY_SLEEP               0x5F
#define KEY_NUMPAD0             0x60
#define KEY_NUMPAD1             0x61
#define KEY_NUMPAD2             0x62
#define KEY_NUMPAD3             0x63
#define KEY_NUMPAD4             0x64
#define KEY_NUMPAD5             0x65
#define KEY_NUMPAD6             0x66
#define KEY_NUMPAD7             0x67
#define KEY_NUMPAD8             0x68
#define KEY_NUMPAD9             0x69
#define KEY_MULTIPLY            0x6A
#define KEY_ADD                 0x6B
#define KEY_SEPARATOR           0x6C
#define KEY_SUBTRACT            0x6D
#define KEY_DECIMAL             0x6E
#define KEY_DIVIDE              0x6F
#define KEY_F1                  0x70
#define KEY_F2                  0x71
#define KEY_F3                  0x72
#define KEY_F4                  0x73
#define KEY_F5                  0x74
#define KEY_F6                  0x75
#define KEY_F7                  0x76
#define KEY_F8                  0x77
#define KEY_F9                  0x78
#define KEY_F10                 0x79
#define KEY_F11                 0x7A
#define KEY_F12                 0x7B
#define KEY_F13                 0x7C
#define KEY_F14                 0x7D
#define KEY_F15                 0x7E
#define KEY_F16                 0x7F
#define KEY_F17                 0x80
#define KEY_F18                 0x81
#define KEY_F19                 0x82
#define KEY_F20                 0x83
#define KEY_F21                 0x84
#define KEY_F22                 0x85
#define KEY_F23                 0x86
#define KEY_F24                 0x87
#define KEY_NUMLOCK             0x90
#define KEY_SCROLL              0x91
#define KEY_LSHIFT              0xA0
#define KEY_RSHIFT              0xA1
#define KEY_LCONTROL            0xA2
#define KEY_RCONTROL            0xA3
#define KEY_LMENU               0xA4
#define KEY_RMENU               0xA5
#define KEY_BROWSER_BACK        0xA6
#define KEY_BROWSER_FORWARD     0xA7
#define KEY_BROWSER_REFRESH     0xA8
#define KEY_BROWSER_STOP        0xA9
#define KEY_BROWSER_SEARCH      0xAA
#define KEY_BROWSER_FAVORITES   0xAB
#define KEY_BROWSER_HOME        0xAC
#define KEY_VOLUME_MUTE         0xAD
#define KEY_VOLUME_DOWN         0xAE
#define KEY_VOLUME_UP           0xAF
#define KEY_MEDIA_NEXT_TRACK    0xB0
#define KEY_MEDIA_PREV_TRACK    0xB1
#define KEY_MEDIA_STOP          0xB2
#define KEY_MEDIA_PLAY_PAUSE    0xB3
#define KEY_LAUNCH_MAIL         0xB4
#define KEY_LAUNCH_MEDIA_SELECT 0xB5
#define KEY_LAUNCH_APP1         0xB6
#define KEY_LAUNCH_APP2         0xB7
#define KEY_OEM_1               0xBA
#define KEY_OEM_PLUS            0xBB
#define KEY_OEM_COMMA           0xBC
#define KEY_OEM_MINUS           0xBD
#define KEY_OEM_PERIOD          0xBE
#define KEY_OEM_2               0xBF
#define KEY_OEM_3               0xC0
#define KEY_OEM_4               0xDB
#define KEY_OEM_5               0xDC
#define KEY_OEM_6               0xDD
#define KEY_OEM_7               0xDE
#define KEY_OEM_8               0xDF
#define KEY_ATTN                0xF6
#define KEY_CRSEL               0xF7
#define KEY_EXSEL               0xF8
#define KEY_EREOF               0xF9
#define KEY_PLAY                0xFA
#define KEY_ZOOM                0xFB
#define KEY_NONAME              0xFC
#define KEY_PA1                 0xFD
#define KEY_OEM_CLEAR           0xFE

#define CONTROLKEY_CTRL		1
#define CONTROLKEY_ALT		2
#define CONTROLKEY_SHIFT	4

union KeyEventArgs
{
    struct
    {
        u8 KeyCode;
        union
        {
            char AsciiChar;
            wchar_t UnicodeChar;
        };
        struct
        {
            bool Control : 1;
            bool Alt     : 1;
            bool Shift   : 1;
        };
    };
    u32 Value;
};

u8 KBD_GetStatus();
u8 KBD_ReadBuffer();

void KDB_Encoder_SendCommand(u8 command);
void KDB_Controller_SendCommand(u8 command);

void KBD_SetLEDs(bool numLock, bool capsLock, bool scrollLock);
bool KBD_SelfTest();

void KBD_Disable();
void KBD_Enable();
void KBD_ResetSystem();

bool KBD_IsKeyPressed(u8 keyCode);
KeyEventArgs KBD_GetLastPressedKey();

void KBD_Install();

extern u8 DefaultScanCodes[];
extern u8 DefaultExtendedScanCodes[];
extern char CharCodesNormal[];
extern char CharCodesShift[];

extern bool keyBuffer[0xFF];
extern KeyEventArgs lastPressedKey;

#endif