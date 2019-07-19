#ifndef _KERNEL_ATA_H_
#define _KERNEL_ATA_H_

#include <System/Common.h>

#define IO_PRIMARY 0x01F0

#define IO_DATA          0
#define IO_FEATURES      1
#define IO_ERROR         1
#define IO_SECTOR_COUNT  2
#define IO_SECTOR_NUMBER 3
#define IO_LBA_LO        3
#define IO_TRACK_LO      4
#define IO_LBA_MID       4
#define IO_TRACK_HI      5
#define IO_LBA_HI        5
#define IO_DRIVE         6
#define IO_HEAD          6
#define IO_COMMAND       7
#define IO_STATUS        7

#define STATUS_ERR (1 << 0)
#define STATUS_DRQ (1 << 3)
#define STATUS_SRV (1 << 4)
#define STATUS_DF  (1 << 5)
#define STATUS_RDY (1 << 6)
#define STATUS_BSY (1 << 7)

#define CMD_IDENTIFY      0xEC
#define CMD_READ_SECTORS  0x20
#define CMD_WRITE_SECTORS 0x30
#define CMD_CACHE_FLUSH   0xE7

// PartitionTypes
#define PARTITION_FAT16 0x06

#define ATA_WaitNoMoreBusy(bus) while (ATA_GetStatus(bus).Busy)
#define ATA_WaitForData(bus) while (!ATA_GetStatus(bus).Data)
#define ATA_Wait400ns(bus) ATA_GetStatus(bus); ATA_GetStatus(bus); ATA_GetStatus(bus); ATA_GetStatus(bus)

union ATA_Status
{
    struct
    {
        bool Error      : 1;
        bool _1         : 1;
        bool _2         : 1;
        bool Data       : 1;
        bool Service    : 1;
        bool DriveFault : 1;
        bool Ready      : 1;
        bool Busy       : 1;
    };
    u8 Value;
};
struct ATA_IdentifyData
{
    struct
    {
        bool _data_0 : 1;
        bool _data_1 : 1;
        bool _data_2 : 1;
        bool _data_3 : 1;
        bool _data_4 : 1;
        bool _data_5 : 1;
        bool _data_6 : 1;
        bool _data_7 : 1;
        bool _data_8 : 1;
        bool _data_9 : 1;
        bool _data_10 : 1;
        bool _data_11 : 1;
        bool _data_12 : 1;
        bool _data_13 : 1;
        bool _data_14 : 1;
        bool NonATADevice : 1;
    } GeneralInformations; // 0
    u16 _data_0[59];
    u32 Addressable28bitLogicalSectors; // 60-61
    u16 _data_1[21];
    u16 SupportedCommandSets; // 83
    u16 _data_2[4];
    u16 UltraDMAModes; // 88
    u16 _data_3[4];
    u16 HardwareResetResult; // 93
    u16 _data_4[6];
    u64 Addressable48bitLogicalSectors; // 100-103
    u16 _data_5[152];
};

struct ATA_PartitionEntry
{
    u8 Status;
    u8 FirstSector[3];
    u8 Type;
    u8 LastSector[3];
    u32 LBA;
    u32 Sectors;
};
struct ATA_MasterBootRecord
{
    u8 Bootstrap[446];
    ATA_PartitionEntry Partitions[4];
    u16 Signature;
};

void ATA_Identify(u16 bus, bool master, ATA_IdentifyData* data);
void ATA_PIO_Read28(u16 bus, bool master, u32 lba, u8 count, void* buffer);
void ATA_PIO_Write28(u16 bus, bool master, u32 lba, u8 count, void* buffer);

#endif