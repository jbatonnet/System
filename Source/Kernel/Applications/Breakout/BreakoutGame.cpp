#include "BreakoutGame.h"

#include <System/Graphics/Surface.h>
#include <System/Utilities/Time/Timer.h>
#include <System/Utilities/Random.h>
#include <System/Debugging/Serial.h>
#include <System/Interface/Controls/Image.h>
#include <System/Interface/Controls/Graph.h>
#include <System/Interface/Window.h>
#include <System/Maths/Maths.h>

using namespace System::Graphics;
using namespace System::Interface;

int value = 0;

struct Shape
{
    s32 dx, dy;
    u32 x, y;
    u32 color;
};

#define SHAPE_COUNT 500
#define SHAPE_SIZE 8

Shape* shapes;
Random random;

FontFamily* fontFamily;
Font* font;

Graph* graph;
Graph::Curve *updateCurve, *drawCurve;
u32 n = 0;

void BreakoutGame::Initialize()
{
    Serial::WriteLine("Initialize");

    vSync = false;
    frameSkip = 10;

    // Add a small graph
    window->Add(graph = new Graph());
    graph->Dock = DockStyle::BottomLeft;
    graph->Position = Point(8, window->Size.Y - 40);
    graph->Size = Point(48, 32);
    graph->GridSize = Point(10, 10);
    graph->BackColor = Colors::White;
    graph->SegmentSize = 2;
    graph->FillBelow = true;
    updateCurve = graph->AddCurve(Colors::Green);
    drawCurve = graph->AddCurve(Colors::Red);
}

void BreakoutGame::Load()
{
    Serial::WriteLine("Load");

    shapes = new Shape[SHAPE_COUNT];
    for (int i = 0; i < SHAPE_COUNT; i++)
    {
        shapes[i].dx = (random.Generate<u32>() % 2) ? -1 : 1;
        shapes[i].dy = (random.Generate<u32>() % 2) ? -1 : 1;
        shapes[i].x = random.Generate<u32>() % (image->Size.X - SHAPE_SIZE);
        shapes[i].y = random.Generate<u32>() % (image->Size.Y - SHAPE_SIZE);
        shapes[i].color = random.Generate<u32>() & 0xFFFFFF;
    }

    fontFamily = FontFamily::Load("/System/Fonts/Consolas.font.raw");
    font = fontFamily->GetFont(14);
}
void BreakoutGame::Unload()
{
    Serial::WriteLine("Unload");
}

void BreakoutGame::Update(u64 lastTime, u64 time)
{
    for (int i = 0; i < SHAPE_COUNT; i++)
    {
        shapes[i].x += shapes[i].dx * 2;
        shapes[i].y += shapes[i].dy * 2;

        shapes[i].x = Maths::Clamp<u32>(shapes[i].x, 0, image->Size.X - SHAPE_SIZE);
        shapes[i].y = Maths::Clamp<u32>(shapes[i].y, 0, image->Size.Y - SHAPE_SIZE);

        if (shapes[i].x <= 0) shapes[i].dx = 1;
        if (shapes[i].x + SHAPE_SIZE >= image->Size.X) shapes[i].dx = -1;
        if (shapes[i].y <= 0) shapes[i].dy = 1;
        if (shapes[i].y + SHAPE_SIZE >= image->Size.Y) shapes[i].dy = -1;
    }

    // Debug
    if (n % 10 == 0)
    {
        updateCurve->AddValue(Maths::Clamp<s32>(ups, 0, 100));
        drawCurve->AddValue(Maths::Clamp<s32>(dps, 0, 100));
    }
    if (n % 60 == 0)
        Timer::Sleep(random.Generate<u16>() % 250);

    n++;
}
void BreakoutGame::Draw(u64 lastTime, u64 time)
{
    image->Surface->Clear(Colors::Black);

    for (int i = 0; i < SHAPE_COUNT; i++)
        image->Surface->FillRectangle(shapes[i].x, shapes[i].y, SHAPE_SIZE, SHAPE_SIZE, shapes[i].color);

    string upsText = String::Format("UPS: {0}", (u32)ups);
    image->Surface->DrawText(upsText, font, Point2(9, 9), Colors::Black);
    image->Surface->DrawText(upsText, font, Point2(8, 8), Colors::White);

    string dpsText = String::Format("DPS: {0}", (u32)dps);
    image->Surface->DrawText(dpsText, font, Point2(9, 27), Colors::Black);
    image->Surface->DrawText(dpsText, font, Point2(8, 26), Colors::White);

    image->Redraw();
}

void BreakoutGame_Main()
{
    BreakoutGame game;
    game.Start();

    for (;;);
}