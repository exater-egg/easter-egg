#ifndef __UTILS_H__
#define __UTILS_H__

#include "lex.yy.h"
#include "tokens.h"
#include <stdlib.h>

enum token tok;

extern int yylex();

void error();
void advance();
void eat(enum token t);
char* token_to_str(int tok);
void error_verbose(int givenTok, int tokc, int* tokv);

#endif /** __UTILS_H__ **/
