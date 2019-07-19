#ifndef _SYSTEM_NAMESPACE_H_
#define _SYSTEM_NAMESPACE_H_

#include <System/Common.h>

namespace System
{
    namespace Runtime
    {
        class Reflection;

        class Namespace : public Object
        {
            friend class Reflection;

        private:
            Namespace* parent;
            string name;
        };
    }
}

#endif