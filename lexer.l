%option nounput

%{

#include "parser.hpp"
#include <string>

char terminal;
int non_terminal;
int previous_non_terminal;
std::string identifier;

%}

%%

 /* Removal of characters that should not be parsed */
[ \t\n]                  { /* Spaces */ }
\/\/.*                   { /* One-line comments */ }
\/\*([^\*]|\*[^\/])*\*\/ { /* Multi-line comments */ }

 /* Key-words of the LEA language */
(I|i)(N|n)(I|i)(T|t)(I|i)(A|a)(L|l)                     return(INITIAL_KW);
(F|f)(I|i)(N|n)(A|a)(L|l)                               return(FINAL_KW);

 /* Operators and signs of the LEA language */
"|-" return(L_TRANS);
"->" return(R_TRANS);
"("  return(L_PAR);
")"  return(R_PAR);
"{"  return(L_BRACE);
"}"  return(R_BRACE);
";"  return(SEMICOLON);
"="  return(EQUAL);
"|"  return(OR);
"*"  return(STAR);
"+"  return(PLUS);

 /* Terminals (define the alphabets of the recognized languages) : lower-case letters of the latin alphabet */
[a-z]                  {terminal=*yytext;                  return(TERMINAL);   }

 /* Non terminals (define the states of the automata) : non-negative integer numbers */
[1-9][0-9]*            {previous_non_terminal=non_terminal; non_terminal=atoi(yytext); return(NONTERMINAL);   }
"0"                    {previous_non_terminal=non_terminal; non_terminal=0; return(NONTERMINAL);   }

 /* Identifiers (used as language names) : must start with an upper-case letter */
[A-Z][A-Za-z_0-9]*    {identifier=std::string(yytext); return(IDENTIFIER);}
