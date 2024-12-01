#include "../include/cli.hpp"

void parseArgs(int argc, char **argv, Database *db)
{
    if (argc == 1)
    {
        printHelp();
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "--dan") == 0)
        {
            deleteAllNotes(db);
        }
    }
}

void printHelp()
{
    cout << "Help Page" << endl; // to-do make help page
}

void deleteAllNotes(Database *db)
{
    string delVal = R"(
                DELETE FROM notes
            )";
    if (!db->execQuery(delVal))
    {
        cerr << "Error deleting Values from Database Return Code 1";
    }
}
