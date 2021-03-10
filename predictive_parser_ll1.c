#include "tokens.h"
#include "syntax.h"
#include "lex.yy.h"

void error() { printf("Error!"); }
void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(enum token t) {if (tok==t) advance(); else error();}

// rename main to parser
#define parser main

int parser () {
    advance();
    return 0;
}

