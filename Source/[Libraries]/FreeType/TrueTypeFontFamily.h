#ifndef _FREETYPE_TRUETYPEFONTFAMILY_H_
#define _FREETYPE_TRUETYPEFONTFAMILY_H_

#include "FreeTypeFontFamily.h"

class TrueTypeFontFamily : public System::Graphics::FontFamily
{
public:
    static FontFamily* Load(System::IO::Stream* stream);
};

#endif