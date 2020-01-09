#ifndef PROJECT_MATH_H
#define PROJECT_MATH_H

#include "symbolTable.h"

using namespace std;

#include <string>
#include <map>

class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

//value / variable

class Value : public Expression {

public:
    Value(double val);
    virtual double calculate();

protected:
    double val;
};

class Variable : public Expression {

public:
    //double is a placeholder for the variable table
    Variable(string name, double value);
    virtual double calculate();

protected:
    string name;
    double value;
};

//unary operators

class UnaryOperator : public Expression {

public:
    UnaryOperator(Expression* expr);
    virtual ~UnaryOperator();

protected:
    Expression* expr;
};

class UPlus : public UnaryOperator {

public:
    UPlus(Expression* expr);
    virtual double calculate();
};

class UMinus : public UnaryOperator {

public:
    UMinus(Expression* expr);
    virtual double calculate();
};


//binary operators

class BinaryOperator : public Expression {

public:
    BinaryOperator(Expression* left, Expression* right);
    virtual ~BinaryOperator();

protected:
    Expression* left;
    Expression* right;
};

class Plus : public BinaryOperator {

public:
    Plus(Expression* left, Expression* right);
    virtual double calculate();
};

class Minus : public BinaryOperator {

public:
    Minus(Expression* left, Expression* right);
    virtual double calculate();
};

class Mul : public BinaryOperator {

public:
    Mul(Expression* left, Expression* right);
    virtual double calculate();
};

class Div : public BinaryOperator {

public:
    Div(Expression* left, Expression* right);
    virtual double calculate();
};

class Interpreter {
public:
    Interpreter() : variables() {}
    double interpret(string exp);

private:
    SymbolTable variables;
    Expression* getOperatorExpression(char *&end, char *&curr, char c, Expression* leftSide);
    Expression* parse(char *&end, char *&curr);
};


#endif
