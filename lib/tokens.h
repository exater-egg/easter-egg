#ifndef __TOKENS_H__
#define __TOKENS_H__

#include <stdio.h>

enum token {
    PACKAGE = 177,
    IMPORT,
    PROGRAM,
    CONSTS,
    CLASSES,
    ATTRIBUTES,
    METHODS,
    VARIABLES,
    BEGIN_TOK,
    END_TOK,
    IF,
    THEN,
    ELSE,
    ELSEIF,
    WHILE,
    DO,
    FOR,
    TO,
    RAISE,
    TRY,
    EXCEPT,
    ON,
    THIS,
    NOT,
    ASSIGN_SIGN,
    AND,
    OR,
    XOR,
    DOUB_EQ_SIGN,
    NEG_EQ_SIGN,
    LESS_EQ_SIGN,
    MORE_EQ_SIGN,
    MOD,
    EXP_SIGN,
    BOOLEAN_LITERAL,
    NULL_TOK,
    RETURN,
    DOUBLE_PLUS_SIGN,
    DOUBLE_MINUS_SIGN,
    INT_LITERAL,
    FLOAT_LITERAL,
    ID,
    STRING_LITERAL,
    FINALLY
};

#endif /** __TOKENS_H__ **/
