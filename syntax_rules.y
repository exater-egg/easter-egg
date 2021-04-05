%{
#include <stdio.h>

int yylex(void);
int yyerror(char *s);
extern int yylineno;
extern int colno;
extern char * yytext;
char *token_to_str(int tok);

%}

%union {
	int     intVal; 	/* integer value */
	float   floatVal; 	/* float value */
	short   boolVal;    /* boolean value */
	char *  strVal;		/* string value */
	};

%token <intVal> INT_LITERAL
%token <floatVal> FLOAT_LITERAL
%token <boolVal> BOOLEAN_LITERAL
%token <strVal> ID STRING_LITERAL 
%token PACKAGE IMPORT PROGRAM CONSTS CLASSES ATTRIBUTES METHODS VARIABLES
%token BEGIN_TOK END_TOK IF THEN ELSE ELSEIF WHILE DO FOR TO RAISE TRY EXCEPT
%token ON THIS NOT ASSIGN_SIGN AND OR XOR DOUB_EQ_SIGN NEG_EQ_SIGN LESS_EQ_SIGN
%token MORE_EQ_SIGN MOD EXP_SIGN NULL_TOK RETURN
%token DOUBLE_PLUS_SIGN DOUBLE_MINUS_SIGN FINALLY

%start Prog

%%

Prog : Pack Impt PROGRAM ID ';' ProgBody '.' { printf("Prog\n"); } ;

Pack : { printf("Pack(empty\n)"); }
	 | PACKAGE ID ';' { printf("Pack(PACKAGE)\n"); } ;

Impt : { printf("Impt(empty\n)"); }
	 | IMPORT STRING_LITERAL Impts { printf("Impt(IMPORT)\n"); } ;

Impts : { printf("Impts(empty\n)"); } 
	  | ';' Impt  { printf("Impts(;)\n"); } ;

ProgBody : ConstDefPart ClassDefPart VarDeclPart MethDefPart StmtsPart { printf("ProgBody\n"); } ;

ConstDefPart : { printf("ConstDefPart(empty\n)"); }
	| CONSTS ConstDef { printf("ConstDefPart(CONSTS)\n"); } ;

ConstDef : ID '=' Const ConstDefs { printf("ConstDef(ID)\n"); } ;

ConstDefs : { printf("ConstDefs(empty\n)"); }
	| ';' ConstDef { printf("ConstDefs(;)\n"); } ;

Const : Num { printf("Const(Num)\n"); }
	| Ids { printf("Const(Ids)\n"); }
	| STRING_LITERAL { printf("Const(STRING_LITERAL)\n"); }
	| BOOLEAN_LITERAL { printf("Const(BOOLEAN_LITERAL)\n"); }
	| SignedConst { printf("Const(SignedConst\n)"); }
	| ArrayLit { printf("Const(ArrayLit)\n"); }
	| NULL_TOK { printf("Const(NULL_TOK)\n"); } ;

SignedConst : Sign Const { printf("SignedConst\n"); } ;

Num : INT_LITERAL { printf("Num(INT_LITERA\nL)"); }
	| FLOAT_LITERAL { printf("Num(FLOAT_LITERAL\n)"); } ;

Sign : '+' { printf("Sign(+)\n"); }
	| '-' { printf("Sign(-)\n"); } ;

ArrayLit : '[' ExpList ']'  { printf("ArrayLit\n"); } ;

ExpList : { printf("ExpList(empty)\n"); }
	| Exp ExpList1 { printf("ExpList(Exp)\n"); } ;

ExpList1 : { printf("ExpList1(empty)\n"); }
	| ',' Exp ExpList1 { printf("ExpList1(,)\n"); } ;

ClassDefPart : { printf("ConstDefPart(empty)\n"); }
	| CLASSES ClassDef { printf("ConstDefPart(empty)\n"); } ;

ClassDef : ID ClassInherance AttrDeclPart MethDeclPart ClassDefs { printf("ClassDef\n"); } ;

ClassInherance : { printf("ClassInherance(empty)\n"); }
	| '=' ID { printf("ClassInherance(=)\n"); } ;

ClassDefs : { printf("ClassDefs(empty)\n"); } 
	| ClassDef { printf("ClassDefs(ClassDef)\n"); } ;

AttrDeclPart : { printf("AttrDeclPart(empty)\n"); }
	| ATTRIBUTES AttrInit { printf("AttrDeclPart(ATTRIBUTES)\n"); } ;

AttrInit : ID ':' AttrDecl AttrInits { printf("AttrInit\n"); } ;

AttrInits : { printf("AttrInits(empty)\n"); }
	| ';' AttrInit { printf("AttrInits(;)\n"); };

AttrDecl : ID AttrVal AttrDecls { printf("AttrDecl\n"); };

AttrVal : { printf("AttrVal(empty)\n"); }
	| '=' Const { printf("AttrVal(=)\n"); } ;

AttrDecls : { printf("AttrDecls(empty)\n"); }
	| ',' AttrDecl { printf("AttrDecls(,)\n"); } ;

MethDeclPart : METHODS MethHead { printf("MethDeclPart\n"); } ;

MethHead : ID '(' ParSec ')' MethType MethHeads ;

MethType : 
	| ':' ID ;

MethHeads : 
	| ';' MethHead ;

ParSec : 
	| ID ':' Param ParSecs ;

Param : ID Params ;

Params : 
	| ',' Param ;

ParSecs : 
	| ';' ParSec ;

VarDeclPart : 
	| VARIABLES VarDef ;

VarDef : ID ':' Var VarDefs ;

Var : ID VarAssign VarList ;

VarList : 
	| ',' Var ;

VarAssign : 
	| '=' Exp ;

VarDefs : 
	| ';' VarDef ;

MethDefPart : METHODS MethDef ;

MethDef : ID '.' ID VarDeclPart StmtsPart MethDefs ;

MethDefs : 
	| ';' MethDef ;

StmtsPart : BEGIN_TOK Stmts END_TOK ;

Stmts : 
	| Stmt StmtsList ;

StmtsList : 
	| ';' Stmt StmtsList ;

Stmt : IfStmt 
	| WhileStmt 
	| ForStmt 
	|  ReturnStmt 
	| Exp 
	| IncrStmt 
	| ErrorStmt ;

IfStmt : IF Exp THEN StmtsPart ElseIfStmt ;

ElseIfStmt : ElseStmt 
	| ELSEIF StmtsPart ElseIfStmt;

ElseStmt : 
	| ELSE StmtsPart ;

WhileStmt : WHILE Exp DO StmtsPart ;

ReturnStmt : RETURN Exp ;

ForStmt : FOR AssignStmt TO Exp DO StmtsPart ;

AssignStmt : Ids ASSIGN_SIGN Exp ;

Ids : ID IdList AccessIndex 
	| THIS IdList AccessIndex ;

IdList : 
	| '.' ID MethCall IdList ;

AccessIndex : 
	| ArrayLit AccessIndex ;

MethCall : 
	| '(' ExpList ')' ;

Exp : TermoLogico LogicExp ;

LogicExp : OR Exp 
	| XOR Exp 
	| ASSIGN_SIGN Exp 
	| ;

TermoLogico : FatorLogico TermoLogico1 ;

TermoLogico1 : AND TermoLogico 
	| ;

FatorLogico : RelExp 
	| NOT RelExp  ;

RelExp : ArithExp Comparacao ;

Comparacao : '<' ArithExp 
	| '>' ArithExp 
	| LESS_EQ_SIGN ArithExp 
	| MORE_EQ_SIGN ArithExp 
	| DOUB_EQ_SIGN ArithExp 
	| NEG_EQ_SIGN ArithExp 
	| ;

ArithExp : Termo ArithExp1 ;

ArithExp1 : '+' Termo ArithExp1 
	| '-' Termo ArithExp1 
	| ;

Termo : Fator Termo1 ;

Termo1 : '*' Fator Termo1 
	| '/' Fator Termo1 
	| MOD Fator Termo1 
	| ;

Fator : Const 
	| '(' ArithExp ')' ;

IncrStmt : DOUBLE_PLUS_SIGN ID 
	| DOUBLE_MINUS_SIGN ID ;

ErrorStmt : RaiseStmt 
	| TryBlk ;

RaiseStmt : RAISE Exp ;

TryBlk : TRY StmtsPart EXCEPT ExceptBlk FinalBlk;

ExceptBlk : ON ID DoStmt ExceptBlks ;

DoStmt : 
	| DO StmtsPart ;

ExceptBlks : 
	| ExceptBlk ;

FinalBlk : 
	| FINALLY StmtsPart ;

%%

int main (void) {
	return yyparse ( );
}

int yyerror (char *msg) {
	fprintf (stderr, "%d,%d: %s at '%s'\n", yylineno, colno, msg, yytext);
	return 0;
}

char *token_to_str(int tok)
{
    switch (tok)
    {
    case PACKAGE:
        return "package";
        break;
    case IMPORT:
        return "import";
        break;
    case PROGRAM:
        return "program";
        break;
    case CONSTS:
        return "conts";
        break;
    case CLASSES:
        return "classes";
        break;
    case ATTRIBUTES:
        return "attributes";
        break;
    case METHODS:
        return "methods";
        break;
    case VARIABLES:
        return "variables";
        break;
    case BEGIN_TOK:
        return "begin";
        break;
    case END_TOK:
        return "end";
        break;
    case IF:
        return "if";
        break;
    case THEN:
        return "then";
        break;
    case ELSE:
        return "else";
        break;
    case ELSEIF:
        return "elseif";
        break;
    case WHILE:
        return "while";
        break;
    case DO:
        return "do";
        break;
    case FOR:
        return "for";
        break;
    case TO:
        return "to";
        break;
    case RAISE:
        return "raise";
        break;
    case TRY:
        return "try";
        break;
    case EXCEPT:
        return "except";
        break;
    case ON:
        return "on";
        break;
    case THIS:
        return "this";
        break;
    case NOT:
        return "not";
        break;
    case ASSIGN_SIGN:
        return ":=";
        break;
    case AND:
        return "and";
        break;
    case OR:
        return "or";
        break;
    case XOR:
        return "xor";
        break;
    case DOUB_EQ_SIGN:
        return "==";
        break;
    case NEG_EQ_SIGN:
        return "!=";
        break;
    case LESS_EQ_SIGN:
        return "<=";
        break;
    case MORE_EQ_SIGN:
        return ">=";
        break;
    case MOD:
        return "%";
        break;
    case EXP_SIGN:
        return "**";
        break;
    case BOOLEAN_LITERAL:
        return "boolean value";
        break;
    case NULL_TOK:
        return "null";
        break;
    case RETURN:
        return "return";
        break;
    case DOUBLE_PLUS_SIGN:
        return "++";
        break;
    case DOUBLE_MINUS_SIGN:
        return "--";
        break;
    case INT_LITERAL:
        return "int value";
        break;
    case FLOAT_LITERAL:
        return "float";
        break;
    case ID:
        return "identifier";
        break;
    case STRING_LITERAL:
        return "string value";
        break;
    case FINALLY:
        return "finally";
        break;
    case '\0':
        return "EOF";
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
