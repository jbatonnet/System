#ifndef _SYSTEM_FUNCTIONS_H_
#define _SYSTEM_FUNCTIONS_H_

#include <System/Base/Types.h>
#include <System/Base/Templates.h>

#include <System/Memory/Memory.h>

/// <summary>
/// Represents a callable function with the specified parameters returning a value
/// </summary>
template<typename Result, typename... Args> struct Function
{
public:
    enum { Size = 64 };

private:
    class Callable
    {
    public:
        virtual Result operator()(Args... parameters) = 0;
        virtual void* GetPointer() { return null; }
    };
    class NullCallable : public Callable
    {
    public:
        Result operator()(Args... parameters)
        {
			return DefaultValue<Result>::Get();
        }
    };
    class BaseCallable : public Callable
    {
    private:
        Result(*action)(Args...);

    public:
        BaseCallable(Result(*action)(Args...)) : action(action) { }

        Result operator()(Args... parameters)
        {
            return action(parameters...);
        }
        void* GetPointer() { return *(void**)&action; }
    };
    template<typename T> class ObjectCallable : public Callable
    {
    private:
        T* object;
        Result(T::*action)(Args...);

    public:
        ObjectCallable(T* object, Result(T::*action)(Args...)) : object(object), action(action) { }

        Result operator()(Args... parameters)
        {
            return (object->*action)(parameters...);
        }
    };
    template<typename T> class GenericCallable : public Callable
    {
        static_assert(sizeof(T) <= Function::Size, "Function is not big enough to carry this data");

    private:
        T callable;

    public:
        GenericCallable(T& other) : callable(other) { }

		GenericCallable(const GenericCallable& other) = delete;
		GenericCallable& operator=(const GenericCallable& other) = delete;

        Result operator()(Args... parameters)
        {
            return callable(parameters...);
        }
    };

    class Empty
    {
    public: Result operator()(Args... parameters);
    };

private:
    byte data[Size];

public:
    Function()
    {
for (u32 i = 0; i < Size; i++) data[i] = 0;
        new (data) NullCallable();
    }
    Function(Function<Result, Args...>&& function)
    {
        for (u32 i = 0; i < Size; i++)
            data[i] = function.data[i];
    }
    Function(const Function<Result, Args...>& function)
    {
        for (u32 i = 0; i < Size; i++)
            data[i] = function.data[i];
    }
    Function(Result(*action)(Args...))
    {
for (u32 i = 0; i < Size; i++) data[i] = 0;
        new (data) BaseCallable(action);
    }
    template<typename T> Function(T* object, Result(T::*action)(Args...))
    {
for (u32 i = 0; i < Size; i++) data[i] = 0;
        new (data) ObjectCallable<T>(object, action);
    }
    template<typename T> Function(T& object, Result(T::*action)(Args...))
    {
for (u32 i = 0; i < Size; i++) data[i] = 0;
        new (data) ObjectCallable<T>(&object, action);
    }
    template<typename T> Function(T& callable)
    {
for (u32 i = 0; i < Size; i++) data[i] = 0;
        new (data) GenericCallable<T>(callable);
    }

    Function<Result, Args...>& operator=(const Function<Result, Args...>& function)
    {
        for (u32 i = 0; i < Size; i++)
            data[i] = function.data[i];

        return *this;
    }

    Result operator()(Args... parameters) const
    {
        return ((Callable*)(data))->operator()(parameters...);
    }
    bool operator==(const Function<Result, Args...>& function) const
    {
        for (u32 i = 0; i < Size; i++)
            if (data[i] != function.data[i])
                return false;
        return true;
    }

    void* GetPointer() const
    {
        return ((Callable*)(data))->GetPointer();
    }
};

/// <summary>
/// Represents a callable function with the specified parameters and no return value
/// </summary>
template<typename... Args> using Action = Function<void, Args...>;

#endif