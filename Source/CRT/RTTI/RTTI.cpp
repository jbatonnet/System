#include "RTTI.h"

type_info::type_info(const type_info& other) : name(other.name) { }
//type_info::type_info(const char* name) : name((char*)name) { }
type_info::~type_info() { }

bool type_info::operator==(const type_info& other) const
{
    return name == other.name;
}
bool type_info::operator!=(const type_info& other) const
{
    return name != other.name;
}

template<typename T>
T ReadData(u32 pointer)
{
    return *((const T*)pointer);
}
template<typename T,typename U>
T ReadData(const U* pointer)
{
    return ReadData<T>((u32)pointer);
}

// We assume the vftable is at offset 0
// If it is not the case, we assume the vbtable should be at offset 0, and with its first entry equal to 0 (point to itself).
// Then its second entry should contain the offset of vftable
template<typename T>
RTTI_CompleteObjectLocator* RTTI_GetCompleteObjectLocator(const T* pointer) //not have vbtable
{
    u32 offset = 0;
    if (ReadData<u32>(ReadData<u32>(pointer)) == 0)
        offset = ReadData<u32>(ReadData<u32>(pointer) + 4);

    return (RTTI_CompleteObjectLocator*)(ReadData<u32>(ReadData<u32>((u32)pointer + offset) - 4));
}

void* __RTtypeid(void* pointer)
{
    if (!pointer)
        return 0;

    RTTI_CompleteObjectLocator* completeObjectLocator = RTTI_GetCompleteObjectLocator(pointer);
    RTTI_TypeDescriptor* typeDescriptor = completeObjectLocator->Type;

    return typeDescriptor;
}