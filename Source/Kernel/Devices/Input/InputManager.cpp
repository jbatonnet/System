#include <System/Devices/Input/InputManager.h>
#include <System/Structures/Collections/List.h>
#include <System/Maths/Maths.h>

#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>

using namespace System::Devices;
using namespace System::Graphics;

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

List<PointerDevice*> InputManager::pointers;
PointerDevice* InputManager::defaultPointer = null;
Point2 InputManager::PointerPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

List<ButtonsDevice*> InputManager::buttons;
CharactersMapping InputManager::charactersMappingNormal, InputManager::charactersMappingShift, InputManager::charactersMappingAlt;
ButtonsState InputManager::buttonsState;

Event<PointerPositionEvent> InputManager::PointerMove;
Event<PointerEvent> InputManager::PointerDown, InputManager::PointerUp;
Event<ButtonEvent> InputManager::ButtonDown, InputManager::ButtonUp;
Event<JaugeEvent> InputManager::JaugeChange;

void InputManager::Initialize()
{
    // Normal
    charactersMappingNormal[Buttons::Oem1] = '²';

    charactersMappingNormal[Buttons::Digit1] = '&';
    charactersMappingNormal[Buttons::Digit2] = 'é';
    charactersMappingNormal[Buttons::Digit3] = '"';
    charactersMappingNormal[Buttons::Digit4] = '\'';
    charactersMappingNormal[Buttons::Digit5] = '(';
    charactersMappingNormal[Buttons::Digit6] = '-';
    charactersMappingNormal[Buttons::Digit7] = 'è';
    charactersMappingNormal[Buttons::Digit8] = '_';
    charactersMappingNormal[Buttons::Digit9] = 'ç';
    charactersMappingNormal[Buttons::Digit0] = 'à';

    charactersMappingNormal[Buttons::Oem2] = ')';
    charactersMappingNormal[Buttons::Oem3] = '=';

    charactersMappingNormal[Buttons::A] = 'a';
    charactersMappingNormal[Buttons::Z] = 'z';
    charactersMappingNormal[Buttons::E] = 'e';
    charactersMappingNormal[Buttons::R] = 'r';
    charactersMappingNormal[Buttons::T] = 't';
    charactersMappingNormal[Buttons::Y] = 'y';
    charactersMappingNormal[Buttons::U] = 'u';
    charactersMappingNormal[Buttons::I] = 'i';
    charactersMappingNormal[Buttons::O] = 'o';
    charactersMappingNormal[Buttons::P] = 'p';

    charactersMappingNormal[Buttons::Oem4] = '^';
    charactersMappingNormal[Buttons::Oem5] = '$';

    charactersMappingNormal[Buttons::Q] = 'q';
    charactersMappingNormal[Buttons::S] = 's';
    charactersMappingNormal[Buttons::D] = 'd';
    charactersMappingNormal[Buttons::F] = 'f';
    charactersMappingNormal[Buttons::G] = 'g';
    charactersMappingNormal[Buttons::H] = 'h';
    charactersMappingNormal[Buttons::J] = 'j';
    charactersMappingNormal[Buttons::K] = 'k';
    charactersMappingNormal[Buttons::L] = 'l';
    charactersMappingNormal[Buttons::M] = 'm';

    charactersMappingNormal[Buttons::Oem6] = 'ù';
    charactersMappingNormal[Buttons::Oem7] = '*';

    charactersMappingNormal[Buttons::Oem8] = '<';

    charactersMappingNormal[Buttons::W] = 'w';
    charactersMappingNormal[Buttons::X] = 'x';
    charactersMappingNormal[Buttons::C] = 'c';
    charactersMappingNormal[Buttons::V] = 'v';
    charactersMappingNormal[Buttons::B] = 'b';
    charactersMappingNormal[Buttons::N] = 'n';
    
    charactersMappingNormal[Buttons::Oem8] = '<';
    charactersMappingNormal[Buttons::Oem9] = ',';
    charactersMappingNormal[Buttons::Oem10] = ';';
    charactersMappingNormal[Buttons::Oem11] = ':';
    charactersMappingNormal[Buttons::Oem12] = '!';

    charactersMappingNormal[Buttons::Space] = ' ';
    charactersMappingNormal[Buttons::Enter] = '\n';
    charactersMappingNormal[Buttons::Backspace] = '\b';

    // Shift
    charactersMappingShift[Buttons::Oem1] = '³';

    charactersMappingShift[Buttons::Digit1] = '1';
    charactersMappingShift[Buttons::Digit2] = '2';
    charactersMappingShift[Buttons::Digit3] = '3';
    charactersMappingShift[Buttons::Digit4] = '4';
    charactersMappingShift[Buttons::Digit5] = '5';
    charactersMappingShift[Buttons::Digit6] = '6';
    charactersMappingShift[Buttons::Digit7] = '7';
    charactersMappingShift[Buttons::Digit8] = '8';
    charactersMappingShift[Buttons::Digit9] = '9';
    charactersMappingShift[Buttons::Digit0] = '0';

    charactersMappingShift[Buttons::Oem2] = '°';
    charactersMappingShift[Buttons::Oem3] = '+';

    charactersMappingShift[Buttons::A] = 'A';
    charactersMappingShift[Buttons::Z] = 'Z';
    charactersMappingShift[Buttons::E] = 'E';
    charactersMappingShift[Buttons::R] = 'R';
    charactersMappingShift[Buttons::T] = 'T';
    charactersMappingShift[Buttons::Y] = 'Y';
    charactersMappingShift[Buttons::U] = 'U';
    charactersMappingShift[Buttons::I] = 'I';
    charactersMappingShift[Buttons::O] = 'O';
    charactersMappingShift[Buttons::P] = 'P';

    charactersMappingShift[Buttons::Oem4] = '¨';
    charactersMappingShift[Buttons::Oem5] = '£';

    charactersMappingShift[Buttons::Q] = 'Q';
    charactersMappingShift[Buttons::S] = 'S';
    charactersMappingShift[Buttons::D] = 'D';
    charactersMappingShift[Buttons::F] = 'F';
    charactersMappingShift[Buttons::G] = 'G';
    charactersMappingShift[Buttons::H] = 'H';
    charactersMappingShift[Buttons::J] = 'J';
    charactersMappingShift[Buttons::K] = 'K';
    charactersMappingShift[Buttons::L] = 'L';
    charactersMappingShift[Buttons::M] = 'M';

    charactersMappingShift[Buttons::Oem6] = '%';
    charactersMappingShift[Buttons::Oem7] = 'µ';

    charactersMappingShift[Buttons::Oem8] = '>';

    charactersMappingShift[Buttons::W] = 'W';
    charactersMappingShift[Buttons::X] = 'X';
    charactersMappingShift[Buttons::C] = 'C';
    charactersMappingShift[Buttons::V] = 'V';
    charactersMappingShift[Buttons::B] = 'B';
    charactersMappingShift[Buttons::N] = 'N';
    
    charactersMappingShift[Buttons::Oem8] = '>';
    charactersMappingShift[Buttons::Oem9] = '?';
    charactersMappingShift[Buttons::Oem10] = '.';
    charactersMappingShift[Buttons::Oem11] = '/';
    charactersMappingShift[Buttons::Oem12] = '§';

    charactersMappingShift[Buttons::Space] = ' ';

    // Alt
    charactersMappingAlt[Buttons::Digit2] = '~';
    charactersMappingAlt[Buttons::Digit3] = '#';
    charactersMappingAlt[Buttons::Digit4] = '{';
    charactersMappingAlt[Buttons::Digit5] = '[';
    charactersMappingAlt[Buttons::Digit6] = '|';
    charactersMappingAlt[Buttons::Digit7] = '`';
    charactersMappingAlt[Buttons::Digit8] = '\\';
    charactersMappingAlt[Buttons::Digit9] = '^';
    charactersMappingAlt[Buttons::Digit0] = '@';

    charactersMappingAlt[Buttons::Oem2] = ']';
    charactersMappingAlt[Buttons::Oem3] = '}';

    charactersMappingAlt[Buttons::E] = '€';

    charactersMappingAlt[Buttons::Oem5] = '¤';

    charactersMappingAlt[Buttons::Oem6] = '%';
    charactersMappingAlt[Buttons::Oem7] = 'µ';

    charactersMappingAlt[Buttons::Oem8] = '>';
}

// Pointer
u8 pointerModifier[6] = { 0, 1, 1, 3, 6, 9 };
void DefaultPointer_PointerMove(void* origin, PointerMoveEvent e)
{
    u8 x = Maths::Abs(e.X), y = Maths::Abs(e.Y);
    e.X = (e.X < 0 ? -1 : 1) * (x > 5 ? x * 2 : pointerModifier[x]);
    e.Y = (e.Y < 0 ? -1 : 1) * (y > 5 ? y * 2 : pointerModifier[y]);

    u16 pointerX = InputManager::PointerPosition.X = Maths::Clamp(InputManager::PointerPosition.X + e.X, 0, SCREEN_WIDTH - 1);
    u16 pointerY = InputManager::PointerPosition.Y = Maths::Clamp(InputManager::PointerPosition.Y - e.Y, 0, SCREEN_HEIGHT - 1);

    /*_asm
    {
        mov eax, 0x564D5868
        mov cx, 0x0004
        mov dx, 0x5658
        
        in eax, dx

        mov [pointerY], bx
        shr ebx, 16
        mov [pointerX], bx
    }*/

    //InputManager::PointerPosition.X = InputManager::PointerPosition.X = Maths::Clamp<u16>(pointerX, 0, SCREEN_WIDTH - 1);
    //InputManager::PointerPosition.Y = InputManager::PointerPosition.Y = Maths::Clamp<u16>(pointerY, 0, SCREEN_HEIGHT - 1);

    PointerPositionEvent ppe;
    ppe.Index = e.Index;
    ppe.X = InputManager::PointerPosition.X;
    ppe.Y = InputManager::PointerPosition.Y;

    //Serial::WriteLine("InputManager::PointerMove() : { X: {0}, Y: {1} }", InputManager::PointerPosition.X, InputManager::PointerPosition.Y);

    InputManager::PointerMove(origin, ppe);
}
void DefaultPointer_PointerDown(void* origin, PointerEvent e)
{
    InputManager::PointerDown(origin, e);
}
void DefaultPointer_PointerUp(void* origin, PointerEvent e)
{
    InputManager::PointerUp(origin, e);
}
void InputManager::AddDevice(PointerDevice* pointer, bool default)
{
    pointers.Add(pointer);

    if (default || !defaultPointer)
    {
        if (defaultPointer)
        {
            defaultPointer->PointerMove -= DefaultPointer_PointerMove;
            defaultPointer->PointerDown -= DefaultPointer_PointerDown;
            defaultPointer->PointerUp -= DefaultPointer_PointerUp;
        }

        defaultPointer = pointer;

        defaultPointer->PointerMove += DefaultPointer_PointerMove;
        defaultPointer->PointerDown += DefaultPointer_PointerDown;
        defaultPointer->PointerUp += DefaultPointer_PointerUp;
    }
}

// Buttons
void InputManager::ButtonsDevice_ButtonDown(void* origin, RawButtonEvent e)
{
    static bool numLock = false;
    static bool capsLock = false;

    InputManager::buttonsState[e.Button] = true;

    // Modifiers switches
    if (e.Button == Buttons::NumLock) numLock = !numLock;
    if (e.Button == Buttons::CapsLock) capsLock = !capsLock;

    // Combined buttons
    buttonsState[Buttons::Shift] = buttonsState[Buttons::LeftShift] || buttonsState[Buttons::RightShift];
    buttonsState[Buttons::Control] = buttonsState[Buttons::LeftControl] || buttonsState[Buttons::RightControl];
    buttonsState[Buttons::Alt] = buttonsState[Buttons::LeftAlt] || buttonsState[Buttons::RightAlt];

    // Character mapping
    char character = charactersMappingNormal[e.Button];
    if (buttonsState[Buttons::Shift] || capsLock)
    {
        char characterShift = charactersMappingShift[e.Button];
        if (characterShift)
            character = characterShift;
    }
    if (buttonsState[Buttons::Alt])
    {
        char characterAlt = charactersMappingAlt[e.Button];
        if (characterAlt)
            character = characterAlt;
    }

    // Dispatch event
    ButtonEvent be;
    be.Button = e.Button;
    be.Character = character;
    ButtonDown(origin, be);
}
void InputManager::ButtonsDevice_ButtonUp(void* origin, RawButtonEvent e)
{
    InputManager::buttonsState[e.Button] = false;

    // Combined buttons
    buttonsState[Buttons::Shift] = buttonsState[Buttons::LeftShift] || buttonsState[Buttons::RightShift];
    buttonsState[Buttons::Control] = buttonsState[Buttons::LeftControl] || buttonsState[Buttons::RightControl];
    buttonsState[Buttons::Alt] = buttonsState[Buttons::LeftAlt] || buttonsState[Buttons::RightAlt];

    // Character mapping
    char character = charactersMappingNormal[e.Button];
    if (buttonsState[Buttons::Shift])
    {
        char characterShift = charactersMappingShift[e.Button];
        if (characterShift)
            character = characterShift;
    }
    if (buttonsState[Buttons::Alt])
    {
        char characterAlt = charactersMappingAlt[e.Button];
        if (characterAlt)
            character = characterAlt;
    }

    //Console::WriteLine("InputManager::ButtonUp() : {0}", character);

    // Dispatch event
    ButtonEvent be;
    be.Button = e.Button;
    be.Character = character;
    ButtonUp(origin, be);
}
void InputManager::AddDevice(ButtonsDevice* buttonDevice)
{
    buttons.Add(buttonDevice);

    buttonDevice->ButtonDown += InputManager::ButtonsDevice_ButtonDown;
    buttonDevice->ButtonUp += InputManager::ButtonsDevice_ButtonUp;
}