#ifndef _KERNEL_TEST_H_
#define _KERNEL_TEST_H_

#include <System/Common.h>
#include <System/Debugging/Console.h>

struct TestFunction;

u32 TestFunctionsCount;
TestFunction* TestFunctions[100];

struct TestFunction
{
    char* Name;
    void (*Function)(const string&);

    TestFunction(char* name, void (*function)(const string&)) : Name(name), Function(function)
    {
        TestFunctions[TestFunctionsCount++] = this;
    }
};

void RunTest(const string& command, const string& parameters = string::Empty)
{
    TestFunction* testFunction = null;
    for (u32 i = 0; i < TestFunctionsCount; i++)
        if (command == TestFunctions[i]->Name)
            testFunction = TestFunctions[i];

    if (!testFunction)
        return Console::WriteLine("Unrecognized test function {0}", command);

    Console::WriteLine("-- Test: \"{0}\", Parameters: \"{1}\" --", command, parameters);
    Console::WriteLine();

    testFunction->Function(parameters);

    Console::WriteLine();
    Console::WriteLine("-- End --");

    loop
}

/// <summary>
/// Use this macro to declare a new test
/// </summary>
#define AddTest(name) void Test##name(const string& parameters); TestFunction TestFunction_##name(#name, Test##name); void Test##name(const string& parameters)

#endif