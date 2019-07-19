#ifndef _SYSTEM_USER_H_
#define _SYSTEM_USER_H_

#include <System/Objects/Entity.h>

namespace System
{
    namespace Objects
    {
        class User : public Entity
        {
        private:
            string name;

        public:
            User(string name) : name(name) { }

            _declspec(property(get = GetName)) string Name;
            string GetName() const { return name; }
        };
    }
}

#endif