//
// Created by Sean Mitchell on 2/12/20.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include "lexer.h"
#include "syntax.h"



using namespace std;

int main()
{
     Lexer lextest;
     Syntax syntaxtest;
     string fileName="input.txt";

     //TODO create a menu
     lextest.inputFile(fileName);
     lextest.printFile();
     syntaxtest.parse(lextest.getTokens(), lextest.getLexemes());

     return 0;
}