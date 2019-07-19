#ifndef _SYSTEM_EXECUTABLE_H_
#define _SYSTEM_EXECUTABLE_H_

#include <System/Runtime/Threading/Process.h>
#include <System/IO/Streams/Stream.h>
#include <System/IO/File.h>

namespace System
{
    namespace Runtime
    {
        class Executable : public Object
        {
        protected:
            bool allowMultipleInstances;

        public:
            virtual Process* CreateProcess() = 0;

            static Executable* Load(const string& path);
            static Executable* Load(IO::File* file);

            template<typename T> static Executable* Load(IO::Stream* stream)
            {
                (Executable*)(T*)0;
                return T::Load(stream);
            }
        };
    }
}

#endif