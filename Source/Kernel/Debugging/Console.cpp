#include <System/Debugging/Console.h>
#include <Kernel/Memory/Memory.h>
#include <HAL/IO.h>
#include <System/Devices/Input/InputManager.h>

using namespace System::IO;
using namespace System::Devices;

class DefaultConsoleStream : public ConsoleStream
{
public:
    u32 Read(void* buffer, u32 count, bool intercept);
    void Write(void* buffer, u32 count);
};

ConsoleStream* Console::BaseConsoleStream = new DefaultConsoleStream();
TextStream* Console::BaseStream = new TextStream(Console::BaseConsoleStream);

u16 cursorX = 0;
u16 cursorY = 7;

union ScreenCharacter
{
    struct
    {
        char Character;
        u8 Attributes;
    };
    u16 Value;
};
ScreenCharacter* screen = (ScreenCharacter*)0x0B8000;

void Console_SetCursorPosition()
{
    u16 cursorPosition = cursorY * 80 + cursorX;

    IO_Write8(0x03D4, 14);
    IO_Write8(0x03D5, (u8)(cursorPosition >> 8));
    IO_Write8(0x03D4, 15);
    IO_Write8(0x03D5, (u8)cursorPosition);
}
void Console_GetCursorPosition()
{
    u16 cursorPosition;

    IO_Write8(0x3D4, 14);
    cursorPosition = (u16)IO_Read8(0x3D5) << 8;
    IO_Write8(0x3D4, 15);
    cursorPosition |= (u16)IO_Read8(0x3D5);

    cursorX = cursorPosition % 80;
    cursorY = cursorPosition / 80;
}

char lastCharacter = 0;
bool initialized = false;

void ConsoleStream_ButtonDown(void* origin, ButtonEvent buttonEvent)
{
    lastCharacter = buttonEvent.Character;
}

u32 DefaultConsoleStream::Read(void* buffer, u32 count, bool intercept)
{
    if (!initialized)
    {
        InputManager::ButtonDown += ConsoleStream_ButtonDown;
        initialized = true;
    }

    char* bufferBytes = (char*)buffer;

    for (u32 i = 0; i < count; i++)
    {
        while (!lastCharacter)
            ;//_asm hlt

        if (!intercept)
            Write(&lastCharacter, 1);

        bufferBytes[i] = lastCharacter;
        lastCharacter = 0;
    }

    return count;
}
void DefaultConsoleStream::Write(void* buffer, u32 count)
{
    Console_GetCursorPosition();

    for (u32 i = 0; i < count; i++)
    {
        char value = ((char*)buffer)[i];

        switch (value)
        {
            case 'â': value = (char)0x83; break;
            case 'ä': value = (char)0x84; break;
            case 'à': value = (char)0x85; break;

            case 'é': value = (char)0x82; break;
            case 'ê': value = (char)0x88; break;
            case 'ë': value = (char)0x89; break;
            case 'è': value = (char)0x8A; break;

            case 'ï': value = (char)0x8B; break;
            case 'î': value = (char)0x8C; break;

            case 'ô': value = (char)0x93; break;
            case 'ö': value = (char)0x94; break;

            case 'û': value = (char)0x96; break;
            case 'ü': value = (char)0x81; break;
        }

        switch (value)
        {
            case 0:
                break;

            // New line
            case '\n':
                cursorX = 0;
                if (++cursorY == 25)
                {
                    Memory::Copy(screen + 80, screen, 80 * 24 * 2);

                    for (int j = 0; j < 80; j++)
                    {
                        screen[80 * 24 + j].Character = ' ';
                        screen[80 * 24 + j].Attributes = ((u8)Console::BackColor & 0xF) << 4 | ((u8)Console::Color & 0xF);
                    }

                    cursorY = 24;
                }
                break;

            // Carriage return
            case '\r':
                cursorX = 0;
                break;

            // Backspace
            case '\b':
                if (--cursorX < 0)
                {
                    cursorX = 79;
                    if (--cursorY < 0)
                        cursorX = cursorY = 0;
                }

                screen[cursorY * 80 + cursorX].Character = ' ';
                screen[cursorY * 80 + cursorX].Attributes = ((u8)Console::BackColor & 0xF) << 4 | ((u8)Console::Color & 0xF);

                break;

            // Tab
            case '\t':
                do
                    Write(" ", 1);
                while (cursorX % 4);
                break;

            // Other
            default:
                screen[cursorY * 80 + cursorX].Character = value;
                screen[cursorY * 80 + cursorX].Attributes = ((u8)Console::BackColor & 0xF) << 4 | ((u8)Console::Color & 0xF);

                if (++cursorX == 80)
                {
                    cursorX = 0;
                    if (++cursorY == 25)
                    {
                        Memory::Copy(screen + 80, screen, 80 * 24 * 2);

                        for (int j = 0; j < 80; j++)
                        {
                            screen[80 * 24 + j].Character = ' ';
                            screen[80 * 24 + j].Attributes = ((u8)Console::BackColor & 0xF) << 4 | ((u8)Console::Color & 0xF);
                        }

                        cursorY = 24;
                    }
                }
                break;
        }
    }

    Console_SetCursorPosition();
}

ConsoleColor Console::Color = ConsoleColor::Gray;
ConsoleColor Console::BackColor = ConsoleColor::Black;

void Console::Clear()
{
    for (u32 i = 0; i < 80 * 25; i++)
    {
        screen[i].Character = ' ';
        screen[i].Attributes = 0x07;
    }

    cursorX = 0;
    cursorY = 0;
    Console_SetCursorPosition();
}