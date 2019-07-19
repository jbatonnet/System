#ifndef _SQLITE_SQLITETABLE_H_
#define _SQLITE_SQLITETABLE_H_

#include <System/Data/Table.h>
#include "sqlite-3.8.7.4/sqlite3.h"

#include <System/Debugging/Console.h>

class SQLiteTableIterator : public Iterator<Reference<System::Data::Record>>
{
private:
    sqlite3_stmt* statement;
    bool end;

public:
    SQLiteTableIterator(sqlite3_stmt* statement) : statement(statement), end(false)
    {
    }

    bool IsEnd();
    Reference<System::Data::Record> GetCurrent();
    bool Next();
};

class SQLiteTable : public System::Data::Table
{
private:
    sqlite3_stmt* statement;

public:
    SQLiteTable(sqlite3_stmt* statement);

    Reference<Iterator<Reference<System::Data::Record>>> GetIterator() const;
};

#endif
