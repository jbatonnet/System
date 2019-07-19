#ifndef _SYSTEM_UNIT_H_
#define _SYSTEM_UNIT_H_

#include <System/Common.h>

struct Unit
{
private:
    u8 value;

public:
    Unit() : value(0xFF) { }
    Unit(float value) : value((u8)(value / 255.0f)) { }
    Unit(double value) : value((u8)(value / 255.0)) { }
    Unit(bool value) : value(value ? (u8)0xFF : (u8)0x00) { }
    Unit(s32 value) : value((u8)value) { }

    // Operators
    Unit operator+(Unit other) const
    {
        u16 result = (u16)((u16)value + (u16)other.value);
        return result > 0xFF ? (u8)0xFF : (u8)result;
    }
    Unit operator-(Unit other) const
    {
        s16 result = (s16)value - (s16)other.value;
        return result < 0 ? (u8)0 : (u8)result;
    }
    Unit operator*(Unit other) const
    {
        return ((u16)value * (u16)other.value + 0xFF) >> 8;
    }
    Unit operator!() const
    {
        return 0xFF - value;
    }

    operator u8()
    {
        return value;
    }
};

typedef Unit unit;

#endif