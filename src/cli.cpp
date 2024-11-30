#include "../include/cli.hpp"

void parseArgs(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "No arguments provided" << endl;
        printHelp();
    }
}

void printHelp()
{
    cout << "Help Page" << endl;
}