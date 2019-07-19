#ifndef _SHELL_H_
#define _SHELL_H_

#include <System/System.h>

struct ShellCommand;

extern u32 ShellCommandsCount;
extern ShellCommand* ShellCommands[100];

struct ShellCommand
{
    char* Name;
    void (*Function)(const string&);
    char* Documentation;

    ShellCommand(char* name, void (*function)(const string&), char* documentation) : Name(name), Function(function), Documentation(documentation)
    {
        ShellCommands[ShellCommandsCount++] = this;
    }
};

#define AddShellCommand(name, documentation) void ShellFunction_##name(const string& parameters); ShellCommand ShellCommand_##name(#name, ShellFunction_##name, documentation); void ShellFunction_##name(const string& parameters)

#endif