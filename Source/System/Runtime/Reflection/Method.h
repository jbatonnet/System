#ifndef _SYSTEM_METHODINFO_H_
#define _SYSTEM_METHODINFO_H_

#include <System/Common.h>
#include <System/Runtime/Reflection/Symbol.h>

namespace System
{
    namespace Runtime
    {
        enum class VirtualizationModifier
        {
            None,
            Abstract,
            Virtual,
        };

        class Method : public Object//Symbol
        {
        private:
            void* address;
            string rawName;

        public:
            template<typename C, typename T> static Method& AddFunction(const string& name, const Type& parent, void*);

            static Method* Load(void* address, string rawName);
        };
    }
}

#endif