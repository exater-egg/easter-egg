#include "tokens.h"
#include "syntax.h"
#include "lex.yy.h"

// rename main to parser
#define parser main

int parser () {
    advance();
    return 0;
}

