//
// Created by Sean Mitchell on 4/12/20.
//

#include "syntax.h"

//Default Constructor
Syntax::Syntax()
{
     currentStack.push(DS);
     currentIndex = 0;
     symbolTable.clear();
     vectAssembly.clear();
     line = 1;
}

//Converts token/lexem to assigned column for declaration grammar table.
int Syntax::tokenColumnsDesc(string token, string lexem)
{
     int column = -1;
     if (token == "Identifier")
     {
          column = 0;
     }
     else if (token == "KeyWord")
     {
          if (lexem == "int")
          {
               column = 1;
          }
          else if (lexem == "float")
          {
               column = 2;
          }
          else if (lexem == "bool")
          {
               column = 3;
          }
          else
          {
               column = -1;
          }
     }
     else if (token == "Seperators")
     {

          if (lexem[0] == ';')
          {
               column = 4;
          }
          else if (lexem[0] == ',')
          {
               column = 5;
          }
          else
          {
               column = -1;
          }
     }
     else
     {
          column = -1;
     }
     return column;
}

//Converts token/lexem to assigned column for assignment grammar table.
int Syntax::tokenColumnAssign(string token, string lexem)
{
     int column = -1;
     if (token == "Identifier")
     {
          column = 0;
     }
     else if (token == "Valid Integer" || token == "Valid Real")
     {
          column = 1;
     }
     else if (token == "Operators")
     {
          if (lexem[0] == '+')
          {
               column = 2;
          }
          else if (lexem[0] == '-')
          {
               column = 3;
          }
          else if (lexem[0] == '*')
          {
               column = 4;
          }
          else if (lexem[0] == '/')
          {
               column = 5;
          }
          else if (lexem[0] == '=')
          {
               column = 8;
          }
     }
     else if (token == "Seperators")
     {
          if (lexem[0] == '(')
          {
               column = 6;
          }
          else if (lexem[0] == ')')
          {
               column = 7;
          }
          else if (lexem[0] == ';')
          {
               column = 9;
          }
     }
     else
     {
          column = -1;
     }
     return column;
}

//Checks statement to see if all values are of same type
bool Syntax::match(string type, const vector<string> &tokens, const vector<string> &lexems, int i)
{
     bool isMismatching = false;
     while (lexems[i] != ";")
     {
          //create a vector for assembly intructions
          vectAssembly.push_back(lexems[i]);

          if (unsigned(i) == lexems.size() - 1) return true;

          if (tokens[i] == "Identifier")
          {
               if (symbolTable.find(lexems[i]) != symbolTable.end())
               {
                    if (symbolTable[lexems[i]].second != type)
                    {
                         isMismatching = true;
                         vectAssembly.clear();
                         break;
                    }
               }
          }
          else if (tokens[i] == "Valid Integer" && type != "int")
          {
               isMismatching = true;
               vectAssembly.clear();
               break;
          }
          else if (tokens[i] == "Valid Real" && type != "float")
          {
               isMismatching = true;
               vectAssembly.clear();
               break;
          }
          i++;
     }
     //add the semicolon
     if (!isMismatching) 
          vectAssembly.push_back(lexems[i]);

     return isMismatching;
}

//Compares top stack value to current input: True if equal, false otherwise.
bool Syntax::compareTokens(int enumVal, string token, string lexem)
{
     bool is_equal = false;

     switch (enumVal)
     {
     case ID:
          is_equal = (token == "Identifier");
          break;

     case INT:
          is_equal = (token == "KeyWord" && lexem == "int");
          break;

     case FLOAT:
          is_equal = (token == "KeyWord" && lexem == "float");
          break;

     case BOOL:
          is_equal = (token == "KeyWord" && lexem == "bool");
          break;

     case COMMA:
          is_equal = (token == "Seperators" && lexem[0] == ',');
          break;

     case SC_ASS:
          is_equal = (token == "Seperators" && lexem[0] == ';');
          break;

     case SC_DEC:
          is_equal = (token == "Seperators" && lexem[0] == ';');
          break;

     case NUM:
          is_equal = (token == "Valid Integer" || token == "Valid Real");
          break;

     case PLUS:
          is_equal = (token == "Operators" && lexem[0] == '+');
          break;

     case MINUS:
          is_equal = (token == "Operators" && lexem[0] == '-');
          break;

     case MUL:
          is_equal = (token == "Operators" && lexem[0] == '*');
          break;

     case DIV:
          is_equal = (token == "Operators" && lexem[0] == '/');
          break;

     case EQU:
          is_equal = (token == "Operators" && lexem[0] == '=');
          break;

     case LP:
          is_equal = (token == "Seperators" && lexem[0] == '(');
          break;

     case RP:
          is_equal = (token == "Seperators" && lexem[0] == ')');
          break;

     default:
          is_equal = false;
          break;
     }
     return is_equal;
}

//Checks if enum value is a non terminal
bool Syntax::isNonTerminal(int enumVal)
{
     bool is_Non_Terminal = false;
     switch (enumVal)
     {
     case ST:
          is_Non_Terminal = true;
          break;

     case DE:
          is_Non_Terminal = true;
          break;

     case TY:
          is_Non_Terminal = true;
          break;

     case MID:
          is_Non_Terminal = true;
          break;

          is_Non_Terminal = false;
          break;

     case AS:
          is_Non_Terminal = true;
          break;

     case EX:
          is_Non_Terminal = true;
          break;

     case EX_PRIME:
          is_Non_Terminal = true;
          break;

     case TE:
          is_Non_Terminal = true;
          break;

     case TE_PRIME:
          is_Non_Terminal = true;
          break;

     case FA:
          is_Non_Terminal = true;
          break;

     }
     return is_Non_Terminal;
}

//Checks if enum value is a terminal
bool Syntax::isTerminal(int enumVal)
{
     bool is_Terminal = false;
     switch (enumVal)
     {
     case ID:
          is_Terminal = true;
          break;

     case INT:
          is_Terminal = true;
          break;

     case FLOAT:
          is_Terminal = true;
          break;

     case BOOL:
          is_Terminal = true;
          break;

     case SC_ASS:
          is_Terminal = true;
          break;

     case SC_DEC:
          is_Terminal = true;
          break;

     case COMMA:
          is_Terminal = true;
          break;

     case NUM:
          is_Terminal = true;
          break;

     case PLUS:
          is_Terminal = true;
          break;

     case MINUS:
          is_Terminal = true;
          break;

     case MUL:
          is_Terminal = true;
          break;

     case DIV:
          is_Terminal = true;
          break;

     case LP:
          is_Terminal = true;
          break;

     case RP:
          is_Terminal = true;
          break;

     case EQU:
          is_Terminal = true;
          break;

     case DS:
          is_Terminal = true;
          break;

     default:
          is_Terminal = false;
          break;

     }
     return is_Terminal;
}

//uses predictive parser table to check if code has correct syntax.
void Syntax::parse(const vector<string> &tokens, const vector<string> &lexems)
{

     int memoryAddresses = 2000;
     int deriv = -1;
     int col = -1;
     int currentTop = -1;
     
     bool matchFlag = false;
     bool printFlag = true;
     bool assignmentFlag = false;
     bool STflag = true;
     bool typeFlag = false;
     bool declarativeFlag = false;

     string type = "";
     string currentType = "";
     string assemblyFileName = "OutputAssembly.txt";
     string tableChoice = "";

     ofstream syntaxOut;
     ofstream symbolOut;
     ofstream assemblyOut;
  
     assemblyOut.open("OutputAssembly.txt");
     syntaxOut.open("OutputSyntaxAnalysis.txt");
     symbolOut.open("OutputSymbolTable.txt");

     currentStack.push(ST);
     while (!currentStack.empty())
     {

          currentTop = currentStack.top();
          // if top = $: end
          if (currentTop == DS && currentIndex > tokens.size() - 1)
          {
               syntaxOut << "Finish." << endl;
               currentStack.pop();
               continue;
          }
          //Error handle: if no $ at end
          else if (currentIndex >= tokens.size() && currentTop != DS)
          {
               syntaxOut << "ERROR: Entire file has been read, stack is NOT empty." << endl;
               syntaxOut.close();
               return;
          }
          // Check current token and display
          if (printFlag && currentIndex < tokens.size())
          {
               syntaxOut << "Token: \t " << tokens[currentIndex] << " Lexeme: \t" << lexems[currentIndex] << endl;
               printFlag = false;
          }
          // Pick the table
          if (tokens[currentIndex] == "KeyWord" && STflag)
          {
               tableChoice = "Declarative";
               STflag = false;
          }
          else if (tokens[currentIndex] == "Identifier" && STflag)
          {
               tableChoice = "Assignment";
               STflag = false;
          }

          //**Assignment 3: create symbol table/assembly code**

          if (compareTokens(currentTop, tokens[currentIndex], lexems[currentIndex]))
          {
               // Check for declarations
               if (tableChoice == "Assignment" && tokens[currentIndex] == "Identifier" && assignmentFlag)
               {
                    if (symbolTable.find(lexems[currentIndex]) == symbolTable.end())
                    {
                         symbolOut << "The " << tokens[currentIndex] << " \"" << lexems[currentIndex] << "\" is being used without declaration. \n" << endl;
                         symbolOut << "Either declare \'" << lexems[currentIndex] << "\" or remove it " << endl;
                    }
               }//check for any mismatches
               else if (tableChoice == "Assignment" && matchFlag)
               {
                    //Check if token exists in declaration table
                    if (symbolTable.find(lexems[currentIndex - 1]) != symbolTable.end())
                    {
                         currentType = symbolTable[lexems[currentIndex - 1]].second;
                         if (!match(currentType, tokens, lexems, currentIndex - 1))
                         {
                              matchFlag = false;
                              vectToAssembly(assemblyOut);
                         }
                         else return;
                    }
               }
               // Assign if int float or bool
               if (tableChoice == "Declarative" && tokens[currentIndex] == "KeyWord" && (lexems[currentIndex] == "int" || lexems[currentIndex] == "float" || lexems[currentIndex] == "bool") && typeFlag)
                    type = lexems[currentIndex];

               //Insert the identifier into the memory address
               if (tableChoice == "Declarative" && tokens[currentIndex] == "Identifier" && declarativeFlag)
               {
                    if (symbolTable.find(lexems[currentIndex]) == symbolTable.end())
                    {
                         symbolTable.insert(make_pair(lexems[currentIndex], make_pair(memoryAddresses, type)));
                         memoryAddresses += 1;
                    }
                    else
                    {
                         symbolOut << "The " << tokens[currentIndex] << " \"" << lexems[currentIndex] << "\" has already been declared." << endl;
                         return;
                    }
               }

               //pop stack if not empty
               if (!currentStack.empty()) 
                    currentStack.pop();

               if (lexems[currentIndex][0] == ';' && currentIndex != tokens.size() - 1)
               {
                    currentStack.push(ST);
                    STflag = true;
                    declarativeFlag = false;
                    matchFlag = false;

               }
               printFlag = true;
               currentIndex++;
          }
          else
          {
               //If stack top is not equal, and terminal, error
               if (isTerminal(currentTop))
               {
                    syntaxOut << "Error with terminal: " << Terminals(currentTop) << endl;
                    syntaxOut.close();
                    return;
               }
               else if (isNonTerminal(currentTop))
               {
                    if (nonTerminals(currentTop) != "")
                    {
                         syntaxOut << nonTerminals(currentTop);
                    }
                    if (tableChoice == "Declarative")
                    {
                         col = tokenColumnsDesc(tokens[currentIndex], lexems[currentIndex]);
                    }
                    else if (tableChoice == "Assignment")
                    {
                         col = tokenColumnAssign(tokens[currentIndex], lexems[currentIndex]);
                    }
                    if (col != -1)
                    {
                         if (tableChoice == "Declarative")
                         {
                              if (currentTop == DE) declarativeFlag = true;
                              if (currentTop == TY) typeFlag = true;
                              if (currentTop != 0)
                              {
                                   currentTop -= 30;
                              }
                              deriv = declarativeTable[currentTop][col];
                         }
                         else if (tableChoice == "Assignment")
                         {
                              if (currentTop == AS) matchFlag = true;
                              if (currentTop == AS) assignmentFlag = true;
                              deriv = assignmentTable[currentTop][col];;
                         }
                         if (deriv != -1)
                         {
                              if (!currentStack.empty()) currentStack.pop();
                              syntaxOut << DerivationPrintString(deriv);
                              reverseDerivation(deriv);
                         }
                         else
                         {
                              syntaxOut << "Derivation DNE! \n";
                              syntaxOut.close();
                              return;
                         }
                    }
                    else
                    {
                         syntaxOut << "\nError with Token: " << tokens[currentIndex] << "\t Lexeme: " << lexems[currentIndex] << endl;
                         syntaxOut.close();
                         return;
                    }

               }
          }

     }
     if (currentIndex != tokens.size())
     {
          syntaxOut << "Error, the stack is empty but the entire file has not been read" << endl;
          syntaxOut.close();
          return;
     }
     outputSymbolTable(symbolOut);
     symbolOut.close();
}

//converts assignment statement in vector into assembly instructions then outputs.
void Syntax::vectToAssembly(ofstream &table_oFile)
{
     stack<string> stack;
     int valCount = 0;

     if (vectAssembly.empty()) 
          return;

     if (vectAssembly[1] != "=" || vectAssembly.size() < 4)
     {
          vectAssembly.clear();
          return;
     }
     else
     {
          for (size_t i = 1; i < vectAssembly.size(); i++)
          {
               if (vectAssembly[i] == ")")
               {
                    if (!stack.empty())
                    {
                         table_oFile << line++ << "\t" << stack.top() << "\t" << endl;
                         stack.pop();
                    }

               }

               if (symbolTable.find(vectAssembly[i]) != symbolTable.end())
               {
                    table_oFile << line++ << "\t" << "PUSHM" << "\t" << symbolTable[vectAssembly[i]].first << endl;
                    valCount++;
               }
               else if (isdigit(vectAssembly[i][0]))
               {
                    table_oFile << line++ << "\t" << "PUSHI" << "\t" << vectAssembly[i] << endl;
                    valCount++;
               }
               if ((valCount % 2 == 0 && valCount > 1) || (valCount % 2 != 0 && valCount >= 3) || vectAssembly[i] == "(")
               {
                    if (vectAssembly[i - 1] == "+")
                    {
                         if (vectAssembly[i] == "(")
                              stack.push("ADD");
                         else
                              table_oFile << line++ << "\t" << "ADD \t" << endl;
                    }
                    else if (vectAssembly[i - 1] == "-")
                    {
                         if (vectAssembly[i] == "(")
                              stack.push("SUB");
                         else
                              table_oFile << line++ << "\t" << "SUB \t" << endl;
                    }
                    else if (vectAssembly[i - 1] == "*")
                    {
                         if (vectAssembly[i] == "(")
                              stack.push("MUL");
                         else
                              table_oFile << line++ << "\t" << "MUL \t" << endl;
                    }
                    else if (vectAssembly[i - 1] == "/")
                    {
                         if (vectAssembly[i] == "(")
                              stack.push("DIV");
                         else
                              table_oFile << line++ << "\t" << "DIV \t" << endl;
                    }
               }
          }

     }
     table_oFile << line++ << "\t" << "POPM" << "\t" << symbolTable[vectAssembly[0]].first << endl;

     vectAssembly.clear();

}

//Outputs the symbol table.
void Syntax::outputSymbolTable(ofstream &table_oFile)
{
     table_oFile << "\nSymbol Table" << endl;
     for (auto &iter : symbolTable)
     {
          table_oFile << iter.first << "\t" << iter.second.first << "\t" << iter.second.second << endl;
     }
     table_oFile.close();
}

//converts input to proper column for grammar table.
void Syntax::reverseDerivation(int der)
{
     switch (der)
     {
     case _DE:
          currentStack.push(DE);
          break;

     case _INT:
          currentStack.push(INT);
          break;

     case _FLOAT:
          currentStack.push(FLOAT);
          break;

     case _BOOL:
          currentStack.push(BOOL);
          break;

     case _TY_ID_MID_SC:
          currentStack.push(SC_DEC);
          currentStack.push(MID);
          currentStack.push(ID);
          currentStack.push(TY);
          break;

     case _COMMA_ID_MID:
          currentStack.push(MID);
          currentStack.push(ID);
          currentStack.push(COMMA);
          break;

     case _AS:
          currentStack.push(AS);
          break;

     case _ID_EQU_EX:
          currentStack.push(SC_ASS);
          currentStack.push(EX);
          currentStack.push(EQU);
          currentStack.push(ID);
          break;

     case _TE_EX_PRIME:
          currentStack.push(EX_PRIME);
          currentStack.push(TE);
          break;

     case _PLUS_TE_EX_PRIME:
          currentStack.push(EX_PRIME);
          currentStack.push(TE);
          currentStack.push(PLUS);
          break;

     case MINUS_TE_EX_PRIME:
          currentStack.push(EX_PRIME);
          currentStack.push(TE);
          currentStack.push(MINUS);
          break;

     case _FA_TE_PRIME:
          currentStack.push(TE_PRIME);
          currentStack.push(FA);
          break;

     case _MUL_FA_TE_PRIME:
          currentStack.push(TE_PRIME);
          currentStack.push(FA);
          currentStack.push(MUL);
          break;

     case _DIV_FA_TE_PRIME:
          currentStack.push(TE_PRIME);
          currentStack.push(FA);
          currentStack.push(DIV);
          break;

     case _ID:
          currentStack.push(ID);
          break;

     case _NUM:
          currentStack.push(NUM);
          break;

     case _LP_EX_RP:
          currentStack.push(RP);
          currentStack.push(EX);
          currentStack.push(LP);
          break;
     }
}

//Converts enum to string. Requires input of a symbol enum value
string Syntax::nonTerminals(int symbol)
{
     string retString = "";
     switch (symbol)
     {
     case ST:
          retString = "<Statement> -> ";
          break;

     case DE:
          retString = "<Declaration> -> ";
          break;

     case TY:
          retString = "<Type> -> ";
          break;

     case MID:
          retString = "<MoreIdentifiers> -> ";
          break;

     case AS:
          retString = "<Assignment> -> ";
          break;

     case EX:
          retString = "<Expression> -> ";
          break;

     case EX_PRIME:
          retString = "<Expression Prime> -> ";
          break;

     case TE:
          retString = "<Term> -> ";
          break;

     case TE_PRIME:
          retString = "<Term Prime> -> ";
          break;

     case FA:
          retString = "<Factor> -> ";
          break;

     default:
          retString = "";
          break;
     }
     return retString;
}

//Converts enum to string. Requires input of a symbol enum value. Uses right side prod rule
string Syntax::DerivationPrintString(int symbol)
{
     string retString = "";
     switch (symbol)
     {
     case _DE:
          retString = "<Declaration>\n";
          break;

     case _TY_ID_MID_SC:
          retString = "<Type> ID <MID> SC\n";
          break;

     case _INT:
          retString = "INT\n";
          break;

     case _FLOAT:
          retString = "FLOAT\n";
          break;

     case _BOOL:
          retString = "BOOL\n";
          break;

     case _COMMA_ID_MID:
          retString = "COMMA ID <MID>\n";
          break;

     case _EPSILON_ASS:
          retString = "epsilon\n";
          break;

     case _EPSILON_DEC:
          retString = "epsilon\n";
          break;

     case _AS:
          retString = "<Assignment>\n";
          break;

     case _ID_EQU_EX:
          retString = "<Identifier> = <Expression>\n";
          break;

     case _TE_EX_PRIME:
          retString = "<Term> <Expression Prime>\n";
          break;

     case _PLUS_TE_EX_PRIME:
          retString = "+ <Term> <Expression Prime>\n";
          break;

     case MINUS_TE_EX_PRIME:
          retString = "- <Term> <Expression Prime>\n";
          break;

     case _FA_TE_PRIME:
          retString = "<Factor> <Term Prime>\n";
          break;

     case _MUL_FA_TE_PRIME:
          retString = "* <Factor> <Term Prime>\n";
          break;

     case _DIV_FA_TE_PRIME:
          retString = "/ <Factor> <Term Prime>\n";
          break;

     case _ID:
          retString = "<Identifier> \n";
          break;

     case _NUM:
          retString = "<Number>\n";
          break;

     case _LP_EX_RP:
          retString = "(<Expression>)\n";
          break;

     default:
          retString = "";
          break;
     }
     return retString;
}

//Converts enum to string. Requires input of a symbol enum value.
string Syntax::Terminals(int symbol)
{
     string retString = "";
     switch (symbol)
     {
     case ID:
          retString = "Identifier";
          break;

     case INT:
          retString = "int";
          break;

     case FLOAT:
          retString = "float";
          break;

     case BOOL:
          retString = "bool";
          break;

     case SC_ASS:
          retString = ";";
          break;

     case SC_DEC:
          retString = ";";
          break;

     case COMMA:
          retString = ",";
          break;

     case NUM:
          retString = "Valid Integer";
          break;

     case PLUS:
          retString = "+";
          break;

     case MINUS:
          retString = "-";
          break;

     case MUL:
          retString = "*";
          break;

     case DIV:
          retString = "/";
          break;

     case LP:
          retString = "(";
          break;

     case RP:
          retString = ")";
          break;

     case EQU:
          retString = "=";
          break;

     case DS:
          retString = "$";
          break;

     default:
          retString = "";
          break;
     }
     return retString;
}
