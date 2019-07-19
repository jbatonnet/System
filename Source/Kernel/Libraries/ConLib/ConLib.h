#ifndef _CONLIB_H_
#define _CONLIB_H_

#include <HAL/HAL.h>

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include "../../Devices/Drivers/Keyboard/Keyboard.h"

#define ZeroMemory(ptr, num) memset(ptr, 0, num)

typedef struct _COORD {
  short X;
  short Y;
} COORD, *PCOORD;

typedef struct _CHAR_INFO {
  char AsciiChar;
  uint8  Attributes;
} CHAR_INFO, *PCHAR_INFO;

typedef struct _MOUSE_EVENT_RECORD {
  COORD dwMousePosition;
  int dwButtonState;
  int dwControlKeyState;
  int dwEventFlags;
} MOUSE_EVENT_RECORD;

typedef struct _SMALL_RECT {
  short Left;
  short Top;
  short Right;
  short Bottom;
} SMALL_RECT, *PSMALL_RECT;

typedef struct _CONSOLE_CURSOR_INFO {
  int dwSize;
  bool  bVisible;
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;

typedef void FILE;
typedef void* HANDLE;
typedef int time_t;


typedef enum
{
    Fatal,
    Error,
    Warning,
    Info,
} DebugLevel;

typedef enum
{
    Black,
    DarkBlue,
    DarkGreen,
    DarkCyan,
    DarkRed,
    DarkMagenta,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
    Transparent
} ConsoleColor;
#define DefaultColor 7

typedef struct
{
    bool enabled;
    int time;
    int duration;
    COORD shift;
} ShakeEffect;

// Images
typedef struct
{
    int width;
    int height;
    CHAR_INFO* data;
} Buffer;

// Animations
#define ANIM_FULLFRAME 0xFF
#define ANIM_PARTFRAME 0xFE
typedef struct
{
    short width;
    short height;
    FILE* animationFile;
    Buffer* currentFrame;
} Animation, Video;

typedef struct
{
    COORD position;
    bool visible;
    Buffer* buffer;
    Animation* animation;
    ShakeEffect shakeEffect;
} Object;

typedef struct
{
    bool keyState[256];
    int controlKeyState;
} KEYBOARD_DATA;

typedef struct
{
    int state;
    char* text;
    int textLength;
    int attributes;
    short x;
    short y;
    short cursorX;
} TextInput;

extern Buffer* screen;

// Structure builders
COORD Cl_Coord(short X, short Y);
Buffer* Cl_Buffer(short width, short height);
CHAR_INFO Cl_CharInfo(char charCode, int attrColor);

// Colors
int Cl_CreateColor(int foreColor, int backColor);
int Cl_GetDarkerColor(int attrColor);
int Cl_GetLighterColor(int attrColor);
void Cl_SetBufferColor(Buffer* buffer, int attrColor);
int Cl_GetForeColor(int attrColor);
int Cl_GetBackColor(int attrColor);

// Objects
Object* Cl_CreateObject(Buffer* buffer, short x, short y);
Object* Cl_CreateAnimatedObject(Animation* anim, short x, short y);
void Cl_FreeObject(Object* object);
void Cl_ClearObjects();
bool Cl_IsPointInObject(Object* object, short x, short y);
bool Cl_IsCollision(Object* object1, Object* object2);

// Buffer
Buffer* Cl_BuildScreen();
void Cl_DisplayScreen(Buffer* _screenBuffer);
void Cl_FlushScreen();
void Cl_Process(short fps);
void Cl_ClearBuffer(Buffer* buffer, short x, short y, short w, short h);
void Cl_CopyBuffer(Buffer* dstBuffer, Buffer* srcBuffer, short dstX, short dstY, short width, short height, short srcX, short srcY);
void Cl_DrawBuffer(Buffer* buffer, short x, short y);
Buffer* Cl_LoadBuffer(char* fileName);
void Cl_SaveBuffer(Buffer* buffer, char* fileName, short x, short y, short w, short h);
CHAR_INFO Cl_GetCharInfo(Buffer* buffer, short x, short y);
void Cl_FillBuffer(Buffer* buffer, char charCode, short x, short y, short width, short height, int attrColor);
Buffer* Cl_CreateBuffer(short width, short height, char charCode, int attrColor);

// Text
void Cl_StartTextInput(short x, short y, int attrColor);
char* Cl_GetTextInput(short x, short y, int attrColor);
void Cl_DrawChar(Buffer* buffer, char charCode, short x, short y, int attrColor);
void Cl_DrawString(Buffer* buffer, char* str, short x, short y, int attrColor);
void Cl_DrawText(Buffer* buffer, char* strChar, short width, bool justify, short x, short y, int attrColor);
Buffer* Cl_CreateChar(char charCode, int attrColor);
Buffer* Cl_CreateString(char* str, int attrColor);
Buffer* Cl_CreateText(char* strChar, short width, bool justify, int attrColor);
char* Cl_ConvertToDos(char* strIn);

// Effects
void Cl_ShakeEffect(Object* object, bool enabled, int duration);

// Library
void Cl_Init(int width, int height);
void Cl_Free();
char* Cl_GetLastError();
void Cl_Debug(int debugLevel, char* format, ...);
void Cl_SetVerbosity(int debugLevel);

// Console
void Cl_ShowConsoleCursor(bool visible);
void Cl_SetCursorPosition(short x, short y);
int Cl_IsConsoleFocused();
bool Cl_ResizeConsole(short width, short height);
void Cl_SetConsoleTitle(char* title);

// Utilities
void Cl_WaitFrameRate(int fps);
char* Cl_FormatString(char* format, ...);
char* Cl_RepeatChar(char charCode, short number);
CHAR_INFO Cl_CorrectCharInfo(CHAR_INFO ci);

// Inputs
COORD Cl_GetMousePosition();
bool Cl_IsMouseOver(Object* object);
short Cl_GetWheelValue();
bool Cl_IsButtonPressed(int buttonCode);
bool Cl_HasButtonChanged(int buttonCode);
bool Cl_HasButtonReleased(int buttonCode);
int Cl_GetLastButton();
void Cl_ProcessEvents();

// Animations
Animation* Cl_CreateAnimation(char* fileName, short width, short height);
Animation* Cl_LoadAnimation(char* fileName);
void Cl_ReadFrame(Animation* animation);
void Cl_WriteFrame(Animation* animation, Buffer* buffer);

#endif