#ifndef _KERNEL_FAT_H_
#define _KERNEL_FAT_H_

#include <System/Devices/Storage/FileSystem.h>
#include <System/Devices/Storage/StorageDevice.h>

using namespace System::Devices;

// Boot sector
struct FAT_BiosParameterBlock
{
    u16 BytesPerSector;
    u8  SectorsPerCluster;
    u16 ReservedSectors;
    u8  Fats;
    u16 RootEntries;
    u16 Sectors16;
    u8  Media;
    u16 SectorsPerFat16;
    u16 SectorsPerTrack;
    u16 Heads;
    u32 HiddenSectors;
    u32 Sectors32;
};
struct FAT16_Informations
{
    u8  DriveNumber;   // 0x00 for floppy, 0x80 for hard disk
    u8  Reserved;      // 0x00
    u8  BootSignature; // 0x29
    u32 VolumeId;
    char   Label[11];
    char   Type[8];       // FAT12, FAT16 or FAT
    u8  Filler[28];
};
struct FAT32_Informations
{
    u32 SectorsPerFat32;
    u16 ExtendedFlags;
    u16 Version;         // 0x00, 0x00
    u32 RootCluster;     // 0x02 usually
    u16 FsInfo;          // 0x01 usually
    u16 BootRecordCopy;  // 0x06 usually
    u8  Reserved[12];    // 0x00
    u8  DriveNumber;     // 0x00 for floppy, 0x80 for hard disk
    u8  Reserved2;       // 0x00
    u8  BootSignature;   // 0x29
    u32 VolumeID;
    char   Label[11];
    char   Type[8];         // FAT32
};
union FAT_Informations
{
    FAT16_Informations FAT16;
    FAT32_Informations FAT32;
};
struct FAT_BootSector
{
    u8                  BootCode[3];
    char                   OEMName[8];
    FAT_BiosParameterBlock Bpb;
    FAT_Informations       Informations;
    u8                  Filler[420];
    u16                 Magic;        // 0x55AA
};

// Others fields
struct FAT32_FSInfo
{
    u32 LeadSignature;    // 0x41615252
    u8  Reserved1[480];   // 0x00
    u32 StructSignature;  // 0x61417272
    u32 FreeClusterCount;
    u32 NextFreeCluster;
    u8  Reserved2[12];    // 0x00
    u32 TrailSignature;   // 0xAA550000
};

#define DOSIME_SECONDS 0x001F
#define DOSIME_MINUTES 0x07E0
#define DOSIME_HOURS   0xF800

#define DOS_DATE_DAY   0x001F
#define DOS_DATE_MONTH 0x01E0
#define DOS_DATE_YEAR  0xFE00

enum class FAT_DirectoryAttribute : u8
{
    ReadOnly  = 0x01,
    Hidden    = 0x02,
    System    = 0x04,
    VolumeID  = 0x08,
    Directory = 0x10,
    Archive   = 0x20,
    LongName  = 0x0F,
};
struct FAT_DirectoryEntry
{
    char                   Name[11];          // "FILE     EXT"
    FAT_DirectoryAttribute Attributes;
    u8                  Reserved;          // 0x00
    u8                  CreationTimeTenth;
    u16                 CreationTime;
    u16                 CreationDate;
    u16                 AccessDate;
    u16                 ClusterHi;         // 0x00 for FAT12 and FAT16
    u16                 ModificationTime;
    u16                 ModificationDate;
    u16                 ClusterLo;
    u32                 Size;
};
struct FAT_LongDirectoryEntry
{
    u8 Order;                      // 0x01 for the first, 0x40 for the last
    wchar_t Name1[5];
    FAT_DirectoryAttribute Attribute; // FAT_DirectoryAttribute::LongName
    u8 Type;                       // 0x00
    u8 Checksum;
    wchar_t Name2[6];
    u16 ClusterLo;                 // 0x00
    wchar_t Name3[2];

    /* 
    Chechsum algorithm
    unsigned char ChkSum (unsigned char *pFcbName)
	{
		short FcbNameLen;
		unsigned char Sum;

		Sum = 0;
		for (FcbNameLen=11; FcbNameLen!=0; FcbNameLen--) {
			// NOTE: The operation is an unsigned char rotate right
			Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
		}
		return (Sum);
	}
    */
};

#endif