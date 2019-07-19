#include <System/Runtime/Reflection/Method.h>

using namespace System::Runtime;

/*
    ?Before@String@@QBE?AU1@D@Z
        QBE  = const char*&
        ?AU1 = String&
*/

/*
    ?Contains@String@@QBE_ND@Z
        String::Contains
        QBE = const char*&
        _N  = bool
        D   = char
*/

/*
    ?Sleep@Timer@@SAX_K@Z
        Timer::Sleep
        S  : const volatile pointer
        A  : reference
        X  : void, coclass
        _K : u64
*/

/*
    String String::Replace(const String&, const String&, u32) const;
    ?Replace@String@@QBE?AU1@ABU1@0I@Z
        Q = public
        BE = u8&


        String::Replace
        QBE = const char*&
        ?AU1 = String&
        ABU1 = String&
        0I


        S  : const volatile pointer
        A  : reference
        _K : u64

*/

Method* Method::Load(void* address, string rawName)
{
    if (rawName[0] != '?' || rawName[1] == '?')
        return null;

    return null;
}