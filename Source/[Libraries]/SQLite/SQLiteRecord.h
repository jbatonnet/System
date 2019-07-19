#ifndef _SQLITE_RECORD_H_
#define _SQLITE_RECORD_H_

#include <System/Data/Record.h>
#include "sqlite-3.8.7.4/sqlite3.h"

class SQLiteRecord : public System::Data::Record
{
private:
    sqlite3_stmt* statement;
    u32 count;

public:
    SQLiteRecord(sqlite3_stmt* statement);

    string GetString(u32 index);
    bool GetBool(u32 index);
    u8 GetU8(u32 index);
    u16 GetU16(u32 index);
    u32 GetU32(u32 index);
    u64 GetU64(u32 index);
    s8 GetS8(u32 index);
    s16 GetS16(u32 index);
    s32 GetS32(u32 index);
    s64 GetS64(u32 index);
    float GetFloat(u32 index);
    double GetDouble(u32 index);
};

#endif