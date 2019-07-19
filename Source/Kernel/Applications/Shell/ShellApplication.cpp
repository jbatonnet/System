#include <Kernel/Kernel.h>

#include "ShellApplication.h"
#include "ShellControl.h"

using namespace System::Interface;
using namespace System::Graphics;

void Shell_AppMain()
{
    Shell app;
    app.Start();
}

void Shell::Start(string parameters)
{
    Window* window;
    Label* title;
    ShellControl* shell;

    Timer::Sleep(1000); // FIXME
    
    //FontFamily* defaultFontFamily = FontFamily::GetDefaultFamily();
    //FontFamily* monospaceFontFamily = FontFamily::GetDefaultFamily(FontType::Monospace);

    // Controls creation
    window = new Window("Shell");
    window->Position = Point(256, 96);
    window->Size = Point(640, 480);

    window->Add(title = new Label("Shell"));
    title->Position = Point(16, 12);
    //title->Font = Font::Slot[0];
    title->Color = 0x627d93;

    window->Add(shell = new ShellControl((void*)0xB8000));
    shell->Position = Point(8, 48);
    //shell->Font = Font::Slot[3];

    WindowsManager::Add(window);

    char line[81];

    for (;;)
    {
        //WriteLine("Time: %D", Timer::Time());
        shell->Redraw();

        Timer::Sleep(100);
    }
}