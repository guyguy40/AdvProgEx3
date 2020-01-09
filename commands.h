#ifndef PROJECT_OPTABLE_H
#define PROJECT_OPTABLE_H

#include "parser.h"
#include "math.h"
#include "symbolTable.h"

#include <string>
#include <vector>

class ExpressionHandler {
public:
    ExpressionHandler() : inter() {};
    double handleDouble(string exp);
    string handleDouble(string exp);

private:
    Interpreter inter;
};

class Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line) = 0;
}

class DataServerCommand : public Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line);
}

class ConnectCommand : public Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line);
}

class LoopCommand : public Command {
public:
    virtual double execute(vector<vector<string>> lexed, int line);
    virtual double loop(string cond) = 0;
}

class WhileCommand : public LoopCommand {
public:
    WhileCommand() : exp() {}
    virtual double loop(string cond);
private:
    Interpreter exp;
}

class IfCommand : public LoopCommand {
public:
    WhileCommand() : exp(), prevCond(""), times(0) {}
    virtual double loop(string cond);
private:
    Interpreter exp;
    string prevCond;
    int times;
}

class PrintCommand : public Command {
public:
    PrintCommand() : exp() {}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    Interpreter exp;
}

class SleepCommand : public Command {
public:
    SleepCommand() : exp() {}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    Interpreter exp;
}

class VariableCommand : public Command {
public:
    VariableCommand() : exp(), symb() {}
    virtual double execute(vector<vector<string>> lexed, int line);
private:
    Interpreter exp;
    SymbolTable symb;
}

#endif
