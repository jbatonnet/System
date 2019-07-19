#include "Shell.h"

using namespace System::IO;

#define COMMAND_MAX_LENGTH 77

extern "C" void* memset(void* ptr, int value, size_t num)
{
    Memory::Clear(ptr, num, value);
    //Memory::Set(ptr, value, num);
    return ptr;
}
extern "C" void* memcpy(void* dst, const void* src, size_t num)
{
    Memory::Copy((void*)src, dst, num);
    return dst;
}

u32 ShellCommandsCount = 0;
ShellCommand* ShellCommands[100];

void AppMain()
{
    char commandBuffer[COMMAND_MAX_LENGTH + 1] = { 0 };
    char* commandPointer = commandBuffer;
    char* commandLimit = commandPointer + COMMAND_MAX_LENGTH;
    //List<string> commandHistory;

    Console::Write("{0}> ", Directory::Current->FullPath);

    for (;;)
    {
        //Timer::Sleep(10);
        //_asm hlt

        //Buttons key = Console::ReadKey();

        char key = Console::Read(true);
        if (!key)
            continue;

        switch (key)
        {
            case 0:
                continue;

            case '\b':
                if (commandPointer > commandBuffer)
                {
                    *commandPointer-- = 0;
                    Console::Write('\b');
                }
                continue;

            case '\n':
                *commandPointer = 0;
                Console::WriteLine();
                break;

            default:
                if (commandPointer < commandLimit)
                {
                    *commandPointer++ = key;
                    Console::Write(key);
                }
                continue;
        }

        string buffer = commandBuffer;
        string command = buffer.Before(' ');
        string parameters = buffer.After(' ');

        if (command.Length == 0) ;
        else
        {
            ShellCommand* shellCommand = null;
            for (u32 i = 0; i < ShellCommandsCount; i++)
                if (command == ShellCommands[i]->Name)
                    shellCommand = ShellCommands[i];

            if (shellCommand)
                shellCommand->Function(parameters);
            else
                Console::WriteLine("Unrecognized command {0}", command);
        }

        //commandHistory.Add(buffer);
        commandPointer = commandBuffer;
        *commandPointer = 0;

        Console::Write("{0}> ", Directory::Current->FullPath);
    }
}