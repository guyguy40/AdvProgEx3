#include "parser.h"
#include <iostream>

void Parser::parse(vector<vector<string>> lexed) {
    int line = 0;
    while(line < lexed.size()) {
        if(lexed[line].size() < 1) {
            line++;
            continue;
        }
        cout << "in parse loop! " << lexed[line][0] << endl;
        string startVal = string(lexed[line][0]);
        Command* toExecute;
        if(commands.count(startVal)) {
            toExecute = commands[startVal];
            line += toExecute->execute(lexed,line);
        }
        else {
            cout << "at default! Value is " << startVal << endl;
            return;
            //toExecute = commands[string("var")];
        }
    }
}

void Parser::initializeMap() {
    commands["Print"] = new PrintCommand();
    commands["Sleep"] = new SleepCommand();

    WhileCommand* whCmd = new WhileCommand();
    whCmd->initializeParser(this);
    commands["while"] = whCmd;

    IfCommand* ifCmd = new IfCommand();
    ifCmd->initializeParser(this);
    commands["if"] = ifCmd;
}
