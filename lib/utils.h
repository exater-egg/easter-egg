#ifndef __UTILS_H__
#define __UTILS_H__

#include "tokens.h"

enum token tok;

extern int yylex();

void error();
void advance();
void eat(enum token t);

#endif /** __UTILS_H__ **/
