#ifndef _SYSTEM_GRAPH_H_
#define _SYSTEM_GRAPH_H_

#include <System/Interface/Controls/Control.h>
#include <System/Structures/Collections/List.h>
#include <System/Graphics/Colors.h>
#include <System/Graphics/Point.h>

#define GRAPH_CURVE_MAX_VALUES 100

namespace System
{
    namespace Interface
    {
        class Graph : public Control
        {
        public:
            class Curve
            {
            private:
                Graph* graph;

            public:
                Color24 Color;
                s32 Values[GRAPH_CURVE_MAX_VALUES];

                Curve(Graph* graph) : graph(graph) { }

                void AddValue(s32 value);
                void Clear(s32 value = 0);
            };

        private:
            List<Curve*> curves;
            u16 segmentSize;
            s32 minimum, maximum;
            Graphics::Point gridSize;
            u16 gridShift;
            bool fillBelow;

        public:
            Graph();

            // Accessors
            _declspec(property(get = GetSegmentSize, put = SetSegmentSize)) u16 SegmentSize;
            u16 GetSegmentSize() { return segmentSize; }
            virtual u16& SetSegmentSize(u16 value) { segmentSize = value; Redraw(); return segmentSize; }
            _declspec(property(get = GetGridSize, put = SetGridSize)) Graphics::Point GridSize;
            Graphics::Point GetGridSize() { return gridSize; }
            virtual Graphics::Point& SetGridSize(Graphics::Point value) { gridSize = value; Redraw(); return gridSize; }
            _declspec(property(get = GetGridShift, put = SetGridShift)) u16 GridShift;
            u16 GetGridShift() { return gridShift; }
            virtual u16& SetGridShift(u16 value) { gridShift = value; Redraw(); return gridShift; }
            _declspec(property(get = GetFillBelow, put = SetFillBelow)) bool FillBelow;
            bool GetFillBelow() { return fillBelow; }
            virtual bool& SetFillBelow(bool value) { fillBelow = value; Redraw(); return fillBelow; }

            // Graph
            Curve* AddCurve(Color24 color);

            // Methods
            void Redraw();
            void Redraw(bool fullRedraw);
        };
    }
}

#endif