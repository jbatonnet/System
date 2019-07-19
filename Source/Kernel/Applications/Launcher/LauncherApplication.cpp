#include "LauncherApplication.h"

#include <Kernel/Kernel.h>
#include <Kernel/Runtime/Threading/Thread.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Runtime;

bool selecting = false;
Point2 selectionStart;
Point2 selectionStop;

Container* selection;

void UpdateSelection()
{
    selection->Visible = selecting;

    if (selecting)
    {
        selection->Position = Point2(Maths::Min(selectionStop.X, selectionStart.X), Maths::Min(selectionStop.Y, selectionStart.Y));
        selection->Size = Point2(Maths::Max(selectionStop.X, selectionStart.X) - selection->Position.X, Maths::Max(selectionStop.Y, selectionStart.Y) - selection->Position.Y);
    }
}

void Window_PointerDown(void* origin, PointerEvent pointerEvent)
{
    selecting = true;
    selectionStop = selectionStart;

    UpdateSelection();
}
void Window_PointerUp(void* origin, PointerEvent pointerEvent)
{
    selecting = false;

    UpdateSelection();
}
void Window_PointerMove(void* origin, PointerPositionEvent pointerMoveEvent)
{
    if (selecting)
        selectionStop = Point2(pointerMoveEvent.X, pointerMoveEvent.Y);
    else
        selectionStart = Point2(pointerMoveEvent.X, pointerMoveEvent.Y);

    UpdateSelection();
}

void TestButton_PointerUp(void* origin, PointerEvent pointerEvent)
{
    //Debugger::Break();
	//Thread::Start(TestApplication_Main, "Test");
}

void LauncherApplication::Start(string parameters)
{
    Window *window;
    Button *clockButton;

    // Window
    window = new Window("Launcher");
    window->Layer = WindowLayer::Bottom;
    window->BackColor = 0x627D93;
    window->PointerDown += Window_PointerDown;
    window->PointerUp += Window_PointerUp;
    window->PointerMove += Window_PointerMove;

    // Clock
    window->Add(clockButton = new Button("--:--"));
    clockButton->Size = Point(80, 40, SizeUnit::Pixel);
    clockButton->Position = Point(window->Size.X - clockButton->Size.X, window->Size.Y - clockButton->Size.Y);
    clockButton->Dock = DockStyle::BottomRight;
    clockButton->Color = Colors::Black;

    // Selection
    window->Add(selection = new Container());
    selection->Visible = false;
    selection->BackColor = 0xC0FFFFFF;

    #pragma region Apps

    {
        Button* testButton = new Button("Test");
        testButton->Position = Point(0, 40);
        testButton->Size = Point(128, 40);
        //testButton->Dock = DockStyle::TopFull;
        testButton->PointerUp += TestButton_PointerUp; // [](auto o, auto e) { Thread::Start(TestApplication_Main, "Test"); };
        window->Add(testButton);
    }

    {
        Button* breakoutButton = new Button("Breakout");
        breakoutButton->Position = Point(0, 80);
        breakoutButton->Size = Point(128, 40);
        //breakoutButton->Dock = DockStyle::TopFull;
        //breakoutButton->PointerUp += TestButton_PointerUp;
        window->Add(breakoutButton);
    }

    #pragma endregion

    WindowsManager::Add(window);

    for (;;)
    {
        Timer::Sleep(20);

        // Update the clock
        u32 time = Timer::Time();
        clockButton->Text = String::Format("{0:d2}:{1:d2}", time / 60000, (time / 1000) % 60);
    }
}

void LauncherApplication_Main()
{
    LauncherApplication app;
    app.Start();

    for (;;)
        Timer::Sleep(1000);
}