#include "Shell.h"

using namespace System::IO;
using namespace System::Runtime;

// Basic
AddShellCommand(help, "Shows this help")
{
    for (u32 i = 0; i < ShellCommandsCount; i++)
    {
        string name = ShellCommands[i]->Name;
        Console::WriteLine("  {0}{1}{2}", name, string(' ', 8 - name.Length), ShellCommands[i]->Documentation);
    }
}
AddShellCommand(echo, "Shows some text on the console")
{
    Console::WriteLine(parameters);
}
AddShellCommand(clear, "Clears the console")
{
    Console::Clear();
}

// IO
AddShellCommand(pwd, "Shows the current directory path")
{
    Directory* path[255];
    u8 pathIndex = 0;

    Directory* directory = Directory::Current;
    while (Directory* parent = directory->Parent)
    {
        path[pathIndex++] = directory;
        directory = parent;
    }

    if (!pathIndex)
        Console::Write('/');

    for (int i = pathIndex - 1; i >= 0; i--)
    {
        Console::Write('/');
        Console::Write(path[i]->Name);
    }

    Console::WriteLine();
}
AddShellCommand(ls, "Lists the directories and files in the current directory")
{
    Reference<Collection<Directory*>> directories = Directory::Current->Directories;
    Reference<Collection<File*>> files = Directory::Current->Files;

    Console::WriteLine("[{0}]", Directory::Current->Name);

    for (Directory* directory : directories)
        Console::WriteLine("- [{0}]", directory->Name);

    for (File* file : files)
        Console::WriteLine("- {0}", file->Name);
}
AddShellCommand(cd, "Changes the current directory")
{
    Directory* directory = Directory::Open(parameters);
    if (!directory)
        return Console::WriteLine("Unknown directory {0}", parameters);

    Directory::Current = directory;
}
AddShellCommand(cat, "Shows the content of the specified file")
{
    File* file = File::Open(parameters);
    if (!file)
        return Console::WriteLine("Unknown file {0}", parameters);

    Stream* stream = file->GetStream();
    TextStream* textStream = new TextStream(stream);

    string content = textStream->ReadAll();
    Console::WriteLine(content);
}

// Processes
AddShellCommand(run, "Runs the specified file")
{
    Exception::NotImplemented();
}

// Statistics
AddShellCommand(cpu, "Shows some informations about processor")
{
    Exception::NotImplemented();
}
AddShellCommand(memory, "Shows some informations about memory")
{
    Exception::NotImplemented();
}

// Debugging
AddShellCommand(break, "Breaks the debugger if present")
{
    Debugger::Break();
}