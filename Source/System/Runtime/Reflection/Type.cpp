#include <System/Runtime/Reflection/Type.h>
#include <System/Debugging/Console.h>

using namespace System::Runtime;

List<Type*> Type::typeInfos;

#ifndef WINDOWS
Type* Type::Get(RTTI_TypeDescriptor* type, RTTI_ClassHierarchyDescriptor* hierarchy)
{
    Type* typeInfo = typeInfos.First([&](Type* t) -> bool { return t->RawName == &type->name; });

    if (!typeInfo)
    {
        typeInfo = new Type();
        typeInfo->type = type;
        typeInfo->ComputeName();
        typeInfos.Add(typeInfo);
    }

    if (!typeInfo->hierarchy && hierarchy)
    {
        typeInfo->hierarchy = hierarchy;
        typeInfo->ComputeBaseTypes();
    }

    return typeInfo;
}
#endif

void Type::ComputeName()
{
    // RawName
#ifndef WINDOWS
    rawName = &type->name;
#endif

    // Name
    name = rawName.SubString(4).Before('@');

    // FullName
    string tempFullName = rawName.SubString(4).Before("@@");
    while (tempFullName.Contains('@'))
    {
        fullName = fullName + tempFullName.AfterLast('@').AfterLast('?') + "::";
        tempFullName = tempFullName.BeforeLast('@');
    }
    fullName = fullName + tempFullName;
}
void Type::ComputeBaseTypes()
{
#ifndef WINDOWS
    for (u32 i = 1; i < hierarchy->BaseClassesCount; i++)
    {
        RTTI_BaseClassDescriptor* baseClass = hierarchy->BaseClasses[i];
        baseTypes.Add(Type::Get(baseClass->Type, baseClass->Hierarchy));
    }
#endif
}