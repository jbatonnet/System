#ifndef _SYSTEM_REFERENCE_H_
#define _SYSTEM_REFERENCE_H_

#include <System/Base/Types.h>
#include <System/Base/Functions.h>

/// <summary>
/// A reference structure to store a pointer to objects
/// </summary>
template<typename T> struct Pointer
{
protected:
    T* pointer;

public:
    Pointer() : pointer(null) { }
    Pointer(T* pointer) : pointer(pointer) { }
    Pointer(T& object) : pointer(&object) { }
    Pointer(const Pointer<T>& other) : pointer(other.pointer) { }
    Pointer(Pointer<T>&& other) : pointer(other.pointer) { }

    _declspec(property(get = GetValid)) bool Valid;
    bool GetValid() const
    {
        return pointer != null;
    }

    /// <summary>
    /// Provides access to the referenced object
    /// </summary>
    T* operator->() const
    {
        Exception::Assert(pointer, "NullReferenceException :)");
        return pointer;
    }

    /// <summary>
    /// Returns the referenced object
    /// </summary>
    T& operator*() const
    {
        return *pointer;
    }

    bool operator==(const Pointer<T>& other)
    {
        return other.pointer == pointer;
    }
};

template<typename T> struct Dynamic;

/// <summary>
/// A reference structure to automatically free allocated objects
/// </summary>
template<typename T> struct Reference : Pointer<T>
{
public:
    static const Reference<T> Invalid;

private:
    u32* counter;

protected:
    Reference(T* pointer, u32* counter) : Pointer(pointer), counter(counter) { }

public:
	Reference() : counter(null) { }
    Reference(const T* pointer) : Pointer((T*)pointer)
    {
        counter = new u32(1);
    }
    Reference(T* pointer) : Pointer(pointer)
    {
        counter = new u32(1);
    }
    Reference(const Reference<T>& other) : counter(other.counter), Pointer(other.pointer)
    {
        if (counter)
            *counter = *counter + 1;
    }
    Reference(Reference<T>&& other) : counter(other.counter), Pointer(other.pointer)
    {
        if (counter)
            *counter = *counter + 1;
    }
    Reference(const Pointer<T>& other) : Pointer(other), counter(null) { }
    Reference(Pointer<T>&& other) : Pointer(other), counter(null) { }
    Reference(Dynamic<T>& other);
    Reference(Dynamic<T>&& other);
    ~Reference()
    {
        if (!counter)
            return;

        *counter = *counter - 1;
        if (*counter == 0)
        {
            delete counter;
            delete[] pointer;

            counter = null;
        }
    }
    
    _declspec(property(get = GetValid)) bool Valid;
    bool GetValid() const
    {
        return pointer != null && counter != null && *counter > 0;
    }

    Reference<T>& operator=(const Reference<T>& other)
    {
        this->~Reference();
        new (this) Reference(other);

        return *this;
    }
    /*void operator=(Reference<T>&& other)
    {
        pointer = other.pointer;
        counter = other.counter;

        *counter++;
        WriteLine("operator=(Reference<T>&& other) : 0x%x, %d", pointer, *counter);
    }
    */
};

template<typename T> const Reference<T> Reference<T>::Invalid;

/// <summary>
/// A reference structure to automatically load objects on demand
/// </summary>
template<typename T> struct Dynamic
{
    template<typename U>
    friend struct Reference;

private:
    Reference<T> object;
    Function<Reference<T>> loader;

public:
    Dynamic(const Function<Reference<T>>& loader) : loader(loader) { }

    /// <summary>
    /// Provides access to the referenced object
    /// </summary>
    T* operator->()
    {
        if (!object.Valid)
            Load();
        
        Exception::Assert(object.Valid, "NullReferenceException :)");
        return object.operator->();
    }

    /// <summary>
    /// Returns the referenced object
    /// </summary>
    T& operator*()
    {
        if (!object.Valid)
            Load();

        Exception::Assert(object.Valid, "NullReferenceException :)");
        return pointer.operator*();
    }

    void Load()
    {
        object = loader();
    }
};

template<typename T> Reference<T>::Reference(Dynamic<T>& other)
{
    other.Load();

    pointer = other.object.pointer;
    counter = other.object.counter;

    if (counter)
        *counter = *counter + 1;
}
template<typename T> Reference<T>::Reference(Dynamic<T>&& other)
{
    other.Load();

    pointer = other.object.pointer;
    counter = other.object.counter;

    if (counter)
        *counter = *counter + 1;
}

#endif