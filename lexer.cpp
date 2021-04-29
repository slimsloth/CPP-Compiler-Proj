//
// Created by Sean Mitchell on 2/12/20.
//

#include "lexer.h"

//Hashtables for keywords
set<string> KEYWORDS = { "int", "float", "bool", "if", "else","then","endif",
"while", "whileend", "do", "doend", "for",
"forend", "input", "output","and", "or", "function" };
set<char> SEPARATORS = { '\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', ' ', '\n', '\t', '!', '\0' };
set<char> OPERATORS = { '*', '+', '-', '=', '/', '>', '<', '%' };

//FSM States
enum state { Initial, Identifier, Whole, Real, Comment, IdentifierFinal, WholeFinal, RealFinal, SeperatorFinal, OperatorFinal, Unidentified, CommentFinal };

Lexer::Lexer()
{
     currentState = 0;
     currentIndex = 0;
     currentSize = sourceCode.size();
     isComment = false;
}

//Main lexer function
void Lexer::lexerAnalyzer()
{
     string bufferString;
     string str;
     int column = 0;
     int f = 0, a = 0;
     char c;
     char followChar;


     // check for comments
     f = a = count(sourceCode.begin(), sourceCode.end(), '!');

     while (currentIndex < sourceCode.size())
     {
          c = sourceCode[currentIndex];
          if (c == '!' && a > 1)
          {
               isComment = !isComment;
               a -= 1;
          }
          else if (c == '!' && a == 1)
          {
               if (f % 2 == 0)
               {
                    currentState = Initial;
               }
               else
               {
                    currentState = SeperatorFinal;
               }
               a -= 1;
               isComment = false;
          }
          //check the following character in compound scenarios
          if (currentIndex + 1 <= sourceCode.size())
          {
               followChar = sourceCode[currentIndex + 1];
          }
          column = isInputs(c);
          if (column != -420 && !isComment && c != '!')
          {
               currentState = stateTable[currentState][column];
          }

          switch (currentState)
          {
               //Check states
          case Comment:
               bufferString.clear();
               break;

          case Identifier:
               bufferString.push_back(c);
               break;

          case Whole:
               bufferString.push_back(c);
               break;

          case Real:
               bufferString.push_back(c);
               break;
               //Final States
          case CommentFinal:
               bufferString.clear();
               currentState = Initial;
               break;

          case IdentifierFinal:
               if (isKeyword(bufferString) && !isSeperator(followChar))
               {
                    tokens.push_back("KeyWord");
                    lexemes.push_back(bufferString);
               }
               else if (isKeyword(bufferString))
               {
                    tokens.push_back("KeyWord");
                    lexemes.push_back(bufferString);
               }
               else
               {
                    tokens.push_back("Identifier");
                    lexemes.push_back(bufferString);
               }

               bufferString.clear();
               currentIndex -= 1;
               currentState = Initial;
               break;

          case WholeFinal:
               tokens.push_back("Valid Integer");
               lexemes.push_back(bufferString);
               bufferString.clear();
               currentIndex -= 1;
               currentState = Initial;
               break;

          case RealFinal:
               tokens.push_back("Valid Real");
               lexemes.push_back(bufferString);
               bufferString.clear();
               currentIndex -= 1;
               currentState = Initial;
               break;

          case SeperatorFinal:
               if (c != '\n' && !isblank(c))
               {
                    tokens.push_back("Seperators");
                    str.push_back(c);
                    lexemes.push_back(str);
               }
               str.clear();
               bufferString.clear();
               currentState = Initial;
               break;

          case OperatorFinal:
               tokens.push_back("Operators");
               str.push_back(c);
               lexemes.push_back(str);
               str.clear();
               bufferString.clear();
               currentState = Initial;
               break;

          case Unidentified:
               tokens.push_back("Undefined");
               str.append(bufferString);
               str.push_back(c);
               lexemes.push_back(str);
               bufferString.clear();
               currentState = Initial;
               break;
          }
          currentIndex += 1;
     }
}

//Outputs lexemes with tokens
void Lexer::printFile()
{
     ofstream oFile;
     oFile.open("OutputLexicalAnalysis.txt");

     oFile << endl;
     oFile << setw(5) << left << "TOKENS\t " << "\tLEXEMES" << endl;

     oFile << endl;

     for (size_t i = 0; i < tokens.size(); i++)
     {
          oFile << setw(10) << left << tokens[i] << "\t" << lexemes[i] << endl;
     }
}

//Reads a text file then parses it through lexer
bool Lexer::inputFile(string filename)
{
     ifstream inFile(filename);
     string line;
     bool fileRead = false;

     if (inFile.is_open())
     {
          while (getline(inFile, line))
          {
               line.append("\n");
               sourceCode.append(line);
          }
          fileRead = true;
          inFile.close();
     }
     else
     {
          fileRead = false;
     }
     if (fileRead)
     {
          lexerAnalyzer();
     }

     return fileRead;
}

//Check if character is a valid operator: OPERATORS = { '*', '+', '-', '=', '/', '>', '<', '%' };
bool Lexer::isOperator(char c)
{
     bool flag;

     if (OPERATORS.find(c) == OPERATORS.end())
     {
          flag = false;
     }
     else
     {
          flag = true;
     }
     return flag;
}

//Takes a character and finds the column in FSM associated with character.
int Lexer::isInputs(char c)
{
     if (toupper(c) >= 'A' && toupper(c) <= 'Z')
          return 0;
     if (c >= '0' && c <= '9')
          return 1;
     if (c == '$')
          return 2;
     if (c == '.')
          return 3;
     if (isSeperator(c))
          return 4;
     if (isOperator(c))
          return 5;
     if (c == '!')
          return 6;

     return -420;
}

//Checks if the character is a valid keyword: KEYWORDS = { "int", "float", "bool", "if", "else","then","endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or", "function" };
bool Lexer::isKeyword(string test)
{
     bool flag;

     if (KEYWORDS.find(test) == KEYWORDS.end())
     {
          flag = false;
     }
     else
     {
          flag = true;
     }
     return flag;

}

//Checks if character is a valid seprator: SEPARATORS = { '\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', ' ', '\n', '\t', '!', '\0' }; 
bool Lexer::isSeperator(char c)
{
     bool flag;

     if (SEPARATORS.find(c) == SEPARATORS.end())
     {
          flag = false;
     }
     else
     {
          flag = true;
     }
     return flag;
}
