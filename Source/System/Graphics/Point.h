#ifndef _SYSTEM_POINT_H_
#define _SYSTEM_POINT_H_

#include <System/Common.h>
#include <System/Maths/Vectors.h>
#include <System/Utilities/Units.h>

namespace System
{
    namespace Graphics
    {
        struct Point : Point2
        {
            SizeUnit Unit;

            Point() : Unit(SizeUnit::Pixel), Point2(0, 0) { }
            Point(Point2 point, SizeUnit unit = SizeUnit::Default) : Unit(SizeUnit::Pixel), Point2(point.X, point.Y)
            {
                if (unit == SizeUnit::Pixel)
                    return;

                X = Units::Convert(X, unit, SizeUnit::Pixel);
                Y = Units::Convert(Y, unit, SizeUnit::Pixel);
            }
            Point(s32 x, s32 y, SizeUnit unit = SizeUnit::Default) : Unit(SizeUnit::Pixel), Point2(x, y)
            {
                if (unit == SizeUnit::Pixel)
                    return;

                X = Units::Convert(X, unit, SizeUnit::Pixel);
                Y = Units::Convert(Y, unit, SizeUnit::Pixel);
            }
        };

        struct Rectangle
        {
            Point Position;
            Point Size;

            Rectangle() : Position(0, 0), Size(0, 0) { }
            Rectangle(Point position, Point size) : Position(position), Size(size) { }
            Rectangle(s32 x, s32 y, u32 w, u32 h) : Position(x, y), Size((s32)w, (s32)h) { }
            Rectangle(s32 x, s32 y, u32 w, u32 h, SizeUnit unit) : Position(x, y, unit), Size((s32)w, (s32)h, unit) { }

            bool operator==(const Rectangle& rectangle)
            {
                return Position.X == rectangle.Position.X && Position.Y == rectangle.Position.Y && Size.X == rectangle.Size.X && Size.Y == rectangle.Size.Y;
            }

            /*Rectangle Intersect(const Rectangle& rectangle)
            {
                if (Position.X + Size.X <= rectangle.Position.X || Position.Y + Size.Y <= rectangle.Position.Y)
                    return;
                if (rectangle.Position.X + rectangle.Size.X <= Position.X || rectangle.Position.Y + rectangle.Size.Y <= Position.Y)
                    return;

                s32 x = Maths::Max(Position.X, rectangle.Position.X),
                    y = Maths::Max(Position.Y, rectangle.Position.Y);

                return Rectangle(x, y, Maths::Min(Position.X + Size.X, rectangle.Position.X + rectangle.Size.X) - x, Maths::Min(Position.Y + Size.Y, rectangle.Position.Y + rectangle.Size.Y) - y);
            }*/

            Rectangle Expand(s32 size)
            {
                return Rectangle(Position.X - size, Position.Y - size, Size.X + size * 2, Size.Y + size * 2);
            }
        };

        struct Outline
        {
            u32 Top;
            u32 Right;
            u32 Bottom;
            u32 Left;

            Outline() : Top(0), Right(0), Bottom(0), Left(0) { }
            Outline(const Outline& outline) : Top(outline.Top), Right(outline.Right), Bottom(outline.Bottom), Left(outline.Left) { }
            Outline(u32 value) : Top(value), Right(value), Bottom(value), Left(value) { }
            Outline(u32 top, u32 right, u32 bottom, u32 left) : Top(top), Right(right), Bottom(bottom), Left(left) { }

            bool operator==(const Outline& outline)
            {
                return Top == outline.Top && Right == outline.Right && Bottom == outline.Bottom && Left == outline.Left;
            }
        };
    }
}

#endif