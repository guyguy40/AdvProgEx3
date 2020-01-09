#ifndef PROJECT_OPTABLE_H
#define PROJECT_OPTABLE_H

using namespace std;

#include "parser.h"
#include "math.h"
#include "symbolTable.h"

#include <string>
#include <vector>

class ExpressionHandler {
public:
    ExpressionHandler() : inter() {};
    double handleDouble(string exp);
    string handleString(string exp);

private:
    Interpreter inter;
};

class Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line) = 0;
};

class DataServerCommand : public Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line);
};

class ConnectCommand : public Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line);
};

class LoopCommand : public Command {
public:
    void initializeParser(Parser* p) {p = p;}
    virtual double execute(vector<vector<string>> lexed, int line);
    virtual double loop(string cond) = 0;
private:
    Parser* p;
};

class WhileCommand : public LoopCommand {
public:
    WhileCommand() : exp(){}
    virtual double loop(string cond);
private:
    ExpressionHandler exp;
};

class IfCommand : public LoopCommand {
public:
    IfCommand() : exp(), prevCond(""), times(0) {}
    virtual double loop(string cond);
private:
    ExpressionHandler exp;
    string prevCond;
    int times;
};

class PrintCommand : public Command {
public:
    PrintCommand() : exp() {}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    ExpressionHandler exp;
};

class SleepCommand : public Command {
public:
    SleepCommand() : exp() {}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    ExpressionHandler exp;
};

class VariableCommand : public Command {
public:
    VariableCommand(SymbolTable* symb) : exp() {symb = symb;}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    ExpressionHandler exp;
    SymbolTable* symb;
};

#endif
