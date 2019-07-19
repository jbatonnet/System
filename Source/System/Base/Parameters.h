#ifndef _SYSTEM_PARAMETERS_H_
#define _SYSTEM_PARAMETERS_H_

#include <System/Common.h>

template<typename T> struct Parameters
{
private:
    T value;

public:
    Parameters(const T& arg) : value(arg) { }

    T& GetValue(u32 i) const
    {
        T result = ((T*)this)[i];
        return result;
    }
    T* GetPointer() const
    {
        return (T*)result;
    }

    /*List<T> GetList(u32 count) const
    {
        List<T> result(count);

        for (u32 i = 0; i < count; i++)
            result.Add(GetValue(i));

        return result;
    }*/
};

#endif