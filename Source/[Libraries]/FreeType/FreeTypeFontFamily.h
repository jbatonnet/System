#ifndef _FREETYPE_FREETYPEFONTFAMILY_H_
#define _FREETYPE_FREETYPEFONTFAMILY_H_

#include <System/Graphics/Font.h>

class FreeTypeFontFamily : public System::Graphics::FontFamily
{
public:
    static FontFamily* Load(System::IO::File* file);
};

#endif