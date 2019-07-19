#ifndef _SYTEM_EXCEPTION_H_
#define _SYTEM_EXCEPTION_H_

#include <System/Common.h>
#include <System/Structures/Collections/List.h>

class Exception : public Object
{
protected:
    string message;
    List<void*> frames;

public:
    Exception() : frames(0x20)
    {
        ExtractFrames();
    }
    Exception(string message) : message(message), frames(0x20)
    {
        ExtractFrames();
    }

    _declspec(property(get = GetMessage)) string Message;
    string GetMessage() const { return message; }

    _declspec(property(get = GetFrames)) Collection<void*>* Frames;
    Collection<void*>* GetFrames() const { return (Collection<void*>*)&frames; }

private:
    virtual void ExtractFrames();
    void ExtractFrames(void* stack);
    
public:
    static void NotImplemented()
    {
        Assert("This method is not implemented yet");
    }

    static void Assert();
    static void Assert(bool condition)
    {
        if (condition)
            return;

        Assert();
    }
    static void Assert(void* pointer)
    {
        if (pointer)
            return;

        Assert();
    }

    static void Assert(const char* message);
    static void Assert(const string& message);
    static void Assert(bool condition, const char* message)
    {
        if (condition)
            return;

        Assert(message);
    }
    static void Assert(void* pointer, const char* message)
    {
        if (pointer)
            return;

        Assert(message);
    }

    template<typename T = Exception, typename... Args> static void Assert(bool condition, const string& message, Args... parameters)
    {
        if (condition)
            return;

        Assert(String::Format(message, parameters...));
    }
    template<typename T = Exception, typename... Args> static void Assert(void* pointer, const string& message, Args... parameters)
    {
        if (pointer)
            return;

        Assert(String::Format(message, parameters...));
    }
};

/*

try : 

// Save EIP

Exception* exception = null;
Exception::Try(exception);

if (!exception) // try
{
}
else // catch
{
}

*/

/*#define try for (bool concat(_try_flag, __LINE__) = true; concat(_try_flag, __LINE__); ) for (Exception* concat(_try_exception, __LINE__) = null; concat(_try_flag, __LINE__); concat(_try_flag, __LINE__) = false) if (!concat(_try_exception, __LINE__))
#define catch else

void _dededede()
{
    try
    {
    }
    catch
    {
    }
}*/

#endif