#ifndef _SYSTEM_THREAD_H_
#define _SYSTEM_THREAD_H_

#include <System/Base/Types.h>
#include <System/Base/Functions.h>

namespace System
{
    namespace Runtime
    {
        class Process;
        class Dispatcher;

        shared class Thread
        {
        protected:
            Thread() { }

        public:
            // Accessors
            virtual u32 GetId() const = 0;
            _declspec(property(get = GetId)) u32 Id;

            virtual string GetName() const = 0;
            _declspec(property(get = GetName)) string Name;

            virtual Process* GetProcess() const = 0;
            _declspec(property(get = GetProcess)) Process* Process;

            virtual Dispatcher* GetDispatcher() const = 0;
            virtual void SetDispatcher(Dispatcher* value) = 0;
            _declspec(property(get = GetDispatcher, put = SetDispatcher)) Dispatcher* Dispatcher;

            // Methods
            virtual void Start() = 0;
            virtual void Kill() = 0;

            // Static
            static Thread* GetCurrent();
            static Thread* Create(const Action<>& function, const string& name = "");
            static Thread* Start(const Action<>& function, const string& name = "");
        };
    }
}

#endif