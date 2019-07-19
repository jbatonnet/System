#include <System/System.h>

#include "EditorApplication.h"

using namespace System::Interface;
using namespace System::Graphics;

void EditorApplication_Main()
{
    EditorApplication app;
    app.Start();

    for (;;)
        Timer::Sleep(1000);
}

void EditorApplication::Start(string parameters)
{
    Window *window;
    TabContainer *container;

    Timer::Sleep(1500); // FIXME
    
    // Window
    window = new Window("Editor");
    window->Position = Point(420, 64);
    window->Size = Point(720, 480);
    window->BackColor = 0xE4E9EB;

    // Tabs
    window->Add(container = new TabContainer());
    container->Dock = DockStyle::Full;
    container->Size = window->Size;

    WindowsManager::Add(window);

    // Loop
    for (u32 i = 0;; i++)
    {
        Timer::Sleep(100);
    }
}