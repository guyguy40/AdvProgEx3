#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

using namespace std;

class Command;

#include <vector>
#include <string>
#include <map>

class Parser {

public:
    Parser();
    void parse(vector<vector<string>> lexed);

private:
    map<string, Command*> commands;
};

#include "commands.h"

#endif
