#ifndef _SYSTEM_SPINLOCK_H_
#define _SYSTEM_SPINLOCK_H_

#include <System/Base/Types.h>
#include <System/Runtime/Threading/Lockable.h>

namespace System
{
    namespace Runtime
    {
        class Spinlock : public ILockable
        {
        private:
            u32 state;

        public:
            Spinlock() : state(0) { }

            bool Lock(u32 timeout = 0);
            bool TryLock();

            void Unlock();
        };
    }
}

#endif