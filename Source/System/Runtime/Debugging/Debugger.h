#ifndef _SYSTEM_DEBUGGER_H_
#define _SYSTEM_DEBUGGER_H_

namespace System
{
    namespace Runtime
    {
        /// <summary>
        /// A set of function to help interact with a debugger
        /// </summary>
        class Debugger
        {
        public:
            /// <summary>
            /// If a debugger is present, break when this code is executed
            /// </summary>
            static void Break();
        };
    }
}

#endif