#ifndef _DATABASESAPPLICATION_H_
#define _DATABASESAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class Databases : public Application
{
public:
    void Start(string parameters = "");
};

void DatabasesApplication_Main();

#endif