#ifndef __TOKENS_H__
#define __TOKENS_H__

enum token {
    PACKAGE,
    IMPORT,
    PROGRAM,
    SEP,
    DOT,
    CONSTS,
    EQ_SIGN,
    PLUS_SIGN,
    MINUS_SIGN,
    CLASSES,
    ATTRIBUTES,
    COMMA,
    COLLON,
    METHODS,
    METHOD,
    OPEN_PARENT,
    CLOSE_PARENT,
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
    LESS_THAN_SIGN,
    MORE_THAN_SIGN,
    LESS_EQ_SIGN,
    MORE_EQ_SIGN,
    MULTI_SIGN,
    DIV_SIGN,
    MOD,
    EXP_SIGN,
    BOOLEAN_LITERAL,
    NULL_TOK,
    OPEN_BRAKET,
    CLOSE_BRAKET,
    DOUBLE_PLUS_SIGN,
    DOUBLE_MINUS_SIGN,
    INT_LITERAL,
    FLOAT_LITERAL,
    ID,
    STRING_LITERAL,
    COMMENT   
};


extern int yylex(void);

enum token tok;

void error() { printf("Error!"); }
void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(enum token t) {if (tok==t) advance(); else error();}

#endif /** __TOKENS_H__ **/

