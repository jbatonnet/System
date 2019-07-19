#ifndef _SYSTEM_DEFAULT_H_
#define _SYSTEM_DEFAULT_H_

#include <System/Base/Types.h>

template<typename T> struct DefaultValue
{
public:
    static T Get()
    {
        return T();
    }
};
template<typename T> struct DefaultValue<T*>
{
public:
    static T* Get()
    {
        return null;
    }
};

#define RegisterDefault(Type, Value) template<> struct DefaultValue<Type> { public: static Type Get() { return Value; } };

RegisterDefault(bool, false);
RegisterDefault(u8, 0);
RegisterDefault(u16, 0);
RegisterDefault(u32, 0);
RegisterDefault(u64, 0);
RegisterDefault(s8, 0);
RegisterDefault(s16, 0);
RegisterDefault(s32, 0);
RegisterDefault(s64, 0);
RegisterDefault(float, 0);
RegisterDefault(double, 0);
RegisterDefault(unit, 0xFF);

//#define default(T) (DefaultValue<T>::Get())

#endif