#include "SQLiteDatabase.h"
#include "SQLiteTable.h"
#include "SQLiteRecord.h"

using namespace System::Data;

bool SQLiteTableIterator::IsEnd()
{
    return end;
}
Reference<System::Data::Record> SQLiteTableIterator::GetCurrent()
{
    return new SQLiteRecord(statement);
}
bool SQLiteTableIterator::Next()
{
    if (end)
        return false;

    int error = sqlite3_step(statement);
    if (error == SQLITE_DONE)
        end = true;

    return !SQLite_CheckError(error, __FILE__, __LINE__);
}

SQLiteTable::SQLiteTable(sqlite3_stmt* statement) : statement(statement)
{
    //Console::WriteLine("SQLiteTable: {0}", statement);
}

Reference<Iterator<Reference<Record>>> SQLiteTable::GetIterator() const
{
    return new SQLiteTableIterator(statement);
}