#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

using namespace std;

class Command;

#include <vector>
#include <string>
#include <map>

#include "symbolTable.h"

class Parser {

public:
    Parser() : commands() {}
    void initializeMap(SymbolTable* symb);
    void parse(vector<vector<string>> lexed);

private:
    map<string, Command*> commands;
};

#include "commands.h"

#endif
