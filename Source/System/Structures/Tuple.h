#ifndef _SYSTEM_TUPLE_H_
#define _SYSTEM_TUPLE_H_

#include <System/Common.h>

template<typename... Parameters> struct Tuple;
template<typename Last> struct Tuple<Last>
{
    enum { Size = 1 };

public:
    Last Value;

public:
    Tuple() : Value(DefaultValue<Last>::Get()) { }
    Tuple(Last value) : Value(value) { }

    template<u32 index> Last& At()
    {
        static_assert(index == 0, "This tuple does not contain enough items");
        return Value;
    }
};
template<typename First, typename... Other> struct Tuple<First, Other...>
{
    enum { Size = Types::Count<First, Other...>::Value };

public:
    First Value;
    Tuple<Other...> Values;

public:
    Tuple() : Value(DefaultValue<First>::Get()), Values() { }
    Tuple(First value, Other... values) : Value(value), Values(values...) { }

    template<u32 index> typename Types::Nth<index, First, Other...>::Type& At()
    {
        return Values.At<index - 1>();
    }
    template<> typename First& At<0>()
    {
        return Value;
    }
};

#endif