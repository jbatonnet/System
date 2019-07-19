#ifndef _SYSTEM_TEST_H_
#define _SYSTEM_TEST_H_

#include <System/Common.h>

/// <summary>
/// A test class with some test functions
/// </summary>
class Test
{
public:
    /// <summary>
    /// Displays a message
    /// </summary>
    shared static void Action();

    /// <summary>
    /// Displays a message with the specified parameter
    /// </summary>
    /// <param name="parameter">The parameter to display</param>
    shared static void Action(u32 parameter);

    /// <summary>
    /// Displays a message and returns a value
    /// </summary>
    shared static u32 Function();

    /// <summary>
    /// Displays a message with the specified parameter and returns a value
    /// </summary>
    /// <param name="parameter">The parameter to display</param>
    shared static u32 Function(u32 parameter);
};

#endif