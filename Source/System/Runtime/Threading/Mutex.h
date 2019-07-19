#ifndef _SYSTEM_MUTEX_H_
#define _SYSTEM_MUTEX_H_

#include <System/Common.h>
#include <System/Runtime/Threading/Lockable.h>

namespace System
{
    namespace Runtime
    {
        /// <summary>
        /// Provides a way to lock and synchronize different threads
        /// </summary>
        class Mutex : public ILockable
        {
        private:
            u32 id;
            bool locked;
            void Initialize();

        public:
            /// <summary>
            /// Constructs a new unique mutex
            /// </summary>
            Mutex();
            /// <summary>
            /// Constructs a new unique mutex with the specified initial state
            /// </summary>
            /// <param name="locked">The initial state of this mutex</param>
            Mutex(bool locked);

            /// <summary>
            /// Lock this mutex. If it is already locked, it will wait until it is unlocked
            /// </summary>
            /// <param name="timeout">The number of milliseconds before the timeout, or 0 to disable the timeout</param>
            /// <returns>true if the lock was successfully acquired, false if this operation timed out</returns>
            bool Lock(u32 timeout = 0);

            /// <summary>
            /// Unlock this mutex
            /// </summary>
            void Unlock();
        };
    }
}

#endif