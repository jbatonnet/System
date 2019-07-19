#include <System/Base/Object.h>
#include <System/Base/String.h>
#include <System/Runtime/Reflection/Type.h>

#include <CRT/typeinfo>
#include <CRT/RTTI/RTTI.cpp>

#include <System/Debugging/Console.h>

using namespace System::Runtime;

#ifndef WINDOWS

bool Object::Is(const RTTI_TypeDescriptor& typeDescriptor)
{
    Type* typeInfo = GetType();
    Type* testType = Type::Get((RTTI_TypeDescriptor*)&typeDescriptor, null);

    if (typeInfo == testType)
        return true;

    for (u32 i = 0; i < typeInfo->BaseTypes.Count; i++)
        if (typeInfo->BaseTypes.At(i) == testType)
            return true;

    return false;
}

void* Object::As(const RTTI_TypeDescriptor& typeDescriptor)
{
    RTTI_CompleteObjectLocator* objectLocator = RTTI_GetCompleteObjectLocator(this);

    if (objectLocator->Type == &typeDescriptor)
        return this;

    for (u32 i = 0; i < objectLocator->Hierarchy->BaseClassesCount; i++)
        if (objectLocator->Hierarchy->BaseClasses[i]->Type == &typeDescriptor)
            return (byte*)this + 1 + objectLocator->Hierarchy->BaseClasses[i]->Pmd.MemberOffset + objectLocator->Hierarchy->BaseClasses[i]->Pmd.VTableOffset;

    return null;
}

#endif

string Object::ToString()
{
    return GetType()->FullName;
}
u32 Object::Hash()
{
    return 0;
}
Type* Object::GetType()
{
    return Type::Get(this);
}