#include <Kernel/Devices/Drivers/FileSystems/VFS/VFS.h>
#include <System/IO/Directory.h>

using namespace System::Devices::Drivers;
using namespace System::IO;

/*
    System
     |- Storage
     |   |- Floppy
     |   |- Disc
     |   |- HardDrive
     |- Temp
     |- Drivers
     |- Frameworks
     |   |- CLI
     |   |- Java
     |- Settings
         |- ...
    Apps
     |- Editor
         |- Name
    Users
     |- Julien
         |- Documents
         |- Pictures
         |- Videos
         |- Music
         |- Downloads
*/

VFS::VFS()
{
    //name = "Virtual file system";

    //Directory *temp, *drivers, *fonts;
    //Directory *apps, *users;

    /*system = new Directory("System", root);
        storage = new Directory("Storage", system);
        fonts = new Directory("Fonts", system);
        temp = new Directory("Temp", system);
    apps = new Directory("Apps", root);
    users = new Directory("Users", root)*/;

    /*root->AddDirectory(system = new Directory("System", root));
        system->AddDirectory(storage = new Directory("Storage", system));
        system->AddDirectory(fonts = new Directory("Fonts", system));
        system->AddDirectory(temp = new Directory("Temp", system));
            //temp->AddFile(new File("Test.txt"));
    root->AddDirectory(apps = new Directory("Apps", root));
    root->AddDirectory(users = new Directory("Users", root));*/
}