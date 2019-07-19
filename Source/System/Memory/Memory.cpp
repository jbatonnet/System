#include <System/Memory/Memory.h>

void* Memory::Allocate(u32 count, MemoryType type, s16 value)
{
    if (type == MemoryType::Heap)
        return Allocate(count, value);

    // TODO: Allocation on the stack
    return null;
}

void* operator new(u32 size)
{
    return Memory::Allocate(size, 0);
}
void* operator new[](u32 size)
{
    return Memory::Allocate(size, 0);
}

void operator delete (void* pointer)
{
    if (pointer)
        Memory::Free(pointer);
}
void operator delete[](void* pointer)
{
    if (pointer)
        Memory::Free(pointer);
}

#ifndef WINDOWS
void* operator new(u32, void* pointer)
{
    return pointer;
}
void operator delete(void*, void*)
{
}
#endif