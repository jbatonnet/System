#ifndef _SYSTEM_FONT_H_
#define _SYSTEM_FONT_H_

#include <System/Common.h>
#include <System/IO/File.h>
#include <System/IO/Streams/Stream.h>
#include <System/Graphics/Point.h>
#include <System/Structures/Collections/Dictionary.h>
#include <System/Graphics/FontFamily.h>
#include <System/Graphics/Surface.h>

namespace System
{
    namespace Graphics
    {
        class Font
        {
		public:
            /// <summary>
            /// Returns this font family
            /// </summary>
            _declspec(property(get = GetFamily)) Reference<FontFamily> Family;
            virtual Reference<FontFamily> GetFamily() const = 0;

            /// <summary>
            /// Returns this font size
            /// </summary>
            _declspec(property(get = GetSize)) u8 Size;
            virtual u8 GetSize() const = 0;

            /// <summary>
            /// Returns this font attributes
            /// </summary>
            _declspec(property(get = GetAttributes)) FontAttribute Attributes;
            virtual FontAttribute GetAttributes() const = 0;

            void Draw(Surface* surface, const string& text, Point2 position, Color32 color = 0x000000, Alignment alignment = Alignment::TopLeft)
            {
                Draw(surface, text, position.X, position.Y, color, alignment);
            }
            virtual void Draw(Surface* surface, const string& text, u16 x, u16 y, Color32 color = 0x000000, Alignment alignment = Alignment::TopLeft) = 0;

            /// <summary>
            /// Returns the size of the specified text, once rendered
            /// </summary>
            /// <param name="text">The text to measure</param>
            /// <returns>The size of the specified text, once rendered</returns>
            virtual Point2 Measure(const string& text) = 0;

            /// <summary>
            /// Returns the size of the specified character, once rendered
            /// </summary>
            /// <param name="text">The character to measure</param>
            /// <returns>The size of the specified character, once rendered</returns>
            virtual Point2 Measure(char character) = 0;
        };
    }
}

#endif