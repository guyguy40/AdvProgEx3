#include "parser.h"
#include <iostream>

Parser::Parser() : commands() {
    commands["Print"] = new PrintCommand();
    commands["Sleep"] = new SleepCommand();
    commands["while"] = new WhileCommand();
    commands["if"] = new IfCommand();
    commands["var"] = new VariableCommand();
}

void Parser::parse(vector<vector<string>> lexed) {
    int line = 0;
    //while(line < lexed.size()) {
        if(lexed[line].size() < 1) {
            line++;
            //continue;
            return;
        }
        cout << "in parse loop! " << lexed[line][0] << endl;
        string startVal = string(lexed[line][0]);
        Command* toExecute;
        if(commands.count(startVal)) toExecute = commands[startVal];
        else {toExecute = commands[string("var")];}
        line += toExecute->execute(lexed,line);
    //}
}
