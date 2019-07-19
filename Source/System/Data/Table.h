#ifndef _SYSTEM_TABLE_H_
#define _SYSTEM_TABLE_H_

#include <System/Common.h>
#include <System/Data/Record.h>
#include <System/Structures/Collections/Collection.h>

namespace System
{
    namespace Data
    {
        class Table : public Collection<Reference<Record>>
        {

        };
    }
}

#endif
