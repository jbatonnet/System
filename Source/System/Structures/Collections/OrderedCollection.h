#ifndef _SYSTEM_ORDEREDCOLLECTION_H_
#define _SYSTEM_ORDEREDCOLLECTION_H_

#include <System/Structures/Collections/Collection.h>

template<typename T> class OrderedCollection : public Collection<T>
{
    class OrderedIterator : public Iterator<T>
    {
    private:
        Reference<List<T>> list;
        Function<s32, T, T> comparer;
        T lastItem;

    public:
        OrderedIterator(Reference<List<T>> list, const Function<s32, T, T>& comparer) : list(list), comparer(comparer) { }

        T GetCurrent() override
        {
        }
        bool Next() override
        {
            return false;
        }
    };

private:
    Reference<Collection<T>> collection;
    Function<s32, T, T> comparer;

public:
    OrderedCollection(Reference<Collection<T>> collection, const Function<s32, T, T>& comparer) : collection(collection), comparer(comparer) { }

    Reference<Iterator<T>> GetIterator() const override
    {
        return new OrderedIterator(collection->ToList(), filter);
    }
};

#endif