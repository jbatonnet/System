#ifndef _SYSTEM_OBJECT_H_
#define _SYSTEM_OBJECT_H_

#ifndef WINDOWS
    #include <CRT/typeinfo>
#endif

#include <System/Base/Types.h>

namespace System
{
    namespace Runtime
    {
        class Type;
    }
}

struct String;

/// <summary>
/// The base class of every object
/// </summary>
class Object
{
private:
#ifndef WINDOWS
    bool Is(const RTTI_TypeDescriptor& typeDescriptor);
    void* As(const RTTI_TypeDescriptor& typeDescriptor);
#endif

public:
    virtual ~Object() { }

    /// <summary>
    /// Gets a string representation of this object
    /// </summary>
    virtual String ToString();

    /// <summary>
    /// Compute a hash of this object
    /// </summary>
    virtual u32 Hash();

    /// <summary>
    /// Gets the type infomartions of this object
    /// </summary>
    /// <returns>The type infomartions of this object</returns>
    System::Runtime::Type* GetType();

    /// <summary>
    /// Check if this object is of the specified type
    /// </summary>
    /// <returns>true if this object is of the specified type, false otherwise</returns>
    template<typename T> bool Is()
    {
#ifdef WINDOWS
        return dynamic_cast<T*>(this) != nullptr;
#else
        return Is(typeid(T));
#endif
    }

    /// <summary>
    /// Get the current object dynamically casted to the specified type
    /// </summary>
    /// <returns>This object dynamically casted to the specified type</returns>
    template<typename T> T* As()
    {
#ifdef WINDOWS
        return dynamic_cast<T*>(this);
#else
        return (T*)As(typeid(T));
#endif
    }
};

#endif