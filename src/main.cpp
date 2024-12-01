#include "../include/cli.hpp"
#include "../include/database.hpp"

int main(int argc, char **argv)
{
    Database *db = initDb();
    if (!db)
    {
        return 1;
    }
    parseArgs(argc, argv, db);

    // example of how to add a note to the table
    string insertVal = R"(
        INSERT INTO notes(title, content)
        VALUES ('A Note!','Content of my note!')
    )";
    if (!db->execQuery(insertVal))
    {
        cerr << "Error inserting Value Return Code 1" << endl;
    }

    // example of how to get all info on a table
    string getValTest = R"(
        SELECT * FROM notes
    )";
    sqlite3_stmt *find = db->prepStatement(getValTest);
    if (!find)
    {
        cerr << "Error finding Values Return Code 1" << endl;
    }
    while (sqlite3_step(find) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(find, 0);
        bool quick = bool(sqlite3_column_int(find, 1));
        const unsigned char *title = sqlite3_column_text(find, 2);
        const unsigned char *content = sqlite3_column_text(find, 3);
        cout << "ID: " << id << " quick flag: " << quick << " title: " << title << " content: " << content << endl;
    }
    sqlite3_finalize(find);
    // end examples

    // close db connection and return successful exit code 0
    db->close();
    return 0;
}