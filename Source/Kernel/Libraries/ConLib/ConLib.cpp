#include "ConLib.h"


int clock()
{
    return 0;//GetTicks() * 10;
}
bool WriteConsoleOutputA(HANDLE hConsoleOutput, const CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD dwBufferCoord, PSMALL_RECT lpWriteRegion)
{
    memcpy((void*)0x0B8000, lpBuffer, 80 * 25 * 2);
    return true;
}
FILE* fopen(const char* filename, const char* mode)
{
    return NULL;
}
int fgetc(FILE* stream)
{
    return 0;
}
int fclose(FILE* stream)
{
    return 0;
}
int fputc(int character, FILE* stream)
{
    return 0;
}
int fputs(const char* str, FILE* stream)
{
    return 0;
}
time_t time(time_t* timer)
{
    return clock();
}
void exit(int status)
{
    int i = 0;
    int j = 1 / i;
    for (;;);
}





// Console
static HANDLE _hStdout = NULL;
static HANDLE _hStdin = NULL;
static HANDLE _hConsole = NULL;

// Library
static int _initialized = false;
static int _lastTime = 0;
static int _verbosity = Fatal;

// Graphics
Buffer* screen = NULL;

// Effects
static ShakeEffect _shakeEffect;

// Inputs
static MOUSE_EVENT_RECORD _oldMouseData;
static MOUSE_EVENT_RECORD _mouseData;
static short _mouseWheel = 0;
static KEYBOARD_DATA _oldKeyboardData;
static KEYBOARD_DATA _keyboardData;
static char _lastKey = 0;
static TextInput _textInput;

// Objects
static Object** _lstObjects = NULL;
static int _nbObjects = 0;

// Records
static bool _playing = false;
static bool _recording = false;
static Buffer* _lastFrame = NULL;
static FILE* _recordFile = NULL;

// Structure builders
COORD Cl_Coord(short X, short Y)
{
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    return coord;
}
Buffer* Cl_Buffer(short width, short height)
{
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->width = width;
    buffer->height = height;
    buffer->data = (CHAR_INFO*)calloc(width * height, sizeof(CHAR_INFO));
    return buffer;
}
CHAR_INFO Cl_CharInfo(char charCode, int attrColor)
{
    CHAR_INFO ci;
    ci.AsciiChar = charCode;
    ci.Attributes = attrColor;
    return ci;
}

// Colors
int Cl_CreateColor(int foreColor, int backColor)
{
    return foreColor + backColor * 16;
}
int Cl_GetDarkerColor(int attrColor)
{
    int foreColor = attrColor % 16,
        backColor = attrColor / 16;
    if (foreColor > 7)
        foreColor -= 8;
    else
        foreColor = 0;
    if (backColor > 7)
        backColor -= 8;
    else
        backColor = 0;
    return foreColor + backColor * 16;
}
int Cl_GetLighterColor(int attrColor)
{
    int foreColor = attrColor % 16,
        backColor = attrColor / 16;
    if (foreColor < 8)
        foreColor += 8;
    else
        foreColor = 0;
    if (backColor < 8)
        backColor += 8;
    else
        backColor = 0;
    return foreColor + backColor * 16;
}
void Cl_SetBufferColor(Buffer* buffer, int attrColor)
{
   int i, j;
   if (!buffer)
    {
        Cl_Debug(Warning, "[Cl_SetBufferColor] buffer cannot be null");
        return;
    }
    for (j = 0; j < buffer->height; j++)
        for (i = 0; i < buffer->width; i++)
            buffer->data[j * buffer->width + i].Attributes = attrColor;
}
int Cl_GetForeColor(int attrColor)
{
    return attrColor % 16;
}
int Cl_GetBackColor(int attrColor)
{
    return attrColor / 16;
}

// Objects
Object* Cl_CreateObject(Buffer* buffer, short x, short y)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_CreateObject] Cl is not initialized");
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_CreateObject] buffer cannot be null");
        return NULL;
    }
    _lstObjects = (Object**)realloc(_lstObjects, (_nbObjects + 1) * sizeof(Object*));
    _lstObjects[_nbObjects] = (Object*)malloc(sizeof(Object));
    _lstObjects[_nbObjects]->position = Cl_Coord(x, y);
    _lstObjects[_nbObjects]->visible = true;
    _lstObjects[_nbObjects]->buffer = (Buffer*)malloc(sizeof(Buffer));
    _lstObjects[_nbObjects]->buffer->width = buffer->width;
    _lstObjects[_nbObjects]->buffer->height = buffer->height;
    _lstObjects[_nbObjects]->buffer->data = (CHAR_INFO*)malloc(buffer->width * buffer->height * sizeof(CHAR_INFO));
    _lstObjects[_nbObjects]->animation = NULL;
    _lstObjects[_nbObjects]->shakeEffect.enabled = false;
    memcpy(_lstObjects[_nbObjects]->buffer->data, buffer->data, buffer->width * buffer->height * sizeof(CHAR_INFO));
    return _lstObjects[_nbObjects++];
}
Object* Cl_CreateAnimatedObject(Animation* animation, short x, short y)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_CreateAnimatedObject] Cl is not initialized");
    if (!animation)
    {
        Cl_Debug(Warning, "[Cl_CreateAnimatedObject] Animation cannot be null");
        return NULL;
    }
    _lstObjects = (Object**)realloc(_lstObjects, (_nbObjects + 1) * sizeof(Object*));
    _lstObjects[_nbObjects] = (Object*)malloc(sizeof(Object));
    _lstObjects[_nbObjects]->position = Cl_Coord(x, y);
    _lstObjects[_nbObjects]->visible = true;
    _lstObjects[_nbObjects]->buffer = NULL;
    _lstObjects[_nbObjects]->animation = animation;
    _lstObjects[_nbObjects]->shakeEffect.enabled = false;
    return _lstObjects[_nbObjects++];
}
void Cl_FreeObject(Object* object)
{
    int i;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_FreeObject] Cl is not initialized");
    if (object == NULL)
    {
        Cl_Debug(Warning, "[Cl_FreeObject] object cannot be null");
        return;
    }
    for (i = 0; i < _nbObjects; i++)
        if (_lstObjects[i] == object)
            break;
    if (i == _nbObjects)
        return;
    free(_lstObjects[i]);
    _nbObjects --;
    for (; i < _nbObjects; i++)
        _lstObjects[i] = _lstObjects[i + 1];
    _lstObjects = (Object**)realloc(_lstObjects, _nbObjects * sizeof(Object*));
}
void Cl_ClearObjects()
{
    int i;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_ClearObjects] Cl is not initialized");
    for (i = 0; i < _nbObjects; i++)
    {
        free(_lstObjects[i]->buffer->data);
        free(_lstObjects[i]->buffer);
        free(_lstObjects[i]);
    }
    _nbObjects = 0;
}
bool Cl_IsPointInObject(Object* object, short x, short y)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_IsPointInObject] Cl is not initialized");
    if (object == NULL)
    {
        Cl_Debug(Warning, "[Cl_IsPointInObject] object cannot be null");
        return false;
    }
    if (!object->visible)
        return false;
    if (x < object->position.X ||
        x >= (object->position.X + object->buffer->width) ||
        y < object->position.Y ||
        y >= (object->position.Y + object->buffer->height))
        return false;
    else if (Cl_GetCharInfo(object->buffer, x - object->position.X, y - object->position.Y).AsciiChar == 0)
        return false;
    else
        return true;
}
bool Cl_IsCollision(Object* object1, Object* object2)
{
    int x, y;
    bool c;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_IsCollision] Cl is not initialized");
    if (object1 == NULL || object2 == NULL)
    {
        Cl_Debug(Warning, "[Cl_IsCollision] objects cannot be null");
        return false;
    }
    if (!object1->visible || !object2->visible)
        return false;
    c = false;
    for (y = object1->position.Y; y < object1->position.Y + object1->buffer->height; y++)
        for (x = object1->position.X; x < object1->position.X + object1->buffer->width; x++)
            if (Cl_GetCharInfo(object1->buffer, x - object1->position.X, y - object1->position.Y).AsciiChar)
                c |= Cl_IsPointInObject(object2, x, y);
    return c;
}

// Buffer
Buffer* Cl_BuildScreen()
{
    int x, y, w, h, i;
    static Buffer* _screenBuffer = NULL;

    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_BuildScreen] Cl is not initialized");

    // Initialize base buffer
    if (_screenBuffer == NULL)
    {
        _screenBuffer = (Buffer*)malloc(sizeof(Buffer));
        _screenBuffer->width = screen->width;
        _screenBuffer->height = screen->height;
        _screenBuffer->data = (CHAR_INFO*)malloc(screen->width * screen->height * sizeof(CHAR_INFO));
    }
    ZeroMemory(_screenBuffer->data, screen->width * screen->height * sizeof(CHAR_INFO));

    // Manage effects
    if (_shakeEffect.enabled && (clock() - _shakeEffect.time) > 50)
    {
        _shakeEffect.time = clock();
        if (_shakeEffect.duration > 0)
        {
            _shakeEffect.duration -= 50;
            if (_shakeEffect.duration <= 0)
                _shakeEffect.enabled = false;
        }
        _shakeEffect.shift = Cl_Coord(rand() % 3 - 1, rand() % 3 - 1);
    }

    // Copy base buffer
    if (_shakeEffect.enabled)
        Cl_CopyBuffer(_screenBuffer, screen, _shakeEffect.shift.X, _shakeEffect.shift.Y, screen->width, screen->height, 0, 0);
    else
        Cl_CopyBuffer(_screenBuffer, screen, 0, 0, screen->width, screen->height, 0, 0);

    // Draw objects
    for (i = 0; i < _nbObjects; i++)
    {
        if (_lstObjects[i]->shakeEffect.enabled && (clock() - _lstObjects[i]->shakeEffect.time) > 50)
        {
            _lstObjects[i]->shakeEffect.time = clock();
            if (_lstObjects[i]->shakeEffect.duration > 0)
            {
                _lstObjects[i]->shakeEffect.duration -= 50;
                if (_lstObjects[i]->shakeEffect.duration <= 0)
                    _lstObjects[i]->shakeEffect.enabled = false;
            }
            _lstObjects[i]->shakeEffect.shift = Cl_Coord(rand() % 3 - 1, rand() % 3 - 1);
        }

        if (!_lstObjects[i]->visible)
            continue;

        x = _lstObjects[i]->position.X;
        y = _lstObjects[i]->position.Y;
        if (_lstObjects[i]->buffer)
        {
            w = _lstObjects[i]->buffer->width;
            h = _lstObjects[i]->buffer->height;
        }
        else if (_lstObjects[i]->animation)
        {
            w = _lstObjects[i]->animation->width;
            h = _lstObjects[i]->animation->height;
        }

        if (_lstObjects[i]->shakeEffect.enabled)
        {
            x += _lstObjects[i]->shakeEffect.shift.X;
            y += _lstObjects[i]->shakeEffect.shift.Y;
        }
        if (_shakeEffect.enabled)
        {
            x += _shakeEffect.shift.X;
            y += _shakeEffect.shift.Y;
        }

        if (_lstObjects[i]->buffer)
            Cl_CopyBuffer(_screenBuffer, _lstObjects[i]->buffer, x, y, w, h, 0, 0);
        else if (_lstObjects[i]->animation)
            Cl_CopyBuffer(_screenBuffer, _lstObjects[i]->animation->currentFrame, x, y, w, h, 0, 0);
    }

    // Text input
    if (_textInput.state == 1)
    {
        Cl_DrawString(_screenBuffer, _textInput.text, _textInput.x, _textInput.y, _textInput.attributes);
        Cl_SetCursorPosition(_textInput.x + _textInput.cursorX, _textInput.y);
    }
    else
        Cl_ShowConsoleCursor(false);

    return _screenBuffer;
}
void Cl_DisplayScreen(Buffer* _screenBuffer)
{
    SMALL_RECT bufferRect;
    if (_screenBuffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_DisplayScreen] _screenBuffer cannot be null");
        return;
    }
    bufferRect.Left = 0;
    bufferRect.Top = 0;
    bufferRect.Right = _screenBuffer->width - 1;
    bufferRect.Bottom = _screenBuffer->height - 1;
    WriteConsoleOutputA(_hStdout, _screenBuffer->data, Cl_Coord(_screenBuffer->width, _screenBuffer->height), Cl_Coord(0, 0), &bufferRect);
}
void Cl_FlushScreen()
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_FlushScreen] Cl is not initialized");
    Cl_DisplayScreen(Cl_BuildScreen());
}
void Cl_Process(short fps)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_Process] Cl is not initialized");
    Cl_FlushScreen();
    Cl_ProcessEvents();
    if (fps)
        Cl_WaitFrameRate(fps);
}
void Cl_ClearBuffer(Buffer* buffer, short x, short y, short w, short h)
{
    int i, j;
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_ClearBuffer] buffer cannot be null");
        return;
    }
    for (j = y; j < y + h; j++)
        for (i = x; i < x + w; i++)
        {
            buffer->data[j * buffer->width + i].AsciiChar = 0;
            buffer->data[j * buffer->width + i].Attributes = 0;
        }
}
void Cl_CopyBuffer(Buffer* dstBuffer, Buffer* srcBuffer, short dstX, short dstY, short width, short height, short srcX, short srcY)
{
    int x, y;
    CHAR_INFO ci;
    if (srcBuffer == NULL || dstBuffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_CopyBuffer] srcBuffer and dstBuffer cannot be null");
        return;
    }
    for (y = dstY; y < dstY + height; y++)
        for (x = dstX; x < dstX + width; x++)
        {
            ci = Cl_GetCharInfo(srcBuffer, x - dstX + srcX, y - dstY + srcY);
            if (!ci.AsciiChar)
                continue;
            if (x < 0 || x > dstBuffer->width - 1 || y < 0 || y > dstBuffer->height - 1)
                continue;
            dstBuffer->data[y * dstBuffer->width + x] = ci;
        }
}
void Cl_DrawBuffer(Buffer* buffer, short x, short y)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_DrawBuffer] Cl is not initialized");
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_DrawBuffer] buffer cannot be null");
        return;
    }
    Cl_CopyBuffer(screen, buffer, x, y, buffer->width, buffer->height, 0, 0);
}
Buffer* Cl_LoadBuffer(char* fileName)
{
    int version, i;
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));

    FILE* mapFile = fopen(fileName, "r");
    if (mapFile == NULL)
    {
        Cl_Debug(Error, "[Cl_LoadBuffer] Unable to open the file %s", fileName);
        return NULL;
    }

    version = fgetc(mapFile);
    switch (version)
    {
        case 0x01: // Version 1
            buffer->width = fgetc(mapFile) | fgetc(mapFile) << 8;
            buffer->height = fgetc(mapFile) | fgetc(mapFile) << 8;
            buffer->data = (CHAR_INFO*)malloc(buffer->width * buffer->height * sizeof(CHAR_INFO));
            for (i = 0; i < buffer->width * buffer->height; i++)
            {
                buffer->data[i].AsciiChar = fgetc(mapFile);
                buffer->data[i].Attributes = fgetc(mapFile) | fgetc(mapFile) << 8;
            }
            break;
        case 0x02: // Version 2
            buffer->width = fgetc(mapFile);
            buffer->height = fgetc(mapFile);
            buffer->data = (CHAR_INFO*)malloc(buffer->width * buffer->height * sizeof(CHAR_INFO));
            for (i = 0; i < buffer->width * buffer->height; i++)
            {
                buffer->data[i].AsciiChar = fgetc(mapFile);
                buffer->data[i].Attributes = fgetc(mapFile);
            }
            break;
        default:
            Cl_Debug(Error, "[Cl_LoadBuffer] Wrong CLB version found in file %s", fileName);
            return NULL;
    }

    fclose(mapFile);
    return buffer;
}
void Cl_SaveBuffer(Buffer* buffer, char* fileName, short x, short y, short width, short height)
{
    FILE* bufferFile;
    int i, j;
    CHAR_INFO ci;

    if (!buffer)
    {
        Cl_Debug(Warning, "[Cl_SaveBuffer] buffer cannot be null");
        return;
    }
    bufferFile = fopen(fileName, "w+");
    if (!bufferFile)
    {
        Cl_Debug(Error, "[Cl_LoadBuffer] Unable to open the file %s", fileName);
        return;
    }

    // Version 1
    /*fputc(1, mapFile);
    fputc(w % 256, mapFile);
    fputc(w / 256, mapFile);
    fputc(h % 256, mapFile);
    fputc(h / 256, mapFile);
    for (j = y; j < y + h; j++)
        for (i = x; i < x + w; i++)
        {
            ci = Cl_CorrectCharInfo(Cl_GetCharInfo(buffer, i, j));
            fputc(ci.Char.AsciiChar, mapFile);
            fputc(ci.Attributes % 256, mapFile);
            fputc(ci.Attributes / 256, mapFile);
        }*/

    // Version 2
    fputc(0x02, bufferFile);
    fputc(width % 256, bufferFile);
    fputc(height % 256, bufferFile);
    for (j = y; j < y + height; j++)
        for (i = x; i < x + width; i++)
        {
            ci = Cl_CorrectCharInfo(Cl_GetCharInfo(buffer, i, j));
            fputc(ci.AsciiChar, bufferFile);
            fputc(ci.Attributes % 256, bufferFile);
        }
    fclose(bufferFile);
}
CHAR_INFO Cl_GetCharInfo(Buffer* buffer, short x, short y)
{
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_GetCharInfo] Buffer cannot be null");
        return Cl_CharInfo(0, 0);
    }
    if (x < 0 || x >= buffer->width || y < 0 || y >= buffer->height)
        return Cl_CharInfo(0, 0);
    return buffer->data[y * buffer->width + x];
}
void Cl_FillBuffer(Buffer* buffer, char charCode, short x, short y, short width, short height, int attrColor)
{
    int i, j;
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_FillBuffer] buffer cannot be null");
        return;
    }
    for (j = y; j < y + height; j++)
        for (i = x; i < x + width; i++)
            Cl_DrawChar(buffer, charCode, i, j, attrColor);
}
Buffer* Cl_CreateBuffer(short width, short height, char charCode, int attrColor)
{
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->width = width;
    buffer->height = height;
    buffer->data = (CHAR_INFO*)malloc(width * height * sizeof(CHAR_INFO));
    Cl_FillBuffer(buffer, charCode, 0, 0, width, height, attrColor);
    return buffer;
}

// Text
void Cl_StartTextInput(short x, short y, int attrColor)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_StartTextInput] Cl is not initialized");
    Cl_SetCursorPosition(x, y);
    Cl_ShowConsoleCursor(true);
    _textInput.state = 1;
    _textInput.x = x;
    _textInput.y = y;
    _textInput.attributes = attrColor;
    _textInput.cursorX = 0;
    _textInput.textLength = 0;
    _textInput.text[0] = 0;
}
char* Cl_GetTextInput(short x, short y, int attrColor)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_GetTextInput] Cl is not initialized");
    Cl_StartTextInput(x, y, attrColor);
    while(_textInput.state == 1)
        Cl_Process(50);
    return _textInput.text;
}
void Cl_DrawChar(Buffer* buffer, char charCode, short x, short y, int attrColor)
{
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_DrawChar] Buffer cannot be null");
        return;
    }
    if (x < 0 || x >= buffer->width || y < 0 || y >= buffer->height)
        return;
    buffer->data[y * buffer->width + x] = Cl_CharInfo(charCode, attrColor);
}
void Cl_DrawString(Buffer* buffer, char* str, short x, short y, int attrColor)
{
    int i, l;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_DrawString] Cl is not initialized");
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_DrawString] Buffer cannot be null");
        return;
    }
    str = Cl_ConvertToDos(str);
    l = (int)strlen(str);
    for (i = x; i < x + l; i++)
    {
        if (i < 0 || i >= buffer->width || y < 0 || y >= buffer->height)
            continue;
        buffer->data[y * buffer->width + i].AsciiChar = str[i - x];
        buffer->data[y * buffer->width + i].Attributes = attrColor;
    }
}
void Cl_DrawText(Buffer* buffer, char* strChar, short width, bool justify, short x, short y, int attrColor)
{
    int i, j, l, len;
    char* str;

    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_DrawText] Cl is not initialized");
    if (buffer == NULL)
    {
        Cl_Debug(Warning, "[Cl_DrawText] Buffer cannot be null");
        return;
    }

    l = 0;
    strChar = Cl_ConvertToDos(strChar);
    len = (int)strlen(strChar);

    str = (char*)malloc(len + 1);
    memcpy(str, strChar, len);
    *(str + len) = 0;

    while(len > width)
    {
        for (i = width; i > 0; i--)
            if (str[i] == ' ')
                break;

        if (i)
        {
            if (justify)
            {
                len += width - i;
                str = (char*)realloc(str, len + 1);
                while (width - i)
                    for (j = 0; j < i && (width - i); j++)
                        if (str[j] == ' ')
                        {
                            memmove(str + j + 1, str + j, len - j);
                            while (str[j] == ' ')
                                j++;
                            i++;
                        }
            }
            for (j = 0; j < i; j++)
            {
                if (y + l < 0 || y + l >= buffer->height || x + j < 0 || x + j >= buffer->width)
                    continue;
                buffer->data[(y + l) * buffer->width + x + j].AsciiChar = *(str + j);
                buffer->data[(y + l) * buffer->width + x + j].Attributes = attrColor;
            }
            i++;
        }
        else
        {
            i = width;
            for (j = 0; j < i; j++)
            {
                if (y + l < 0 || y + l >= buffer->height || x + j < 0 || x + j >= buffer->width)
                    continue;
                buffer->data[(y + l) * buffer->width + x + j].AsciiChar = *(str + j);
                buffer->data[(y + l) * buffer->width + x + j].Attributes = attrColor;
            }
        }

        memmove(str, str + i, len - i + 1);
        len = (int)strlen(str);

        l++;
    }

    // Last line
    for (i = 0; *(str + i) != '\0'; i++)
    {
        if (y + l < 0 || y + l >= buffer->height || x + i < 0 || x + i >= buffer->width)
            continue;
        buffer->data[(y + l) * buffer->width + x + i].AsciiChar = *(str + i);
        buffer->data[(y + l) * buffer->width + x + i].Attributes = attrColor;
    }

    free(str);
}
Buffer* Cl_CreateChar(char charCode, int attrColor)
{
    Buffer* buffer = Cl_Buffer(1, 1);
    buffer->data[0].AsciiChar = charCode;
    buffer->data[0].Attributes = attrColor;
    return buffer;
}
Buffer* Cl_CreateString(char* str, int attrColor)
{
    int i;
    short w;
    Buffer* buffer;
    str = Cl_ConvertToDos(str);
    w = (short)strlen(str);
    buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->width = w;
    buffer->height = 1;
    buffer->data = (CHAR_INFO*)malloc(w * sizeof(CHAR_INFO));
    for (i = 0; i < w; i++)
    {
        buffer->data[i].AsciiChar = str[i];
        buffer->data[i].Attributes = attrColor;
    }
    return buffer;
}
Buffer* Cl_CreateText(char* strChar, short width, bool justify, int attrColor)
{
    int i, j, len;
    char* str;

    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->width = width;
    buffer->height = 1;
    buffer->data = (CHAR_INFO*)calloc(width, sizeof(CHAR_INFO));

    strChar = Cl_ConvertToDos(strChar);
    len = (int)strlen(strChar);

    str = (char*)malloc(len + 1);
    memcpy(str, strChar, len);
    *(str + len) = 0;

    while(len > width)
    {
        for (i = width; i > 0; i--)
            if (str[i] == ' ')
                break;

        if (i)
        {
            if (justify)
            {
                len += width - i;
                str = (char*)realloc(str, len + 1);
                while (width - i)
                    for (j = 0; j < i && (width - i); j++)
                        if (str[j] == ' ')
                        {
                            memmove(str + j + 1, str + j, len - j);
                            while (str[j] == ' ')
                                j++;
                            i++;
                        }
            }
            for (j = 0; j < i; j++)
            {
                buffer->data[(buffer->height - 1) * width + j].AsciiChar = *(str + j);
                buffer->data[(buffer->height - 1) * width + j].Attributes = attrColor;
            }
            i++;
        }
        else
        {
            i = width;
            for (j = 0; j < i; j++)
            {
                buffer->data[(buffer->height - 1) * width + j].AsciiChar = *(str + j);
                buffer->data[(buffer->height - 1) * width + j].Attributes = attrColor;
            }
        }

        memmove(str, str + i, len - i + 1);
        len = (int)strlen(str);

        buffer->height++;
        buffer->data = (CHAR_INFO*)realloc(buffer->data, width * buffer->height * sizeof(CHAR_INFO));
        ZeroMemory(buffer->data + (buffer->height - 1) * width, width);
    }

    // Last line
    for (i = 0; *(str + i) != '\0'; i++)
    {
        buffer->data[(buffer->height - 1) * width + i].AsciiChar = *(str + i);
        buffer->data[(buffer->height - 1) * width + i].Attributes = attrColor;
    }

    return buffer;
}
char* Cl_ConvertToDos(char* strIn)
{
    char* strOut = NULL;
    int i, l = 1;

    for (i = 0; i < strlen(strIn); i++, l++)
    {
        strOut = (char*)realloc(strOut, l);
        if (*(strIn + i) == -61)
        {
            i++;
            switch (*(strIn + i))
            {
                case -68: *(strOut + l - 1) = 0x81; break; // ü
                case -87: *(strOut + l - 1) = 0x82; break; // é
                case -94: *(strOut + l - 1) = 0x83; break; // â
                case -92: *(strOut + l - 1) = 0x84; break; // ä
                case -96: *(strOut + l - 1) = 0x85; break; // à
                case -89: *(strOut + l - 1) = 0x87; break; // ç
                case -86: *(strOut + l - 1) = 0x88; break; // ê
                case -85: *(strOut + l - 1) = 0x89; break; // ë
                case -88: *(strOut + l - 1) = 0x8A; break; // è
                case -81: *(strOut + l - 1) = 0x8B; break; // ï
                case -82: *(strOut + l - 1) = 0x8C; break; // î
                case -76: *(strOut + l - 1) = 0x93; break; // ô
                case -74: *(strOut + l - 1) = 0x94; break; // ö
                case -71: *(strOut + l - 1) = 0x97; break; // ù
                default: *(strOut + l - 1) = *(strIn + i);
            }
        }
        else
            *(strOut + l - 1) = *(strIn + i);
    }

    strOut = (char*)realloc(strOut, l);
    *(strOut + l - 1) = 0;
    return strOut;
}

// Effects
void Cl_ShakeEffect(Object* object, bool enabled, int duration)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_ShakeEffect] Cl is not initialized");
    if (object == NULL)
    {
        if (enabled)
        {
            if (!_shakeEffect.enabled)
                _shakeEffect.time = clock();
            _shakeEffect.enabled = true;
            _shakeEffect.duration = duration;
        }
        else
            _shakeEffect.enabled = false;
    }
    else
    {
        if (enabled)
        {
            if (!object->shakeEffect.enabled)
                object->shakeEffect.time = clock();
            object->shakeEffect.enabled = true;
            object->shakeEffect.duration = duration;
        }
        else
            object->shakeEffect.enabled = false;
    }
}

// Library
void Cl_Init(int width, int height)
{
    if (_initialized)
    {
        Cl_Debug(Warning, "[Cl_Init] Conlib is already initialized");
        return;
    }

    /*
    _hConsole = GetConsoleWindow();
    if (_hConsole == NULL)
        Cl_Debug(Fatal, "[Cl_Init] Unable to find the attached console window");

    _hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (_hStdout == INVALID_HANDLE_VALUE)
        Cl_Debug(Fatal, "[Cl_Init] Unable to find the output handle");

    _hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (_hStdin == INVALID_HANDLE_VALUE)
        Cl_Debug(Fatal, "[Cl_Init] Unable to find the input handle");

    if (!Cl_ResizeConsole(width, height))
        Cl_Debug(Fatal, "[Cl_Init] Unable to resize the console buffer");
    */

    // Init background buffer
    screen = (Buffer*)malloc(sizeof(Buffer));
    screen->width = width;
    screen->height = height;
    screen->data = (CHAR_INFO*)calloc(width * height, sizeof(CHAR_INFO));

    // Init text input
    ZeroMemory(&_textInput, sizeof(TextInput));
    _textInput.text = (char*)calloc(1, sizeof(char));
    *_textInput.text = 0;

    // Init inputs
    ZeroMemory(&_mouseData, sizeof(MOUSE_EVENT_RECORD));
    ZeroMemory(&_keyboardData, sizeof(KEYBOARD_DATA));

    // Clear effects
    ZeroMemory(&_shakeEffect, sizeof(ShakeEffect));

    // Init random
    srand((int)time(NULL));

    _initialized = true;
    Cl_ShowConsoleCursor(false);
}
void Cl_Free()
{
    int i;
    _initialized = false;
    _hStdout = NULL;
    free(screen);
    screen = NULL;
    for (i = 0; i < _nbObjects; i++)
    {
        if (_lstObjects[i]->buffer)
        {
            free(_lstObjects[i]->buffer->data);
            free(_lstObjects[i]->buffer);
        }
        else if (_lstObjects[i]->animation)
        {
            free(_lstObjects[i]->animation->currentFrame);
        }
        free(_lstObjects[i]);
    }
    free(_lstObjects);
    _nbObjects = 0;
}
void Cl_Debug(int debugLevel, char* format, ...)
{
    /*int len;
    char* ret;
    if (debugLevel <= _verbosity)
    {
        FILE* debug = fopen("Cl_debug.txt", "w+");
        /*char str[8192]; // TODO: make it dynamically
        va_list args;
        va_start(args, format);
        len = vsprintf(str, format, args);
        va_end(args);
        ret = (char*)calloc(len + 1, sizeof(char));
        memcpy(ret, str, len);
        *(ret + len) = 0;
        fputs(ret, debug);
        fputc('\n', debug);
        fclose(debug);
    }
    if (debugLevel == Fatal)
        exit(-1);*/
}
void Cl_SetVerbosity(int debugLevel)
{
    _verbosity = debugLevel;
}

// Console
void Cl_ShowConsoleCursor(bool visible)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 25;
    cursorInfo.bVisible = visible;
    //if (!SetConsoleCursorInfo(_hStdout, &cursorInfo))
    //    Cl_Debug(Fatal, "[Cl_ShowConsoleCursor] Unable to show/hide cursor");
}
void Cl_SetCursorPosition(short x, short y)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_SetCursorPosition] Cl is not initialized");
    if (x < 0 || x >= screen->width || y < 0 || y >= screen->height)
        return;
    //SetConsoleCursorPosition(_hStdout, Cl_Coord(x, y));
}
int Cl_IsConsoleFocused()
{
    /*if (_hConsole == NULL)
        _hConsole = GetConsoleWindow();
    if (_hConsole == NULL)
        Cl_Debug(Fatal, "[Cl_IsConsoleFocused] Unable to find the attached console window");
    return GetForegroundWindow() == _hConsole;*/
    return true;
}
bool Cl_ResizeConsole(short width, short height)
{
    /*CONSOLE_SCREEN_BUFFER_INFO info;
    COORD coordMax;

    if (_hStdout == NULL)
        _hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (_hStdout == INVALID_HANDLE_VALUE)
        Cl_Debug(Fatal, "[Cl_ResizeConsole] Unable to find the output handle");

    coordMax = GetLargestConsoleWindowSize(_hStdout);
    if (height > coordMax.Y || width > coordMax.X || height < 1 || width < 1 || !GetConsoleScreenBufferInfo(_hStdout, &info))
        return false;

    info.srWindow.Left = 0;
    info.srWindow.Right = info.dwSize.X - 1;
    info.srWindow.Top = 0;
    info.srWindow.Bottom = height - 1;
    if (height < info.dwSize.Y)
    {
        if (!SetConsoleWindowInfo(_hStdout, true, &info.srWindow))
            return false;
        info.dwSize.Y = height;
        if (!SetConsoleScreenBufferSize(_hStdout, info.dwSize))
            return false;
    }
    else if (height > info.dwSize.Y)
    {
        info.dwSize.Y = height;
        if (!SetConsoleScreenBufferSize(_hStdout, info.dwSize))
            return false;
        if (!SetConsoleWindowInfo(_hStdout, true, &info.srWindow))
            return false;
    }
    if (!GetConsoleScreenBufferInfo(_hStdout, &info))
        return false;

    info.srWindow.Left = 0;
    info.srWindow.Right = width - 1;
    info.srWindow.Top = 0;
    info.srWindow.Bottom = info.dwSize.Y - 1;
    if (width < info.dwSize.X)
    {
        if (!SetConsoleWindowInfo(_hStdout, true, &info.srWindow))
            return false;
        info.dwSize.X = width;
        if (!SetConsoleScreenBufferSize(_hStdout, info.dwSize))
            return false;
    }
    else if (width > info.dwSize.X)
    {
        info.dwSize.X = width;
        if (!SetConsoleScreenBufferSize(_hStdout, info.dwSize))
            return false;
        if (!SetConsoleWindowInfo(_hStdout, true, &info.srWindow))
            return false;
    }*/

    return true;

    // TODO: Resize screen, and re-init
}
void Cl_SetConsoleTitle(char* title)
{
    //SetConsoleTitleA(title);
}

// Utilities
void Cl_WaitFrameRate(int fps)
{
    if (_lastTime)
        while ((clock() - _lastTime) < (100 / fps));
            //Sleep(1);
    _lastTime = clock();
}
char* Cl_FormatString(char* format, ...)
{
    char* ret = (char*)malloc(strlen(format + 1));
    strcpy(ret, format);
    return ret;

    /*int len;
    char* ret;
    char str[8192]; // TODO: make it dynamically
    va_list args;
    va_start(args, format);
    len = vsprintf(str, format, args);
    va_end(args);
    ret = (char*)calloc(len + 1, sizeof(char));
    memcpy(ret, str, len);
    *(ret + len) = 0;
    return ret;*/
}

#pragma optimize("", off)
char* Cl_RepeatChar(char charCode, short number)
{
    char* str = (char*)malloc(number);
    int i;
    for (i = 0; i < number; i++)
        *(str + i) = charCode;
    return str;
}
#pragma optimize("", on)

CHAR_INFO Cl_CorrectCharInfo(CHAR_INFO ci)
{
    char c;
    int fore, back;
    c = ci.AsciiChar;
    fore = Cl_GetForeColor(ci.Attributes);
    back = Cl_GetBackColor(ci.Attributes);
    if (!c)
        return Cl_CharInfo(0, 0);
    else if (fore == back || c == (char)0xDB)
        return Cl_CharInfo(' ', Cl_CreateColor(Black, fore));
    else
        return Cl_CharInfo(c, Cl_CreateColor(fore, back));
}
// Inputs
COORD Cl_GetMousePosition()
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_GetMousePosition] Cl is not initialized");
    return _mouseData.dwMousePosition;
}
bool Cl_IsMouseOver(Object* object)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_IsMouseOver] Cl is not initialized");
    if (object == NULL)
    {
        Cl_Debug(Warning, "[Cl_IsMouseOver] object cannot be null");
        return false;
    }
    return Cl_IsPointInObject(object, _mouseData.dwMousePosition.X, _mouseData.dwMousePosition.Y);
}
short Cl_GetWheelValue()
{
    short w;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_GetWheelValue] Cl is not initialized");
    w = _mouseWheel;
    _mouseWheel = 0;
    return w;
}
bool Cl_IsButtonPressed(int buttonCode)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_IsButtonPressed] Cl is not initialized");
    if (buttonCode < 5)
        return (_mouseData.dwButtonState & buttonCode) == buttonCode;
    else
        return _keyboardData.keyState[buttonCode];
}
bool Cl_HasButtonChanged(int buttonCode)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_HasButtonChanged] Cl is not initialized");
    if (buttonCode < 5)
        return ((_oldMouseData.dwButtonState & buttonCode) == buttonCode) ^ ((_mouseData.dwButtonState & buttonCode) == buttonCode);
    else
        return _oldKeyboardData.keyState[buttonCode] ^ _keyboardData.keyState[buttonCode];
}
bool Cl_HasButtonReleased(int buttonCode)
{
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_HasButtonChanged] Cl is not initialized");
    if (buttonCode < 5)
        return (((_oldMouseData.dwButtonState & buttonCode) == buttonCode) ^ ((_mouseData.dwButtonState & buttonCode) == buttonCode)) && !((_mouseData.dwButtonState & buttonCode) == buttonCode);
    else
        return (_oldKeyboardData.keyState[buttonCode] ^ _keyboardData.keyState[buttonCode]) && !_keyboardData.keyState[buttonCode];
}
int Cl_GetLastButton()
{
    char lk;
    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_GetLastButton] Cl is not initialized");
    lk = _lastKey;
    _lastKey = 0;
    return lk;
}
void Cl_ProcessEvents()
{
    /*DWORD nbEvents = 0;
    DWORD readEvents = 0;
    INPUT_RECORD* eventBuffer = NULL;
    unsigned int i;
    int j;

    if (!_initialized)
        Cl_Debug(Fatal, "[Cl_ProcessEvents] Cl is not initialized");

    _oldKeyboardData = _keyboardData;
    _oldMouseData = _mouseData;

    GetNumberOfConsoleInputEvents(_hStdin, &nbEvents);

    if (nbEvents == 0)
        return;

    eventBuffer = (INPUT_RECORD*)malloc(nbEvents * sizeof(INPUT_RECORD));

    ReadConsoleInputA(_hStdin, eventBuffer, nbEvents, &readEvents);

    for (i = 0; i < readEvents; i++)
    {
        if (eventBuffer[i].EventType == KEY_EVENT)
        {
            if (eventBuffer[i].Event.KeyEvent.wRepeatCount == 1)
            {
                _keyboardData.controlKeyState = eventBuffer[i].Event.KeyEvent.dwControlKeyState;
                _keyboardData.keyState[eventBuffer[i].Event.KeyEvent.wVirtualKeyCode] = eventBuffer[i].Event.KeyEvent.bKeyDown;
                _lastKey = (char)eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
            }
            if (_textInput.state == 1 && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
            {
                int keyCode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
                int charCode = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
                switch (keyCode)
                {
                    case VK_BACK: // Backspace
                        if (_textInput.cursorX > 0)
                        {
                            _textInput.cursorX--;
                            _textInput.textLength--;
                            for (j = _textInput.cursorX; j < _textInput.textLength; j++)
                                *(_textInput.text + j) = *(_textInput.text + j + 1);
                            _textInput.text = (char*)realloc(_textInput.text, _textInput.textLength + 1);
                            *(_textInput.text + _textInput.textLength) = 0;
                        }
                        break;
                    case VK_DELETE:
                        if (_textInput.cursorX < _textInput.textLength)
                        {
                            _textInput.textLength--;
                            for (j = _textInput.cursorX; j < _textInput.textLength; j++)
                                *(_textInput.text + j) = *(_textInput.text + j + 1);
                            _textInput.text = (char*)realloc(_textInput.text, _textInput.textLength + 1);
                            *(_textInput.text + _textInput.textLength) = 0;
                        }
                        break;
                    case VK_RETURN: // Enter
                        _textInput.state = 0;
                        break;
                    case VK_LEFT:
                        if (_textInput.cursorX > 0)
                            _textInput.cursorX--;
                        break;
                    case VK_RIGHT:
                        if (_textInput.cursorX < _textInput.textLength)
                            _textInput.cursorX++;
                        break;
                    case VK_HOME:
                        _textInput.cursorX = 0;
                        break;
                    case VK_END:
                        _textInput.cursorX = _textInput.textLength;
                        break;
                    default:
                        if (charCode >= 0x20 ||
                            (keyCode >= 48 && keyCode <= 90) ||
                            (keyCode >= 219 && keyCode <= 223 && keyCode != 221) ||
                            keyCode == 186 || keyCode == 192) // Displayable chars
                        {
                            _textInput.cursorX++;
                            _textInput.textLength++;
                            _textInput.text = (char*)realloc(_textInput.text, _textInput.textLength + 1);
                            for (j = _textInput.textLength - 1; j >= _textInput.cursorX; j--)
                                *(_textInput.text + j) = *(_textInput.text + j - 1);
                            *(_textInput.text + _textInput.cursorX - 1) = charCode;
                            *(_textInput.text + _textInput.textLength) = 0;
                        }
                }
            }
        }
        else if (eventBuffer[i].EventType == MOUSE_EVENT)
        {
            if (eventBuffer[i].Event.MouseEvent.dwEventFlags < 2)
            {
                _mouseData = eventBuffer[i].Event.MouseEvent;
            }
            else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 4)
            {
                if (eventBuffer[i].Event.MouseEvent.dwButtonState & 0xFF000000)
                    _mouseWheel++;
                else
                    _mouseWheel--;
            }
        }
    }

    free(eventBuffer);*/

    _oldKeyboardData = _keyboardData;
    _oldMouseData = _mouseData;

    memcpy(_keyboardData.keyState, keyBuffer, 256);
}

// Animations
Animation* Cl_CreateAnimation(char* fileName, short width, short height)
{
    Animation* animation = (Animation*)malloc(sizeof(Animation));
    animation->width = width;
    animation->height = height;
    animation->currentFrame = NULL;

    animation->animationFile = fopen(fileName, "w+");
    if (!animation->animationFile)
    {
        Cl_Debug(Error, "[Cl_CreateAnimation] Unable to open the file %s", fileName);
        return NULL;
    }

    fputc(0x02, animation->animationFile); // Version 2
    fputc(width, animation->animationFile);
    fputc(height, animation->animationFile);

    return animation;
}
Animation* Cl_LoadAnimation(char* fileName)
{
    Animation* animation = (Animation*)malloc(sizeof(Animation));
    animation->animationFile = fopen(fileName, "r");
    if (!animation->animationFile)
    {
        Cl_Debug(Error, "[Cl_LoadAnimation] Unable to open the file %s", fileName);
        return NULL;
    }

    if (fgetc(animation->animationFile) != 2)
    {
        Cl_Debug(Error, "[Cl_LoadAnimation] Animation version of %s is not supported", fileName);
        return NULL;
    }
    animation->width = fgetc(animation->animationFile);
    animation->height = fgetc(animation->animationFile);
    animation->currentFrame = Cl_Buffer(animation->width, animation->height);
    Cl_ReadFrame(animation);

    return animation;
}
void Cl_ReadFrame(Animation* animation)
{
    int x, y, c, a, t, i;
    if (!animation)
    {
        Cl_Debug(Warning, "[Cl_ReadFrame] Animation cannot be null");
        return;
    }
    if (!animation->animationFile)
        return;

    switch (fgetc(animation->animationFile))
    {
        case ANIM_FULLFRAME:
            for (y = 0; y < animation->height; y++)
                for (x = 0; x < animation->width; x++)
                {
                    c = fgetc(animation->animationFile);
                    a = fgetc(animation->animationFile);
                    Cl_DrawChar(animation->currentFrame, c, x, y, a);
                }
            break;
        case ANIM_PARTFRAME:
            t = fgetc(animation->animationFile);
            t += fgetc(animation->animationFile) * 256;
            for (i = 0; i < t; i++)
            {
                x = fgetc(animation->animationFile);
                y = fgetc(animation->animationFile);
                c = fgetc(animation->animationFile);
                a = fgetc(animation->animationFile);
                Cl_DrawChar(animation->currentFrame, c, x, y, a);
            }
            break;
        default:
            fclose(animation->animationFile);
            animation->animationFile = NULL;
            Cl_Debug(Error, "[Cl_ReadFrame] Animation file is corrupted");
            return;
    }
}
void Cl_WriteFrame(Animation* animation, Buffer* buffer)
{
    int frameType, diffCount = 0, x, y;
    CHAR_INFO lastCi, curCi;
    if (!animation)
    {
        Cl_Debug(Warning, "[Cl_WriteFrame] Animation cannot be null");
        return;
    }
    if (!buffer)
    {
        Cl_Debug(Warning, "[Cl_WriteFrame] Buffer cannot be null");
        return;
    }

    /*if (!animation->currentFrame)
        frameType = ANIM_FULLFRAME;
    else
    {
        for (y = 0; y < animation->height; y++)
            for (x = 0; x < animation->width; x++)
            {
                lastCi = Cl_GetCharInfo(animation->currentFrame, x, y);
                curCi = Cl_GetCharInfo(buffer, x, y);
                if (lastCi.Attributes != curCi.Attributes || lastCi.Char.AsciiChar != curCi.Char.AsciiChar)
                    diffCount++;
            }
            if (diffCount > animation->width * animation->height)
                frameType = ANIM_FULLFRAME;
            else
                frameType = ANIM_PARTFRAME;
    }*/
    frameType = ANIM_FULLFRAME;

    switch (frameType)
    {
        case ANIM_PARTFRAME:
            fputc(ANIM_PARTFRAME, animation->animationFile);
            fputc(diffCount % 256, animation->animationFile);
            fputc(diffCount / 256, animation->animationFile);
            for (y = 0; y < animation->height; y++)
                for (x = 0; x < animation->width; x++)
                {
                    lastCi = Cl_GetCharInfo(animation->currentFrame, x, y);
                    curCi = Cl_GetCharInfo(buffer, x, y);
                    if (lastCi.Attributes != curCi.Attributes || lastCi.AsciiChar != curCi.AsciiChar)
                    {
                        fputc(x, animation->animationFile);
                        fputc(y, animation->animationFile);
                        fputc(curCi.AsciiChar, animation->animationFile);
                        fputc(curCi.Attributes % 256, animation->animationFile);
                    }
                }
            break;
        case ANIM_FULLFRAME:
            fputc(ANIM_FULLFRAME, animation->animationFile);
            for (y = 0; y < animation->height; y++)
                for (x = 0; x < animation->width; x++)
                {
                    curCi = Cl_GetCharInfo(buffer, x, y);
                    fputc(curCi.AsciiChar, animation->animationFile);
                    fputc(curCi.Attributes % 256, animation->animationFile);
                }
            break;
    }
    
    if (!animation->currentFrame)
        animation->currentFrame = Cl_Buffer(animation->width, animation->height);
    Cl_FillBuffer(animation->currentFrame, 0, 0, 0, animation->width, animation->height, 0);
    Cl_CopyBuffer(animation->currentFrame, buffer, 0, 0, animation->width, animation->height, 0, 0);
}
