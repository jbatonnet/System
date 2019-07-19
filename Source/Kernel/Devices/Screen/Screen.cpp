#include "Screen.h"

#include <CRT/stdarg.h>
#include <HAL/HAL.h>
#include <System/Memory/Memory.h>

u8 CursorX = 0;
u8 CursorY = 0;

union ScreenCharacter
{
    struct
    {
        char Character;
        u8 Attributes;
    };
    u16 Value;
};
ScreenCharacter* Screen = (ScreenCharacter*)0x0B8000;

void SetCursorPosition()
{
    u16 cursorPosition = CursorY * 80 + CursorX;
    IO_Write8(0x03D4, 14);
    IO_Write8(0x03D5, cursorPosition >> 8);
    IO_Write8(0x03D4, 15);
    IO_Write8(0x03D5, cursorPosition);
}
void GetCursorPosition()
{
    u16 cursorPosition;

    IO_Write8(0x3D4, 14);
    cursorPosition = IO_Read8(0x3D5) << 8;
    IO_Write8(0x3D4, 15);
    cursorPosition |= IO_Read8(0x3D5);

    CursorX = cursorPosition % 80;
    CursorY = cursorPosition / 80;
}

void Clear()
{
    for (u32 i = 0; i < 80 * 25; i++)
    {
        Screen[i].Character = ' ';
        Screen[i].Attributes = 0x07;
    }
    CursorX = 0;
    CursorY = 0;
    SetCursorPosition();
}

void Write(char value)
{
    GetCursorPosition();
    // TODO: Handle colors

    switch (value)
    {
        case 0:
            break;

        // New line
        case '\n':
            CursorX = 0;
            if (++CursorY == 25)
            {
                Memory::Copy(Screen + 80, Screen, 80 * 24 * 2);
                for (int i = 0; i < 80; i++)
                    Screen[80 * 24 + i].Value = 0x0720;
                CursorY = 24;
            }
            break;

        // Carriage return
        case '\r':
            CursorX = 0;
            break;

        // Backspace
        case '\b':
            if (--CursorX < 0)
            {
                CursorX = 79;
                if (--CursorY < 0)
                    CursorX = CursorY = 0;
            }
            Screen[CursorY * 80 + CursorX].Value = 0x0720;
            break;

        // Tab
        case '\t':
            do
                Write(' ');
            while (CursorX % 4);
            break;

        // Other
        default:
            Screen[CursorY * 80 + CursorX].Character = value;
            if (++CursorX == 80)
            {
                CursorX = 0;
                if (++CursorY == 25)
                {
                    Memory::Copy(Screen + 80, Screen, 80 * 24 * 2);
                    for (int i = 0; i < 80; i++)
                        Screen[80 * 24 + i].Value = 0x0720;
                    CursorY = 24;
                }
            }
            break;
    }

    SetCursorPosition();
}
void Write(u32 value, u8 base, u8 size = 0)
{
    static char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char result[34] = { 0 };
    s8 i;

    if (base < 2 || base > 16)
        return;

    if (!value && size < 2)
        return Write('0');

    for (i = 1; value; i++)
    {
        result[i] = digits[value % base];
        value /= base;
    }

    while (size-- > i - 1)
        Write('0');
    while (result[--i])
        Write(result[i]);
}
void Write(u32 value)
{
    Write(value, 10);
}
void Write(s32 value, u8 base, u8 size = 0)
{
    if (value < 0)
        Write('-');
    Write((u32)(value * (value < 0 ? -1 : 1)), base, size);
}
void Write(s32 value)
{
    Write(value, 10);
}
void Write(void* value)
{
    Write("0x");
    Write((u32)value, 16);
}
void Write(bool value)
{
    Write(value ? "true" : "false");
}
void Write(char* format, ...)
{
    va_list params;
    va_start(params, format);

    while (*format)
    {
        if (*format == '%')
            switch (*++format)
            {
                case 'c': Write(va_arg(params, char)); break;
                case 'd': Write(va_arg(params, s32)); break;
                case 'x': Write(va_arg(params, u32), 16); break;
                case 'b': Write(va_arg(params, u32), 2); break;
                case 's': Write(va_arg(params, char*)); break;
                case '%': format++;
                default: Write('%'); format--;
            }
        else
            Write(*format);
        format++;
    }

    va_end(params);
}