%{
  #include <stdio.h>
  //#include "y.tab.h"

  //extern int yyerror(char *msg);
%}

%%

[ \t\n]                         {/* Ignore spaces, tabs and end of line */};
"program"                       { printf("PROGRAM "); }
\;                              { printf("SEP "); /* Can be SEMICOLON also*/}
\.                              { printf("DOT "); }
"consts"                        { printf("CONSTS "); }
"="                             { printf("EQ_SIGN "); }
"+"                             { printf("PLUS_SIGN "); }
"-"                             { printf("MINUS_SIGN "); }
"classes"                       { printf("CLASSES "); }
"attributes"                    { printf("ATTRIBUTES "); }
\,                              { printf("COMMA "); }
\:                              { printf("COLLON "); }
"methods"                       { printf("METHODS "); }
"method"                        { printf("METHOD "); }
\(                              { printf("OPEN_PARENT( "); }
\)                              { printf("CLOSE_PARENT) "); }
"vars"                          { printf("VARIABLES "); }
"variables"                     { printf("VARIABLES "); }
"begin"                         { printf("BEGIN "); }
"end"                           { printf("END "); }
"if"                            { printf("IF "); }
"then"                          { printf("THEN "); }
"else"                          { printf("ELSE "); }
"while"                         { printf("WHILE "); }
"do"                            { printf("DO "); }
":="                            { printf("ASSIGN_SIGN "); }
"and"                           { printf("AND "); }
"or"                            { printf("OR "); }
"xor"                           { printf("XOR "); }
"=="                            { printf("DOUB_EQ_SIGN "); }
"!="                            { printf("NEG_EQ_SIGN "); }
"<"                             { printf("LESS_THAN_SIGN "); }
">"                             { printf("MORE_THAN_SIGN "); }
"<="                            { printf("LESS_EQ_SIGN "); }
">="                            { printf("MORE_EQ_SIGN "); }
"*"                             { printf("MULTI_SIGN "); }
"/"                             { printf("DIV_SIGN "); }
"mod"                           { printf("MOD "); }
"**"                            { printf("EXP_SIGN "); }
"true"                          { printf("BOOLEAN_LITERAL('true') "); }
"false"                         { printf("BOOLEAN_LITERAL('false') "); }
"Array"                         { printf("ARRAY_SIGN "); }
\[                              { printf("OPEN_BRAKET "); }
\]                              { printf("CLOSE_BRAKET "); }
"++"                            { printf("DOUBLE_PLUS_SIGN "); }
"--"                            { printf("DOUBLE_MINUS_SIGN "); }
[0-9]+                          { printf("INT_LITERAL(%i) ", atoi(yytext)); }
([0-9]+.[0-9]*|[0-9]*.[0-9]+)   { printf("FLOAT_LITERAL(%f) ", atof(yytext)); }
[a-zA-Z_][a-zA-Z0-9_]*          { printf("ID(%s) ", yytext); }
\".*\"                          { printf("STRING_LITERAL(%s) ", yytext); }
.                               { /*yyerror("Invalid Character")*/ printf("ERROR: Invalid Character(%s) ", yytext); }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#else
int main(void)
{
  yylex();
  printf("\n");
  return 0;
}
#endif
