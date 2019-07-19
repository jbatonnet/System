#include <System/Interface/WindowsManager.h>
#include <System/Interface/Window.h>
#include <System/Utilities/Time/Timer.h>
#include <Kernel/Runtime/Threading/Task.h>
#include <System/Runtime/Threading/Mutex.h>
#include <System/Maths/Maths.h>

#include <System/Debugging/Serial.h>
#include <System/Debugging/Console.h>
#include <System/Runtime/Debugging/Debugger.h>

#include <HAL/IO.h>

#include <Kernel/Devices/DeviceManager.h>
#include <System/Devices/Device.h>
#include <System/Devices/Display/DisplayDevice.h>
//#include <Kernel/Devices/Drivers/VMware/Tools/Backdoor.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;
using namespace System::Runtime;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define RENDER (!DEBUG_TASKING)
#define FLASH_REDRAW 0
#define SLOW_REDRAW 0

#define BACKCOLOR 0x808080
#define BORDER 24
#define SHADOW_INTENSITY 2 / 3

Mutex windowsMutex,
      refreshesMutex;
Spinlock windowsSpinlock,
         refreshesSpinlock;

List<Window*> windows;
List<Rectangle> refreshes;
Window* focusedWindow;

Window* movingWindow;
Point2 moveStart, windowStart;

u16 pointerX = 0,
    pointerY = 0;

Surface* buffer;
Surface* cursor;

void Refresh(Rectangle rectangle)
{
    // Out of screen
    if (rectangle.Position.X + rectangle.Size.X < 0) return;
    if (rectangle.Position.Y + rectangle.Size.Y < 0) return;

    // Screen clamping
    if (rectangle.Position.X < 0) { rectangle.Size.X += rectangle.Position.X; rectangle.Position.X = 0; }
    if (rectangle.Position.Y < 0) { rectangle.Size.Y += rectangle.Position.Y; rectangle.Position.Y = 0; }
    if (rectangle.Position.X + rectangle.Size.X > SCREEN_WIDTH) { rectangle.Size.X = SCREEN_WIDTH - rectangle.Position.X; }
    if (rectangle.Position.Y + rectangle.Size.Y > SCREEN_HEIGHT) { rectangle.Size.Y = SCREEN_HEIGHT - rectangle.Position.Y; }

    // Rectangles merging
    bool found = false;
    for (u32 i = 0; i < refreshes.Count; i++)
    {
        Rectangle& original = refreshes[i];

        if (original.Position.X > rectangle.Position.X + rectangle.Size.X) continue;
        if (original.Position.X + original.Size.X < rectangle.Position.X) continue;
        if (original.Position.Y > rectangle.Position.Y + rectangle.Size.Y) continue;
        if (original.Position.Y + original.Size.Y < rectangle.Position.Y) continue;

        //Serial::WriteLine("Original: { X: {0}, Y: {1}, W: {2}, H: {3} }", original.Position.X, original.Position.Y, original.Size.X, original.Size.Y);

        Rectangle merged = original;

        merged.Position.X = Maths::Min(original.Position.X, rectangle.Position.X);
        merged.Size.X = Maths::Max(original.Position.X + original.Size.X, rectangle.Position.X + rectangle.Size.X) - merged.Position.X;
        merged.Position.Y = Maths::Min(original.Position.Y, rectangle.Position.Y);
        merged.Size.Y = Maths::Max(original.Position.Y + original.Size.Y, rectangle.Position.Y + rectangle.Size.Y) - merged.Position.Y;

        //Serial::WriteLine("Merged: { X: {0}, Y: {1}, W: {2}, H: {3} }", merged.Position.X, merged.Position.Y, merged.Size.X, merged.Size.Y);

        refreshes[i] = merged;
        found = true;
        break;
    }

    if (!found)
        refreshes.Add(rectangle);
}

void Window_Refreshed(void* sender, Rectangle rectangle)
{
    //lock (refreshesSpinlock)
        Refresh(rectangle);
}
void Window_StateChanged(void* origin, WindowState oldState)
{
}
void Window_LayerChanged(void* origin, WindowLayer oldLayer)
{
}
void Window_PositionChanged(void* sender, ChangeEventParameter<Point> position)
{
    Window* window = (Window*)sender;

    Refresh(Rectangle(position.OldValue.X, position.OldValue.Y, window->Size.X, window->Size.Y).Expand(BORDER));
    Refresh(Rectangle(position.NewValue.X, position.NewValue.Y, window->Size.X, window->Size.Y).Expand(BORDER));
}
void Window_SizeChanged(void* sender, ChangeEventParameter<Point> size)
{
}

void WindowsManager_PointerMove(void* origin, PointerPositionEvent pointerPositionEvent)
{
    //lock (windowsMutex)
    {
        for (u32 i = 0; i < windows.Count; i++)
        {
            Window* window = windows[i];

            bool wasPointed = window->pointed;
            bool isPointed = !(pointerPositionEvent.X < window->Position.X || pointerPositionEvent.X > window->Position.X + window->Size.X || pointerPositionEvent.Y < window->Position.Y || pointerPositionEvent.Y > window->Position.Y + window->Size.Y);

            PointerPositionEvent pointerSubPositionEvent = pointerPositionEvent;
            pointerSubPositionEvent.X -= window->Position.X;
            pointerSubPositionEvent.Y -= window->Position.Y;

            if (!wasPointed && isPointed)
            {
                window->PointerIn(origin, pointerPositionEvent);
                window->PointerMove(origin, pointerSubPositionEvent);
            }
            else if (wasPointed && isPointed)
                window->PointerMove(origin, pointerSubPositionEvent);
            else if (wasPointed && !isPointed)
                window->PointerOut(origin, pointerPositionEvent);

            window->pointed = isPointed;

            if (window == movingWindow)
                ;// window->Position = Point2(windowStart.X + (InputManager::PointerPosition.X - moveStart.X), windowStart.Y + (InputManager::PointerPosition.Y - moveStart.Y));
        }
    }

    pointerX = pointerPositionEvent.X;
    pointerY = pointerPositionEvent.Y;
}
void WindowsManager_PointerDown(void* origin, PointerEvent pointerEvent)
{
    Log::WriteLine(Log::Debug, "WindowsManager_PointerDown");

    //lock (windowsMutex)
    {
        for (s32 i = windows.Count - 1; i >= 0; i--)
        {
            Window* window = windows[i];
            if (window->pointed)
                window->PointerDown(origin, pointerEvent);

            if (window->pointed && window->Layer != WindowLayer::Bottom)
            {
                movingWindow = window;
                moveStart = InputManager::PointerPosition;
                windowStart = window->Position;

                focusedWindow = window;
                windows.SendToBack(i);
                break;
            }
        }
    }
}
void WindowsManager_PointerUp(void* origin, PointerEvent pointerEvent)
{
    Log::WriteLine(Log::Debug, "WindowsManager_PointerUp");

    movingWindow = false;

    for (u32 i = 0; i < windows.Count; i++)
    {
        Window* window = windows[i];
        if (window->pointed)
            window->PointerUp(origin, pointerEvent);
    }
}

void WindowsManager_ButtonDown(void* origin, ButtonEvent buttonEvent)
{
    //Serial::WriteLine("Button: {0}", (u8)buttonEvent.Button);

    for (u32 i = 0; i < windows.Count; i++)
    {
        Window* window = windows[i];
        //if (window->focused)
            window->ButtonDown(origin, buttonEvent);
    }
}
void WindowsManager_ButtonUp(void* origin, ButtonEvent buttonEvent)
{
    for (u32 i = 0; i < windows.Count; i++)
    {
        Window* window = windows[i];
        //if (window->focused)
            window->ButtonUp(origin, buttonEvent);
    }
}

#pragma optimize("", off)

void WindowsManager_Loop()
{
    DisplayDevice* displayDevice;
    DisplayMode* displayMode;
    Surface* screen;

    Log::WriteLine(Log::Trace, "T{0} : WindowsManager::Loop", Task::Current->id);

    //Thread::Current->Dispatcher = new Dispatcher();

    lock (windowsSpinlock)
    {
        //windows = List<Window*>(32);
        refreshes = List<Rectangle>(256);

#if RENDER
        displayDevice = DeviceManager::GetDevice<DisplayDevice>();

        // Find display mode
        displayMode = displayDevice->FindDisplayMode(1280, 720, 32, false);
#else
        DisplayMode _displayMode;
        displayMode = &_displayMode;

        displayMode->Width = 1280;
        displayMode->Height = 720;
#endif

        Console::WriteLine("DisplayMode: {0}x{1}", displayMode->Width, displayMode->Height);

        // Create buffer
        buffer = new Surface(displayMode->Width, displayMode->Height);
        cursor = new Surface(16, 24);

#if RENDER
        // Setup display mode
        displayDevice->SetDisplayMode(displayMode);

        // Clear screen
        screen = displayDevice->GetSurface();
        screen->Clear(Colors::DarkGray);
        displayDevice->Update();
#endif

        Refresh(Rectangle(0, 0, displayMode->Width, displayMode->Height));

        InputManager::PointerMove += WindowsManager_PointerMove;
        InputManager::PointerDown += WindowsManager_PointerDown;
        InputManager::PointerUp += WindowsManager_PointerUp;

        InputManager::ButtonDown += WindowsManager_ButtonDown;
        InputManager::ButtonUp += WindowsManager_ButtonUp;
    }

    u16 lastPointerX = 0, lastPointerY = 0;
    for (u32 n = 0;; n++)
    {
        //Thread::Current->Dispatcher->Flush();

        // Cursor update
        u16 pointerX = InputManager::PointerPosition.X,
            pointerY = InputManager::PointerPosition.Y;
        bool pointerMoved = pointerX != lastPointerX || pointerY != lastPointerY;

        // VSync
#if RENDER
        //displayDevice->VSync->Wait(33); // Wait 33ms if no vSync
#if SLOW_REDRAW
        Timer::Sleep(n % 2 ? 50 : 500);
#endif
#else
        Log::WriteLine(Log::Trace, "WindowsManager::Loop : Update {0}", n);
#endif

        // Interface update
        if (true)
        {
            for (u32 j = 0; j < windows.Count; j++)
            {
                Window* window = windows[j];
                Window_Refreshed(null, Rectangle(window->Position, window->Size).Expand(BORDER));
            }
        }

        //Refresh(Rectangle(0, 0, videoWidth, videoHeight));

        if (refreshes.Count)
        {
            refreshesSpinlock.Lock();

            // Draw loop
            for (u32 i = 0; i < refreshes.Count; i++)
            {
                Rectangle& rectangle = refreshes[i];
                buffer->FillRectangle(rectangle.Position.X, rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y, BACKCOLOR);

                //Log::WriteLine(Log::Debug, "Updating region { X: {0}, Y: {1}, Width: {2}, Height: {3} }", rectangle.Position.X, rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y);

                for (u32 j = 0; j < windows.Count; j++)
                {
                    Window* window = windows[j];

                    //Log::WriteLine(Log::Debug, "Testing window { X: {0}, Y: {1}, Width: {2}, Height: {3} }", window->Position.X, window->Position.Y, window->Size.X, window->Size.Y);

                    if (window->Position.X > rectangle.Position.X + rectangle.Size.X) continue;
                    if (window->Position.X + window->Size.X < rectangle.Position.X) continue;
                    if (window->Position.Y > rectangle.Position.Y + rectangle.Size.Y) continue;
                    if (window->Position.Y + window->Size.Y < rectangle.Position.Y) continue;

                    Rectangle& refresh = refreshes[i];
                    Rectangle rectangle = refresh;

                    rectangle.Position.X = Maths::Max(rectangle.Position.X - window->Position.X, 0);
                    rectangle.Position.Y = Maths::Max(rectangle.Position.Y - window->Position.Y, 0);
                    rectangle.Size.X = Maths::Min(rectangle.Position.X + rectangle.Size.X, window->Size.X) - rectangle.Position.X;
                    rectangle.Size.Y = Maths::Min(rectangle.Position.Y + rectangle.Size.Y, window->Size.Y) - rectangle.Position.Y;

                    //Log::WriteLine(Log::Debug, "Redrawing position { X: {0}, Y: {1}, Width: {2}, Height: {3} }", rectangle.Position.X, rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y);

                    buffer->FillRectangle(window->Position.X + rectangle.Position.X, window->Position.Y + rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y, window->BackColor);

                    SubSurface subSurface(buffer, window->Position.X, window->Position.Y, window->Size.X, window->Size.Y);
                    window->Redraw(&subSurface, rectangle);

                    if (window->Layer != WindowLayer::Bottom)
                    {
                        // Vertical border
                        {
                            u16 yMin = Maths::Max(refresh.Position.Y, window->Position.Y),
                                yMax = Maths::Min(refresh.Position.Y + refresh.Size.Y, window->Position.Y + window->Size.Y);

                            if (yMax >= yMin)
                            {
                                for (u16 i = 0; i < BORDER; i++)
                                {
                                    u16 x = window->Position.X - BORDER + i;
                                    if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X)
                                        buffer->Darken(x, yMin, 1, yMax - yMin, 192 - 1 - i * SHADOW_INTENSITY, 192);

                                    x = window->Position.X + window->Size.X + i;
                                    if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X)
                                        buffer->Darken(x, yMin, 1, yMax - yMin, 192 - BORDER * SHADOW_INTENSITY + i * SHADOW_INTENSITY, 192);
                                }
                            }
                        }

                        // Horizontal border
                        {
                            u16 xMin = Maths::Max(refresh.Position.X, window->Position.X),
                                xMax = Maths::Min(refresh.Position.X + refresh.Size.X, window->Position.X + window->Size.X);

                            if (xMax >= xMin)
                            {
                                for (u16 i = 0; i < BORDER; i++)
                                {
                                    u16 y = window->Position.Y - BORDER + i;
                                    if (y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                        buffer->Darken(xMin, y, xMax - xMin, 1, 192 - 1 - i * SHADOW_INTENSITY, 192);

                                    y = window->Position.Y + window->Size.Y + i;
                                    if (y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                        buffer->Darken(xMin, y, xMax - xMin, 1, 192 - BORDER * SHADOW_INTENSITY + i * SHADOW_INTENSITY, 192);
                                }
                            }
                        }

                        // Top left corner
                        for (u16 y = window->Position.Y - BORDER; y < window->Position.Y; y++)
                            for (u16 x = window->Position.X - BORDER; x < window->Position.X; x++)
                                if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X && y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                {
                                    u16 factor = (BORDER + 2 - (window->Position.Y - y)) * (BORDER + 2 - (window->Position.X - x)) / BORDER;
                                    buffer->Darken(x, y, 1, 1, 192 - factor * SHADOW_INTENSITY, 192);
                                }

                        // Top right corner
                        for (u16 y = window->Position.Y - BORDER; y < window->Position.Y; y++)
                            for (u16 x = window->Position.X + window->Size.X; x < window->Position.X + window->Size.X + BORDER; x++)
                                if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X && y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                {
                                    u16 factor = (BORDER + 2 - (window->Position.Y - y)) * (BORDER + 2 - (x - (window->Position.X + window->Size.X))) / BORDER;
                                    buffer->Darken(x, y, 1, 1, 192 - factor * SHADOW_INTENSITY, 192);
                                }

                        // Bottom right corner
                        for (u16 y = window->Position.Y + window->Size.Y; y < window->Position.Y + window->Size.Y + BORDER; y++)
                            for (u16 x = window->Position.X + window->Size.X; x < window->Position.X + window->Size.X + BORDER; x++)
                                if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X && y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                {
                                    u16 factor = (BORDER + 2 - (y - (window->Position.Y + window->Size.Y))) * (BORDER + 2 - (x - (window->Position.X + window->Size.X))) / BORDER;
                                    buffer->Darken(x, y, 1, 1, 192 - factor * SHADOW_INTENSITY, 192);
                                }

                        // Bottom left corner
                        for (u16 y = window->Position.Y + window->Size.Y; y < window->Position.Y + window->Size.Y + BORDER; y++)
                            for (u16 x = window->Position.X - BORDER; x < window->Position.X; x++)
                                if (x >= refresh.Position.X && x < refresh.Position.X + refresh.Size.X && y >= refresh.Position.Y && y < refresh.Position.Y + refresh.Size.Y)
                                {
                                    u16 factor = (BORDER + 2 - (y - (window->Position.Y + window->Size.Y))) * (BORDER + 2 - (window->Position.X - x)) / BORDER;
                                    buffer->Darken(x, y, 1, 1, 192 - factor * SHADOW_INTENSITY, 192);
                                }
                    }
                }
            }

            if (pointerMoved)
            {
                Refresh(Rectangle(lastPointerX, lastPointerY, cursor->Size.X, cursor->Size.Y));
                Refresh(Rectangle(pointerX, pointerY, cursor->Size.X, cursor->Size.Y));
            }

            cursor->DrawBitmap(pointerX, pointerY, 0, 0, cursor->Size.X, cursor->Size.Y, buffer);
            //buffer->DrawBitmap(0, 0, pointerX, pointerY, cursor->Size.X, cursor->Size.Y, Bitmaps::Cursors::Normal.operator->(), true);

            for (u32 i = 0; i < refreshes.Count; i++)
            {
                Rectangle& rectangle = refreshes[i];
#if RENDER
#if FLASH_REDRAW
                if (n % 2 == 0)
                    screen->FillRectangle(rectangle.Position, rectangle.Size, Colors::Magenta);
                else
#endif
                    screen->DrawBitmap(rectangle.Position, rectangle.Position, rectangle.Size, buffer);

                //displayDevice->Flush(rectangle.Position.X, rectangle.Position.Y, rectangle.Size.X, rectangle.Size.Y);
#endif
            }

            buffer->DrawBitmap(0, 0, pointerX, pointerY, cursor->Size.X, cursor->Size.Y, cursor);

#if FLASH_REDRAW
            if (n % 2)
#endif
                refreshes.Clear();

            refreshesSpinlock.Unlock();

#if RENDER
            displayDevice->Update();
#endif
        }
        else if (pointerMoved)
        {
            cursor->DrawBitmap(pointerX, pointerY, 0, 0, cursor->Size.X, cursor->Size.Y, buffer);
            buffer->DrawBitmap(0, 0, pointerX, pointerY, cursor->Size.X, cursor->Size.Y, Bitmaps::Cursors::Normal.operator->(), true);// Bitmap::Slot[1], true);

#if RENDER
            screen->DrawBitmap(lastPointerX, lastPointerY, lastPointerX, lastPointerY, cursor->Size.X, cursor->Size.Y, buffer);
            //displayDevice->Flush(lastPointerX, lastPointerY, cursor->Size.X, cursor->Size.Y);
            screen->DrawBitmap(pointerX, pointerY, pointerX, pointerY, cursor->Size.X, cursor->Size.Y, buffer);
            //displayDevice->Flush(pointerX, pointerY, cursor->Size.X, cursor->Size.Y);
#endif

            buffer->DrawBitmap(0, 0, pointerX, pointerY, cursor->Size.X, cursor->Size.Y, cursor);

#if RENDER
            displayDevice->Update();
#endif
        }

        lastPointerX = pointerX;
        lastPointerY = pointerY;
    }
}

#pragma optimize("", on)

void WindowsManager::Initialize()
{
    Thread::Start(WindowsManager_Loop, "WindowsManager");
}
void WindowsManager::Add(Window* window)
{
    Log::WriteLine(Log::Trace, "T{0} : WindowsManager::Add : {1}", Task::Current->id, window->Title);

    lock (windowsSpinlock)
    {
        window->Refreshed += Window_Refreshed;
        window->StateChanged += Window_StateChanged;
        window->LayerChanged += Window_LayerChanged;
        window->PositionChanged += Window_PositionChanged;
        //window->SizeChanged += Callback(WindowsManager::Window_PositionChanged);

        window->cachedSurface = new SubSurface(buffer, (u16)window->Position.X, (u16)window->Position.Y, (u16)window->Size.X, (u16)window->Size.Y);
        window->Initialize();
        
        if (window->Layer == WindowLayer::Bottom)
        {
            window->Position = Point::Zero;
            window->Size = buffer->Size; // FIXME
            //windows.BringToFront(windows.IndexOf(window));
        }

        windows.Add(window);
        focusedWindow = window;

        Refresh(Rectangle(window->Position, window->Size).Expand(BORDER));
    }
}
void WindowsManager::Remove(Window* window)
{
    windows.Remove(window);
    window->Refreshed -= Window_Refreshed;

    Refresh(Rectangle(window->Position, window->Size).Expand(BORDER));
}

void Mover::OnPointerMove(void* origin, PointerPositionEvent pointerPositionEvent)
{
}
void Mover::OnPointerIn(void* origin, PointerEvent pointerEvent)
{
}
void Mover::OnPointerOut(void* origin, PointerEvent pointerEvent)
{
}
void Mover::OnPointerDown(void* origin, PointerEvent pointerEvent)
{
}
void Mover::OnPointerUp(void* origin, PointerEvent pointerEvent)
{
}