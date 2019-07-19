#ifndef _SYSTEM_STACK_H_
#define _SYSTEM_STACK_H_

#include <System/Common.h>
#include <System/Memory/Memory.h>

template<typename T> class Stack : protected List<T>
{
public:
    Stack(u32 limit) : List<T>(limit)
    {
    }
    virtual ~Stack()
    {
    }

    // Methods
    void Push(const T& item)
    {
        Debug::Assert(count < limit, "Stack::Push() : The stack is full");

        u32 index = (current + count) % limit;
        base[index] = item;
        count++;
    }
    T& Pop()
    {
        Debug::Assert(count, "Stack::Pop() : The stack is empty");

        T& item = base[current];
        current = (current + 1) % limit;
        count--;

        return item;
    }
    void Clear()
    {
        current = 0;
        count = 0;
    }
};

#endif