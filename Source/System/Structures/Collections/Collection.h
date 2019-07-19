#ifndef _SYSTEM_COLLECTION_H_
#define _SYSTEM_COLLECTION_H_

#include <System/Common.h>

template<typename T> class Iterator
{
public:
    virtual ~Iterator() { }

    _declspec(property(get = GetCurrent)) T Current;
    virtual T GetCurrent() = 0;

    virtual bool Next() = 0;
};

template<typename T> class Collection
{
    #include <System/Structures/Collections/FilteredCollection.h>
    #include <System/Structures/Collections/ProjectedCollection.h>
    #include <System/Structures/Collections/ConcatenedCollection.h>

public:
#ifndef __INTELLISENSE__
    virtual ~Collection() { }
#endif

    virtual Reference<Iterator<T>> GetIterator() const = 0;

    #pragma region Accessors

    /// <summary>
    /// Returns the first element of this collection
    /// </summary>
    virtual T First() const
    {
        auto iterator = GetIterator();
        Exception::Assert(iterator->Next(), "First : Collection does not contain any elements");

        return iterator->Current;
    }
    /// <summary>
    /// Returns the last element of this collection
    /// </summary>
    virtual T Last() const
    {
        auto iterator = GetIterator();
        Exception::Assert(iterator->Next(), "Last : Collection does not contain any elements");

        while (iterator->Next());

        return iterator->Current;
    }
    /// <summary>
    /// Returns the nth element of this collection
    /// </summary>
    virtual T At(u32 index) const
    {
        auto iterator = GetIterator();
        
        for (u32 i = 0; i <= index; i++)
            Exception::Assert(iterator->Next(), "At : Collection does not contain enough elements");

        return iterator->Current;
    }
    /// <summary>
    /// Returns true if this collection contains at least one element
    /// </summary>
    virtual bool Any() const
    {
        auto iterator = GetIterator();
        return iterator->Next();
    }
    /// <summary>
    /// Returns the number of elements in this collection
    /// </summary>
    virtual u32 Count() const
    {
        auto iterator = GetIterator();

        for (u32 count = 0;; count++)
            if (!iterator->Next())
                return count;
    }
    
    /*// <summary>
    /// Returns the nth element of this collection
    /// </summary>
    /// <param name="index">Index of the element to return</param>
    virtual T At(u32 index) const
    {
        auto iterator = GetIterator();

        for (int i = 0; i < index; i++)
            Exception::Assert(iterator->Next(), "Collection does not contain enough elements");

        return iterator->Current;
    }
    virtual s32 IndexOf(T element) const
    {
        auto iterator = GetIterator();

        for (int i = 0; iterator->Next(); i++)
            if (iterator->Current == element)
                return i;

        return -1;
    }*/

    #pragma endregion
    #pragma region Filters

    /// <summary>
    /// Returns a filtered subset of this collection with the specified predicate
    /// </summary>
    virtual Reference<Collection<T>> Where(const Function<bool, T>& filter) const
    {
        return new FilteredCollection<T>(this, filter);
    }
    /// <summary>
    /// Returns the elements of the collection of the specified type
    /// </summary>
    template<typename U> Reference<Collection<U*>> OfType() const
    {
        return Where([](T element) -> bool { return Type::Get<U>() == Type::Get(element); });
    }

    /// <summary>
    /// Returns the first element of this collection matching the specified filter
    /// </summary>
    virtual T First(const Function<bool, T>& filter) const
    {
        return Where(filter)->First();
    }
    /// <summary>
    /// Returns the last element of this collection matching the specified filter
    /// </summary>
    virtual T Last(const Function<bool, T>& filter) const
    {
        return Where(filter)->Last();
    }
    /// <summary>
    /// Returns true if this collection contains at least one element matching the specified filter
    /// </summary>
    virtual bool Any(const Function<bool, T>& filter) const
    {
        return Where(filter)->Any();
    }
    /// <summary>
    /// Returns the number of elements in this collection matching the specified filter
    /// </summary>
    virtual u32 Count(const Function<bool, T>& filter) const
    {
        return Where(filter)->Count();
    }

    #pragma endregion
    #pragma region Projections

    /// <summary>
    /// Returns a collection containing the specified projection of each element of this collection
    /// </summary>
    template<typename U> Reference<Collection<U>> Select(const Function<U, T>& projection) const
    {
        return new ProjectedCollection<T, U>(this, projection);
    }
    /// <summary>
    /// Returns a collection containing the each element of the specified projection of each element of this collection
    /// </summary>
    template<typename U> Reference<Collection<U>> SelectMany(const Function<Reference<Collection<U>>, T>& projection) const
    {
        return new ConcatenedCollection<U>(new ProjectedCollection<T, Reference<Collection<U>>>(this, projection));
    }

    #pragma endregion

    // TODO: Ordering
    /*template<typename U> Reference<Collection<T>> OrderBy(Function<U, T> comparer)
    {
    }
    template<typename U> Reference<Collection<T>> OrderByDescending(Function<U, T> comparer)
    {
    }*/

    #pragma region Other

    /// <summary>
    /// Returns the concatenation of this collection and the specified one
    /// </summary>
    Reference<Collection<T>> Concat(Reference<Collection<T>> other)
    {
        return new ConcatenedCollection(this, other);
    }

    /*// <summary>
    /// Returns a list containing elements of this collection
    /// </summary>
    Reference<List<T>> ToList() const
    {
        List<T>* list = new List<T>();

        Reference<Iterator<T>> iterator = GetIterator();
        while (iterator->Next())
            list->Add(iterator->GetCurrent());

        return list;
    }*/

    #pragma endregion

    // ToArray
    // ToDictionary
};

template<typename T> class RangeIterator : public Iterator<T>
{
private:
	Reference<Iterator<T>> iterator;
	bool end;

public:
	RangeIterator() { }
	RangeIterator(const Reference<Iterator<T>>& iterator) : iterator(iterator), end(false)
    {
        Next();
    }

	T GetCurrent()
	{
		return iterator->GetCurrent();
	}
	bool Next()
	{
		end = !iterator->Next();
		return !end;
	}

	bool operator!=(RangeIterator<T> iterator)
	{
		return !end;
	}
	void operator++()
	{
		Next();
	}
	T operator*()
	{
		return GetCurrent();
	}
};

template<typename T> RangeIterator<T> begin(const Collection<T>& collection)
{
	return RangeIterator<T>(collection.GetIterator());
}
template<typename T> RangeIterator<T> end(const Collection<T>& collection)
{
	return RangeIterator<T>();
}

template<typename T> RangeIterator<T> begin(Collection<T>* collection)
{
	return RangeIterator<T>(collection->GetIterator());
}
template<typename T> RangeIterator<T> end(Collection<T>* collection)
{
	return RangeIterator<T>();
}

template<typename T> RangeIterator<T> begin(Reference<Collection<T>> collection)
{
	return RangeIterator<T>(collection->GetIterator());
}
template<typename T> RangeIterator<T> end(Reference<Collection<T>> collection)
{
	return RangeIterator<T>(collection->GetIterator());
}

#endif