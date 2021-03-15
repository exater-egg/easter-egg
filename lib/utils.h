#ifndef __UTILS_H__
#define __UTILS_H__

#include "tokens.h"

enum token tok;

extern int yylex();

void error() { printf("Error!"); }
void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(enum token t) {if (tok==t) advance(); else error();}

#endif /** __UTILS_H__ **/
