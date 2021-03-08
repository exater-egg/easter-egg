%{
  #include <stdio.h>
  #include "tokens.h"

  int colno = 1;
  int errono = 0;

  typedef struct{
    int col;
    int line;
    char* text;
  } PosError;

  PosError posError[200];

  int lexerror(int line, int col, char *text){
    posError[errono].col = colno;
    posError[errono].line = yylineno;
    posError[errono].text = yytext;
    fprintf(stderr, "ERROR: Invalid Character(%s) at line %i, column %i\n", text, line, col);
  }

  void printToken(char* token) {
    printf("%i, %i, %i, %s, \"%s\"\n", yylineno, colno, yyleng, token, yytext);
  }

%}

%option yylineno

%%
\n                              { colno = 1; /* printf("\n");*/ }
[ \t]                           {/* Ignore spaces, tabs and end of line */; colno++;}
"package"                       { colno = colno + yyleng; return PACKAGE; }
"import"                        { colno = colno + yyleng; return IMPORT; }
"program"                       { colno = colno + yyleng; return PROGRAM; }
\;                              { colno = colno + yyleng; return SEP; }
\.                              { colno = colno + yyleng; return DOT; }
"consts"                        { colno = colno + yyleng; return CONSTS; }
"="                             { colno = colno + yyleng; return EQ_SIGN; }
"+"                             { colno = colno + yyleng; return PLUS_SIGN; }
"-"                             { colno = colno + yyleng; return MINUS_SIGN; }
"classes"                       { colno = colno + yyleng; return CLASSES; }
"attributes"                    { colno = colno + yyleng; return ATTRIBUTES; }
\,                              { colno = colno + yyleng; return COMMA; }
\:                              { colno = colno + yyleng; return COLLON; }
"methods"                       { colno = colno + yyleng; return METHODS; }
"method"                        { colno = colno + yyleng; return METHOD; }
\(                              { colno = colno + yyleng; return OPEN_PARENT; }
\)                              { colno = colno + yyleng; return CLOSE_PARENT; }
"vars"                          { colno = colno + yyleng; return VARIABLES; }
"variables"                     { colno = colno + yyleng; return VARIABLES; }
"begin"                         { colno = colno + yyleng; return BEGIN_TOK; }
"end"                           { colno = colno + yyleng; return END_TOK; }
"if"                            { colno = colno + yyleng; return IF; }
"then"                          { colno = colno + yyleng; return THEN; }
"else"                          { colno = colno + yyleng; return ELSE; }
"elseif"                        { colno = colno + yyleng; return ELSEIF; }
"while"                         { colno = colno + yyleng; return WHILE; }
"do"                            { colno = colno + yyleng; return DO; }
"for"                           { colno = colno + yyleng; return FOR; }
"to"                            { colno = colno + yyleng; return TO; }
"raise"                         { colno = colno + yyleng; return RAISE; }
"try"                           { colno = colno + yyleng; return TRY; }
"except"                        { colno = colno + yyleng; return EXCEPT; }
"on"                            { colno = colno + yyleng; return ON; }
"this"                          { colno = colno + yyleng; return THIS; }
"not"                           { colno = colno + yyleng; return NOT; }
":="                            { colno = colno + yyleng; return ASSIGN_SIGN; }
"and"                           { colno = colno + yyleng; return AND; }
"or"                            { colno = colno + yyleng; return OR; }
"xor"                           { colno = colno + yyleng; return XOR; }
"=="                            { colno = colno + yyleng; return DOUB_EQ_SIGN; }
"!="                            { colno = colno + yyleng; return NEG_EQ_SIGN; }
"<"                             { colno = colno + yyleng; return LESS_THAN_SIGN; }
">"                             { colno = colno + yyleng; return MORE_THAN_SIGN; }
"<="                            { colno = colno + yyleng; return LESS_EQ_SIGN; }
">="                            { colno = colno + yyleng; return MORE_EQ_SIGN; }
"*"                             { colno = colno + yyleng; return MULTI_SIGN; }
"/"                             { colno = colno + yyleng; return DIV_SIGN; }
"mod"                           { colno = colno + yyleng; return MOD; }
"**"                            { colno = colno + yyleng; return EXP_SIGN; }
"true"                          { colno = colno + yyleng; return BOOLEAN_LITERAL; }
"false"                         { colno = colno + yyleng; return BOOLEAN_LITERAL; }
"null"                          { colno = colno + yyleng; return NULL_TOK; }
\[                              { colno = colno + yyleng; return OPEN_BRAKET; }
\]                              { colno = colno + yyleng; return CLOSE_BRAKET; }
"++"                            { colno = colno + yyleng; return DOUBLE_PLUS_SIGN; }
"--"                            { colno = colno + yyleng; return DOUBLE_MINUS_SIGN; }
[0-9]+                          { colno = colno + yyleng; return INT_LITERAL; }
([0-9]+\.[0-9]*|[0-9]*\.[0-9]+) { colno = colno + yyleng; return FLOAT_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]*          { colno = colno + yyleng; return ID; }
\"(\\.|[^"])*\"                 { colno = colno + yyleng; return STRING_LITERAL; }
\{(\\.|[^}])*\}                 { colno = colno + yyleng; return COMMENT; }
.                               { lexerror(yylineno, colno, yytext); errono += 1; }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#elif parser

#else
int main(void)
{
  printf("Linha, Coluna, tamanho, nome do token, lexema\n");
  yylex();
  return 0;
}
#endif

