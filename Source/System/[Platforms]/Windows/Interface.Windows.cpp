#ifdef WINDOWS

#include <System/System.h>

using namespace System;
using namespace System::Runtime;
using namespace System::Objects;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Interface;
using namespace System::Graphics;

#undef using
#define _INITIALIZER_LIST_

#include <Windows.h>
#include <Dwmapi.h>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_WINDOWS_COUNT 32

using namespace std;

struct WindowInfo
{
    Window* Window;
    Surface* Surface;
    HWND Hwnd;
};
struct PendingWindowInfo
{
    Window* Window;
};

vector<WindowInfo> windowInfos;
queue<PendingWindowInfo> pendingWindowInfos;

Buttons virtualKeyMapping[0x100] = {
    (Buttons)0x00, (Buttons)0x01, (Buttons)0x02, (Buttons)0x03, (Buttons)0x04, (Buttons)0x05, (Buttons)0x06, (Buttons)0x07, Buttons::Backspace, Buttons::Tab, (Buttons)0x0A, (Buttons)0x0B, (Buttons)0x0C, Buttons::Enter, (Buttons)0x0E, (Buttons)0x0F,
    Buttons::Shift, Buttons::Control, Buttons::Alt, (Buttons)0x13, Buttons::CapsLock, (Buttons)0x15, (Buttons)0x16, (Buttons)0x17, (Buttons)0x18, (Buttons)0x19, (Buttons)0x1A, Buttons::Escape, (Buttons)0x1C, (Buttons)0x1D, (Buttons)0x1E, (Buttons)0x1F,
    Buttons::Space, Buttons::PageUp, Buttons::PageDown, Buttons::End, Buttons::Origin, Buttons::Left, Buttons::Up, Buttons::Right, Buttons::Down, (Buttons)0x29, (Buttons)0x2A, (Buttons)0x2B, (Buttons)0x2C, Buttons::Insert, Buttons::Delete, (Buttons)0x2F,
    Buttons::Digit0, Buttons::Digit1, Buttons::Digit2, Buttons::Digit3, Buttons::Digit4, Buttons::Digit5, Buttons::Digit6, Buttons::Digit7, Buttons::Digit8, Buttons::Digit9, (Buttons)0x3A, (Buttons)0x3B, (Buttons)0x3C, (Buttons)0x3D, (Buttons)0x3E, (Buttons)0x3F,
    (Buttons)0x40, Buttons::A, Buttons::B, Buttons::C, Buttons::D, Buttons::E, Buttons::F, Buttons::G, Buttons::H, Buttons::I, Buttons::J, Buttons::K, Buttons::L, Buttons::M, Buttons::N, Buttons::O,
    Buttons::P, Buttons::Q, Buttons::R, Buttons::S, Buttons::T, Buttons::U, Buttons::V, Buttons::W, Buttons::X, Buttons::Y, Buttons::Z, (Buttons)0x5B, (Buttons)0x5C, (Buttons)0x5D, (Buttons)0x5E, (Buttons)0x5F,
    (Buttons)0x60, (Buttons)0x61, (Buttons)0x62, (Buttons)0x63, (Buttons)0x64, (Buttons)0x65, (Buttons)0x66, (Buttons)0x67, (Buttons)0x68, (Buttons)0x69, (Buttons)0x6A, (Buttons)0x6B, (Buttons)0x6C, (Buttons)0x6D, (Buttons)0x6E, (Buttons)0x6F,
    Buttons::F1, Buttons::F2, Buttons::F3, Buttons::F4, Buttons::F5, Buttons::F6, Buttons::F7, Buttons::F8, Buttons::F9, Buttons::F10, Buttons::F11, Buttons::F12, (Buttons)0x7C, (Buttons)0x7D, (Buttons)0x7E, (Buttons)0x7F,
    (Buttons)0x80, (Buttons)0x81, (Buttons)0x82, (Buttons)0x83, (Buttons)0x84, (Buttons)0x85, (Buttons)0x86, (Buttons)0x87, (Buttons)0x88, (Buttons)0x89, (Buttons)0x8A, (Buttons)0x8B, (Buttons)0x8C, (Buttons)0x8D, (Buttons)0x8E, (Buttons)0x8F,
    Buttons::NumLock, (Buttons)0x91, (Buttons)0x92, (Buttons)0x93, (Buttons)0x94, (Buttons)0x95, (Buttons)0x96, (Buttons)0x97, (Buttons)0x98, (Buttons)0x99, (Buttons)0x9A, (Buttons)0x9B, (Buttons)0x9C, (Buttons)0x9D, (Buttons)0x9E, (Buttons)0x9F,
    Buttons::LeftShift, Buttons::RightShift, Buttons::LeftControl, Buttons::RightControl, (Buttons)0xA4, (Buttons)0xA5, (Buttons)0xA6, (Buttons)0xA7, (Buttons)0xA8, (Buttons)0xA9, (Buttons)0xAA, (Buttons)0xAB, (Buttons)0xAC, (Buttons)0xAD, (Buttons)0xAE, (Buttons)0xAF,
    (Buttons)0xB0, (Buttons)0xB1, (Buttons)0xB2, (Buttons)0xB3, (Buttons)0xB4, (Buttons)0xB5, (Buttons)0xB6, (Buttons)0xB7, (Buttons)0xB8, (Buttons)0xB9, (Buttons)0xBA, (Buttons)0xBB, (Buttons)0xBC, (Buttons)0xBD, (Buttons)0xBE, (Buttons)0xBF,
    (Buttons)0xC0, (Buttons)0xC1, (Buttons)0xC2, (Buttons)0xC3, (Buttons)0xC4, (Buttons)0xC5, (Buttons)0xC6, (Buttons)0xC7, (Buttons)0xC8, (Buttons)0xC9, (Buttons)0xCA, (Buttons)0xCB, (Buttons)0xCC, (Buttons)0xCD, (Buttons)0xCE, (Buttons)0xCF,
    (Buttons)0xD0, (Buttons)0xD1, (Buttons)0xD2, (Buttons)0xD3, (Buttons)0xD4, (Buttons)0xD5, (Buttons)0xD6, (Buttons)0xD7, (Buttons)0xD8, (Buttons)0xD9, (Buttons)0xDA, (Buttons)0xDB, (Buttons)0xDC, (Buttons)0xDD, (Buttons)0xDE, (Buttons)0xDF,
    (Buttons)0xE0, (Buttons)0xE1, (Buttons)0xE2, (Buttons)0xE3, (Buttons)0xE4, (Buttons)0xE5, (Buttons)0xE6, (Buttons)0xE7, (Buttons)0xE8, (Buttons)0xE9, (Buttons)0xEA, (Buttons)0xEB, (Buttons)0xEC, (Buttons)0xED, (Buttons)0xEE, (Buttons)0xEF,
    (Buttons)0xF0, (Buttons)0xF1, (Buttons)0xF2, (Buttons)0xF3, (Buttons)0xF4, (Buttons)0xF5, (Buttons)0xF6, (Buttons)0xF7, (Buttons)0xF8, (Buttons)0xF9, (Buttons)0xFA, (Buttons)0xFB, (Buttons)0xFC, (Buttons)0xFD, (Buttons)0xFE, (Buttons)0xFF
};

WNDCLASSEX windowClass;
POINT clientOffset, nonClientSize;

#define DOUBLE_BUFFER 0

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto result = find_if(windowInfos.begin(), windowInfos.end(), [=](WindowInfo w) { return w.Hwnd == hwnd; });
    if (result == windowInfos.end())
        return DefWindowProc(hwnd, msg, wParam, lParam);

    WindowInfo& windowInfo = *result;
    Window* window = windowInfo.Window;
    Surface* surface = windowInfo.Surface;
    
    int captionHeight = 23;

    switch (msg)
    {
        #pragma region Mouse

        case WM_MOUSEMOVE:
        {
            PointerPositionEvent pointerPositionEvent;
            pointerPositionEvent.Index = 0;
            pointerPositionEvent.X = LOWORD(lParam);
            pointerPositionEvent.Y = HIWORD(lParam);

            window->OnPointerMove(window, pointerPositionEvent);
            break;
        }

        case WM_RBUTTONDOWN:
        {
            SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL);

            break;
        }
        case WM_LBUTTONDOWN:
        {
            PointerEvent pointerEvent;
            pointerEvent.Index = 0;

            window->OnPointerDown(window, pointerEvent);

            break;
        }

        case WM_RBUTTONUP:
        {
            break;
        }
        case WM_LBUTTONUP:
        {
            PointerEvent pointerEvent;
            pointerEvent.Index = 0;

            window->OnPointerUp(window, pointerEvent);
            break;
        }

        case WM_MOUSELEAVE:
        {
            break;
        }

        case WM_MOUSEWHEEL:
        {
            PointerScrollEvent pointerScrollEvent;
            pointerScrollEvent.Index = 0;
            pointerScrollEvent.Delta = -GET_WHEEL_DELTA_WPARAM(wParam) / 120;

            window->OnPointerScroll(window, pointerScrollEvent);
            break;
        }

        #pragma endregion
        #pragma region Keyboard

        case WM_CHAR:
        {
            if (wParam < 32)
                break;

            ButtonEvent buttonEvent;
            buttonEvent.Button = Buttons::Unknown;
            buttonEvent.Character = (char)wParam;

            bool pressed = !(lParam >> 31);

            if (pressed)
                window->OnButtonDown(window, buttonEvent);
            else
                window->OnButtonUp(window, buttonEvent);

            return 0;
        }

        case WM_KEYDOWN:
        {
            Buttons button = virtualKeyMapping[wParam];
            if ((WPARAM)button == wParam)
                break;

            u32 character = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);
            if (!character || character < 32)
            {
                ButtonEvent buttonEvent;
                buttonEvent.Button = button;
                buttonEvent.Character = 0;

                window->OnButtonDown(window, buttonEvent);
            }

            return 0;
        }
        case WM_KEYUP:
        {
            Buttons button = virtualKeyMapping[wParam];
            if ((WPARAM)button == wParam)
                break;

            ButtonEvent buttonEvent;
            buttonEvent.Button = button;
            buttonEvent.Character = 'a';

            window->OnButtonUp(window, buttonEvent);

            return 0;
        }

        case WM_SYSKEYDOWN:
        {
            Buttons button = virtualKeyMapping[wParam];
            if ((WPARAM)button == wParam)
                break;

            ButtonEvent buttonEvent;
            buttonEvent.Button = button;
            buttonEvent.Character = 0;

            window->OnButtonDown(window, buttonEvent);

            return 0;
        }
        case WM_SYSKEYUP:
        {
            Buttons button = virtualKeyMapping[wParam];
            if ((WPARAM)button == wParam)
                break;

            ButtonEvent buttonEvent;
            buttonEvent.Button = button;
            buttonEvent.Character = 0;

            window->OnButtonUp(window, buttonEvent);

            return 0;
        }

        #pragma endregion
        #pragma region Window

        case WM_CREATE:
        {
            RECT rect;
            rect.left = window->Position.X;
            rect.top = window->Position.Y;
            rect.right = window->Position.X + window->Size.X;
            rect.bottom = window->Position.Y + window->Size.Y;

            AdjustWindowRect(&rect, WS_POPUP, false);
            SetWindowPos(hwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOREPOSITION | SWP_NOMOVE);

            BufferedPaintInit();

            break;
        }

        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            exit(0); // FIXME

            break;
        }

        case WM_SIZE:
        {
            s16 width = LOWORD(lParam);
            s16 height = HIWORD(lParam);

            window->Size = Point2(width, height);

            delete surface;
            windowInfo.Surface = new Surface(window->Size.X, window->Size.Y);

            InvalidateRect(hwnd, NULL, false);
            UpdateWindow(hwnd);

            break;
        }

        #pragma endregion
        #pragma region Non-client

        case WM_NCPAINT:
        {
            //DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
            //DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, (void*)&policy, sizeof(DWMNCRENDERINGPOLICY));

            MARGINS margins = { 1, 1, 1, 1 };
            DwmExtendFrameIntoClientArea(hwnd, &margins);

            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        case WM_NCCALCSIZE:
            break;

        #pragma endregion

        case WM_ERASEBKGND:
            return 1;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc, hdcBuffer;
            HGDIOBJ oldBitmap;
            BITMAP bitmap;
            HBITMAP hBitmap;
            HPAINTBUFFER hPaintBuffer;

            window->Redraw(surface, System::Graphics::Rectangle(Point2::Zero, window->Size));

#if DOUBLE_BUFFER
            hdc = GetWindowDC(hwnd);
#else
            hdc = BeginPaint(hwnd, &ps);
            hdcBuffer = CreateCompatibleDC(hdc);
#endif

            RECT rect;
            GetClientRect(hwnd, &rect);

#if DOUBLE_BUFFER
            hPaintBuffer = BeginBufferedPaint(hdc, &rect, BPBF_COMPATIBLEBITMAP, NULL, &hdcBuffer);
            BufferedPaintMakeOpaque(hPaintBuffer, NULL);
#endif

            hBitmap = CreateBitmap(window->Size.X, window->Size.Y, 1, 32, surface->Data);
            oldBitmap = SelectObject(hdcBuffer, hBitmap);

            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBuffer, 0, 0, SRCCOPY);

            SelectObject(hdcBuffer, oldBitmap);
            DeleteObject(hBitmap);

#if DOUBLE_BUFFER
            BufferedPaintMakeOpaque(hPaintBuffer, NULL);
            EndBufferedPaint(hPaintBuffer, TRUE);

            ReleaseDC(hwnd, hdc);
#else
            EndPaint(hwnd, &ps);
#endif
            break;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

HWND GetHwndByWindow(Window* window)
{
    auto result = find_if(windowInfos.begin(), windowInfos.end(), [=](WindowInfo w) { return w.Window == window; });
    if (result == windowInfos.end())
        return NULL;

    return result->Hwnd;
}

void Window_PositionChanged(void* origin, ChangeEventParameter<Point> args)
{
    HWND hwnd = GetHwndByWindow((Window*)origin);
    SetWindowPos(hwnd, NULL, args.NewValue.X, args.NewValue.Y, 0, 0, SWP_NOREPOSITION | SWP_NOSIZE);
}
void Window_SizeChanged(void* origin, ChangeEventParameter<Point> args)
{
    HWND hwnd = GetHwndByWindow((Window*)origin);
    SetWindowPos(hwnd, NULL, 0, 0, args.NewValue.X, args.NewValue.Y, SWP_NOREPOSITION | SWP_NOMOVE);
}
void Window_Refreshed(void* origin, System::Graphics::Rectangle rectangle)
{
    Window* window = (Window*)origin;
    HWND hwnd = GetHwndByWindow(window);
    RECT rect = { 0 };

    /*rect.left = rectangle.Position.X;
    rect.top = rectangle.Position.Y;
    rect.right = rectangle.Position.X + rectangle.Size.X;
    rect.bottom = rectangle.Position.Y + rectangle.Size.Y;*/

    rect.left = 0;
    rect.top = 0;
    rect.right = window->Size.X;
    rect.bottom = window->Size.Y;

    InvalidateRect(hwnd, &rect, true);
}

DWORD WINAPI WindowsManager_Loop(LPVOID parameter)
{
    MSG msg;

    for (;;)
    {
        // Handle window creation requests
        while (!pendingWindowInfos.empty())
        {
            PendingWindowInfo pendingWindow = pendingWindowInfos.front();
            pendingWindowInfos.pop();

            // Create the Window
            Window* window = pendingWindow.Window;
            HWND hwnd = CreateWindow("myWindowClass", "", WS_OVERLAPPEDWINDOW, window->Position.X, window->Position.Y, window->Size.X, window->Size.Y, NULL, NULL, NULL, NULL);
            Surface* surface = new Surface(window->Size.X, window->Size.Y);

            // Register to window events
            window->PositionChanged += Window_PositionChanged;
            window->SizeChanged += Window_SizeChanged;
            window->Refreshed += Window_Refreshed;
            //window->Initialize();

            // Adjust the newly created window
            /*RECT rect;
            rect.left = window->Position.X;
            rect.top = window->Position.Y;
            rect.right = window->Position.X + window->Size.X;
            rect.bottom = window->Position.Y + window->Size.Y;

            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);*/

            // Register the new window
            WindowInfo windowInfo;
            windowInfo.Window = window;
            windowInfo.Surface = surface;
            windowInfo.Hwnd = hwnd;

            windowInfos.push_back(windowInfo);

            // Show window
            SetWindowPos(hwnd, NULL, 0, 0, window->Size.X + nonClientSize.x, window->Size.Y + nonClientSize.y, SWP_NOREPOSITION | SWP_NOMOVE);
            ShowWindow(hwnd, SW_SHOW);

            // Force first draw
            InvalidateRect(hwnd, NULL, true);
            UpdateWindow(hwnd);
        }

        // Handle messages
        if (!windowInfos.empty())
        {
            for (int i = 0; i < 1024; i++)
            {
                if (GetMessage(&msg, NULL, 0, 0) > 0)
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
    }

    return 0;
}

void WindowsManager::Initialize()
{
    // Compute non client sizes
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = 0;
    rect.bottom = 0;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    clientOffset.x = -rect.left;
    clientOffset.y = -rect.top;
    nonClientSize.x = rect.right - rect.left;
    nonClientSize.y = rect.bottom - rect.top;

    // Register a new window class
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = 0;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL; // (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = "myWindowClass";
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&windowClass))
        Exception::Assert("Could not register window class");
    
    // Start the window loop thread
    DWORD threadId;
    HANDLE threadHandle = CreateThread(NULL, 0, WindowsManager_Loop, NULL, 0, &threadId);
}
void WindowsManager::Add(Window* window)
{
    int index = 0;

    // Check for existing window
    if (find_if(windowInfos.begin(), windowInfos.end(), [=](WindowInfo w) { return w.Window == window; }) != windowInfos.end())
        return;

    // Push a new window creation request
    PendingWindowInfo pendingWindow;
    pendingWindow.Window = window;
    pendingWindowInfos.push(pendingWindow);

    // Wait for window creation
    for (;;)
    {
        Sleep(20);

        auto result = find_if(windowInfos.begin(), windowInfos.end(), [=](WindowInfo w) { return w.Window == window; });
        if (result != windowInfos.end())
            return;
    }
}
void WindowsManager::Remove(Window* window)
{
    HWND hwnd = GetHwndByWindow(window);
    DestroyWindow(hwnd);

    window->Closed(window, null);
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
    HWND hwnd = GetHwndByWindow(window);

    SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL);
}
void Mover::OnPointerUp(void* origin, PointerEvent pointerEvent)
{
}

#endif