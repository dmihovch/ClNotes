#pragma once
#include <iostream>
#include <string>
#include "../include/database.hpp"
using namespace std;
void parseArgs(int, char **, Database *);
void printHelp();
void deleteAllNotes(Database *);