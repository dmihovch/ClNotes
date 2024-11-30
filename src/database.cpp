#include "../include/database.hpp"
#include "database.hpp"

Database::Database(const string &databaseName)
{
    db = nullptr;
    dbName = databaseName;
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
}

Database::~Database()
{
    close();
}

bool Database::execQuery(const string &query)
{
    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

sqlite3_stmt *Database::prepStatement(const string &query)
{
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }
    return statement;
}

void Database::close()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}