#ifndef _SYSTEM_APPLICATION_H_
#define _SYSTEM_APPLICATION_H_

#include <System/Common.h>

class Application : public Object
{
public:
    virtual void Start(string parameters = "") = 0;
};

#endif