#include "tokens.h"
#include "syntax.h"
#include "lex.yy.h"

int tok;

void error() { printf("Error!"); }
void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(int t) {if (tok==t) advance(); else error();}

#define parser main

int parser () {
    advance();
    return 0;
}

