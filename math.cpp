
#include <iostream>

#include "math.h"

//part 1


//value

Value::Value(double val) : val(val) {}

double Value::calculate() { return val; }


//variable

Variable::Variable(string name, double value) : name(name), value(value) {}

double Variable::calculate() { return value; }


//unary operators

UnaryOperator::UnaryOperator(Expression* expr) : expr(expr) {}

UnaryOperator::~UnaryOperator() { delete expr; }

UPlus::UPlus(Expression* expr) : UnaryOperator(expr) {}

double UPlus::calculate() { return expr->calculate(); }

UMinus::UMinus(Expression* expr) : UnaryOperator(expr) {}

double UMinus::calculate() { return -expr->calculate(); }


//binary operators

BinaryOperator::BinaryOperator(Expression* left, Expression* right) : left(left), right(right) {}

BinaryOperator::~BinaryOperator() { delete left; delete right; }

Plus::Plus(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double Plus::calculate() { return left->calculate() + right->calculate(); }

Minus::Minus(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double Minus::calculate() { return left->calculate() - right->calculate(); }

Mul::Mul(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double Mul::calculate() { return left->calculate() * right->calculate(); }

Div::Div(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double Div::calculate() {
    double r = right->calculate();
    if(r == 0) throw "division by 0!";
    return left->calculate() / r;
}

//part 2

/*void getVariable(map<string, Expression*> &variables, string toVar) {
    /*converts a string of the format "name=value" to the variable with the name 'name' and the value 'value'.
    said variable is then added to the map 'variables' under the name 'name'
    int eqSplit = toVar.find('=');
    string name = toVar.substr(0, eqSplit);

    //check that all chars in the name are valid
    char c = name[0];
    //the first char can either be a letter or an underscore
    if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')) throw "invalid first letter in variable name!";
    for(std::string::iterator it = ++name.begin(); it != name.end(); ++it) {
        c = *it;
        //all non-first chars can either be a letter, an underscore, or a number
        bool is_good_char = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9');
        if(!is_good_char) throw "invalid middle letter in variable name!";
    }

    double value;
    try {
        //get the value of the variable
        value = stod(toVar.substr(eqSplit + 1, toVar.length()));
    }
    catch (const std::invalid_argument& e) {
        throw "invalid variable value!";
    }

    variables[name] = new Variable(name, value);
}

void Interpreter::setVariables(string vars) {
    int pos = vars.find(';');
    while(pos != string::npos) {
        //get a string that represents a variable
        string variable_str = vars.substr(0, pos);
        getVariable(variables, variable_str);
        vars = vars.substr(pos+1, vars.length());
        pos = vars.find(';');
    }
    //if there is a "left_over string" after all of the ;s, convert it as well
    if(vars.length() > 0) {
        getVariable(variables, vars);
    }
}*/

Expression* Interpreter::getOperatorExpression(char *&end, char *&curr, char c, Expression* left_side) {
    /*recieves the current parse information - end and curr - an operator char c, and the left side for said operator.
    returns an expression pointer representing the operator.*/
    //unary or binary expressions
    if(c == '+') {
        if(left_side != nullptr) {
            curr++;
            return new Plus(left_side, parse(end, curr));
        }
        else {
            curr++;
            return new UPlus(parse(end, curr));
        }
    }
    if(c == '-') {
        if(left_side != nullptr) {
            curr++;
            return new Minus(left_side, parse(end, curr));
        }
        else {
            curr++;
            return new UMinus(parse(end, curr));
        }
    }

    //binary expressions
    if(left_side == nullptr) {
        throw "no left side with binary operator!";
    }
    if(c == '*') {
        curr++;
        return new Mul(left_side, parse(end, curr));
    }
    if(c == '/') {
        curr++;
        return new Div(left_side, parse(end, curr));
    }

    return nullptr;
}

Expression* Interpreter::parse(char *&end, char *&curr) {
    bool is_num = false;
    bool is_dec = false;
    //the final number to be converted to a value is num/div_by
    double num = 0;
    double div_by = 1;

    bool is_var = false;
    string var = "";

    Expression * left_over = nullptr;
    while(curr <= end) {
        char c = *curr;

        //value
        if(!is_var && c >= '0' && c <= '9') {
            if(left_over != nullptr) throw "number when a left_over exists!";
            is_num = true;
            num *= 10;
            num += c-'0';
            //if we already read a decimal point the final number should stay in place
            if(is_dec) div_by *= 10;
        }
        //decimal point
        if(c == '.') {
            if(!is_num) throw "decimal point without number!";
            is_dec = true;
        }

        //variable
        if(!is_num) {
            bool is_var_start = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
            bool is_var_good = is_var_start || (c >= '0' && c <= '9');
            if(is_var_start) is_var = true;
            if(is_var_good) {
                if(left_over != nullptr) throw "variable when a left_over exists!";
                if(is_var) {
                    var += c;
                }
                else {
                    throw "variable char without variable starter!";
                }
            }
        }

        //operators
        bool isOperator = (c == '+') || (c == '-') || (c == '*') || (c == '/');
        if(isOperator) {
            if(is_num) return getOperatorExpression(end, curr, c, new Value(num/div_by));
            if(is_var) return getOperatorExpression(end, curr, c, new Value(this->variables.getVar(var)));
            return getOperatorExpression(end, curr, c, left_over);
        }

        //()
        if(c == '(') {
            curr++;
            //parse the subexpression within the bracket
            left_over = parse(end, curr);
            if(*curr != ')') throw "opening bracket without closing bracket!";
            //continue the loop in order to parse the rest of the expression
            curr++;
            continue;
        }
        if(c == ')') {
            /*if(left_over != nullptr) return left_over;
            if(is_num) return new Value(num/div_by);
            if(is_var) return variables[var];
            throw "no valid expression from brackets!";*/
            //an end bracket means we finished parsing the part, and we can thus end the loop
            break;
        }

        //do not continue the loop if a num or a var wasn't detected
        if(!is_num && !is_var) throw "no valid way to parse the given char!";
        //continue loop
        curr++;
    }
    if(left_over != nullptr) return left_over;
    if(is_num) return(new Value(num/div_by));
    if(is_var) return new Value(this->variables.getVar(var));
    throw "finished parsing part but nothing to return!";
    return nullptr;
}

double Interpreter::interpret(string exp) {
    char tmp[exp.size()];
    exp.copy(tmp, exp.size());
    char* start = tmp + 1 - 1;
    char* end = tmp + exp.size() - 1;
    Expression* ret = nullptr;
    return parse(end, start)->calculate();
}
