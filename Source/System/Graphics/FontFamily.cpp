#include <System/System.h>

using namespace System::Graphics;
using namespace System::IO;

template<typename T> Reference<FontFamily> FontFamily::Load(Stream* stream)
{
    return T::Load(stream);
}
Reference<FontFamily> FontFamily::Load(File* file)
{
    if (!file)
        return Reference<FontFamily>::Invalid;

    return ResourceLoaderBase<FontFamily>::Load(file);
}
Reference<FontFamily> FontFamily::Load(const string& path)
{
    return Load(File::Open(path));
}