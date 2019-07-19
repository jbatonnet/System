#ifndef _SYSTEM_PROPERTY_H_
#define _SYSTEM_PROPERTY_H_

#include <System/Common.h>

namespace System
{
    namespace Runtime
    {
        class Property : public Object//Symbol
        {
        public:
            template<typename T> static Property& Add(const string& name, const Type& parent, const Method& getter);
            template<typename T> static Property& AddProperty(const string& name, const Type& parent, const Method& getter, const Method& setter);
        };
    }
}

#endif