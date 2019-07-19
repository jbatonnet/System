#ifndef _SYSTEM_LIST_H_
#define _SYSTEM_LIST_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>
#include <System/Structures/Collections/InitializerCollection.h>

#include <System/Memory/Memory.h>

#include <System/Runtime/Threading/Mutex.h>

/// <summary>
/// A container that represents a dynamically allocated list of elements
/// </summary>
template<typename T> class List : public Collection<T>, public Object
{
    class ListIterator : public Iterator<T>
    {
    private:
        T* pointer;
        u32 count;

    public:
        ListIterator(T* pointer, u32 count) : count(count), pointer(pointer - 1) { }

        bool IsEnd()
        {
            return !count;
        }
        T GetCurrent()
        {
            return *pointer;
        }
        bool Next()
        {
            if (!count)
                return false;

            pointer++;
            count--;

            return true;
        }
    };

protected:
    T* base{ nullptr };
    u32 count;
    u32 limit;

public:
    List(const InitializerCollection<T>& items) : count(0), limit(0)
    {
        // TODO: Reserve with initializer collection size
        for (const T& item : items)
            Add(item);
    }
    List(u32 limit = 0) : count(0), limit(limit)
    {
        if (limit)
            base = Memory::Allocate<T>(limit);
    }
    List(const List& other)
    {
        /*Test::Action(0xDEAD0000);
        for (u32 i = 0; i < other.count; i++)
            Test::Function((u32)base[i]);*/

        count = other.count;
        limit = other.limit;

        base = Memory::Allocate<T>(count);
        Memory::Copy<T>(other.base, base, count);
    }
    virtual ~List()
    {
        Memory::Free(base);
    }

    _declspec(property(get = GetCount)) u32 Count;
    u32 GetCount() const { return count; }

    /// <summary>
    /// Add the specified element to this list
    /// </summary>
    /// <param name="item">The element to add</param>
    virtual void Add(T item)
    {
        if (limit && count == limit)
            return;

        if (!limit)
        {
            T* newBase = Memory::Allocate<T>(count + 1);

            if (base)
            {
                Memory::Copy<T>(base, newBase, count);
                Memory::Free(base);
            }

            base = newBase;
        }

        base[count] = item;
        count++;
    }
    virtual void Add(Reference<Collection<T>> items)
    {
        Reference<Iterator<T>> iterator = items->GetIterator();
        while (iterator->Next())
            Add(iterator->Current);
    }
    virtual void Remove(T item)
    {
        if (!count)
            return;

        u32 i = 0;
        for (i; i < count; i++)
            if (base[i] == item)
                break;
        if (i >= count)
            return;

        T* newBase = Memory::Allocate<T>(count - 1);
        Memory::Copy<T>(base, newBase, i);
        Memory::Copy<T>(base + i + 1, newBase + i, count - 1 - i);
        Memory::Free(base);
        base = newBase;

        count--;
    }
    virtual void Remove(Reference<Collection<T>> items)
    {
        Reference<Iterator<T>> iterator = items->GetIterator();
        while (iterator->Next())
            Remove(iterator->Current);
    }
    virtual void Clear()
    {
        if (!limit)
        {
            Memory::Free(base);
            base = null;
        }

        count = 0;
    }

    // Operators
    List<T>& operator=(const List<T>& other)
    {
        //Console::WriteLine("List<T>& List<T>::operator=(const List<T>& other)");
        //Test::Action(0xDEAD0001);

        count = other.count;
        limit = other.limit;

        base = Memory::Allocate<T>(count);
        Memory::Copy<T>(other.base, base, count);

        return *this;
    }
    List<T>& operator=(List<T>&& other)
    {
        //Console::WriteLine("List<T>& List<T>::operator=(List<T>&& other)");
        //Test::Action(0xDEAD0002);

        count = other.count;
        limit = other.limit;
        base  = other.base;

        other.base = null;

        return *this;
    }

    // Accesors
    T operator[](u32 index) const
    {
        return At(index);
    }
    virtual T At(u32 index) const override
    {
        Exception::Assert(index < count, "List::At() : Out of bounds");
        T& value = base[index];

        return value;
    }

    // Order
    void Move(u32 from, u32 to)
    {
        Exception::Assert(from < count && to < count, "List::Move() : Out of bounds");
        if (from == to)
            return;
        if (from > to)
            return Move(to, from);

        u8* bytes = (u8*)Memory::Allocate(sizeof(T));

        Memory::Copy<T>(base + from, bytes);
        Memory::Copy<T>(base + from + 1, base + from, to - from);
        Memory::Copy<T>(bytes, base + to);

        Memory::Free(bytes);
    }
    void Swap(u32 from, u32 to)
    {
        Exception::Assert(from < count && to < count, "List::Swap() : Out of bounds");
        if (from == to)
            return;

        u8* bytes = Memory::Allocate(sizeof(T));

        Memory::Copy<T>(&base[to], bytes);
        Memory::Copy<T>(&base[from], &base[to]);
        Memory::Copy<T>(bytes, &base[from]);

        Memory::Free(bytes);
    }
    void BringToFront(u32 index)
    {
        Move(index, 0);
    }
    void SendToBack(u32 index)
    {
        Move(index, count - 1);
    }

    // Collection
    Reference<Iterator<T>> GetIterator() const override
    {
        return new ListIterator(base, count);
    }


    #pragma region Accessors

    /// <summary>
    /// Returns the first element of this list
    /// </summary>
    virtual T First() const override
    {
        Exception::Assert(count > 0);
        return base[0];
    }
    /// <summary>
    /// Returns the last element of this list
    /// </summary>
    virtual T Last() const override
    {
        Exception::Assert(count > 0);
        return base[count - 1];
    }
    /// <summary>
    /// Returns true if this list contains at least one element
    /// </summary>
    virtual bool Any() const override
    {
        return !!count;
    }

    virtual s32 IndexOf(T element)
    {
        for (u32 i = 0; i < count; i++)
            if (base[i] == element)
                return i;
        return -1;
    }

    #pragma endregion
    #pragma region Filters

    /// <summary>
    /// Returns the first element of this list matching the specified filter
    /// </summary>
    virtual T First(const Function<bool, T>& filter) const override
    {
        for (u32 i = 0; i < count; i++)
            if (filter(base[i]))
                return base[i];

        return DefaultValue<T>::Get();
    }
    /// <summary>
    /// Returns the last element of this list matching the specified filter
    /// </summary>
    virtual T Last(const Function<bool, T>& filter) const override
    {
        for (u32 i = count - 1; i >= 0; i--)
            if (filter(base[i]))
                return base[i];

        return DefaultValue<T>::Get();
    }
    /// <summary>
    /// Returns true if this list contains at least one element matching the specified filter
    /// </summary>
    virtual bool Any(const Function<bool, T>& filter) const override
    {
        for (u32 i = 0; i < count; i++)
            if (filter(base[i]))
                return true;

        return false;
    }

    #pragma endregion





    // Basics
    T Sum() const
    {
        T sum = 0;
        for (int i = 0; i < count; i++)
            sum += base[i];

        return sum;
    }

    // Filters


    template<typename Func> List<T>* Where(Func& predicate) const
    {
        List<T>* result = new List<T>();

        for (u32 i = 0; i < count; i++)
            if (predicate(base[i]))
                result->Add(base[i]);

        return result;
    }
    /*template<typename Result, typename Func> List<Result> Select(Func& predicate) const
    {
        List<Result> result(Count);

        //Test::Action(0xDEAD0003);
        //for (u32 i = 0; i < count; i++)
        //    Test::Function((u32)base[i]);

        for (u32 i = 0; i < count; i++)
            result.Add(predicate(base[i]));

        //for (u32 i = 0; i < count; i++)
        //    Test::Function((u32)result[i]);

        return result;
    }*/
};

#endif