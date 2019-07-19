#include <System/IO/File.h>
#include <System/IO/Directory.h>

using namespace System::IO;

File* File::Open(string path)
{
    return Directory::Current->GetFile(path);
}
Stream* File::OpenStream(string path)
{
    File* file = Directory::Current->GetFile(path);
    if (!file)
        return null;

    return file->GetStream();
}