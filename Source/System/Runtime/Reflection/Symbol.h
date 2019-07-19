#ifndef _SYSTEM_SYMBOL_H_
#define _SYSTEM_SYMBOL_H_

#include <System/Common.h>

namespace System
{
    namespace Runtime
    {
        enum class AccessibilityModifier
        {
            Public,
            Protected,
            Private,
            Static
        };

        class Symbol : public Object
        {
        protected:
            string name;
            AccessibilityModifier accessibility;

        public:
            _declspec(property(get = GetName)) string Name;
            string GetName() const { return name; }

            virtual string ToString() = 0;
        };
    }
}

#endif