#ifndef _KERNEL_REFLECTION_H_
#define _KERNEL_REFLECTION_H_

#include <System/Runtime/Reflection/Namespace.h>
#include <System/Runtime/Reflection/Type.h>
#include <System/Runtime/Reflection/Method.h>
#include <System/Runtime/Reflection/Constructor.h>
#include <System/Runtime/Reflection/Property.h>

namespace System
{
    namespace Runtime
    {
        class Reflection
        {
        public:
            static void Initialize();

        private:
            static Namespace* RegisterNamespace(const string& name);
            static Namespace* RegisterNamespace(Namespace* parent, const string& name);

			template<typename T> static Type* RegisterType(const string& name);
			template<typename T> static Type* RegisterType(Namespace* parent, const string& name);
            template<typename T> static Type* RegisterType(Type* parent, const string& name);

            template<typename T, typename... Parameters> static Constructor* RegisterConstructor(Type* parent);

            template<typename... Parameters> static Method* RegisterAction(Type* parent, const string& name);
            template<typename Result, typename... Parameters> static Method* RegisterFunction(Type* parent, const string& name);

			template<typename T> static Property* RegisterProperty(Type* parent, const string& name, Method* getAccessor, Method* setAccessor);
        };
    }
}

#endif