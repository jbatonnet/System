#include <iostream>

#include "Reflection.h"

using namespace std;

#include <System/Memory/Memory.h>
void Memory::Free(void* address) { }

struct Toto
{
    void Test(int param)
    {
        cout << param << endl;
        cout << hex << showbase << this << endl;
    }
    void Test(double) { }
};

int main()
{
    //const Type& type = types[0];
    //cout << texts[type.nameIndex] << endl;

    getchar();
    return 0;
}