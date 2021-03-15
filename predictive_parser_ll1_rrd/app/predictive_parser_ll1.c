// rename main to parser
#define parser main
#include "lex.yy.h"
#include "syntax.h"

int parser () {
    advance();
    return 0;
}
