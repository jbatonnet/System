#ifndef _SYSTEM_TEMPLATE_H_
#define _SYSTEM_TEMPLATE_H_

#include <System/Base/Types.h>

namespace Types
{
    template<u32 condition, typename Type1, typename Type2> struct If
    {
        typedef Type1 Type;
    };
    template<typename Type1, typename Type2> struct If<0, Type1, Type2>
    {
        typedef Type2 Type;
    };

    template<typename Type1, typename Type2> struct Equals
    {
        enum { Value = false };
    };
    template<typename Type> struct Equals<Type, Type>
    {
        enum { Value = true };
    };

    template<u32 index, typename First, typename... Other> struct Nth;
    template<typename First, typename... Other> struct Nth<0, First, Other...>
    {
        typedef First Type;
    };
    template<u32 index, typename First, typename... Other> struct Nth<index, First, Other...>
    {
        typedef typename Nth<index - 1, Other...>::Type Type;
    };

    template<typename T> struct SizeOf
    {
        enum { Value = sizeof(T) };
    };

    template<typename... Args> struct Count;
    template<typename First, typename... Other> struct Count<First, Other...>
    {
        enum { Value = Count<Other...>::Value + 1 };
    };
    template<> struct Count<>
    {
        enum { Value = 0 };
    };
}

namespace Values
{
    template<u32 condition, u32 value1, u32 value2> struct If
    {
        enum { Value = value1 };
    };
    template<u32 value1, u32 value2> struct If<0, value1, value2>
    {
        enum { Value = value2 };
    };

    template<u32 value1, u32 value2> struct Min
    {
        enum
        {
            Condition = value1 < value2,
            Value = If<Condition, value1, value2>::Value
        };
    };
    template<u32 value1, u32 value2> struct Max
    {
        enum
        {
            Condition = value1 > value2,
            Value = If<Condition, value1, value2>::Value
        };
    };
}

#endif