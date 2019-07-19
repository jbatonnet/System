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
    Reference<FontFamily> fontFamily = FontFamily::Load("/System/Fonts/Consolas.font.raw");
    Exception::Assert(fontFamily.Valid, "Font could not be loaded");

    // Controls creation
    window = new Window("Editor");
    window->Position = Point(128, 128);
    window->Size = Point(640, 480);
    window->BackColor = Colors::BrightGray;

    window->Add(editor = new TextBox());
    editor->Position = Point(4, 44);
    editor->Size = Point(window->Size.X - 8, window->Size.Y - 40 - 8);
    editor->Dock = DockStyle::Full;
    editor->Font = fontFamily->GetFont(9);

    // Load some text
    File* file = File::Open("/Code.cpp");
    Exception::Assert(file, "Test file could not be loaded");

    Stream* stream = file->GetStream();
    TextStream* textStream = new TextStream(stream);

    editor->Text = textStream->Read(file->Size);

    WindowsManager::Add(window);

    for (;;)
        Timer::Sleep(100);
}