#include "ShellControl.h"

using namespace System::Graphics;
using namespace System::Interface;

ShellControl::ShellControl(void* address) : address(address) { }

void ShellControl::Initialize()
{
    size = Point(600, 400);
    surface = new System::Graphics::Surface(size.X, size.Y);
    //Control::Initialize();

    Redraw();
}
void ShellControl::Redraw()
{
    char line[81];

    surface->Clear(0xFFFFFF);

    for (u32 y = 0; y < 20; y++)
    {
        Memory::Clear(line, 81, 0);

        for (u32 x = 0; x < 80; x++)
            line[x] = *(char*)((u32)address + (y + 5) * 160 + x * 2);

        surface->DrawText(line, font, 0, y * 30, 0x000000);
    }

    Redrawn(this, Rectangle(Position, Size));
}