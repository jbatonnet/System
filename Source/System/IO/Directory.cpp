#include <System/IO/Directory.h>

using namespace System::IO;

Directory *Directory::Root = Directory::GetRootDirectory(),
          *Directory::Current = Directory::Root;

Directory* Directory::Open(const string& path)
{
    if (Directory::Current)
        return Directory::Current->GetDirectory(path);
    else if (Directory::Root)
        return Directory::Root->GetDirectory(path);

    return null;
}