#include <System/System.h>

#include "Windows.h"

using namespace System::IO;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Graphics;
using namespace System::Devices;

void Test_Timer()
{
    Window *window;
    Label *title, *minutes, *seconds, *milliseconds;

    // Window creation
    Reference<FontFamily> fontFamily = FontFamily::Load("..\\Root\\System\\Fonts\\Open.font.raw");

    // Controls creation
    window = new Window("Chrono");
    window->Position = Point(4, 4, SizeUnit::Centimeter);
    window->Size = Point(208, 104);

    window->Add(title = new Label("Chrono"));
    title->Position = Point(16, 12);
    title->Color = 0x627d93;
    title->Font = fontFamily->GetFont(16);

    window->Add(minutes = new Label("00'"));
    minutes->Position = Point(32, 48);
    minutes->Font = fontFamily->GetFont(36, FontAttribute::Light);

    window->Add(seconds = new Label("00\""));
    seconds->Position = Point(84, 48);
    seconds->Font = fontFamily->GetFont(36, FontAttribute::Light);

    window->Add(milliseconds = new Label("000"));
    milliseconds->Position = Point(142, 58);
    milliseconds->Font = fontFamily->GetFont(22, FontAttribute::Light);

    WindowsManager::Add(window);

    u32 start = Timer::Time();
    u16 lm = -1, ls = -1, lms = -1;

    for (;;)
    {
        u32 time = Timer::Time() - start;
        u16 m = (time / 60000) % 60, s = (time / 1000) % 60, ms = time % 1000;

        if (m != lm) minutes->Text = String::Format("{0:d2}'", lm = m);
        if (s != ls) seconds->Text = String::Format("{0:d2}\"", ls = s);
        if (ms != lms) milliseconds->Text = String(lms = ms, "d3");

        Timer::Sleep(11);
    }
}