#ifndef _SYSTEM_QUEUE_H_
#define _SYSTEM_QUEUE_H_

#include <System/Common.h>
#include <System/Memory/Memory.h>

template<typename T> class Queue : public Object, public Collection<T>
{
private:
    T* base;
    u32 count;
    u32 limit;
    u32 current;

public:
    Queue(u32 limit) : base(null), count(0), limit(limit), current(0)
    {
        Debug::Assert(limit, "Not implemented yet");
        base = Memory::Allocate<T>(limit);
    }
    virtual ~Queue()
    {
        Memory::Free(base);
    }

    // Accessors
    _declspec(property(get = GetCount)) u32 Count;
    u32 GetCount() const { return count; }

    // Methods
    void Enqueue(const T& item)
    {
        Debug::Assert(count < limit, "Queue::Enqueue() : The queue is full");

        u32 index = (current + count) % limit;
        base[index] = item;
        count++;
    }
    T& Dequeue()
    {
        Debug::Assert(count, "Queue::Enqueue() : The queue is empty");

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