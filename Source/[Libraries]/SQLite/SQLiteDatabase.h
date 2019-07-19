#ifndef _KERNEL_SQLITEDATABASE_H_
#define _KERNEL_SQLITEDATABASE_H_

#include <System/Data/Database.h>
#include "sqlite-3.8.7.4/sqlite3.h"

bool SQLite_CheckError(int error, char* file = 0, u32 line = -1, sqlite3* database = 0);

class SQLiteDatabase : public System::Data::Database
{
private:
    sqlite3* database;

public:
    SQLiteDatabase();
    SQLiteDatabase(const string& path);
    //SQLiteDatabase(Stream* stream);

    u32 Execute(const string& query);
    Reference<System::Data::Table> QueryTable(const string& query);
};

#endif