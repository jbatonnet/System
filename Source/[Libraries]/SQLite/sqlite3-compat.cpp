#include "sqlite3-compat.h"
#include "sqlite-3.8.7.4/sqlite3.h"

#include <System/Memory/Memory.h>
#include <System/Utilities/Random.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>
#include <System/IO/File.h>
#include <System/IO/Streams/Stream.h>

#define SQLITE_DEBUG 0
#define SQLITE_MAX_ALLOCATIONS 1024

using namespace System::IO;

struct SQLiteStream : public sqlite3_file
{
    Stream* stream;
    string Name;
};

sqlite3_vfs vfs = { 0 };
sqlite3_io_methods methods = { 0 };

struct SQLiteAllocation
{
    void* Pointer;
    u32 Size;
} allocations[SQLITE_MAX_ALLOCATIONS] = { 0 };

void* malloc(size_t size)
{
    void* pointer = Memory::Allocate(size);
    //Serial::WriteLine("malloc({0}) => {1}", size, pointer);

    for (int i = 0; i < SQLITE_MAX_ALLOCATIONS; i++)
        if (!allocations[i].Pointer)
        {
            allocations[i].Pointer = pointer;
            allocations[i].Size = size;

            return pointer;
        }

    Exception::Assert("malloc(OUILLE)");
    return null;
}
void free(void* pointer)
{
    Memory::Free(pointer);
    //Serial::WriteLine("free({0})", pointer);

    for (int i = 0; i < SQLITE_MAX_ALLOCATIONS; i++)
        if (allocations[i].Pointer == pointer)
        {
            allocations[i].Pointer = null;
            allocations[i].Size = 0;

            return;
        }

    Exception::Assert(false, "free(OUILLE)");
}
void* realloc(void* pointer, size_t size)
{
    //Serial::WriteLine("realloc({0}, {1})", pointer, size);

    for (int i = 0; i < SQLITE_MAX_ALLOCATIONS; i++)
        if (allocations[i].Pointer == pointer)
        {
            if (size > allocations[i].Size)
            {
                pointer = Memory::Allocate(size);
                Memory::Copy(allocations[i].Pointer, pointer, allocations[i].Size);
                Memory::Free(allocations[i].Pointer);

                allocations[i].Pointer = pointer;
                allocations[i].Size = size;
            }

            return pointer;
        }

    Exception::Assert(false, "realloc(OUILLE)");
    return null;
}
struct tm* gmtime(const time_t* timer)
{
    static struct tm result;
    return &result;
}
size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr)
{
    return 0;
}
void* memcpy(void *v_dst, const void *v_src, size_t c)
{
	const char *src = (const char*)v_src;
	char *dst = (char*)v_dst;

	/* Simple, byte oriented memcpy. */
	while (c--)
		*dst++ = *src++;

	return v_dst;
}
void* memmove(void *v_dst, const void *v_src, size_t c)
{
	const char *src = (const char*)v_src;
	char *dst = (char*)v_dst;

	if (!c)
		return v_dst;

	/* Use memcpy when source is higher than dest */
	if (v_dst <= v_src)
		return memcpy(v_dst, v_src, c);

	/* copy backwards, from end to beginning */
	src += c;
	dst += c;

	/* Simple, byte oriented memmove. */
	while (c--)
		*--dst = *--src;

	return v_dst;
}
int memcmp(const void* str1, const void* str2, size_t count)
{
	const unsigned char* s1 = (const unsigned char*)str1;
	const unsigned char* s2 = (const unsigned char*)str2;

	while (count-- > 0)
	{
		if (*s1++ != *s2++)
			return s1[-1] < s2[-1] ? -1 : 1;
	}
	return 0;
}
int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}
int strcmp(const char* X, const char* Y)
{
	while (*X)
	{
		// if characters differ or end of second string is reached
		if (*X != *Y)
			break;

		// move to next pair of characters
		X++;
		Y++;
}

	// return the ASCII difference after converting char* to unsigned char*
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int xClose(sqlite3_file* file)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xClose({0})", file);
#endif
    return SQLITE_OK;
}
int xRead(sqlite3_file* file, void* buffer, int count, s64 position)
{
#if SQLITE_DEBUG
    Serial::Write("xRead({0}, {1}, {2}, {3}) ... ", file, buffer, count, (u32)position);
#endif

    SQLiteStream* stream = (SQLiteStream*)file;
    stream->stream->Seek(position);
    u32 read = stream->stream->Read((char*)buffer, count);

#if SQLITE_DEBUG
    Serial::WriteLine("Read {0} bytes", read);
#endif
    return SQLITE_OK;
}
int xWrite(sqlite3_file* file, const void* buffer, int count, s64 position)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xWrite({0}, {1}, {2}, {3})", file, buffer, count, (u32)position);
#endif
    return 0;
}
int xTruncate(sqlite3_file* file, s64 size)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xTruncate({0}, {1})", file, size);
#endif
    return SQLITE_OK;
}
int xSync(sqlite3_file* file, int flags)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xSync({0}, {1})", file, flags);
#endif
    return SQLITE_OK;
}
int xFileSize(sqlite3_file* file, s64 *pSize)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::Write("xFileSize('{0}') ...", stream->Name);
    Serial::WriteLine(" {0} bytes", (u32)stream->stream->Length);
#endif

    *pSize = (u32)stream->stream->Length;
    return SQLITE_OK;
}
int xLock(sqlite3_file* file, int type)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xLock('{0}', {1})", stream->Name, type);
#endif

    return SQLITE_OK;
}
int xUnlock(sqlite3_file* file, int type)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xUnlock('{0}', {1})", stream->Name, type);
#endif

    return SQLITE_OK;
}
int xCheckReservedLock(sqlite3_file* file, int *result)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xCheckReservedLock('{0}')", stream->Name);
#endif

    *result = 0;

    return SQLITE_OK;
}
int xFileControl(sqlite3_file* file, int op, void *pArg)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xFileControl('{0}', {1})", stream->Name, op);
#endif

    return SQLITE_OK;
}
int xSectorSize(sqlite3_file* file)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xSectorSize({0})", file);
#endif

    return 0;
}
int xDeviceCharacteristics(sqlite3_file* file)
{
    SQLiteStream* stream = (SQLiteStream*)file;
#if SQLITE_DEBUG
    Serial::WriteLine("xDeviceCharacteristics('{0}')", stream->Name);
#endif

    return 0;
}

int xOpen(sqlite3_vfs* vfs, const char* path, sqlite3_file* file, int flags, int* outFlags)
{
#if SQLITE_DEBUG
    Serial::Write("xOpen({0}, '{1}', {2}, {3}) ... ", vfs, path, file, flags);
#endif

    SQLiteStream* stream = (SQLiteStream*)file;

    stream->Name = path;
    stream->stream = File::OpenStream(path);

    if (!stream->stream)
    {
#if SQLITE_DEBUG
        Serial::WriteLine("Error");
#endif
        return SQLITE_CANTOPEN;
    }

    stream->pMethods = &methods;
    *outFlags = flags;//SQLITE_OPEN_READONLY;

#if SQLITE_DEBUG
    Serial::WriteLine("OK");
#endif
    return SQLITE_OK;
}
int xDelete(sqlite3_vfs* vfs, const char* path, int syncDir)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xDelete({0}, '{1}', {2})", vfs, path, syncDir);
#endif
    return SQLITE_OK;
}
int xAccess(sqlite3_vfs* vfs, const char* path, int flags, int* outRes)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xAccess({0}, '{1}', {2})", vfs, path, flags);
#endif

    *outRes = false;

    return SQLITE_OK;
}
int xFullPathname(sqlite3_vfs* vfs, const char* path, int length, char* out)
{
#if SQLITE_DEBUG
    Serial::Write("xFullPathname({0}, '{1}', {2}, {3}) ... ", vfs, path, length, out);
#endif

    string file = string(path).After(':').Before('?');
    Memory::Copy(file.Buffer, out, file.Length + 1);
    out[file.Length] = 0;

    Serial::WriteLine("OK");
    return 0;
}
void* xDlOpen(sqlite3_vfs* vfs, const char* path)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xDlOpen({0}, '{1}')", vfs, path);
#endif
    return 0;
}
void xDlError(sqlite3_vfs* vfs, int length, char* message)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xDlError({0}, {1}, '{2}')", vfs, length, message);
#endif
}
void(*xDlSym(sqlite3_vfs* vfs, void* pH, const char* z))(void)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xDlSym(?)");
#endif
    return 0;
}
void xDlClose(sqlite3_vfs* vfs, void* data)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xDlClose({0}, {1})", vfs, data);
#endif
}
int xRandomness(sqlite3_vfs* vfs, int count, char* out)
{
#if SQLITE_DEBUG
    Serial::Write("xRandomness({0}, {1}) ... ", vfs, count);
#endif

    Random random;
    for (u32 i = 0; i < count; i++)
        out[i] = random.Generate<byte>();

    Serial::WriteLine("OK");
    return count;
}
int xSleep(sqlite3_vfs* vfs, int microseconds)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xSleep(%x, %d)", vfs, microseconds);
#endif
    return 0;
}
int xCurrentTime(sqlite3_vfs* vfs, double* data)
{
#if SQLITE_DEBUG
    Serial::WriteLine("xCurrentTime(%x, %x)", vfs, data);
#endif
    return 0;
}

int sqlite3_os_init()
{
#if SQLITE_DEBUG
    Serial::WriteLine("sqlite3_os_init()");
#endif

    if (vfs.iVersion)
        return SQLITE_ERROR;

    vfs.iVersion = 1;
    vfs.szOsFile = sizeof(SQLiteStream);
    vfs.mxPathname = 255;
    vfs.pNext = 0;
    vfs.zName = "myvfs";
    vfs.pAppData = 0;
    vfs.xOpen = xOpen;
    vfs.xDelete = xDelete;
    vfs.xAccess = xAccess;
    vfs.xFullPathname = xFullPathname;
    vfs.xDlOpen = xDlOpen;
    vfs.xDlError = xDlError;
    vfs.xDlSym = xDlSym;
    vfs.xDlClose = xDlClose;
    vfs.xRandomness = xRandomness;
    vfs.xSleep = xSleep;
    vfs.xCurrentTime = vfs.xCurrentTime;

    methods.iVersion = 1;
    methods.xClose = xClose;
    methods.xRead = xRead;
    methods.xWrite = xWrite;
    methods.xTruncate = xTruncate;
    methods.xSync = xSync;
    methods.xFileSize = xFileSize;
    methods.xLock = xLock;
    methods.xUnlock = xUnlock;
    methods.xCheckReservedLock = xCheckReservedLock;
    methods.xFileControl = xFileControl;
    methods.xSectorSize = xSectorSize;
    methods.xDeviceCharacteristics = xDeviceCharacteristics;

    int result = sqlite3_vfs_register(&vfs, true);
    Exception::Assert(!result, String::Format("SQLiteDatabase: Error {0} while registering vfs", result));

    return 0;
}
int sqlite3_os_end()
{
#if SQLITE_DEBUG
    Serial::WriteLine("sqlite3_os_end()");
#endif
    return 0;
}