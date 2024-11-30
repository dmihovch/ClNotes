#include "../include/cli.hpp"
#include "../include/database.hpp"

int main(int argc, char **argv)
{
    Database db("clNotes.db");

    string createTableQ = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            quick INTEGER DEFAULT 1,
            title TEXT NOT NULL,
            content TEXT NOT NULL
        );
    )";

    if (!db.execQuery(createTableQ))
    {
        cerr << "Error Creating/Opening Table Return Code 1" << endl;
        return 1;
    }

    string insertVal = R"(
        INSERT INTO notes(title, content)
        VALUES ('A Note!','Content of my note!')
    )";
    if (!db.execQuery(insertVal))
    {
        cerr << "Error inserting Value Return Code 1" << endl;
    }

    // example of how to get all info on a table
    string getValTest = R"(
        SELECT * FROM notes
    )";
    sqlite3_stmt *find = db.prepStatement(getValTest);
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

    if (argc > 1)
    {
        if (strcmp(argv[1], "--dan") == 0) // is true, ya it's weird dan = delete all notes
        {
            string delVal = R"(
                DELETE FROM notes
            )";
            if (!db.execQuery(delVal))
            {
                cerr << "Error deleting Values from Database Return Code 1";
            }
        }
    }

    db.close();
    return 0;
}