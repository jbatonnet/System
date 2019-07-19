#ifndef _FILESAPPLICATION_H_
#define _FILESAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class Files : public Application
{
public:
    void Start(string parameters = "");
};

void FilesApplication_Main();

#endif