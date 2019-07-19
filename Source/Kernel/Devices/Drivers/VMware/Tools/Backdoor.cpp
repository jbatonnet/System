#include "Backdoor.h"

#include <System/Debugging/Console.h>

u32 Backdoor_MouseId()
{
    u16 command = (u16)Backdoor_Commands::PointerCommand;
    u32 parameter = (u32)Backdoor_MouseCommands::GetId;

    _asm
    {
        mov eax, BACKDOOR_MAGIC
        mov ebx, [parameter]
        mov cx, [command]
        mov dx, BACKDOOR_PORT

        in eax, dx
    }

    // Find where is the ID
    return 0;
}
u16 Backdoor_MouseStatus()
{
    u16 command = (u16)Backdoor_Commands::PointerStatus;
    u32 status;

    _asm
    {
        mov eax, BACKDOOR_MAGIC
        mov ebx, 0
        mov cx, [command]
        mov dx, BACKDOOR_PORT

        in eax, dx

        mov [status], eax
    }

    return status;
}
void Backdoor_MouseData(void* buffer = null, u32 words = 1)
{
    u16 command = (u16)Backdoor_Commands::PointerData;
    u32 a, b, c, d;

    _asm
    {
        mov eax, BACKDOOR_MAGIC
        mov ebx, words
        mov cx, [command]
        mov dx, BACKDOOR_PORT

        in eax, dx

        mov [a], eax
        mov [b], ebx
        mov [c], ecx
        mov [d], edx
    }

    if (buffer)
    {
        u32* data = (u32*)buffer;

        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
    }
}
void Backdoor_MouseRequest(bool absolute = true)
{
    u16 command = (u16)Backdoor_Commands::PointerCommand;
    u32 parameter = (u32)(absolute ? Backdoor_MouseCommands::GetAbsolute : Backdoor_MouseCommands::GetRelative);

    _asm
    {
        mov eax, BACKDOOR_MAGIC
        mov ebx, [parameter]
        mov cx, [command]
        mov dx, BACKDOOR_PORT

        in eax, dx
    }
}

void Backdoor_MouseInitialize()
{
    Backdoor_MouseId();
    Backdoor_MouseStatus();
    Backdoor_MouseData();
    Backdoor_MouseRequest();
}
bool Backdoor_MouseGetPacket(Backdoor_MousePacket* packet)
{
    u16 status = Backdoor_MouseStatus();
    if (status < 4)
        return false;

    Backdoor_MouseData(packet, 4);
    return true;
}