#ifndef _SYSTEM_PROFILER_H_
#define _SYSTEM_PROFILER_H_

namespace System
{
    namespace Runtime
    {
        class Profiler
        {
        public:
            static void Trace();
            static void Trace(const char* tag);
        };
    }
}

#endif