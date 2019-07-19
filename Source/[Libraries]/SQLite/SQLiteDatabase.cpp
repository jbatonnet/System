#include "SQLiteDatabase.h"
#include "SQLiteTable.h"

#include "sqlite-3.8.7.4/sqlite3.h"

using namespace System::Data;
using namespace System::IO;

#define check(error) Exception::Assert(!error || error >= 100, String::Format("SQLiteDatabase.cpp({0}) Error {1}: {2}, {3}", __LINE__, error, sqlite3_errstr(error), sqlite3_errmsg(database)));

SQLiteDatabase::SQLiteDatabase()
{
    //Initialize();

    int error = sqlite3_open(":memory:", (sqlite3**)&database);
    check(error);
}
SQLiteDatabase::SQLiteDatabase(const string& path)
{
    //Initialize();

    char* buffer = new char[path.Length + 1];
    Memory::Copy<char>(path.Buffer, buffer, path.Length);
    buffer[path.Length] = 0;

    int error = sqlite3_open(buffer, (sqlite3**)&database);
    check(error);

    delete[] buffer;
}

u32 SQLiteDatabase::Execute(const string& query)
{
    sqlite3_stmt* statement;
    int error;

    char* buffer = new char[query.Length + 1];
    Memory::Copy<char>(query.Buffer, buffer, query.Length);
    buffer[query.Length] = 0;

    error = sqlite3_prepare(database, buffer, query.Length, &statement, null);
    delete[] buffer;

    if (error)
    {
        Console::WriteLine("SQLiteDatabase.cpp({0}) Error {1}: {2}, {3}", __LINE__, error, sqlite3_errstr(error), sqlite3_errmsg(database));
        return (u32)-1;
    }

    error = sqlite3_step(statement);
    if (error && error < 100)
    {
        Console::WriteLine("SQLiteDatabase.cpp({0}) Error {1}: {2}, {3}", __LINE__, error, sqlite3_errstr(error), sqlite3_errmsg(database));
        return (u32)-1;
    }

    error = sqlite3_finalize(statement);
    Exception::Assert(!error, String::Format("SQLiteDatabase.cpp({0}) Error {1}: {2}, {3}", __LINE__, error, sqlite3_errstr(error), sqlite3_errmsg(database)));

    return (u32)sqlite3_total_changes(database);
}
Reference<Table> SQLiteDatabase::QueryTable(const string& query)
{
    sqlite3_stmt* statement;
    int error;

    char* buffer = new char[query.Length + 1];
    Memory::Copy<char>(query.Buffer, buffer, query.Length);
    buffer[query.Length] = 0;

    error = sqlite3_prepare(database, buffer, query.Length, &statement, null);
    delete[] buffer;

    if (error)
    {
        Console::WriteLine("SQLiteDatabase.cpp({0}) Error {1}: {2}, {3}", __LINE__, error, sqlite3_errstr(error), sqlite3_errmsg(database));
        return (Table*)null;
    }

    return new SQLiteTable(statement);
}

bool SQLite_CheckError(int error, char* file, u32 line, sqlite3* database)
{
    switch (error)
    {
        case SQLITE_OK:
        case SQLITE_DONE:
        case SQLITE_ROW:
            return false;

        default:
            if (file != null && line != -1)
                Console::Write("{0}({1}) ", file, line);

            Console::Write("Error {0}: {1}", error, sqlite3_errstr(error));
            if (database != null)
                Console::Write(sqlite3_errmsg(database));

            Console::WriteLine();
            return true;
    }
}