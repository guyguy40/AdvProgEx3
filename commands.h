#ifndef PROJECT_OPTABLE_H
#define PROJECT_OPTABLE_H

#include "parser.h"
#include "math.h"

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

#endif
