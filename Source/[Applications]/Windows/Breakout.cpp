#include "Windows.h"
#include <System/System.h>

using namespace System::IO;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Graphics;
using namespace System::Devices;

int value = 0;

struct Shape
{
    s32 dx, dy;
    s32 x, y;
    u32 color;
};

#define SHAPE_COUNT 500
#define SHAPE_SIZE 8

Shape* shapes;
Random random;

Window* breakoutWindow;
Image* image;

void Test_Breakout()
{
    // Window creation
    Reference<FontFamily> fontFamily = FontFamily::Load("..\\Root\\System\\Fonts\\Consolas.font.raw");
    Reference<Font> font = fontFamily->GetFont(14);

    breakoutWindow = new Window("Breakout");
    breakoutWindow->Position = Point(128, 128);
    breakoutWindow->Size = Point(640, 480);

    breakoutWindow->Add(image = new Image(640, 480));
    image->Position = Point::Zero;
    image->Dock = DockStyle::Full;

    // Shapes initialization
    shapes = new Shape[SHAPE_COUNT];
    for (int i = 0; i < SHAPE_COUNT; i++)
    {
        shapes[i].dx = (random.Generate<u32>() % 2) ? -1 : 1;
        shapes[i].dy = (random.Generate<u32>() % 2) ? -1 : 1;
        shapes[i].x = random.Generate<u32>() % (image->Size.X - SHAPE_SIZE);
        shapes[i].y = random.Generate<u32>() % (image->Size.Y - SHAPE_SIZE);
        shapes[i].color = random.Generate<u32>() & 0xFFFFFF;
    }

    WindowsManager::Add(breakoutWindow);

    for (;;)
    {
        for (int i = 0; i < SHAPE_COUNT; i++)
        {
            shapes[i].x += shapes[i].dx * 2;
            shapes[i].y += shapes[i].dy * 2;

            shapes[i].x = Maths::Clamp<s32>(shapes[i].x, 0, image->Size.X - SHAPE_SIZE);
            shapes[i].y = Maths::Clamp<s32>(shapes[i].y, 0, image->Size.Y - SHAPE_SIZE);

            if (shapes[i].x <= 0) shapes[i].dx = 1;
            if (shapes[i].x + SHAPE_SIZE >= image->Size.X) shapes[i].dx = -1;
            if (shapes[i].y <= 0) shapes[i].dy = 1;
            if (shapes[i].y + SHAPE_SIZE >= image->Size.Y) shapes[i].dy = -1;
        }

        //image->Surface->Clear(Colors::Black);

        //for (int i = 0; i < SHAPE_COUNT; i++)
        //    image->Surface->FillRectangle(shapes[i].x, shapes[i].y, SHAPE_SIZE, SHAPE_SIZE, shapes[i].color);

        /*string upsText = String::Format("UPS: {0}", (u32)ups);
        image->Surface->DrawText(upsText, font, Point2(9, 9), Colors::Black);
        image->Surface->DrawText(upsText, font, Point2(8, 8), Colors::White);

        string dpsText = String::Format("DPS: {0}", (u32)dps);
        image->Surface->DrawText(dpsText, font, Point2(9, 27), Colors::Black);
        image->Surface->DrawText(dpsText, font, Point2(8, 26), Colors::White);*/

        //image->Redraw();

        Timer::Sleep(16);
    }
}