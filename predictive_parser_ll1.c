#include "tokens.h"
#include "syntax.h"

enum token tok;

void advance() {tok=getToken();}
void eat(enum token t) {if (tok==t) advance(); else error();}

