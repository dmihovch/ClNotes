#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

class Database
{
private:
    sqlite3 *db;
    string dbName;

public:
    explicit Database(const string &);
    ~Database();
    bool execQuery(const string &);
    sqlite3_stmt *prepStatement(const string &);
    void close();
};