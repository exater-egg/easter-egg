#include "utils.h"

void error() { printf("Error!"); }
void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(enum token t) {if (tok==t) advance(); else error();}
