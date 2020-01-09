#include "lexer.h"
#include "parser.h"

class Command;

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    ifstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile) {
        throw "input file doesn't exist!";
    }
    std::string code((std::istreambuf_iterator<char>(inputFile)),
                 std::istreambuf_iterator<char>());

    Lexer lexer = Lexer();
    vector<vector<string>> lines = lexer.lex(code);
    cout << "lexed!" << endl;

    Parser parser = Parser();
    parser.initializeMap();
    parser.parse(lines);
    cout << "parsed!" << endl;

    return 0;
}
