#ifndef _SYSTEM_FLAGS_H_
#define _SYSTEM_FLAGS_H_

class Flag
{
public:
    template<typename T, typename U> static bool Test(T value, U flag)
    {
        return ((u32)value & (u32)flag) == (u32)flag;
    }
    template<typename T, typename U> static U Get(T value, U mask)
    {
        return (U)((u32)value & (u32)mask);
    }
};

#endif