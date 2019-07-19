#ifndef _SYSTEM_DATABASE_H_
#define _SYSTEM_DATABASE_H_

#include <System/Common.h>
#include <System/Data/Table.h>

namespace System
{
    namespace Data
    {
        class Database
        {
        public:
            virtual u32 Execute(const string& query) = 0;
            virtual Reference<Table> QueryTable(const string& query) = 0;

            template<typename First, typename... Other> u32 Execute(const string& format, First parameter, Other... parameters)
            {
                return Execute(String::Format(format, parameter, parameters...));
            }
            template<typename First, typename... Other> Reference<Table> QueryTable(const string& query, First parameter, Other... parameters)
            {
                return QueryTable(String::Format(query, parameters...));
            }
            template<typename... Args> Reference<Record> QueryRecord(const string& query, Args... parameters)
            {
                Reference<Table> table = QueryTable(String::Format(query, parameters...));
                return table->First();
            }
            template<typename T = string, typename... Args> T QueryValue(const string& query, Args... parameters)
            {
                Reference<Table> table = QueryTable(String::Format(query, parameters...));
                Reference<Record> record = table->First();
                return record->Get<T>(0);
            }

            static Database* Default;
        };
    }
}

#endif