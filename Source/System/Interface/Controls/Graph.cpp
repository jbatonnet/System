#include <System/Interface/Controls/Graph.h>
#include <System/Maths/Maths.h>

using namespace System::Interface;
using namespace System::Graphics;

Graph::Graph() : segmentSize(8), minimum(0), maximum(100), gridSize(), gridShift(0), fillBelow(false)
{
    backColor = Colors::White;
    surface = new Graphics::Surface(1, 1);
}

/*void Graph::Initialize()
{
    Control::Initialize();

    Redraw(true);
}*/
void Graph::Redraw()
{
    Redraw(false);
}
void Graph::Redraw(bool fullRedraw)
{
    surface->Clear(backColor);

    if (gridSize.X > 1)
        for (s16 x = gridSize.X - gridShift; x < size.X; x += gridSize.X)
            surface->DrawLine(x, 0, x, size.Y - 1, Colors::BrightGray);

    if (gridSize.Y > 1)
        for (s16 y = gridSize.Y; y < size.Y; y += gridSize.Y)
            surface->DrawLine(0, y, size.X - 1, y, Colors::BrightGray);

    u16 x = size.X;
    if (fillBelow)
    {
        for (u8 i = GRAPH_CURVE_MAX_VALUES - 2; i > 0 && x > 0; i--)
        {
            for (u32 j = 0; j < curves.Count; j++)
            {
                u16 y1 = Maths::Map<s32>(curves[j]->Values[i], minimum, maximum, size.Y - 1, 0);
                u16 y2 = Maths::Map<s32>(curves[j]->Values[i + 1], minimum, maximum, size.Y - 1, 0);
            
                for (u8 k = 0; k < segmentSize; k++)
                {
                    u16 y = Maths::Map<s16>(k + 1, 0, segmentSize, y1, y2);
                    surface->DrawLine(x - segmentSize + k, y, x - segmentSize + k, size.Y - 1, Color32(curves[j]->Color, 0xE0));
                }
            }

            x -= segmentSize;
        }
        x = size.X;
    }

    for (u8 i = GRAPH_CURVE_MAX_VALUES - 2; i > 0 && x > 0; i--)
    {
        for (u32 j = 0; j < curves.Count; j++)
        {
            u16 y1 = Maths::Map<s32>(curves[j]->Values[i], minimum, maximum, size.Y - 1, 0);
            u16 y2 = Maths::Map<s32>(curves[j]->Values[i + 1], minimum, maximum, size.Y - 1, 0);

            surface->DrawLine(x - segmentSize, y1, x, y2, curves[j]->Color, true);
        }

        x -= segmentSize;
    }

    surface->DrawRectangle(0, 0, size.X, size.Y, Colors::Gray);
    Redrawn(this, Rectangle(position, size));
}

Graph::Curve* Graph::AddCurve(Color24 color)
{
    Curve* curve = new Curve(this);
    curve->Color = color;

    Memory::Clear<u32>(curve->Values, GRAPH_CURVE_MAX_VALUES);
    Redraw(true);

    curves.Add(curve);
    return curve;
}
void Graph::Curve::AddValue(s32 value)
{
    //for (u8 i = 0; i < GRAPH_CURVE_MAX_VALUES - 1; i++)
    //    Values[i] = Values[i + 1];

    Memory::Copy<s32>(Values + 1, Values, GRAPH_CURVE_MAX_VALUES - 1);
    Values[GRAPH_CURVE_MAX_VALUES - 1] = Maths::Clamp(value, graph->minimum, graph->maximum);
    
    graph->gridShift += graph->segmentSize;

    graph->Redraw(false);
}
void Graph::Curve::Clear(s32 value)
{
    Memory::Clear<s32>(Values, GRAPH_CURVE_MAX_VALUES, value);

    graph->Redraw(false);
}