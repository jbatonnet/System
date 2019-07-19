#ifndef _SYSTEM_CONSTRUCTOR_H_
#define _SYSTEM_CONSTRUCTOR_H_

#include <System/Common.h>
#include <System/Runtime/Reflection/Symbol.h>

namespace System
{
    namespace Runtime
    {
        class Constructor : public Object // Symbol
        {
        private:
            string rawName;

        public:
            static Constructor* Load(void* address, string rawName);
        };
    }
}

#endif