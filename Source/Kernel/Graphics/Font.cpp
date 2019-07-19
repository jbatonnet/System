#include <System/Graphics/Font.h>
#include <System/Graphics/Surface.h>
#include <Kernel/Devices/Screen/Screen.h>
#include <System/Debugging/Log.h>
#include <System/Runtime/Debugging/Debugger.h>
#include <System/IO/Directory.h>

#include <System/IO/ResourceLoader.h>
#include <[Libraries]/Basics/Documents/Fonts/BasicFontFamily.h>

using namespace System::Graphics;
using namespace System::IO;
using namespace System::Runtime;

ResourceLoader<FontFamily, BasicFontFamily> basicFontFamilyLoader("raw");

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