#ifndef _SYSTEM_BITMAP_H_
#define _SYSTEM_BITMAP_H_

#include <System/Common.h>
#include <System/IO/File.h>
#include <System/IO/Streams/Stream.h>
#include <System/Graphics/Point.h>
#include <System/Graphics/Colors.h>
#include <System/Structures/Collections/Dictionary.h>

namespace System
{
    namespace Graphics
    {
        enum class Alignment : u8
        {
            Top       = 0x01,
            Middle    = 0x02,
            Baseline  = 0x04,
            Bottom    = 0x08,
            Left      = 0x10,
            Center    = 0x20,
            Right     = 0x40,

            TopLeft        = Top | Left,
            TopCenter      = Top | Center,
            TopRight       = Top | Right,
            MiddleLeft     = Middle | Left,
            MiddleCenter   = Middle | Center,
            MiddleRight    = Middle | Right,
            BaselineLeft   = Baseline | Left,
            BaselineCenter = Baseline | Center,
            BaselineRight  = Baseline | Right,
            BottomLeft     = Bottom | Left,
            BottomCenter   = Bottom | Center,
            BottomRight    = Bottom | Right
        };
        enum class Orientation : u8
        {
            LeftToRight,
            RightToLeft,
            TopToBottom,
            BottomToTop,

            Horizontal = LeftToRight,
            Vertical = TopToBottom
        };
        enum class Direction : u8
        {
            Left,
            Up,
            Right,
            Down
        };

        struct BitmapLoaderBase;

        /// <summary>
        /// Represents a two-dimension array of pixels
        /// </summary>
        shared class Bitmap : public Object
        {
            friend class Surface;
            friend class SubSurface;

            typedef Color32 Pixel;

        protected:
            Pixel* data;
            Point2 size;
            u16 padding;

        private:
            u16 _pitch;
            u32 _size;

        public:
            Bitmap() { }
            Bitmap(void* data, u16 width, u16 height, u16 padding = 0) : data((Pixel*)data), size(width, height), padding(padding)
            {
                Initialize();
            }
            Bitmap(void* data, Point2 size, u16 padding = 0) : data((Pixel*)data), size(size), padding(padding)
            {
                Initialize();
            }

            /// <summary>
            /// Returns this bitmap internal buffer
            /// </summary>
            void* GetData() const { return data; }
            _declspec(property(get = GetData)) void* Data;

            /// <summary>
            /// Returns this bitmap size
            /// </summary>
            Point2 GetSize() const { return size; }
            _declspec(property(get = GetSize)) Point2 Size;

            // Loaders
            template<typename T> static Reference<Bitmap> Load(IO::Stream* stream);
            static Reference<Bitmap> Load(IO::File* file);
            static Reference<Bitmap> Load(const string& path);

            string ToString() override
            {
                return String::Format("Bitmap: { Width: {0}, Height: {1} }", size.X, size.Y);
            }

        protected:
            void Initialize()
            {
                _pitch = sizeof(Pixel) * size.X + padding;
                _size = _pitch * size.Y;
            }
        };

        struct Bitmaps
        {
            struct Cursors
            {
                static Dynamic<Bitmap> Normal;
            };

            struct Icons
            {
                static Dynamic<Bitmap> Close, Plus;
                static Dynamic<Bitmap> Up, Right, Down, Left;
            };
        };
    }
}

#endif