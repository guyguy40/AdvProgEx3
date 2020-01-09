#include "parser.h"
#include <iostream>

void Parser::parse(vector<vector<string>> lexed) {
    int line = 0;
    while(line < lexed.size()) {
        if(lexed[line].size() < 1) {
            line++;
            continue;
        }
        string startVal = string(lexed[line][0]);
        cout << "in parse loop! " << startVal << endl;
        Command* toExecute;
        cout << "searching for command!" << endl;
        for(auto elem : commands)
        {
           std::cout << elem.first << " " << elem.second << "\n";
        }

        if(commands.find(startVal) != commands.end()) {
            cout << "found command!" << endl;
            toExecute = commands[startVal];
        }
        else {
            cout << "at default! Value is " << startVal << endl;
            toExecute = commands[string("var")];
        }
        line += toExecute->execute(lexed,line);
    }
}

void Parser::initializeMap(SymbolTable* symb) {
    commands["Print"] = new PrintCommand();
    commands["Sleep"] = new SleepCommand();
    commands["var"] = new VariableCommand(symb);

    WhileCommand* whCmd = new WhileCommand();
    whCmd->initializeParser(this);
    commands["while"] = whCmd;

    IfCommand* ifCmd = new IfCommand();
    ifCmd->initializeParser(this);
    commands["if"] = ifCmd;
}
