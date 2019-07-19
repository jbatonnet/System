#ifndef _EDITORAPPLICATION_H_
#define _EDITORAPPLICATION_H_

#include <System/Applications/Application.h>

class EditorApplication : public Application
{
public:
    void Start(string parameters = "");
};

void EditorApplication_Main();

#endif