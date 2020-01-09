#include "lexer.h"

#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <iostream>

vector<string> getLines(string toLines) {
    vector<string> ret = vector<string>();
    std::stringstream ss(toLines);
    string line;

    while (ss.good())
    {
        getline(ss,line,'\n');
        ret.push_back(line);
    }

    return ret;
}

int readParams(string line, int i, vector<string>& tokens) {
    int k = i;
    int j = i+1;
    int brackets = 0;
    while(j<line.size()-1) {
        if(line[j] == ',') {
            string toPush = line.substr(k, j-k);
            toPush.erase(remove(toPush.begin(), toPush.end(), ' '), toPush.end());
            tokens.push_back(string(toPush));
            k = j+1;
        }

        if(line[j] == '(') brackets++;

        if(line[j] == ')') {
            if(brackets == 0) break;
            brackets--;
        }
        j++;
    }
    if(j != i+1) {
        string toPush = line.substr(k, j-k);
        toPush.erase(remove(toPush.begin(), toPush.end(), ' '), toPush.end());
        tokens.push_back(string(toPush));
    }
    return j;
}

vector<string> lexLine(string line) {
    vector<string> tokens = vector<string>();
    int i = -1;
    string generatedToken = "";
    while((line.size() != 0 && i == -1) || i<line.size()-1) {
        i++;
        char c = line[i];

        if(isspace(c)) {
            if(generatedToken != "") tokens.push_back(generatedToken);
            if(generatedToken == "while" || generatedToken == "if") {
                i = readParams(line, i+1, tokens);
            }
            generatedToken = "";
            continue;
        }

        if(c == '<' && line[i+1] == '-') {
            if(generatedToken != "") tokens.push_back(generatedToken);
            tokens.push_back("<-");
            generatedToken = "";
            i++;
            continue;
        }

        if(c == '-' && line[i+1] == '>') {
            if(generatedToken != "") tokens.push_back(generatedToken);
            tokens.push_back("->");
            generatedToken = "";
            i++;
            continue;
        }

        if(c == '(' || c == '=' || c == ',') {
            if(generatedToken != "") tokens.push_back(generatedToken);
            generatedToken = "";
            i = readParams(line, i+1, tokens);
            continue;
        }

        if(c == '/') {
            if(line[i+1] == '/') {
                if(generatedToken != "") tokens.push_back(generatedToken);
                break;
            }
        }

        generatedToken += c;
    }
    if(generatedToken != "") tokens.push_back(generatedToken);
    return tokens;
}

vector<vector<string>> Lexer::lex(string toLex) {
    vector<string> lines = getLines(toLex);
    vector<vector<string>> ret = vector<vector<string>>();
    for(auto&& line : lines) {
        vector<string> lexed = lexLine(line);
        ret.push_back(lexed);
    }
    return ret;
}
