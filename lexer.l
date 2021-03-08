%{
  #include <stdio.h>
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
"package"                       { printToken("PACKAGE"); colno = colno + yyleng; }
"import"                        { printToken("IMPORT"); colno = colno + yyleng; }
"program"                       { printToken("PROGRAM"); colno = colno + yyleng;}
\;                              { printToken("SEP"); colno++; /* Can be SEMICOLON also*/}
\.                              { printToken("DOT"); colno = colno + yyleng; }
"consts"                        { printToken("CONSTS"); colno = colno + yyleng;}
"="                             { printToken("EQ_SIGN"); colno = colno + yyleng; }
"+"                             { printToken("PLUS_SIGN"); colno = colno + yyleng; }
"-"                             { printToken("MINUS_SIGN"); colno = colno + yyleng; }
"classes"                       { printToken("CLASSES"); colno = colno + yyleng; }
"attributes"                    { printToken("ATTRIBUTES"); colno = colno + yyleng; }
\,                              { printToken("COMMA"); colno = colno + yyleng; }
\:                              { printToken("COLLON"); colno = colno + yyleng; }
"methods"                       { printToken("METHODS"); colno = colno + yyleng; }
"method"                        { printToken("METHOD"); colno = colno + yyleng; }
\(                              { printToken("OPEN_PARENT"); colno = colno + yyleng; }
\)                              { printToken("CLOSE_PARENT"); colno = colno + yyleng; }
"vars"                          { printToken("VARIABLES"); colno = colno + yyleng; }
"variables"                     { printToken("VARIABLES"); colno = colno + yyleng; }
"begin"                         { printToken("BEGIN"); colno = colno + yyleng; }
"end"                           { printToken("END"); colno = colno + yyleng; }
"if"                            { printToken("IF"); colno = colno + yyleng; }
"then"                          { printToken("THEN"); colno = colno + yyleng; }
"else"                          { printToken("ELSE"); colno = colno + yyleng; }
"elseif"                        { printToken("ELSEIF"); colno = colno + yyleng; }
"while"                         { printToken("WHILE"); colno = colno + yyleng; }
"do"                            { printToken("DO"); colno = colno + yyleng; }
"for"                           { printToken("FOR"); colno = colno + yyleng; }
"to"                            { printToken("TO"); colno = colno + yyleng; }
"raise"                         { printToken("RAISE"); colno = colno + yyleng; }
"try"                           { printToken("TRY"); colno = colno + yyleng; }
"except"                        { printToken("EXCEPT"); colno = colno + yyleng; }
"on"                            { printToken("ON"); colno = colno + yyleng; }
"this"                          { printToken("THIS"); colno = colno + yyleng; }
"not"                           { printToken("NOT"); colno = colno + yyleng; }
":="                            { printToken("ASSIGN_SIGN"); colno = colno + yyleng; }
"and"                           { printToken("AND"); colno = colno + yyleng; }
"or"                            { printToken("OR"); colno = colno + yyleng; }
"xor"                           { printToken("XOR"); colno = colno + yyleng; }
"=="                            { printToken("DOUB_EQ_SIGN"); colno = colno + yyleng; }
"!="                            { printToken("NEG_EQ_SIGN"); colno = colno + yyleng; }
"<"                             { printToken("LESS_THAN_SIGN"); colno = colno + yyleng; }
">"                             { printToken("MORE_THAN_SIGN"); colno = colno + yyleng; }
"<="                            { printToken("LESS_EQ_SIGN"); colno = colno + yyleng; }
">="                            { printToken("MORE_EQ_SIGN"); colno = colno + yyleng; }
"*"                             { printToken("MULTI_SIGN"); colno = colno + yyleng; }
"/"                             { printToken("DIV_SIGN"); colno = colno + yyleng; }
"mod"                           { printToken("MOD"); colno = colno + yyleng; }
"**"                            { printToken("EXP_SIGN"); colno = colno + yyleng; }
"true"                          { printToken("BOOLEAN_LITERAL"); colno = colno + yyleng; }
"false"                         { printToken("BOOLEAN_LITERAL"); colno = colno + yyleng; }
"null"                          { printToken("NULL"); colno = colno + yyleng; }
\[                              { printToken("OPEN_BRAKET"); colno = colno + yyleng; }
\]                              { printToken("CLOSE_BRAKET"); colno = colno + yyleng; }
"++"                            { printToken("DOUBLE_PLUS_SIGN"); colno = colno + yyleng; }
"--"                            { printToken("DOUBLE_MINUS_SIGN"); colno = colno + yyleng; }
[0-9]+                          { printToken("INT_LITERAL"); colno = colno + yyleng; }
([0-9]+\.[0-9]*|[0-9]*\.[0-9]+) { printToken("FLOAT_LITERAL"); colno = colno + yyleng; }
[a-zA-Z_][a-zA-Z0-9_]*          { printToken("ID"); colno = colno + yyleng; }
\"(\\.|[^"])*\"                 { printToken("STRING_LITERAL"); colno = colno + yyleng; }
\{(\\.|[^}])*\}                 { printToken("COMMENT"); colno = colno + yyleng; }
.                               { lexerror(yylineno, colno, yytext); errono += 1; }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#else
int main(void)
{
  printf("Linha, Coluna, tamanho, nome do token, lexema\n");
  yylex();
  return 0;
}
#endif

