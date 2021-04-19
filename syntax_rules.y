%{
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "symtable.h"

int yylex(void);
int yyerror(char *s);
extern int yylineno;
extern int colno;
//extern char* lookup_type(char*);
extern char * yytext;
char *token_to_str(int tok);

int tmps_int[4];
int* tmps_int_result[3];
char* tmp_type;
char* tmp_str;
typeEntry tye2;

/**
 * TODO
 * struct TABLE
 * TABLE* create_sym_table()
 * int check_types(void* rsh, void* lsh)
 * void* get_value(symbol)
 * void* eval(expression)
 */

%}

%code requires {
#include "symtable.h"

typedef struct nonTermStruct{
	int sym;
	void* val;
	char* id;
	char* type;
	short check;
} nonTerm;
typeEntry tye; 
}

%union {
    int     intVal;     /* integer value */
    float   floatVal;     /* float value */
    short   boolVal;    /* boolean value */
    char *  strVal;        /* string value */
    nonTerm nonTermVal;
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

%type <nonTermVal> Prog
%type <nonTermVal> Pack
%type <nonTermVal> Impt
%type <nonTermVal> Impts
%type <nonTermVal> ProgBody
%type <nonTermVal> ConstDefPart
%type <nonTermVal> ConstDef
%type <nonTermVal> ConstDefs
%type <nonTermVal> Const
%type <nonTermVal> SignedConst
%type <nonTermVal> Num
%type <nonTermVal> Sign
%type <nonTermVal> ArrayLit
%type <nonTermVal> ExpList
%type <nonTermVal> ExpList1
%type <nonTermVal> ClassDefPart
%type <nonTermVal> ClassDef
%type <nonTermVal> ClassInherance
%type <nonTermVal> ClassDefs
%type <nonTermVal> AttrDeclPart
%type <nonTermVal> AttrInit
%type <nonTermVal> AttrInits
%type <nonTermVal> AttrDecl
%type <nonTermVal> AttrVal
%type <nonTermVal> AttrDecls
%type <nonTermVal> MethDeclPart
%type <nonTermVal> MethHead
%type <nonTermVal> MethType
%type <nonTermVal> MethHeads
%type <nonTermVal> ParSec
%type <nonTermVal> Param
%type <nonTermVal> Params
%type <nonTermVal> ParSecs
%type <nonTermVal> VarDeclPart
%type <nonTermVal> VarDef
%type <nonTermVal> Var
%type <nonTermVal> VarList
%type <nonTermVal> VarAssign
%type <nonTermVal> VarDefs
%type <nonTermVal> MethDefPart
%type <nonTermVal> MethDef
%type <nonTermVal> MethDefs
%type <nonTermVal> StmtsPart
%type <nonTermVal> Stmts
%type <nonTermVal> StmtsList
%type <nonTermVal> Stmt
%type <nonTermVal> IfStmt
%type <nonTermVal> ElseIfStmt
%type <nonTermVal> ElseStmt
%type <nonTermVal> WhileStmt
%type <nonTermVal> ReturnStmt
%type <nonTermVal> ForStmt
%type <nonTermVal> AssignStmt
%type <nonTermVal> Ids
%type <nonTermVal> IdList
%type <nonTermVal> AccessIndex
%type <nonTermVal> MethCall
%type <nonTermVal> Exp
%type <nonTermVal> LogicExp
%type <nonTermVal> TermoLogico
%type <nonTermVal> TermoLogico1
%type <nonTermVal> FatorLogico
%type <nonTermVal> RelExp
%type <nonTermVal> Comparacao
%type <nonTermVal> ArithExp
%type <nonTermVal> ArithExp1
%type <nonTermVal> Termo
%type <nonTermVal> Termo1
%type <nonTermVal> Fator
%type <nonTermVal> IncrStmt
%type <nonTermVal> ErrorStmt
%type <nonTermVal> RaiseStmt
%type <nonTermVal> TryBlk
%type <nonTermVal> ExceptBlk
%type <nonTermVal> DoStmt
%type <nonTermVal> ExceptBlks
%type <nonTermVal> FinalBlk

%start Prog

%%

Prog : { 
	tableEntry te; te.id = strdup("Object"); te.type = strdup("Type"); te.parent = NULL;
	insert_symtable(te);
	te; te.id = strdup("Integer"); te.type = strdup("Type"); te.parent = strdup("Object");
	insert_symtable(te);
	te; te.id = strdup("Float"); te.type = strdup("Type");te.parent = strdup("Integer");
	insert_symtable(te);
	te; te.id = strdup("String"); te.type = strdup("Type");te.parent = strdup("Object");
	insert_symtable(te);
	te; te.id = strdup("Boolean"); te.type = strdup("Type");te.parent = strdup("Object");
	insert_symtable(te);
	te; te.id = strdup("Array"); te.type = strdup("Type");te.parent = strdup("Object");
	insert_symtable(te);
    }
    Pack Impt PROGRAM ID ';' ProgBody '.'  { /*printf("[%i,%i] Prog\n", yylineno, colno);*/ if ($7.check) exit(0); else exit(1);} ;

Pack : { /*printf("[%i,%i] Pack(empty)\n", yylineno, colno);*/ }
     | PACKAGE ID ';' { /*printf("[%i,%i] Pack(PACKAGE)\n", yylineno, colno);*/ } ;

Impt : { /*printf("[%i,%i] Impt(empty)\n", yylineno, colno);*/ }
     | IMPORT STRING_LITERAL Impts { /*printf("[%i,%i] Impt(IMPORT)\n", yylineno, colno);*/ } ;

Impts : { /*printf("[%i,%i] Impts(empty)\n", yylineno, colno);*/ } 
      | ';' Impt  { /*printf("[%i,%i] Impts(;)\n", yylineno, colno);*/ } ;

ProgBody : ConstDefPart ClassDefPart VarDeclPart MethDefPart StmtsPart { /*printf("[%i,%i] ProgBody\n", yylineno, colno);*/ } ;

ConstDefPart : { /*printf("[%i,%i] ConstDefPart(empty)\n", yylineno, colno);*/ }
    | CONSTS ConstDef { /*printf("[%i,%i] ConstDefPart(CONSTS)\n", yylineno, colno);*/ } ;

ConstDef : ID '=' Const ConstDefs { 
	tableEntry te; te.id = $1; te.type = $3.type;
	insert_symtable(te);
	/*printf("[%i,%i] ConstDef(ID)\n", yylineno, colno);*/ 
};

ConstDefs : { /*printf("[%i,%i] ConstDefs(empty)\n", yylineno, colno);*/ }
    | ';' ConstDef { /*printf("[%i,%i] ConstDefs(;)\n", yylineno, colno);*/ } ;

Const : Num { $$.type = strdup($1.type); /*printf("[%i,%i] Const(Num)\n", yylineno, colno);*/ }
    | Ids { 
		tmp_type = lookup_type($1.id);
		if (tmp_type == NULL){
			$$.type = "";
			yyerror("Identifier was not declared\n");}
		else 
			$$.type = strdup(tmp_type);
		/*printf("[%i,%i] Const(Ids)\n", yylineno, colno);*/ }
    | STRING_LITERAL { $$.type = strdup("String"); /*printf("[%i,%i] Const(STRING_LITERAL)\n", yylineno, colno);*/ }
    | BOOLEAN_LITERAL { $$.type = strdup("Boolean"); /*printf("[%i,%i] Const(BOOLEAN_LITERAL)\n", yylineno, colno);*/ }
    | SignedConst { $$.type = strdup($1.type); /*printf("[%i,%i] Const(SignedConst)\n", yylineno, colno);*/ }
    | ArrayLit { $$.type = strdup("Array"); /*printf("[%i,%i] Const(ArrayLit)\n", yylineno, colno);*/ }
    | NULL_TOK { $$.type = strdup("Null"); /*printf("[%i,%i] Const(NULL_TOK)\n", yylineno, colno);*/ } ;

SignedConst : Sign Const { $$.type = strdup($2.type); /*printf("[%i,%i] SignedConst\n", yylineno, colno);*/ } ;

Num : INT_LITERAL { $$.type = strdup("Integer"); /*printf("[%i,%i] Num(INT_LITERAL)\n", yylineno, colno);*/ }
    | FLOAT_LITERAL { $$.type = strdup("Float"); /*printf("[%i,%i] Num(FLOAT_LITERAL)\n", yylineno, colno);*/ } ;

Sign : '+' { /*printf("[%i,%i] Sign(+)\n", yylineno, colno);*/ }
    | '-' { /*printf("[%i,%i] Sign(-)\n", yylineno, colno);*/ } ;

ArrayLit : '[' ExpList ']'  { /*printf("[%i,%i] ArrayLit\n", yylineno, colno);*/ } ;

ExpList : { /*printf("[%i,%i] ExpList(empty)\n", yylineno, colno);*/ }
    | Exp ExpList1 { /*printf("[%i,%i] ExpList(Exp)\n", yylineno, colno);*/ } ;

ExpList1 : { /*printf("[%i,%i] ExpList1(empty)\n", yylineno, colno);*/ }
    | ',' Exp ExpList1 { /*printf("[%i,%i] ExpList1(,)\n", yylineno, colno);*/ } ;

ClassDefPart : { /*printf("[%i,%i] ConstDefPart(empty)\n", yylineno, colno);*/ }
    | CLASSES ClassDef { /*printf("[%i,%i] ConstDefPart(empty)\n", yylineno, colno);*/ } ;

ClassDef : ID ClassInherance AttrDeclPart MethDeclPart ClassDefs { 
    tableEntry te; te.id = strdup($1); te.parent = strdup($2.type);
	te.next = NULL; insert_symtable(te);
	/*printf("[%i,%i] ClassDef\n", yylineno, colno);*/ } ;

ClassInherance : { 
		$$.type = strdup("Object");
	/*printf("[%i,%i] ClassInherance(empty)\n", yylineno, colno);*/ }
    | '=' ID { 
		tmp_type = $2; 
        tmp_str = lookup_type(tmp_type);
		if (tmp_str != NULL && strcmp(tmp_str, "Type") == 0){
			$$.type = strdup($2);
		}
		else {
			printf("[%i,%i] Type \"%s\" not defined\n", yylineno, colno, tmp_type); $$.type = strdup("Object");
		}
		/*printf("[%i,%i] ClassInherance(=)\n", yylineno, colno);*/ } ;

ClassDefs : { /*printf("[%i,%i] ClassDefs(empty)\n", yylineno, colno);*/ } 
    | ClassDef { /*printf("[%i,%i] ClassDefs(ClassDef)\n", yylineno, colno);*/ } ;

AttrDeclPart : { /*printf("[%i,%i] AttrDeclPart(empty)\n", yylineno, colno);*/ }
    | ATTRIBUTES AttrInit { /*printf("[%i,%i] AttrDeclPart(ATTRIBUTES)\n", yylineno, colno);*/ } ;

AttrInit : ID ':' AttrDecl AttrInits { /*printf("[%i,%i] AttrInit\n", yylineno, colno);*/ } ;

AttrInits : { /*printf("[%i,%i] AttrInits(empty)\n", yylineno, colno);*/ }
    | ';' AttrInit { /*printf("[%i,%i] AttrInits(;)\n", yylineno, colno);*/ };

AttrDecl : ID AttrVal AttrDecls { /*printf("[%i,%i] AttrDecl\n", yylineno, colno);*/ }
         ;

AttrVal : { /*printf("[%i,%i] AttrVal(empty)\n", yylineno, colno);*/ }
    | '=' Const { /*printf("[%i,%i] AttrVal(=)\n", yylineno, colno);*/ }
    ;

AttrDecls : { /*printf("[%i,%i] AttrDecls(empty)\n", yylineno, colno);*/ }
    | ',' AttrDecl { /*printf("[%i,%i] AttrDecls(,)\n", yylineno, colno);*/ }
    ;

MethDeclPart : METHODS MethHead { /*printf("[%i,%i] MethDeclPart\n", yylineno, colno);*/ }
             ;

MethHead : ID '(' ParSec ')' MethType MethHeads { /*printf("[%i,%i] MethHead(ID)\n", yylineno, colno);*/ }
         ;

MethType : { /*printf("[%i,%i] MethType(empty)\n", yylineno, colno);*/ } 
    | ':' ID { /*printf("[%i,%i] MethType(:)\n", yylineno, colno);*/ }
    ;

MethHeads : { /*printf("[%i,%i] MethHeads(empty)\n", yylineno, colno);*/ } 
    | ';' MethHead { /*printf("[%i,%i] MethHeads(;)\n", yylineno, colno);*/ }
    ;

ParSec : { /*printf("[%i,%i] ParSec(empty)\n", yylineno, colno);*/ }
    | ID ':' Param ParSecs { /*printf("[%i,%i] ParSec(ID)\n", yylineno, colno);*/ }
    ;

Param : ID Params { /*printf("[%i,%i] Param(ID)\n", yylineno, colno);*/ }
      ;

Params : { /*printf("[%i,%i] Parms(empty)\n", yylineno, colno);*/ }
    | ',' Param { /*printf("[%i,%i] Parms(,)\n", yylineno, colno);*/ }
    ;

ParSecs : { /*printf("[%i,%i] ParSecs(empty)\n", yylineno, colno);*/ }
    | ';' ParSec { /*printf("[%i,%i] ParSec(;)\n", yylineno, colno);*/ }
    ;

VarDeclPart :  { /*printf("[%i,%i] VarDeclPart(empty)\n", yylineno, colno);*/ }
    | VARIABLES VarDef { /*printf("[%i,%i] VarDeclPart(VARIABLES)\n", yylineno, colno);*/ }
    ;

VarDef : ID {
		/*declare a temp scope*/
		tmp_type = strdup($1);
        /*Check Type*/
        tmp_str = lookup_type(tmp_type);
        if (tmp_str == NULL)
            printf("[%i,%i] Tipo \'%s\' não declarado\n", yylineno, colno, $1);
	} ':' Var VarDefs { /*printf("[%i,%i] VarDef(ID)\n", yylineno, colno);*/ }
       ;

Var : ID {
		tableEntry te; te.id = $1; te.type = tmp_type;
		insert_symtable(te);
	} VarAssign VarList { /*printf("[%i,%i] Var(ID)\n", yylineno, colno);*/ }
    ;

VarList : { /*printf("[%i,%i] VarList(empty)\n", yylineno, colno);*/ }
    | ',' Var { /*printf("[%i,%i] VarList(,)\n", yylineno, colno);*/ }
    ;

VarAssign : { /*printf("[%i,%i] VarAssign(empty)\n", yylineno, colno);*/ }
    | '=' Exp { /*printf("[%i,%i] VarAssign(=)\n", yylineno, colno);*/ };

VarDefs : { /*printf("[%i,%i] VarDefs(empty)\n", yylineno, colno);*/ }
    | ';' VarDef { /*printf("[%i,%i] VarDefs(;)\n", yylineno, colno);*/ }
    ;

MethDefPart : { /*printf("[%i,%i] MethDef(empty)\n", yylineno, colno);*/ }
    | METHODS MethDef { /*printf("[%i,%i] MethDef(METHODS)\n", yylineno, colno);*/ }
    ;

MethDef : ID '.' ID VarDeclPart StmtsPart MethDefs {} ;

MethDefs : {}
    | ';' MethDef {}
    ;

StmtsPart : BEGIN_TOK Stmts END_TOK {} ;

Stmts : {}
    | Stmt StmtsList {}
    ;

StmtsList : {}
    | ';' Stmt StmtsList {}
    ;

Stmt :  {}
    | IfStmt {}
    | WhileStmt {}
    | ForStmt {}
    | ReturnStmt {}
    | Exp {}
    | IncrStmt {}
    | ErrorStmt {}
    ;

IfStmt : IF Exp THEN StmtsPart ElseIfStmt {} ;

ElseIfStmt : ElseStmt {}
    | ELSEIF StmtsPart ElseIfStmt {}
    ;

ElseStmt : {}
    | ELSE StmtsPart {}
    ;

WhileStmt : WHILE Exp DO StmtsPart {} ;

ReturnStmt : RETURN Exp { /*printf("[%i,%i] ParSec(;)\n", yylineno, colno);*/ } ;

ForStmt : FOR AssignStmt TO Exp DO StmtsPart {} ;

AssignStmt : Ids ASSIGN_SIGN Exp {
        /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str(ASSIGN_SIGN));*/
        $$.type = strdup($3.type);
        /*printf("[%i,%i] Exp(%s)=%s\n", yylineno,colno,token_to_str(ASSIGN_SIGN),$$.type);*/
};

Ids : ID { $<strVal>$ = $1; } IdList AccessIndex {
	/*printf("[Ids]Start\n");*/
    $$.id = strcat($<strVal>$, $3.id);
    /* Resolver accessindex antes $$.val = get_val(symtable, $$.id)[AccessIndex]; */
    /*$$.type = get_type(symtable, $$.id); TODO: Implementar o método get_type*/ 
	/*printf("[Ids]End\n");*/
	}
    | THIS IdList AccessIndex {
        /*
          PROBLEMA Como resolver o this?
          SOLUÇÃO1 Usar algum método da hashtable que devolve o escopo da chamada e
                     trasnformar o this em um "escopo_this"
         */
    } ;

IdList : { $$.id = strdup(""); /* Rever */ }
    | '.' ID { $<strVal>$ = $2; } MethCall IdList {
        $$.id = strcat(".", $<strVal>$);
        /* Resolver MethCall */
        $$.id = strcat($$.id, $4.id);
    };

AccessIndex : {/*printf("[AccessIndex]Empty\n");*/}
    | ArrayLit AccessIndex {} ;

MethCall : { $$.id = ""; /* Rever */ }
    | '(' ExpList ')' {
        $$.id = "";//TODO: Verify if each Exp in ExpList match method types
        //Sugestion: handle method as if it was a attibute by its return type
        //The difference between a method and attribute is a list of param types
    };

Exp : TermoLogico LogicExp { switch($2.sym){
    case '\0':
        /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] Exp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        break;
    default:
        /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        if (strcmp($1.type,$2.type)){
			$$.type = "";
			$$.check = 0;
			yyerror("Types don't match");
		} else {
        	$$.type = strdup($1.type);
		}
        break;
}} ;

LogicExp : OR Exp {
                    $$.sym = OR ;
                    /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] LogicExp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | XOR Exp {
            $$.sym = XOR ;
            /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str($$.sym));*/
            $$.type = strdup($2.type);
            /*printf("[%i,%i] LogicExp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        }
    | ASSIGN_SIGN Exp {
            $$.sym = ASSIGN_SIGN;
            /*printf("[%i,%i] LogicExp(%s)\n", yylineno, colno, token_to_str($$.sym));*/
            $$.type = strdup($2.type);
            /*printf("[%i,%i] LogicExp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        }
    | {$$.sym = '\0';} ;

TermoLogico : FatorLogico TermoLogico1 { switch($2.sym){
    case '\0':
        /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] TermoLogico(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        break;
    default:
        /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        if (strcmp($1.type,$2.type)) {
			$$.type = "";
			$$.check = 0;
			yyerror("Types don't match\n");
		} else {
			$$.type = strdup($1.type);
		}
        break;
} };

TermoLogico1 : AND TermoLogico {
                    $$.sym = AND ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | {$$.sym = '\0';};


FatorLogico : RelExp {
        /*printf("[%i,%i] FatorLogico(%s)\n", yylineno, colno, token_to_str('\0'));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] FatorLogico(%s)=%s\n", yylineno,colno,token_to_str('\0'),$$.type);*/
    }
    | NOT RelExp  {
        /*printf("[%i,%i] FatorLogico(%s)\n", yylineno, colno, token_to_str('\0'));*/
        if (strcmp("Boolean",$2.type)){
			$$.type = "";
			$$.check = 0;
			yyerror("Types don't match");
		} else {
        	$$.type = strdup($2.type);
		}
        /*printf("[%i,%i] FatorLogico(%s)=%s\n", yylineno,colno,token_to_str('\0'),$$.type);*/
    }
    ;

RelExp : ArithExp Comparacao { switch($2.sym) {
    case '\0':
        /*printf("[%i,%i] Comparacao(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] RelExp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        break;
    default:
        /*printf("[%i,%i] RelExp(%s)\n", yylineno, colno, token_to_str($2.sym));*/
		if (strcmp($1.type,$2.type)){
			$$.check = 0; $$.type = "";
			yyerror("Types don't match");
		} else
        	$$.type = strdup($1.type);
        break;
} } ;

Comparacao : '<' ArithExp {
                    $$.sym = '<' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | '>' ArithExp {
                    $$.sym = '>' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | LESS_EQ_SIGN ArithExp {
                    $$.sym = LESS_EQ_SIGN ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | MORE_EQ_SIGN ArithExp {
                    $$.sym = MORE_EQ_SIGN ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | DOUB_EQ_SIGN ArithExp {
                    $$.sym = DOUB_EQ_SIGN ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | NEG_EQ_SIGN ArithExp {
                    $$.sym = NEG_EQ_SIGN ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | {
        $$.sym = '\0';
        /*printf("[%i,%i] Comparacao(%s)\n", yylineno, colno, token_to_str($$.sym));*/
        }
    ;

ArithExp : Termo ArithExp1  { switch($2.sym){
    case '\0':
        /*printf("[%i,%i] ArithExp1(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] ArithExp(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        break;
    default:
        /*printf("[%i,%i] ArithExp1(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        if (strcmp($1.type,$2.type)){
			$$.check = 0; $$.type = ""; yyerror("Types don't match");
		}
		else 
        	$$.type = strdup($1.type);
        break;
} };

ArithExp1 : '+' Termo ArithExp1 {
                    $$.sym = '+' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | '-' Termo ArithExp1 {
                    $$.sym = '-' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | {$$.sym = '\0';};

Termo : Fator  Termo1 { switch($2.sym){
    case '\0':
        /*printf("[%i,%i] Termo1(%s)\n", yylineno, colno, token_to_str($2.sym));*/
        $$.type = strdup($1.type);
        /*printf("[%i,%i] Termo(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
        break;
    default:
        /*printf("[%i,%i] Termo(%s)\n", yylineno, colno, token_to_str($2.sym));*/
		/*printf("Type1: %s; Type2: %s\n", $1.type, $2.type);*/
        if (strcmp($1.type,$2.type)){
			$$.check = 0; $$.type = ""; yyerror("Types don't match");
		}
		else 
        	$$.type = strdup($1.type);
        break;
}} ;

Termo1 : '*' Fator Termo1 {
                    $$.sym = '*' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | '/' Fator Termo1 {
                    $$.sym = '/' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | MOD Fator Termo1 {
                    $$.sym = MOD ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    | {$$.sym = '\0';};

Fator : Const { 
	/*printf("[%i,%i] Const()\n", yylineno, colno);*/
	$$.type = strdup($1.type);
	/*printf("[Fator]End\n");*/}
    | '(' ArithExp ')' {
                    $$.sym = '(' ;
                    /*printf("[%i,%i] TermoLogico1(%s)\n", yylineno, colno, token_to_str($$.sym));*/
                    $$.type = strdup($2.type);
                    /*printf("[%i,%i] TermoLogico1(%s)=%s\n", yylineno,colno,token_to_str($2.sym),$$.type);*/
                }
    ;

IncrStmt : DOUBLE_PLUS_SIGN ID {}
    | DOUBLE_MINUS_SIGN ID {}
    ;

ErrorStmt : RaiseStmt {}
    | TryBlk {}
    ;

RaiseStmt : RAISE Exp {}

TryBlk : TRY StmtsPart EXCEPT ExceptBlk FinalBlk {} ;

ExceptBlk : ON ID DoStmt ExceptBlks {} ;

DoStmt : {}
    | DO StmtsPart {}
    ;

ExceptBlks : {}
    | ExceptBlk {}
    ;

FinalBlk : {}
    | FINALLY StmtsPart {}
    ;

%%

int main (void) {
	init_symtable();
	init_typetable();

    return yyparse ( );
}

int yyerror (char *msg) {
    fprintf (stderr, "%d,%d: %s at '%s'\n", yylineno, colno, msg, yytext);
    return 0;
}

/*char *token_to_str(int tok)
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
}*/
