#ifndef _SYSTEM_LINKEDLIST_H_
#define _SYSTEM_LINKEDLIST_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>

#include <System/Memory/Memory.h>

/// <summary>
/// A container that represents a dynamically allocated list of elements
/// </summary>
template<typename T> class LinkedList : public Collection<T>, public Object
{
private:
    class LinkedListNode
    {
    private:
        T item;
        LinkedListNode* next;

    public:
        _declspec(property(get = GetItem)) T Item;
        T& GetItem() const { return item; }

        _declspec(property(get = GetNext)) LinkedListNode* Next;
        LinkedListNode* GetNext() const { return next; }
        void SetNext(LinkedListNode* value) { next = value; }
    };

public:
    LinkedList();

    void Add(T item)
    {

    }
};

#endif