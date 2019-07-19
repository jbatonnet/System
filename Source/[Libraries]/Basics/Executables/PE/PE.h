#ifndef _PE_H_
#define _PE_H_

#include <System/Common.h>
#include <System/Runtime/Threading/Executable.h>

#define PE_MAGIC 0x00004550

struct PE_DosHeader
{
    u16 Magic;                     // Magic number
    u16 cblp;                      // Bytes on last page of file
    u16 PagesCount;                        // Pages in file
    u16 crlc;                      // Relocations
    u16 cparhdr;                   // Size of header in paragraphs
    u16 minalloc;                  // Minimum extra paragraphs needed
    u16 maxalloc;                  // Maximum extra paragraphs needed
    u16 ss;                        // Initial (relative) SS value
    u16 sp;                        // Initial SP value
    u16 Checksum;                      // Checksum
    u16 ip;                        // Initial IP value
    u16 cs;                        // Initial (relative) CS value
    u16 lfarlc;                    // File address of relocation table
    u16 ovno;                      // Overlay number
    u16 Reserved[4];                    // Reserved words
    u16 OemId;                     // OEM identifier (for e_oeminfo)
    u16 OemInfo;                   // OEM information; e_oemid specific
    u16 Reserved2[10];                  // Reserved words
    u32 PeHeader;                    // File address of new exe header
};

struct PE_PeFileHeader
{
    u16 Machine;
    u16 SectionsCount;
    u32 TimeDate;
    u32 Symbols;
    u32 SymbolsCount;
    u16 OptionalHeaderSize;
    u16 Characteristics;
};
struct PE_PeOptionalHeader
{
	u16 Magic; // 0x010b - PE32, 0x020b - PE32+ (64 bit)
	u8  MajorLinkerVersion;
	u8  MinorLinkerVersion;
	u32 SizeOfCode;
	u32 SizeOfInitializedData;
	u32 SizeOfUninitializedData;
	u32 AddressOfEntryPoint;
	u32 BaseOfCode;
	u32 BaseOfData;
	u32 ImageBase;
	u32 SectionAlignment;
	u32 FileAlignment;
	u16 MajorOperatingSystemVersion;
	u16 MinorOperatingSystemVersion;
	u16 MajorImageVersion;
	u16 MinorImageVersion;
	u16 MajorSubsystemVersion;
	u16 MinorSubsystemVersion;
	u32 Win32VersionValue;
	u32 SizeOfImage;
	u32 SizeOfHeaders;
	u32 CheckSum;
	u16 Subsystem;
	u16 DllCharacteristics;
	u32 SizeOfStackReserve;
	u32 SizeOfStackCommit;
	u32 SizeOfHeapReserve;
	u32 SizeOfHeapCommit;
	u32 LoaderFlags;
	u32 NumberOfRvaAndSizes;
};
struct PE_PeHeader
{
    u32 Magic;
    PE_PeFileHeader FileHeader;
    PE_PeOptionalHeader OptionalHeader;
};
struct PE_PeSection
{
    char Name[8];
    
    union
    {
        u32 PhysicalAddress;
        u32 VirtualSize;
    };

    u32 VirtualAddress;
    u32 SizeOfRawData;
    u32 PointerToRawData;
    u32 PointerToRelocations;
    u32 PointerToLinenumbers;
    u16 NumberOfRelocations;
    u16 NumberOfLinenumbers;
    u32 Characteristics;
};

struct PeSection
{
    string Name;

    u32 Size;
    u32 Real;
    u32 Virtual;
};

/*
    u32 peHeader;
    u32 sections;
    u32 entry;
    u32 textReal, textVirtual, textSize;
    u32 rdataReal, rdataVirtual, rdataSize;
    u32 dataReal, dataVirtual, dataSize;
*/

class PEExecutable : public System::Runtime::Executable
{
private:
    PE_DosHeader* dosHeader;
    PE_PeHeader* peHeader;
    List<PE_PeSection*> sections;

public:
    System::Runtime::Process* CreateProcess();

    static System::Runtime::Executable* Load(const string& path);
    static System::Runtime::Executable* Load(System::IO::File* file);
    static System::Runtime::Executable* Load(System::IO::Stream* stream);
};

#endif