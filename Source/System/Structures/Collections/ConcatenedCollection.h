#ifndef _SYSTEM_CONCATENEDCOLLECTION_H_
#define _SYSTEM_CONCATENEDCOLLECTION_H_

#include <System/Structures/Collections/Collection.h>

template<typename T> class ConcatenedCollection : public Collection<T>
{
    class ConcatenedIterator : public Iterator<T>
    {
    private:
        Reference<Iterator<Reference<Collection<T>>>> mainIterator;
        Reference<Iterator<T>> subIterator;

    public:
        ConcatenedIterator(Reference<Iterator<Reference<Collection<T>>>> iterator) : mainIterator(iterator), subIterator(null) { }

        T GetCurrent() override
        {
            return subIterator->GetCurrent();
        }
        bool Next() override
        {
            while (!subIterator || !subIterator->Next())
            {
                if (!mainIterator->Next())
                    return false;

                Reference<Collection<T>> collection = mainIterator->GetCurrent();
                subIterator = collection->GetIterator();
            }

            return true;
        }
    };

private:
    Reference<Collection<Reference<Collection<T>>>> collections;

public:
    ConcatenedCollection(Reference<Collection<Reference<Collection<T>>>> collections) : collections(collections) { }
    ConcatenedCollection(Reference<Collection<T>> collection1, Reference<Collection<T>> collection2)
    {
        List<Reference<Collection<T>>>* list = new List<Reference<Collection<T>>>();

        list->Add(collection1);
        list->Add(collection2);

        collections = list;
    }

    Reference<Iterator<T>> GetIterator() const override
    {
        return new ConcatenedIterator(collections->GetIterator());
    }
};

#endif