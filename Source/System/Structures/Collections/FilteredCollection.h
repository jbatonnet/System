#ifndef _SYSTEM_FILTEREDCOLLECTION_H_
#define _SYSTEM_FILTEREDCOLLECTION_H_

#include <System/Structures/Collections/Collection.h>

template<typename T> class FilteredCollection : public Collection<T>
{
    class FilteredIterator : public Iterator<T>
    {
    private:
        Reference<Iterator<T>> iterator;
        Function<bool, T> filter;

    public:
        FilteredIterator(Reference<Iterator<T>> iterator, const Function<bool, T>& filter) : iterator(iterator), filter(filter) { }

        T GetCurrent() override
        {
            return iterator->GetCurrent();
        }
        bool Next() override
        {
            while (iterator->Next())
                if (filter(iterator->GetCurrent()))
                    return true;

            return false;
        }
    };

private:
    const Collection<T>* collection;
    Function<bool, T> filter;

public:
    FilteredCollection(const Collection<T>* collection, const Function<bool, T>& filter) : collection(collection), filter(filter) { }

    Reference<Iterator<T>> GetIterator() const override
    {
        return new FilteredIterator(collection->GetIterator(), filter);
    }
};

#endif