#ifndef _SYSTEM_EVENT_H_
#define _SYSTEM_EVENT_H_

#include <System/Common.h>
#include <System/Structures/Collections/List.h>
#include <System/Runtime/Threading/Thread.h>
#include <System/Runtime/Threading/Dispatcher.h>

template<typename T> class Event
{
public:
    using Callback = Action<void*, T>;

protected:
    struct CallbackContext
    {
        System::Runtime::Thread* thread;
        Callback callback;

        CallbackContext() { }
        CallbackContext(System::Runtime::Thread* thread, const Callback& callback) : thread(thread), callback(callback) { }

        bool operator==(const CallbackContext& context)
        {
            return thread == context.thread && callback == context.callback;
        }
    };

    List<CallbackContext> callbacks;

public:
    void operator+=(const Callback& callback)
    {
        callbacks.Add(CallbackContext(System::Runtime::Thread::GetCurrent(), callback));
    }
    void operator-=(const Callback& callback)
    {
        callbacks.Remove(CallbackContext(System::Runtime::Thread::GetCurrent(), callback));
    }
    void operator()(void* origin, T parameter)
    {
        System::Runtime::Thread* thread = System::Runtime::Thread::GetCurrent();

        for (u32 i = 0; i < callbacks.Count; i++)
        {
            CallbackContext& context = callbacks.At(i);
            System::Runtime::Dispatcher* dispatcher = context.thread ? context.thread->Dispatcher : null;

            if (!dispatcher || context.thread == thread)
			    context.callback(origin, parameter);
            else
                context.thread->Dispatcher->Invoke(context.callback, origin, parameter);
        }
    }
};

template<typename T> struct ChangeEventParameter
{
    T& OldValue;
    T& NewValue;

    ChangeEventParameter(T& oldValue, T& newValue) : OldValue(oldValue), NewValue(newValue) { }
};
template<typename T> class ChangeEvent : public Event<ChangeEventParameter<T>>
{
public:
    void operator()(void* origin, T& oldValue, T& newValue)
    {
        ChangeEventParameter<T> change(oldValue, newValue);
        Event<ChangeEventParameter<T>>::operator()(origin, change);
    }
};

#endif