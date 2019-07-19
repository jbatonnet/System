#ifndef _SYSTEM_COLORS_H_
#define _SYSTEM_COLORS_H_

#include <System/Common.h>

struct Color24
{
    union
    {
        u32 Value;
        struct
        {
            u8 Blue;
            u8 Green;
            u8 Red;
            u8 __Unused;
        };
    };

    constexpr Color24() : __Unused(0), Red(0), Green(0), Blue(0) { }
    constexpr Color24(u32 value) : __Unused(0), Red((value >> 16) & 0xFF), Green((value >> 8) & 0xFF), Blue(value & 0xFF) { }
    constexpr Color24(u8 red, u8 green, u8 blue) : __Unused(0), Red(red), Green(green), Blue(blue) { }

    constexpr bool operator==(const Color24& other) const
    {
        return other.Value == Value;
    }
};
struct Color32
{
    union
    {
        u32 Value;
        struct
        {
            u8 Blue;
            u8 Green;
            u8 Red;
            u8 Alpha;
        };
    };

    constexpr Color32() : Alpha(0), Red(0), Green(0), Blue(0) { }
    constexpr Color32(u32 value) : Alpha(value >> 24), Red((value >> 16) & 0xFF), Green((value >> 8) & 0xFF), Blue(value & 0xFF) { }
    constexpr Color32(u8 red, u8 green, u8 blue) : Alpha(0x00), Red(red), Green(green), Blue(blue) { }
    constexpr Color32(u8 alpha, u8 red, u8 green, u8 blue) : Alpha(alpha), Red(red), Green(green), Blue(blue) { }
    constexpr Color32(Color24 color, u8 alpha = 0x00) : Alpha(alpha), Red(color.Red), Green(color.Green), Blue(color.Blue) { }

    constexpr bool operator==(const Color32& other) const
    {
        return other.Value == Value;
    }
};

namespace Colors
{
    static constexpr Color32 Transparent(0xFF000000);

    #define Color(name, color) static constexpr Color24 name(color);
    #define Shade(name, dark, normal, light) Color(Dark##name, dark); Color(name, normal); Color(Light##name, light);

    // Grays
    Color(Black,      0x000000);
    Color(DeepGray,   0x202020);
    Color(DarkGray,   0x404040);
    Color(Gray,       0x808080);
    Color(LightGray,  0xC0C0C0);
    Color(BrightGray, 0xE8E8E8);
    Color(White,      0xFFFFFF);

    // Raw
    Color(RawRed,     0xFF0000);
    Color(RawGreen,   0x00FF00);
    Color(RawBlue,    0x0000FF);
    Color(RawCyan,    0x00FFFF);
    Color(RawMagenta, 0xFF00FF);
    Color(RawYellow,  0xFFFF00);

    // Primary
    Shade(Red,     0x902000, 0xFF3000, 0xFF9880);
    Shade(Green,   0x207000, 0x30B000, 0xA0F080);
    Shade(Blue,    0x003890, 0x0050FF, 0x80C0FF);
    Shade(Cyan,    0x00A0A0, 0x00F0F0, 0x80FFFF);
    Shade(Magenta, 0x900090, 0xF010FF, 0xFF80FF);
    Shade(Yellow,  0xC0A000, 0xFFE800, 0xFFF080);

    // Common
    Shade(Orange, 0xC06000, 0xFF8000, 0xFFC080);
    Shade(Purple, 0x8040C0, 0xA040FF, 0xD0A0FF);
    Shade(Brown,  0x805030, 0xA07040, 0xE0B080);
    Shade(Pink,   0xB050A0, 0xFF60D0, 0xFFA0F0);

    // Other
    Color(Sky,    0x000000); // TODO
    Color(Brick,  0x000000); // TODO
    Color(Salmon, 0x000000); // TODO
    Color(Gold,   0x000000); // TODO
    Color(Ice,    0x000000); // TODO
    Color(Mint,   0x00FF80); // TODO
    Color(Lemon,  0x80FF00); // TODO

    struct System
    {
        static const Color24 Color; // 0x4A6B75

        static const Color24 ActiveBackground,   // 0xFFFFFF
                             InactiveBackground,
                             Border,             // 0xBECACE
                             Menu,
                             ActiveTab,
                             InactiveTab,
                             ActiveSubtab,
                             InactiveSubtab;
    };

    #undef Color
    #undef Shade
};

#endif