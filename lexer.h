#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

using namespace std;

#include <vector>
#include <string>

class Lexer {

public:
    vector<vector<string>> lex(string toLex);
};

#endif
