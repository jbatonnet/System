#include <System/System.h>

#include "Windows.h"

using namespace System::IO;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Graphics;
using namespace System::Devices;

void Test_Editor()
{
    Window *window;
    TextBox *editor;

    // Window creation
    FontFamily* fontFamily = FontFamily::Load("../Root""/System/Fonts/Consolas.font.raw");
    Exception::Assert(fontFamily, "Font could not be loaded");

    // Controls creation
    window = new Window("Editor");
    window->Position = Point(128, 128);
    window->Size = Point(640, 480);
    window->BackColor = Colors::BrightGray;

    window->Add(editor = new TextBox());
    editor->Position = Point(8, 8);
    editor->Size = Point(window->Size.X - 16, window->Size.Y - 16);
    editor->Dock = DockStyle::Full;
    editor->Font = fontFamily->GetFont(9);

    // Load some text
    File* file = File::Open("../Root""/Code.cpp");
    Exception::Assert(file, "Test file could not be loaded");

    Stream* stream = file->GetStream();
    TextStream* textStream = new TextStream(stream);

    editor->Text = textStream->Read(file->Size);

    WindowsManager::Add(window);

    for (;;)
        Timer::Sleep(100);
}