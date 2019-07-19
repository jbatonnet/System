#ifdef KERNEL

#include <HAL/Interrupts.h>

#include <System/System.h>
#include <System/Test.h>

using namespace System;
using namespace Types;
using namespace Values;
using namespace System::Runtime;
using namespace System::Data;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Graphics;
using namespace System::Interface;
using namespace System::Objects;

namespace std
{
    /*template<class T> class initializer_list
    {
    private:
        const T* first;
        const T* last;

    public:
        typedef T value_type;
        typedef const T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;

        typedef const T* iterator;
        typedef const T* const_iterator;

        initializer_list() : first(0), last(0) { }
        initializer_list(const T* first, const T *last) : first(first), last(last) { }

        const T* begin() const
        {
            return first;
        }
        const T *end() const
        {
            return last;
        }
        size_t size() const
        {
            return (size_t)(last - first);
        }

        Reference<Iterator<T>> GetIterator() const override
        {
            return new InitializerCollectionIterator(first, last);
        }
    };*/
}

class KernelConsoleStream : public ConsoleStream
{
private:
    u32 objectId;

public:
    KernelConsoleStream(u32 id) : objectId(id) { }

    u64 GetLength();
    u32 Read(void* buffer, u32 count);
    u32 Read(void* buffer, u32 count, bool intercept);
    void Write(void* buffer, u32 count);
};
class KernelBitmap : public Bitmap
{
private:
    u32 objectId;

public:
    KernelBitmap(u32 id) : objectId(id) { }

    void* GetData();
    Point2 GetSize();
    string ToString();
};
class KernelFontFamily : public FontFamily
{
private:
    u32 objectId;

public:
    KernelFontFamily(u32 id) : objectId(id) { }

    Reference<System::Graphics::Font> GetFont(u8 height, System::Graphics::FontAttribute attributes);
};
class KernelFile : public File
{
private:
    u32 objectId;

public:
    KernelFile(u32 id) : objectId(id) { }

    string GetPath();
    string GetName();
    string GetExtension();
    u64 GetSize();
    System::IO::Stream* GetStream();
};
class KernelDirectory : public Directory
{
private:
    u32 objectId;

public:
    KernelDirectory(u32 id) : objectId(id) { }

    string GetName();
    System::IO::Directory* GetParent();
    string GetFullPath();
    void AddDirectory(System::IO::Directory* directory);
    void AddFile(System::IO::File* file);
    System::IO::Directory* GetDirectory(const string& path);
    System::IO::File* GetFile(string path);
};
class KernelStream : public Stream
{
private:
    u32 objectId;

public:
    KernelStream(u32 id) : objectId(id) { }

    u64 GetPosition();
    void SetPosition(u64 position);
    u64 GetLength();
    bool IsEndOfStream();
    u32 Read(void* buffer, u32 count);
    void Write(void* buffer, u32 count);
    void Seek(u64 position, System::IO::SeekOrigin origin);
};

void Test::Action()
{
    _asm
    {
        mov eax, 0x403A879D

        int INTERRUPT_SYSTEM
    }
}
void Test::Action(u32 parameter)
{
    _asm
    {
        mov eax, 0xB0700201
        lea esi, parameter

        int INTERRUPT_SYSTEM
    }
}
u32 Test::Function()
{
    u32 result;

    _asm
    {
        mov eax, 0x352F0171
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
u32 Test::Function(u32 parameter)
{
    u32 result;

    _asm
    {
        mov eax, 0x108CF096
        lea esi, parameter
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

u64 KernelConsoleStream::GetLength()
{
    u32 id = objectId;
    u64 result;

    _asm
    {
        mov eax, 0xDD1E31FF
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
u32 KernelConsoleStream::Read(void* buffer, u32 count)
{
    u32 id = objectId;
    u32 result;

    _asm
    {
        mov eax, 0x817EB885
        mov ebx, [id]
        lea esi, buffer
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
u32 KernelConsoleStream::Read(void* buffer, u32 count, bool intercept)
{
    u32 id = objectId;
    u32 result;

    _asm
    {
        mov eax, 0xA94D1836
        mov ebx, [id]
        lea esi, buffer
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
void KernelConsoleStream::Write(void* buffer, u32 count)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0x83D4728A
        mov ebx, [id]
        lea esi, buffer

        int INTERRUPT_SYSTEM
    }
}

void Console::Clear()
{
    _asm
    {
        mov eax, 0xB5103AED

        int INTERRUPT_SYSTEM
    }
}

void* Memory::Allocate(u32 count, s16 value)
{
    void* result;

    _asm
    {
        mov eax, 0x6D044766
        lea esi, count
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
void Memory::Free(void* address)
{
    _asm
    {
        mov eax, 0x00ED6A8D
        lea esi, address

        int INTERRUPT_SYSTEM
    }
}

void* KernelBitmap::GetData()
{
    u32 id = objectId;
    void* result;

    _asm
    {
        mov eax, 0x2F3010DA
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
Point2 KernelBitmap::GetSize()
{
    u32 id = objectId;
    Point2 result;

    _asm
    {
        mov eax, 0xE645B6D7
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
string KernelBitmap::ToString()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0xD372CABF
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

Reference<System::Graphics::Font> KernelFontFamily::GetFont(u8 height, System::Graphics::FontAttribute attributes)
{
    u32 id = objectId;
    System::Graphics::Font* result;

    _asm
    {
        mov eax, 0xF70B9008
        mov ebx, [id]
        lea esi, height
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

string KernelFile::GetPath()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0x977FF228
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
string KernelFile::GetName()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0x8B6A1A85
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
string KernelFile::GetExtension()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0xC541E069
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
u64 KernelFile::GetSize()
{
    u32 id = objectId;
    u64 result;

    _asm
    {
        mov eax, 0xC99C2F27
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
System::IO::Stream* KernelFile::GetStream()
{
    u32 id = objectId;
    System::IO::Stream* result;

    _asm
    {
        mov eax, 0x54F72F51
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

string KernelDirectory::GetName()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0xAE028CA3
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
System::IO::Directory* KernelDirectory::GetParent()
{
    u32 id = objectId;
    System::IO::Directory* result;

    _asm
    {
        mov eax, 0x7EB8834F
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
string KernelDirectory::GetFullPath()
{
    u32 id = objectId;
    char result[0x100];

    _asm
    {
        mov eax, 0x1CA0760B
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
void KernelDirectory::AddDirectory(System::IO::Directory* directory)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0xD3A92B1E
        mov ebx, [id]
        lea esi, directory

        int INTERRUPT_SYSTEM
    }
}
void KernelDirectory::AddFile(System::IO::File* file)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0xEE0643BE
        mov ebx, [id]
        lea esi, file

        int INTERRUPT_SYSTEM
    }
}
System::IO::Directory* KernelDirectory::GetDirectory(const string& path)
{
    u32 id = objectId;
    System::IO::Directory* result;

    _asm
    {
        mov eax, 0x221E066B
        mov ebx, [id]
        lea esi, path
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
System::IO::File* KernelDirectory::GetFile(string path)
{
    u32 id = objectId;
    System::IO::File* result;

    _asm
    {
        mov eax, 0x88D3AA3A
        mov ebx, [id]
        lea esi, path
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
System::IO::Directory* Directory::GetRootDirectory()
{
    System::IO::Directory* result;

    _asm
    {
        mov eax, 0x808C9EB8
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

u64 KernelStream::GetPosition()
{
    u32 id = objectId;
    u64 result;

    _asm
    {
        mov eax, 0x482CB04A
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
void KernelStream::SetPosition(u64 position)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0x3EE223AD
        mov ebx, [id]
        lea esi, position

        int INTERRUPT_SYSTEM
    }
}
u64 KernelStream::GetLength()
{
    u32 id = objectId;
    u64 result;

    _asm
    {
        mov eax, 0x5E29FC88
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
bool KernelStream::IsEndOfStream()
{
    u32 id = objectId;
    bool result;

    _asm
    {
        mov eax, 0xE9CF6894
        mov ebx, [id]
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
u32 KernelStream::Read(void* buffer, u32 count)
{
    u32 id = objectId;
    u32 result;

    _asm
    {
        mov eax, 0x7F218A1C
        mov ebx, [id]
        lea esi, buffer
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}
void KernelStream::Write(void* buffer, u32 count)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0x0AF90658
        mov ebx, [id]
        lea esi, buffer

        int INTERRUPT_SYSTEM
    }
}
void KernelStream::Seek(u64 position, System::IO::SeekOrigin origin)
{
    u32 id = objectId;

    _asm
    {
        mov eax, 0xFFCA19D0
        mov ebx, [id]
        lea esi, position

        int INTERRUPT_SYSTEM
    }
}
ConsoleStream* Stream::GetConsoleStream()
{
    u32 result;

    _asm
    {
        mov eax, 0x6F738C09
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return new KernelConsoleStream(result);
}
System::IO::Stream* Stream::GetSerialStream()
{
    System::IO::Stream* result;

    _asm
    {
        mov eax, 0xFAAEDE90
        lea edi, result

        int INTERRUPT_SYSTEM
    }

    return result;
}

#endif
