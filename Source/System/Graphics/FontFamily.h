#ifndef _SYSTEM_FONTFAMILY_H_
#define _SYSTEM_FONTFAMILY_H_

#include <System/Common.h>
#include <System/IO/File.h>
#include <System/IO/Streams/Stream.h>
#include <System/Graphics/Point.h>
#include <System/Structures/Collections/Dictionary.h>

#define FONT_MAX_SIZE 32

namespace System
{
    namespace Graphics
    {
        class Font;

        enum class FontType : u8
        {
            None = 0x00,
            Serif = 0x01,
            Monospace = 0x02
        };
        enum class FontAttribute : u8
        {
            // Sizes
            Thin = 0x01,
            Light = 0x03,
            Regular = 0x04,
            Medium = 0x05,
            SemiBold = 0x06,
            Bold = 0x07,
            ExtraBold = 0x08,
            UltraBold = 0x09,

            // Attributes
            Italic = 0x20,
        };

        class FontFamily
        {
        public:
            /// <summary>
            /// Returns the name of this font family
            /// </summary>
            _declspec(property(get = GetName)) string Name;
            virtual string GetName() const = 0;

            /// <summary>
            /// Returns the type of this font family
            /// </summary>
            _declspec(property(get = GetType)) FontType Type;
            virtual FontType GetType() const = 0;
            
            /// <summary>
            /// Returns the font of this family matching the specified size and attributes
            /// Available font sizes : 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
            /// </summary>
            virtual Reference<Font> GetFont(u8 size, FontAttribute attributes = FontAttribute::Regular) = 0;

            /// <summary>
            /// Opens a font family from the specified stream
            /// </summary>
            /// <param name="stream">The stream of the font data to load</param>
            /// <returns>The open font family, or null if the stream was not valid</returns>
            template<typename T> static Reference<FontFamily> Load(IO::Stream* stream);

            /// <summary>
            /// Opens a font family from the specified path
            /// </summary>
            /// <param name="path">The path of the font family to load</param>
            /// <returns>The open font family, or null if the path was not found</returns>
            static Reference<FontFamily> Load(const string& path);

            /// <summary>
            /// Opens a font family from the specified file
            /// </summary>
            /// <param name="file">The file of the font family to load</param>
            /// <returns>The open font family, or null if the file was not valid</returns>
            static Reference<FontFamily> Load(IO::File* file);

            /// <summary>
            /// Returns the font family matching the specified name
            /// </summary>
            /// <param name="name">The name of the font family to load</param>
            /// <returns>The open font family, or null if no matching font was found</returns>
            static Reference<FontFamily> GetFamily(const string& name);

            /// <summary>
            /// Returns the default font family matching the specified type
            /// </summary>
            /// <param name="type">The type of the font family to load</param>
            /// <returns>The open font family, or null if no matching font was found</returns>
            static Reference<FontFamily> GetDefaultFamily(FontType type = FontType::None);
        };
    }
}

#endif