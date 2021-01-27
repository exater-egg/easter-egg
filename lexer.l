%{
  #include <stdio.h>
  //#include "y.tab.h"

  //extern int yyerror(char *msg);
  // yylineno conta linhas
  // colno a gente define
  // int yylineno = 0;
  int colno = 1;
  int errono = 0;

  typedef struct{
    int col;
    int line;
    char* text;
  }PosError;

  PosError posError[200];

  
  void initPosError(PosError *posError){
    for(int i = 0; i < 200; i++){
      posError[i].col = 1;
      posError[i].line = 0;
      posError[i].text = "";
    }

    return;
  }
  void showErrors(PosError *posError){
    int i = 0;

    while(posError[i].col > 0 && posError[i].line > 0){
        printf("ERROR: Invalid Character(%s) at line %i, column %i ", posError[i].text, posError[i].line, posError[i].col);
        i++;
    } 
    
  };

%}

%%
\n                              { colno = 1; yyset_lineno(yylineno + 1); printf("\n");}
[ \t]                           {/* Ignore spaces, tabs and end of line */; colno++;}
"program"                       { printf("PROGRAM(%i,%i) ", yylineno, colno); colno = colno + yyleng;}
\;                              { printf("SEP(%i,%i) ", yylineno, colno); colno++; /* Can be SEMICOLON also*/}
\.                              { printf("DOT(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"consts"                        { printf("CONSTS(%i,%i) ", yylineno, colno); colno = colno + yyleng;}
"="                             { printf("EQ_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"+"                             { printf("PLUS_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"-"                             { printf("MINUS_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"classes"                       { printf("CLASSES(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"attributes"                    { printf("ATTRIBUTES(%i,%i)", yylineno, colno); colno = colno + yyleng; }
\,                              { printf("COMMA(%i,%i)", yylineno, colno); colno = colno + yyleng; }
\:                              { printf("COLLON(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"methods"                       { printf("METHODS(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"method"                        { printf("METHOD(%i,%i)", yylineno, colno); colno = colno + yyleng; }
\(                              { printf("OPEN_PARENT((%i,%i)", yylineno, colno); colno = colno + yyleng; }
\)                              { printf("CLOSE_PARENT)(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"vars"                          { printf("VARIABLES(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"variables"                     { printf("VARIABLES(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"begin"                         { printf("BEGIN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"end"                           { printf("END(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"if"                            { printf("IF(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"then"                          { printf("THEN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"else"                          { printf("ELSE(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"while"                         { printf("WHILE(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"do"                            { printf("DO(%i,%i)", yylineno, colno); colno = colno + yyleng; }
":="                            { printf("ASSIGN_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"and"                           { printf("AND(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"or"                            { printf("OR(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"xor"                           { printf("XOR(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"=="                            { printf("DOUB_EQ_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"!="                            { printf("NEG_EQ_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"<"                             { printf("LESS_THAN_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
">"                             { printf("MORE_THAN_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"<="                            { printf("LESS_EQ_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
">="                            { printf("MORE_EQ_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"*"                             { printf("MULTI_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"/"                             { printf("DIV_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"mod"                           { printf("MOD(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"**"                            { printf("EXP_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"true"                          { printf("BOOLEAN_LITERAL('true')(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"false"                         { printf("BOOLEAN_LITERAL('false')(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"Array"                         { printf("ARRAY_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
\[                              { printf("OPEN_BRAKET(%i,%i)", yylineno, colno); colno = colno + yyleng; }
\]                              { printf("CLOSE_BRAKET(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"++"                            { printf("DOUBLE_PLUS_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
"--"                            { printf("DOUBLE_MINUS_SIGN(%i,%i)", yylineno, colno); colno = colno + yyleng; }
[0-9]+                          { printf("INT_LITERAL(%i) (%i, %i)", atoi(yytext), yylineno, colno); colno = colno + yyleng; }
([0-9]+.[0-9]*|[0-9]*.[0-9]+)   { printf("FLOAT_LITERAL(%f) (%i, %i)", atof(yytext), yylineno, colno); colno = colno + yyleng; }
[a-zA-Z_][a-zA-Z0-9_]*          { printf("ID(%s)(%i,%i) ", yytext, yylineno, colno); colno = colno + yyleng; }
\".*\"                          { printf("STRING_LITERAL(%s) ", yytext); }
.                               { /*yyerror("Invalid Character")*/posError[errono].col = colno; posError[errono].line = yylineno; posError[errono].text = yytext; errono += 1; }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#else
int main(void)
{
  initPosError(posError);
  yylex();
  printf("\n");
  showErrors(posError);
  return 0;
}
#endif
