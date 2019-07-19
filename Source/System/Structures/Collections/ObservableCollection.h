#ifndef _SYSTEM_COLLECTION_H_
#define _SYSTEM_COLLECTION_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>

template<typename T> class ObservableCollection : Collection<T>
{
public:
    struct Change
    {
        u32 NewItemsIndex;
        Reference<Collection<T>> NewItems;

        u32 OldItemsIndex;
        Reference<Collection<T>> OldItems;
    };

public:
    virtual ~ObservableCollection() { }

    virtual Reference<Iterator<T>> GetIterator() const = 0;
};

#endif