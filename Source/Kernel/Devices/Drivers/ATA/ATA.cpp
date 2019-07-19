#include <HAL/HAL.h>
#include "ATA.h"

inline ATA_Status ATA_GetStatus(u16 bus)
{
    static ATA_Status status = { 0 };
    status.Value = IO_Read8(bus | IO_STATUS);
    return status;
}
inline void ATA_SendCommand(u16 bus, u8 command)
{
    IO_Write8(bus | IO_COMMAND, command);
}

void ATA_Identify(u16 bus, bool master, ATA_IdentifyData* data)
{
    while (ATA_GetStatus(bus).Busy);

    IO_Write8(bus | IO_SECTOR_COUNT, 0x00);
    IO_Write8(bus | IO_LBA_LO, 0x00);
    IO_Write8(bus | IO_LBA_MID, 0x00);
    IO_Write8(bus | IO_LBA_HI, 0x00);
    IO_Write8(bus | IO_DRIVE, master ? 0xA0 : 0xB0);
	ATA_SendCommand(bus, CMD_IDENTIFY);

    while (!ATA_GetStatus(bus).Data);

    u16* dataPtr = (u16*)data;
    for (int i = 0; i < 256; i++)
        dataPtr[i] = IO_Read16(bus | IO_DATA);
}
void ATA_PIO_Read28(u16 bus, bool master, u32 lba, u8 count, void* buffer)
{
    ATA_WaitNoMoreBusy(bus);

    IO_Write8(bus | IO_FEATURES, 0x00);
    IO_Write8(bus | IO_SECTOR_COUNT, count);
    IO_Write8(bus | IO_LBA_LO, lba);
    IO_Write8(bus | IO_LBA_MID, lba >> 8);
    IO_Write8(bus | IO_LBA_HI, lba >> 16);
    IO_Write8(bus | IO_DRIVE, 0xE0 | ((u8)!master << 4) | ((lba >> 24) & 0x0F));

    ATA_SendCommand(bus, CMD_READ_SECTORS);

    while (count--)
    {
        ATA_WaitForData(bus);

        u16* bufferPtr = (u16*)buffer;
        for (int i = 0; i < 256; i++)
            bufferPtr[i] = IO_Read16(bus | IO_DATA);

        ATA_Wait400ns(bus);
        bufferPtr += 512;
    }
}
void ATA_PIO_Write28(u16 bus, bool master, u32 lba, u8 count, void* buffer)
{
    ATA_WaitNoMoreBusy(bus);

    IO_Write8(bus | IO_FEATURES, 0x00);
    IO_Write8(bus | IO_SECTOR_COUNT, count);
    IO_Write8(bus | IO_LBA_LO, lba);
    IO_Write8(bus | IO_LBA_MID, lba >> 8);
    IO_Write8(bus | IO_LBA_HI, lba >> 16);
    IO_Write8(bus | IO_DRIVE, 0xE0 | ((u8)!master << 4) | ((lba >> 24) & 0x0F));

    ATA_SendCommand(bus, CMD_WRITE_SECTORS);

    while (count--)
    {
        u16* bufferPtr = (u16*)buffer;
        for (int i = 0; i < 256; i++)
            IO_Write16(bus | IO_DATA, bufferPtr[i]);

        ATA_SendCommand(bus, CMD_CACHE_FLUSH);
        bufferPtr += 512;
    }
}







int bl_common(int drive, int numblock, int count)
{
    IO_Write8(0x1F1, 0x00);      /* NULL byte to port 0x1F1 */
    IO_Write8(0x1F2, count);     /* Sector count */
    IO_Write8(0x1F3, (unsigned char) numblock);  /* Low 8 bits of the block address */
    IO_Write8(0x1F4, (unsigned char) (numblock >> 8));   /* Next 8 bits of the block address */
    IO_Write8(0x1F5, (unsigned char) (numblock >> 16));  /* Next 8 bits of the block address */

    /* Drive indicator, magic bits, and highest 4 bits of the block address */
    IO_Write8(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));

    return 0;
}
int bl_read(int drive, int numblock, int count, char *buf)
{
    u16 tmpword;
    int idx;

    bl_common(drive, numblock, count);
    IO_Write8(0x1F7, 0x20);

    /* Wait for the drive to signal that it's ready: */
    while (!(IO_Read8(0x1F7) & 0x08));

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword = IO_Read16(0x1F0);
        buf[idx * 2] = (unsigned char) tmpword;
        buf[idx * 2 + 1] = (unsigned char) (tmpword >> 8);
    }

    return count;
}
int bl_write(int drive, int numblock, int count, char *buf)
{
    u16 tmpword;
    int idx;

    bl_common(drive, numblock, count);
    IO_Write8(0x1F7, 0x30);

    /* Wait for the drive to signal that it's ready: */
    while (!(IO_Read8(0x1F7) & 0x08));

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
        IO_Write16(0x1F0, tmpword);
    }

    return count;
}