#include "../include/database.hpp"

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

Database *initDb()
{
    Database *db = new Database("clNotes.db");

    string createTableQ = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            quick INTEGER DEFAULT 1,
            title TEXT NOT NULL,
            content TEXT NOT NULL
        );
    )";

    if (!db->execQuery(createTableQ))
    {
        cerr << "Error Creating/Opening Table Return Code 1" << endl;
        return nullptr;
    }
    return db;
}