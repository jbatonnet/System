#include "SQLiteRecord.h"

SQLiteRecord::SQLiteRecord(sqlite3_stmt* statement) : statement(statement)
{
    count = sqlite3_column_count(statement);
}

string SQLiteRecord::GetString(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (char*)sqlite3_column_text(statement, index);
}
bool SQLiteRecord::GetBool(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return !!sqlite3_column_int(statement, index);
}
u8 SQLiteRecord::GetU8(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (u8)sqlite3_column_int(statement, index);
}
u16 SQLiteRecord::GetU16(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (u16)sqlite3_column_int(statement, index);
}
u32 SQLiteRecord::GetU32(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (u32)sqlite3_column_int(statement, index);
}
u64 SQLiteRecord::GetU64(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (u64)sqlite3_column_int64(statement, index);
}
s8 SQLiteRecord::GetS8(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (s8)sqlite3_column_int(statement, index);
}
s16 SQLiteRecord::GetS16(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (s16)sqlite3_column_int(statement, index);
}
s32 SQLiteRecord::GetS32(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (s32)sqlite3_column_int(statement, index);
}
s64 SQLiteRecord::GetS64(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (s64)sqlite3_column_int64(statement, index);
}
float SQLiteRecord::GetFloat(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (float)sqlite3_column_double(statement, index);
}
double SQLiteRecord::GetDouble(u32 index)
{
    Exception::Assert(index < count, "SQLiteRecord, index < count");
    return (double)sqlite3_column_double(statement, index);
}