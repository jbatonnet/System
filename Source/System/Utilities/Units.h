#ifndef _SYSTEM_UNITS_H_
#define _SYSTEM_UNITS_H_

#include <System/Common.h>

struct UnitGroup
{
    enum Units;
};
struct Units
{
    struct Size : UnitGroup
    {
        enum Units
        {
            Pixel,
            Point,
            Centimeter,
            Inch,

            Count,
            Default = Pixel
        };

        static float Values[Count];
    };
    struct Temperature : UnitGroup
    {
        enum Units
        {
            Celsius,
            Fareneight,

            Count,
            Default = Celsius
        };

        static float Factors[Count];
        static float Deltas[Count];
    };
    struct FileSize : UnitGroup
    {
        enum Units
        {
            Bit,
            Byte,
            KiloByte,
            MegaByte,
            GigaByte,

            Count,
            Default = Byte,

            B = Byte,
            KB = KiloByte,
            MB = MegaByte,
            GB = GigaByte,
        };

        static u32 Factors[Count];
    };

    template<typename T> static s32 Convert(s32 value, T from, T to);
    template<typename T> static float Convert(float value, T from, T to);
};

typedef Units::Size::Units SizeUnit;
typedef Units::Temperature::Units TemperatureUnit;
typedef Units::FileSize::Units FileSizeUnit;

#endif