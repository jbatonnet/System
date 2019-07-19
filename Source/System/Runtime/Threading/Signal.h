#ifndef _SYSTEM_SIGNAL_H_
#define _SYSTEM_SIGNAL_H_

#include <System/Common.h>

namespace System
{
    namespace Runtime
    {
        /// <summary>
        /// Provides a way to send signals between threads
        /// </summary>
        class Signal
        {
        private:
            u32 id;
            void Initialize();

        public:
            /// <summary>
            /// Constructs a new unique signal
            /// </summary>
            Signal();

            /// <summary>
            /// Triggers the signal and resume all the waiters
            /// </summary>
            virtual void Send(); // TODO: Returns the number of waiters ?

            /// <summary>
            /// Waits for the signal to be sent, or for the timeout to be ellapsed
            /// </summary>
            /// <param name="timeout">The number of milliseconds before the timeout, or 0 to disable the timeout</param>
            /// <returns>true if the signal was sent, false if this operation timed out</returns>
			virtual bool Wait(u32 timeout = 0) const;
        };
    }
}

#endif