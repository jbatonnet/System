#ifndef _KERNEL_BACKDOOR_H_
#define _KERNEL_BACKDOOR_H_

#include <System/Common.h>

#define BACKDOOR_MAGIC 0x564D5868
#define BACKDOOR_PORT  0x5658

enum class Backdoor_Commands : u8
{
    ProcessorFrequency = 1,
    ApmFunction,
    GetDiskGeometry,
    GetPointerPosition,
    SetPointerPosition,
    GetSelectionLength,
    GETNEXTPIECE,
    SetSelectionLength,
    SETNEXTPIECE,
    GetVersion,
    GetDeviceInformations,
    ToggleDevice,
    GetGUIOptions,
    SetGUIOptions,
    GetScreenSize,
    MONITOR_CONTROL,
    GETHWVERSION,
    OSNOTFOUND,
    GETUUID,
    GETMEMSIZE,
    HOSTCOPY,
    SERVICE_VM,
    GETTIME,
    STOPCATCHUP,
    PUTCHR,
    ENABLE_MSG,
    GOTO_TCL,
    INITPCIOPROM,
    INT13,
    MESSAGE,
    RSVD0,
    RSVD1,
    RSVD2,
    ISACPIDISABLED,
    TOE,
    ISMOUSEABSOLUTE,
    PATCH_SMBIOS_STRUCTS,
    MAPMEM,
    PointerData,
    PointerStatus,
    PointerCommand,
    TIMER_SPONGE,
    PATCH_ACPI_TABLES,
    DEVEL_FAKEHARDWARE,
    GETHZ,
    GETTIMEFULL,
    STATELOGGER,
    CHECKFORCEBIOSSETUP,
    LAZYTIMEREMULATION,
    BIOSBBS,
    VASSERT,
    ISGOSDARWIN,
    DEBUGEVENT,
    OSNOTMACOSXSERVER,
    GETTIMEFULL_WITH_LAG,
    ACPI_HOTPLUG_DEVICE,
    ACPI_HOTPLUG_MEMORY,
    ACPI_HOTPLUG_CBRET,
    GET_HOST_VIDEO_MODES,
    ACPI_HOTPLUG_CPU,
    MAX
};
enum class Backdoor_MouseCommands : u32
{
    GetId = 0x45414552,
    Disable = 0x000000f5,
    GetRelative = 0x4c455252,
    GetAbsolute = 0x53424152
};

enum class Backdoor_MousePacketButtons : u16
{
    Left   = 0x0020,
    Right  = 0x0010,
    Middle = 0x0008,
};
struct Backdoor_MousePacket
{
   Backdoor_MousePacketButtons Buttons;
   u16 Flags;
   s32 X, Y, Z;
};

void Backdoor_MouseInitialize();
bool Backdoor_MouseGetPacket(Backdoor_MousePacket* packet);



/*
 * Data related defines
 */
#define VMMOUSE_VERSION_ID_STR          "JUB4"
#define VMMOUSE_VERSION_ID              0x3442554a

/*
 * Device related defines
 */
#define VMMOUSE_DATAPORT                96
#define VMMOUSE_STATUSPORT              100
#define VMMOUSE_IRQ                     12
#define VMMOUSE_ERROR                   0xffff0000

/*
 * VMMouse Input packet flags
 */
#define VMMOUSE_MOVE_RELATIVE           1
#define VMMOUSE_MOVE_ABSOLUTE           0

/*
 * VMMouse Input button flags
 */
#define VMMOUSE_LEFT_BUTTON             0x20
#define VMMOUSE_RIGHT_BUTTON            0x10
#define VMMOUSE_MIDDLE_BUTTON           0x08

#endif