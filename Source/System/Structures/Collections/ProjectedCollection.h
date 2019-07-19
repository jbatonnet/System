#ifndef _SYSTEM_PROJECTEDCOLLECTION_H_
#define _SYSTEM_PROJECTEDCOLLECTION_H_

#include <System/Structures/Collections/Collection.h>

template<typename From, typename To> class ProjectedCollection : public Collection<To>
{
    class ProjectedIterator : public Iterator<To>
    {
    private:
        Reference<Iterator<From>> iterator;
        Function<To, From> projection;

    public:
        ProjectedIterator(Reference<Iterator<From>> iterator, const Function<To, From>& projection) : iterator(iterator), projection(projection) { }

        To GetCurrent() override
        {
            return projection(iterator->GetCurrent());
        }
        bool Next() override
        {
            return iterator->Next();
        }
    };

private:
    Reference<Collection<From>> collection;
    Function<To, From> projection;

public:
    ProjectedCollection(Reference<Collection<From>> collection, const Function<To, From>& projection) : collection(collection), projection(projection) { }

    Reference<Iterator<To>> GetIterator() const override
    {
        return new ProjectedIterator(collection->GetIterator(), projection);
    }
};

#endif