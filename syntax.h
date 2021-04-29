//
// Created by Sean Mitchell on 4/12/20.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <stack>
#include <locale>
#include <cctype>

using namespace std;


//DEFINING SYMBOLS:
enum symbols {
     ST, AS, EX, EX_PRIME, TE, TE_PRIME, FA, // NONTERMINALS
     ID_ASS, NUM, PLUS, MINUS, MUL, DIV, LP, RP, EQU, SC_ASS, DS, // TERMINALS
     _AS, _ID_EQU_EX, _TE_EX_PRIME, _PLUS_TE_EX_PRIME, MINUS_TE_EX_PRIME, // DERIVATIONS
     _EPSILON_ASS, _FA_TE_PRIME, _MUL_FA_TE_PRIME, _DIV_FA_TE_PRIME, _ID, _NUM, _LP_EX_RP, // DERIVATIONS
     ST_DEC, DE, TY, MID, // NONTERMINALS
     SC_DEC, INT, FLOAT, BOOL, COMMA, ID, // TERMINALS
     _DE, _EPSILON_DEC, _INT, _FLOAT, _BOOL, _TY_ID_MID_SC, _COMMA_ID_MID //DERIVATIONS
};


//DECLARATION GRAMMAR PRODUCTION LIST 
//Statement -> <Declarative>
//Declarative -> <Type> ID <More Identifiers> SC | _EPSILON
//Type -> INT | FLOAT | BOOL
//More Identifiers -> COMMA ID <More Identifiers> | _EPSILON

//ASSIGNMENT GRAMMAR PRODUCTION LIST
//Statement -> Assignment
//Assignment -> ID EQU EX SC
//Expression -> TE EX_PRIME
//Expression Prime -> PLUS TE EX_PRIME | MINUS TE EX_PRIME |_EPSILON
//Term -> FA TE_PRIME
//Term Prime -> MUL FA TE_PRIME | DIV FA TE_PRIME | _EPSILON
//Factor -> LP EX RP | ID | NUM



class Syntax
{
public:
     Syntax();

     int tokenColumnsDesc(string token, string lexem);
     int tokenColumnAssign(string token, string lexem);

     bool compareTokens(int enumVal, string token, string lexem);
     bool isTerminal(int enumVal);
     bool isNonTerminal(int enumVal);
     bool match(string type, const vector<string> &tokens, const vector<string> &lexems, int currIndex); //assignment 3

     void parse(const vector<string> &tokens, const vector<string> &lexems);
     void reverseDerivation(int);
     void outputSymbolTable(ofstream &oFile); //assignment 3
     void outputFile(string fileName); //assignment 3
     void vectToAssembly(ofstream & oFile); //assignment 3

     string nonTerminals(int symbol);
     string DerivationPrintString(int symbol);
     string Terminals(int symbol);

private:

     int line;
     string outputAssembly;

     vector<string> vectAssembly;
     unordered_map< string, pair<int, string>> symbolTable;
     
     stack<int> currentStack;
     size_t currentIndex;

     // Predictive Parser Tables
     vector<vector<int>> declarativeTable   /*ST*/{ { -1, _DE, _DE, _DE, -1, -1, _EPSILON_ASS },
          /*DE*/{ _EPSILON_ASS, _TY_ID_MID_SC, _TY_ID_MID_SC, _TY_ID_MID_SC, -1, -1, _EPSILON_ASS },
          /*TY*/{ -1, _INT, _FLOAT, _BOOL, -1, -1, -1 },
          /*MID*/{ -1, -1, -1, -1, _EPSILON_ASS, _COMMA_ID_MID, -1 } };

     vector<vector<int>> assignmentTable   /*ST*/{ { _AS, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
          /*AS*/{ _ID_EQU_EX, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
          /*EX*/{ _TE_EX_PRIME, _TE_EX_PRIME, -1, -1, -1, -1, _TE_EX_PRIME, -1, -1, -1, -1 },
          /*EX_P*/{ -1, -1, _PLUS_TE_EX_PRIME, MINUS_TE_EX_PRIME, -1, -1, -1, _EPSILON_DEC, -1, _EPSILON_DEC, -1 },
          /*TE*/{ _FA_TE_PRIME, _FA_TE_PRIME, -1, -1, -1, -1, _FA_TE_PRIME, -1, -1, -1, -1 },
          /*TE_P*/{ -1, -1, _EPSILON_DEC, _EPSILON_DEC, _MUL_FA_TE_PRIME, _DIV_FA_TE_PRIME, -1, _EPSILON_DEC, -1, _EPSILON_DEC, -1 },
          /*FA*/{ _ID, _NUM, -1, -1, -1, -1, _LP_EX_RP, -1, -1, -1, -1 } };

};
