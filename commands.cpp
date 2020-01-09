#include "commands.h"

#include <chrono>
#include <thread>

double DataServerCommand::execute(vector<vector<string>> lexed, int line) {
    //do later
    return 1;
}

double ConnectCommand::execute(vector<vector<string>> lexed, int line) {
    //do later
    return 1;
}

double LoopCommand::execute(vector<vector<string>> lexed, int line) {
    string cond = lexed[line][1];
    int skip = 1;
    int opens = 0;
    while(opens != 0 || lexed[line+skip][0] != "}") {
        if(lexed[line+skip][0] != "while" || lexed[line+skip][0] != "if") opens ++;
        if(lexed[line+skip][0] != "}") opens --;
        skip++;
    }

    vector<vector<string>> commands;
    for(int i = line+1; i<line+skip; i++) {
        commands.push_back(lexed[i]);
    }

    while(loop(cond)) {
        p.parse(commands);
    }
    return skip+1;
}

double WhileCommand::loop(string cond) {
    return this->exp.handleDouble(cond);
}

double IfCommand::loop(string cond) {
    if(cond != prevCond) times = 0;
    prevCond = cond;
    if(times > 0) return 0;
    times++;
    return this->exp.handleDouble(cond);
}

double PrintCommand::execute(vector<vector<string>> lexed, int line) {
    cout << "print command!" << endl;
    cout << this->exp.handleString(lexed[line][1]) << endl;
    return 1;
}

double SleepCommand::execute(vector<vector<string>> lexed, int line) {
    int mils = this->exp.handleDouble(lexed[line][1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(mils));
    return 1;
}

double VariableCommand::execute(vector<vector<string>> lexed, int line) {
    int pos = 0;
    if(lexed[line][pos] == "var") pos++;
    string name = lexed[line][0];

    int type = 0;
    if(lexed[line][pos+1] == "<-") type = 1;
    if(lexed[line][pos+1] == "->") type = 2;

    if(type == 0) {
        double val = this->exp.handleDouble(lexed[line][pos+2]);
        this->symb.valueBind(name, val);
    }
    else {
        string toBind;
        if(lexed[line][pos+2] == "sim") toBind = lexed[line][pos+3].substr(1, lexed[line][pos+3].size() - 2);
        else {toBind = lexed[line][pos+2];}
        if(type == 1) this->symb.leftBind(name, toBind);
        else {this->symb.rightBind(name, toBind);}
    }
    return 1;
}

double ExpressionHandler::handleDouble(string exp) {
    return this->inter.interpret(exp);
}

string ExpressionHandler::handleString(string exp) {
    if(exp[0] == '"') {
        return exp.substr(1, exp.size() - 2);
    }
    return to_string(this->inter.interpret(exp));
}
