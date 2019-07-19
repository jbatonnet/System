#ifndef _SYSTEM_ENTITY_H_
#define _SYSTEM_ENTITY_H_

#include <System/Common.h>

namespace System
{
    namespace Objects
    {
        class Entity
        {
        private:
            u32 id;

        public:
            Entity()
            {
                
            }

            _declspec(property(get = GetId)) u32 Id;
            u32 GetId() const { return id; }
        };
    }
}

#endif