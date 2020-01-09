#include "symbolTable.h"

void SymbolTable::valueBind(string var, double value) {
    valueMap[var] = value;
}

void SymbolTable::rightBind(string var, string bind) {
    rightBindMap[var] = bind;
}

void SymbolTable::leftBind(string var, string bind) {
    leftBindMap[var] = bind;
}

double SymbolTable::getVar(string var) {
    return valueMap[var];
}
