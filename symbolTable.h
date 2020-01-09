
#ifndef PROJECT_OPTABLE_H
#define PROJECT_OPTABLE_H

#include <map>

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
