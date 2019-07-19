#ifndef _SYSTEM_TYPE_H_
#define _SYSTEM_TYPE_H_

#ifndef WINDOWS
    #include <CRT/typeinfo>
#endif

#include <System/Common.h>

namespace System
{
    namespace Runtime
    {
        class Namespace;
        class Reflection;

		/// <summary>
		/// Represents a type declaration
		/// </summary>
        class Type : public Object
        {
            friend class Object;
            friend class Reflection;

        private:
            static List<Type*> typeInfos;

#ifdef WINDOWS
            void* type;
            void* hierarchy;
#else
            RTTI_TypeDescriptor* type;
            RTTI_ClassHierarchyDescriptor* hierarchy;
#endif

            string rawName;
            string name;
            string fullName;

            List<Type*> baseTypes;

            Type() : type(null), hierarchy(null) { }
#ifndef WINDOWS
            static Type* Get(RTTI_TypeDescriptor* type, RTTI_ClassHierarchyDescriptor* hierarchy);
#endif

            void ComputeName();
            void ComputeBaseTypes();

        public:
            // Creators
            template<typename T> static Type* Get()
            {
                const RTTI_TypeDescriptor& typeDescriptor = typeid(T);
                return Get((RTTI_TypeDescriptor*)&typeDescriptor, null);
            }
            static Type* Get(void* pointer)
            {
#ifdef WINDOWS
                return null;
#else
                RTTI_CompleteObjectLocator* objectLocator = RTTI_GetCompleteObjectLocator(pointer);
                return Get(objectLocator->Type, objectLocator->Hierarchy);
#endif
            }

            // Accessors
            _declspec(property(get = GetRawName)) string RawName;
            const string& GetRawName() const { return rawName; }
            _declspec(property(get = GetName)) string Name;
            const string& GetName() const { return name; }
            _declspec(property(get = GetFullName)) string FullName;
            const string& GetFullName() const { return fullName; }
            _declspec(property(get = GetBaseTypes)) List<Type*> BaseTypes;
            const List<Type*>& GetBaseTypes() const { return baseTypes; } // FIXME: Change to Collection<T>
        };
    }
}

#endif