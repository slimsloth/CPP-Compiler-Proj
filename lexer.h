//
// Created by Sean Mitchell on 2/12/20.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Lexer
{

public:
     Lexer();

     void printFile();

     bool inputFile(string fileName);
     
     vector<string> getLexemes() { return lexemes; }
     vector<string> getTokens() { return tokens; }
     
private:

     int currentState;
     int isInputs(char c);

     bool isKeyword(string test);
     bool isOperator(char c);
     bool isComment;
     bool isSeperator(char c);

     void lexerAnalyzer();

     string sourceCode;

     size_t currentSize;
     size_t currentIndex;

     vector<string> tokens;
     vector<string> lexemes;

     vector<vector<int>> stateTable = { { 1,  2, 10, 8, 8, 9, 4 },
                                        { 1,  1, 1, 10, 5, 10, 10 },
                                        { 10, 2, 10, 3, 6, 10, 10 },
                                        { 10, 3, 10, 10, 7, 10, 10 },
                                        { 4,  4, 4, 4, 4, 4, 4, 11 } };
};


