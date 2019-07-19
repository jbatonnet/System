#ifdef WINDOWS

#include <System/System.h>
#include <System/Test.h>

#include <[Libraries]/LibPNG/PngBitmap.h>

using namespace System;
using namespace System::Runtime;
using namespace System::Objects;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Interface;
using namespace System::Graphics;

Dynamic<FontFamily> defaultFontFamily([] { return FontFamily::GetFamily("Open"); });
Dynamic<FontFamily> defaultMonospaceFontFamily([] { return FontFamily::GetFamily("Consolas"); });

Reference<FontFamily> FontFamily::GetFamily(const string& name)
{
    // Try to find a file with the specified name
    File* file = Directory::GetRootDirectory()->GetFile("/System/Fonts/" + name + ".font.raw");
    if (!file)
        return Reference<FontFamily>::Invalid;

    return Load(file);
}
Reference<FontFamily> FontFamily::GetDefaultFamily(FontType type)
{
    switch (type)
    {
        case FontType::None: return defaultFontFamily;
        case FontType::Monospace: return defaultMonospaceFontFamily;
    }

    return Reference<FontFamily>::Invalid;
}

#endif