#include "OrderedArray.h"

generic s32 OrderedArray_DefaultComparer(T value1, T value2)
{
    return (s32)value1 - (s32)value2;
}

generic OrderedArray/*<T>*/ OrderedArray_Place(T* base, u32 capacity)
{
    return OrderedArray_Place/*<T>*/(base, capacity, OrderedArray_DefaultComparer);
}
generic OrderedArray/*<T>*/ OrderedArray_Place(T* base, u32 capacity, s32 (*comparer)(T, T))
{
    OrderedArray/*<T>*/ a = { 0 };
    a.Array = base;
    a.Capacity = capacity;
    a.Comparer = comparer;
    return a;
}

generic void OrderedArray_Add(OrderedArray/*<T>*/& orderedArray, T item)
{
    u32 i = 0;
    while (i < orderedArray.Size && orderedArray.Comparer(orderedArray.Array[i], item) < 0)
        i++;

    if (i < orderedArray.Size)
        for (int j = orderedArray.Size; j > i; j--)
            orderedArray.Array[j] = orderedArray.Array[j - 1];

    orderedArray.Array[i] = item;
    orderedArray.Size++;
}
generic void OrderedArray_RemoveAt(OrderedArray/*<T>*/& orderedArray, u32 i)
{
    for (; i < orderedArray.Size; i++)
        orderedArray.Array[i] = orderedArray.Array[i + 1];
    orderedArray.Size--;
}