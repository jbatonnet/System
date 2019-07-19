#ifndef _SYSTEM_OBSERVABLELIST_H_
#define _SYSTEM_OBSERVABLELIST_H_

#include <System/Common.h>
#include <System/Structures/Collections/Array.h>
#include <System/Structures/Collections/List.h>

template<typename T> class ObservableList : public List<T>
{
public:
    struct Change
    {
        u32 NewItemsIndex;
        Array<T> NewItems;

        u32 OldItemsIndex;
        Array<T> OldItems;

        Change() : NewItemsIndex(0), OldItemsIndex(0) { }
    };

public:
    virtual void Add(T item) override
    {
        List<T>::Add(item);

        // TODO: Generate change
    }
    virtual void Add(Reference<Collection<T>> items) override
    {
        List<T>::Add(items);

        // TODO: Generate change
    }
    virtual void Remove(T item) override
    {
        List<T>::Remove(item);

        // TODO: Generate change
    }
    virtual void Clear() override
    {
        Change change;

        T* buffer = new T[count];
        Memory::Copy<T>(base, buffer, count);

        change.OldItemsIndex = 0;
        change.OldItems = Array<T>(buffer, count);

        List<T>::Clear();

        Changed(this, change);
    }

    Event<Change> Changed;
};

#endif