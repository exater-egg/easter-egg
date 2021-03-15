#include "utils.h"
#include "lex.yy.h"
#include "tokens.h"

extern int colno;

void advance() {tok=yylex(); printf("Token %i found\n", tok); }
void eat(enum token t) {if (tok==t) advance(); else error();}
void error() { 
    printf("Error!");
    printf("Line %d\n", yylineno);
    printf("Column %d\n", colno);
}
char* token_to_str(int tok){
    switch (tok)
    {
    case PACKAGE:
		return "package";break;
    case IMPORT:
		return "import";break;
    case PROGRAM:
		return "program";break;
    case CONSTS:
		return "conts";break;
    case CLASSES:
		return "classes";break;
    case ATTRIBUTES:
		return "attributes";break;
    case METHODS:
		return "methods";break;
    case VARIABLES:
		return "variables";break;
    case BEGIN_TOK:
		return "begin";break;
    case END_TOK:
		return "end";break;
    case IF:
		return "if";break;
    case THEN:
		return "then";break;
    case ELSE:
		return "else";break;
    case ELSEIF:
		return "elseif";break;
    case WHILE:
		return "while";break;
    case DO:
		return "do";break;
    case FOR:
		return "for";break;
    case TO:
		return "to";break;
    case RAISE:
		return "raise";break;
    case TRY:
		return "try";break;
    case EXCEPT:
		return "except";break;
    case ON:
		return "on";break;
    case THIS:
		return "this";break;
    case NOT:
		return "not";break;
    case ASSIGN_SIGN:
		return ":=";break;
    case AND:
		return "and";break;
    case OR:
		return "or";break;
    case XOR:
		return "xor";break;
    case DOUB_EQ_SIGN:
		return "==";break;
    case NEG_EQ_SIGN:
		return "!=";break;
    case LESS_EQ_SIGN:
		return "<=";break;
    case MORE_EQ_SIGN:
		return ">=";break;
    case MOD:
		return "%";break;
    case EXP_SIGN:
		return "**";break;
    case BOOLEAN_LITERAL:
		return "boolean value";break;
    case NULL_TOK:
		return "null";break;
    case RETURN:
		return "return";break;
    case DOUBLE_PLUS_SIGN:
		return "++";break;
    case DOUBLE_MINUS_SIGN:
		return "--";break;
    case INT_LITERAL:
		return "int value";break;
    case FLOAT_LITERAL:
		return "float";break;
    case ID:
		return "identifier";break;
    case STRING_LITERAL:
		return "string value";break;
    case FINALLY:
        return "finally";break;
    default:
    {
        // Return the string with the char atual value (e.g. char 'c' -> char* "c")
        char *pChar = malloc(sizeof(char));
        *pChar = tok;
        return pChar;
        break;
    }
    }
}

/**
 * Error handling showing expected tokens
 * @param tokc  The number of expected tokens options (i.e. expected "if" or "for" or "while" -> tokc=3)
 * @param tokv  The vector of expected tokens options as enums (i.e. tokv={IF, FOR, WHILE})
 */
void error_verbose(int givenTok, int tokc, int* tokv) { 
    printf("Error!");
    printf("Line %d\n", yylineno);
    if (tokc < 1)
        return;
    printf("Expected: \"%s\"", token_to_str(tokv[0]));
    for (size_t i = 1; i < tokc; i++)
    {
        printf(" or \"%s\"", token_to_str(tokv[i]));
    }
    printf(".\nGiven: \"%s\"\n", token_to_str(givenTok));
}
