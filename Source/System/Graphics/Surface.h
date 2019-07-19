#ifndef _SYSTEM_SURFACE_H_
#define _SYSTEM_SURFACE_H_

#include <System/Graphics/Bitmap.h>
#include <System/Graphics/Colors.h>
#include <System/Graphics/Font.h>
#include <System/Graphics/Point.h>

namespace System
{
    namespace Graphics
    {
        class Surface : public Bitmap
        {
            friend class SubSurface;

        protected:
            Surface() { }

        public:
            Surface(void* data, u16 width, u16 height, u16 padding = 0);
            Surface(void* data, Point2 size, u16 padding = 0);
            Surface(u16 width, u16 height);
            Surface(Point2 size);

            // Global
			virtual void Clear(Color32 color);
            virtual void Resize(Point2 size);

            // Shapes
            virtual void DrawPoint(s16 x, s16 y, Color32 color);
            virtual void DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased = false);
            void DrawRectangle(Point2 position, Point2 size, Color32 color)
            {
                DrawRectangle(position.X, position.Y, size.X, size.Y, color);
            }
            virtual void DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);
            void FillRectangle(Point2 position, Point2 size, Color32 color)
            {
                FillRectangle(position.X, position.Y, size.X, size.Y, color);
            }
            virtual void FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color);

            // Bitmaps
            void DrawBitmap(Bitmap* bitmap, bool alpha = false)
            {
                DrawBitmap(0, 0, 0, 0, bitmap->Size.X, bitmap->Size.Y, bitmap, alpha);
            }
            void DrawBitmap(Point2 position, Bitmap* bitmap, bool alpha = false)
            {
                DrawBitmap(0, 0, position.X, position.Y, bitmap->Size.X, bitmap->Size.Y, bitmap, alpha);
            }
            void DrawBitmap(s16 x, s16 y, Bitmap* bitmap, bool alpha = false)
            {
                DrawBitmap(0, 0, x, y, bitmap->Size.X, bitmap->Size.Y, bitmap, alpha);
            }
            void DrawBitmap(Point2 source, Point2 destination, Point2 size, Bitmap* bitmap, bool alpha = false)
            {
                DrawBitmap(source.X, source.Y, destination.X, destination.Y, size.X, size.Y, bitmap, alpha);
            }
            virtual void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, bool alpha = false);
            void DrawBitmap(Point2 source, Point2 destination, Point2 size, Bitmap* bitmap, Color32 color)
            {
                DrawBitmap(source.X, source.Y, destination.X, destination.Y, size.X, size.Y, bitmap, color);
            }
            virtual void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, Color32 color);

            // Text
            void DrawText(const string& text, Reference<Font> font, Point2 position, Color32 color = 0x000000, Alignment alignment = Alignment::TopLeft)
            {
                DrawText(text, font, position.X, position.Y, color, alignment);
            }
            virtual void DrawText(const string& text, Reference<Font> font, s16 x, s16 y, Color32 color = 0x000000, Alignment alignment = Alignment::TopLeft);

            // Effects
            virtual void Darken(s16 x, s16 y, u16 width, u16 height, u16 multiplier, u16 divisor);
        };

        class SubSurface : public Surface
        {
        protected:
            Surface* baseSurface;
            u16 x, y;

        public:
            SubSurface(Surface* surface, s16 x, s16 y, u16 width, u16 height);
            SubSurface(Surface* surface, Point2 position, Point2 size);

            virtual void Resize(Point2 newSize);
        };

        class ShiftedSurface : public Surface
        {
        protected:
            Surface* baseSurface;
            s16 x, y;

        public:
            ShiftedSurface(Surface* surface, s16 x, s16 y);
            ShiftedSurface(Surface* surface, Point2 position);

            virtual void DrawPoint(s16 x, s16 y, Color32 color) override;
            virtual void DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, Color32 color, bool antialiased = false) override;
            virtual void DrawRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color) override;
            virtual void FillRectangle(s16 x, s16 y, u16 w, u16 h, Color32 color) override;
            virtual void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, bool alpha = false) override;
            virtual void DrawBitmap(s16 sourceX, s16 sourceY, s16 destinationX, s16 destinationY, u16 w, u16 h, Bitmap* bitmap, Color32 color) override;
            virtual void DrawText(const string& text, Reference<Font> font, s16 x, s16 y, Color32 color = 0x000000, Alignment alignment = Alignment::TopLeft) override;
        };
    }
}

#endif