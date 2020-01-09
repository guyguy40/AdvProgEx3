#ifndef PROJECT_SYMTABLE_H
#define PROJECT_SYMTABLE_H

#include <map>
#include <string>

using namespace std;

class SymbolTable {

public:
    SymbolTable() : valueMap(), rightBindMap(), leftBindMap() {}
    void valueBind(string var, double value);
    void rightBind(string var, string bind);
    void leftBind(string var, string bind);
    double getVar(string var);
private:
    map<string, double> valueMap;
    map<string, string> rightBindMap;
    map<string, string> leftBindMap;
};

#endif
