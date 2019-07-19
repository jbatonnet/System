#pragma once

#include <System/Base/Types.h>

#define generic// template<typename T>
#define T void*

generic struct OrderedArray
{
    T* Array;
    u32 Size;
    u32 Capacity;
    s32 (*Comparer)(T, T);
};

generic OrderedArray/*<T>*/ OrderedArray_Place(T* base, u32 capacity);
generic OrderedArray/*<T>*/ OrderedArray_Place(T* base, u32 capacity, s32 (*comparer)(T, T));
generic void OrderedArray_Add(OrderedArray/*<T>*/& orderedArray, T item);
generic void OrderedArray_RemoveAt(OrderedArray/*<T>*/& orderedArray, u32 i);