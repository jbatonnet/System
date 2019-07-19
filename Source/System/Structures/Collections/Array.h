#ifndef _SYSTEM_ARRAY_H_
#define _SYSTEM_ARRAY_H_

template<typename T> class ArrayIterator : public Iterator<T>
{
private:
    T* pointer;
    u32 count;

public:
    ArrayIterator(T* pointer, u32 count) : count(count), pointer(pointer - 1) { }

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

template<typename T, u32 Size = 0> class Array : public Collection<T>
{
private:
    T buffer[Size];
    u32 size;

public:
    Array() { }
    Array(Array&& other) = delete;
    Array(const Array& other) = delete;

    /// <summary>
    /// Returns the number of elements in this array
    /// </summary>
    _declspec(property(get = GetCount)) u32 Count;
    u32 GetCount() const { return size; }

    T& operator[](s32 index)
    {
        if (index < 0)
            index += size;

        Exception::Assert(index >= 0 && index < size, "Out of bounds");

        return buffer[index];
    }

    Reference<Iterator<T>> GetIterator() const override
    {
        return new ArrayIterator<T>(buffer, count);
    }
};

template<typename T> class Array<T, 0> : public Collection<T>
{
private:
    T* buffer;
    u32 size;

public:
    Array() : buffer(null), size(0) { }
    Array(T* buffer, u32 size) : buffer(buffer), size(size) { }

    /// <summary>
    /// Returns the number of elements in this array
    /// </summary>
    _declspec(property(get = GetCount)) u32 Count;
    u32 GetCount() const { return size; }

    T& operator[](s32 index)
    {
        if (index < 0)
            index += size;

        Exception::Assert(index >= 0 && index < size, "Out of bounds");

        return buffer[index];
    }

    virtual Reference<Iterator<T>> GetIterator() const override
    {
        return new ArrayIterator<T>(buffer, size);
    }
};

#endif