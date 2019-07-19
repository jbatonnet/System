#ifndef _SYSTEM_MEMORY_H_
#define _SYSTEM_MEMORY_H_

#include <System/Base/Types.h>

enum class MemoryType : byte
{
    Heap,
    Stack
};

/// <summary>
/// A helper class to manipulate memory
/// </summary>
class Memory
{
public:
    // Operations
    // TODO: Extend to 64 bits
    // TODO: Set optimization for 64 bits

    /// <summary>
    /// Copies memory from an address to another
    /// </summary>
    /// <param name="source">The source buffer to copy from</param>
    /// <param name="destination">The destination buffer to copy to</param>
    /// <param name="count">The size of the buffer to copy</param>
    static void Copy(void* source, void* destination, u32 count)
    {
        if (!count)
            return;

        _asm
        {
            mov esi, [source]
            mov edi, [destination]
            mov ecx, [count]

            and ecx, 3
            rep movsb

            mov ecx, [count]
            shr ecx, 2
            rep movsd
        }
    }

    /// <summary>
    /// Copies several structures from an address to another
    /// </summary>
    /// <param name="source">The source buffer to copy from</param>
    /// <param name="destination">The destination buffer to copy to</param>
    /// <param name="count">The number of structures to copy</param>
    template<typename T> static void Copy(void* source, void* destination, u32 count = 1)
    {
        count *= sizeof(T);
        if (!count)
            return;

        _asm
        {
            mov esi, [source]
            mov edi, [destination]
            mov ecx, [count]

            and ecx, 3
            rep movsb

            mov ecx, [count]
            shr ecx, 2
            rep movsd
        }
    }

    // Clear, set
    static void Clear(void* address, u32 count, u8 value = 0)
    {
        /*
        TODO: Use SSE
            
            toAlign = 128 - value % 128;

            if (!value)
                xor eax, eax
            else
                mov eax, value

            if (size > toAlign + 128)


        */

        _asm
        {
            mov al, [value]
            mov ah, [value]
            shl eax, 16
            mov al, [value]
            mov ah, [value]

            mov edi, [address]
            mov ecx, [count]

            and ecx, 3
            rep stosb

            mov ecx, [count]
            shr ecx, 2
            rep stosd
        }
    }
    template<typename T> static void Clear(void* address, u32 count = 1, u8 value = 0)
    {
        Clear(address, count * sizeof(T), value);
    }

    template<typename T> static void Set(void* address, const T& value, u32 count)
    {
        if (!count)
            return;

        for (u32 i = 0; i < count; i++)
            ((T*)address)[i] = value;




        /*_asm
        {
            mov edi, [address]
            mov ebx, unit
            mov edx, value

            cmp ebx, 2
            je set16

            cmp ebx, 4
            je set32

            mov ebx, [count]
            jmp set

            set16: // 16 bits
                mov ax, [edx]
                shl eax, 16
                mov ax, [edx]

                mov ecx, [count] // Optimize by 32 bits
                rep stosw

                jmp finish
            
            set32: // 32 bits
                mov eax, [edx]
            
                mov ecx, [count]
                rep stosd

                jmp finish

            set: // Other
                mov esi, edx

                mov ecx, unit
                and ecx, 3
                rep movsb

                mov ecx, unit
                shr ecx, 2
                rep movsd

                dec ebx
                jnz set

            finish:
        }*/
    }

    // Comparisons
    static bool Compare(void* address1, void* address2, u32 count)
    {
        u8* data1 = (u8*)address1;
        u8* data2 = (u8*)address2;

        for (u32 i = 0; i < count; i++)
            if (data1[i] != data2[i])
                return false;

        return true;
    }
    template<typename T> static bool Compare(void* address1, void* address2, u32 count = 1)
    {
        T* data1 = (T*)address1;
        T* data2 = (T*)address2;

        for (u32 i = 0; i < count; i++)
            if (data1[i] != data2[i])
                return false;

        return true;
    }

    /// <summary>
    /// Allocates the necessary size to store the specified amount of structures, and eventually clears it with the specified value
    /// </summary>
    template<typename T> static T* Allocate(u32 count = 1, s16 value = -1)
    {
        return (T*)Allocate(count * sizeof(T), value);
    }
    /// <summary>
    /// Allocates the necessary size to store the specified amount of structures on the specified memory type, and eventually clears it with the specified value
    /// </summary>
    template<typename T> static T* Allocate(u32 count, MemoryType type, s16 value = -1)
    {
        return (T*)Allocate(count * sizeof(T), type, value);
    }

    /// <summary>
    /// Allocates specified amount of memory, and eventually clears it with the specified value
    /// </summary>
    shared static void* Allocate(u32 count, s16 value = -1);
    /// <summary>
    /// Allocates specified amount of memory on the specified memory type, and eventually clears it with the specified value
    /// </summary>
    shared static void* Allocate(u32 count, MemoryType type, s16 value = -1);

    // Frees a previously allocated memory
    shared static void Free(void* address);
};

void* operator new(u32, void* pointer);

#endif