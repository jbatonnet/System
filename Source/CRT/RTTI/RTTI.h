#ifndef _RTTI_H_
#define _RTTI_H_

typedef unsigned char      u8;
typedef int                s32;
typedef unsigned           u32;
typedef long long          s64;
typedef unsigned long long u64;

class type_info
{
public:
    void* data;
    char name;

public:
    type_info(const type_info&);
    //explicit type_info(const char*);
    virtual ~type_info();

    bool operator==(const type_info&) const;
    bool operator!=(const type_info&) const;
};

typedef type_info RTTI_TypeDescriptor;
struct RTTI_ClassHierarchyDescriptor;

struct RTTI_PMD
{
    s32 MemberOffset; // vftable offset
    s32 VTableOffset; // vbtable offset
    s32 vdisp; // vftable offset (for virtual base class)
};
struct RTTI_BaseClassDescriptor
{
    RTTI_TypeDescriptor* Type;
    u32 BaseClassesCount;
    RTTI_PMD Pmd;
    u32 Attributes;
    RTTI_ClassHierarchyDescriptor* Hierarchy; //of this base class
};
struct RTTI_ClassHierarchyDescriptor
{
    u32 Signature;
    u32 Attributes; // bit 0 multiple inheritance, bit 1 virtual inheritance
    u32 BaseClassesCount; // at least 1 (all base classes, including itself)
    RTTI_BaseClassDescriptor** BaseClasses;
};
struct RTTI_CompleteObjectLocator
{
    u32 Signature;
    u32 Offset; //vftable offset to this
    u32 CdOffset;
    RTTI_TypeDescriptor* Type;
    RTTI_ClassHierarchyDescriptor* Hierarchy;
};

template<typename T>
RTTI_CompleteObjectLocator* RTTI_GetCompleteObjectLocator(const T* pointer);

#endif