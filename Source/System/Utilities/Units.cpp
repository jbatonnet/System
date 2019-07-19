#include <System/Utilities/Units.h>

// Sizes
template<> static float Units::Convert(float value, SizeUnit from, SizeUnit to)
{
    return value * Size::Values[from] / Size::Values[to];
}
template<> static s32 Units::Convert(s32 value, SizeUnit from, SizeUnit to)
{
    return value * Size::Values[from] / Size::Values[to];
}
float Units::Size::Values[SizeUnit::Count] = { /* Pixel */ 1, /* Point */ 1, /* Centimeter */ 64.94f, /* Inch */ 164.95f };
//Unit Units::Size::Default = SizeUnit::Pixel;

// Temperatures
template<> static float Units::Convert(float value, TemperatureUnit from, TemperatureUnit to)
{
    return (value / Temperature::Factors[from] - Temperature::Deltas[from]) * Temperature::Factors[to] + Temperature::Deltas[to];
}
float Units::Temperature::Factors[TemperatureUnit::Count] = { /* Celsius */ 1, /* Fareneight */ 1 };
float Units::Temperature::Deltas[TemperatureUnit::Count] = { /* Celsius */ 1, /* Fareneight */ 1 };
//Unit Units::Temperature::Default = TemperatureUnit::Celsius;

// FileSizes
template<> static float Units::Convert(float value, FileSizeUnit from, FileSizeUnit to)
{
    return value * FileSize::Factors[from] / FileSize::Factors[to];
}
u32 Units::FileSize::Factors[FileSize::Count] = { /* Bit */ 1, /* Byte */ 8, /* KiloByte */ 8 * 1024, /* MegaByte */ 8 * 1024 * 1024, /* GigaByte */ 8 * 1024 * 1024 * 1024 };
//Unit Units::Temperature::Default = TemperatureUnit::Celsius;
