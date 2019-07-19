#ifndef _SYSTEM_PROCESS_H_
#define _SYSTEM_PROCESS_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>

namespace System
{
    namespace Runtime
    {
        class Thread;

        shared class Process
        {
        public:
            // Accessors
            virtual const Collection<Thread*>& GetThreads() const = 0;
            _declspec(property(get = GetThreads)) Collection<Thread*>& Threads;

            // Methods
            virtual void Start() = 0;
            virtual void Kill() = 0;

            // Static
            static Process* GetCurrent();
        };
    }
}

#endif