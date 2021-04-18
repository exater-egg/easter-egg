%{
#include <stdio.h>
#include <string.h>

int yylex(void);
int yyerror(char *s);
extern int yylineno;
extern int colno;
extern char * yytext;
char *token_to_str(int tok);

typedef struct nonTermStruct {
	int sym;
	void* val;
    char* c_code;
    char* id;
} nonTerm;

/**
 * TODO
 * struct TABLE
 * TABLE* create_sym_table()
 * int check_types(void* rsh, void* lsh)
 * void* get_value(symbol)
 * void* eval(expression)
 */

%}

%union {
	int     intVal; 	/* integer value */
	float   floatVal; 	/* float value */
	short   boolVal;    /* boolean value */
	char *  strVal;		/* string value */
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

//%type <nonTermVal> Prog
//%type <nonTermVal> Pack
//%type <nonTermVal> Impt
//%type <nonTermVal> Impts
//%type <nonTermVal> ProgBody
//%type <nonTermVal> ConstDefPart
//%type <nonTermVal> ConstDef
//%type <nonTermVal> ConstDefs
%type <nonTermVal> Const
%type <nonTermVal> SignedConst
%type <nonTermVal> Num
//%type <nonTermVal> Sign
//%type <nonTermVal> ArrayLit
//%type <nonTermVal> ExpList
//%type <nonTermVal> ExpList1
//%type <nonTermVal> ClassDefPart
//%type <nonTermVal> ClassDef
//%type <nonTermVal> ClassInherance
//%type <nonTermVal> ClassDefs
//%type <nonTermVal> AttrDeclPart
//%type <nonTermVal> AttrInit
//%type <nonTermVal> AttrInits
//%type <nonTermVal> AttrDecl
//%type <nonTermVal> AttrVal
//%type <nonTermVal> AttrDecls
//%type <nonTermVal> MethDeclPart
//%type <nonTermVal> MethHead
//%type <nonTermVal> MethType
//%type <nonTermVal> MethHeads
//%type <nonTermVal> ParSec
//%type <nonTermVal> Param
//%type <nonTermVal> Params
//%type <nonTermVal> ParSecs
//%type <nonTermVal> VarDeclPart
//%type <nonTermVal> VarDef
//%type <nonTermVal> Var
//%type <nonTermVal> VarList
//%type <nonTermVal> VarAssign
//%type <nonTermVal> VarDefs
//%type <nonTermVal> MethDefPart
//%type <nonTermVal> MethDef
//%type <nonTermVal> MethDefs
//%type <nonTermVal> StmtsPart
//%type <nonTermVal> Stmts
//%type <nonTermVal> StmtsList
//%type <nonTermVal> Stmt
//%type <nonTermVal> IfStmt
//%type <nonTermVal> ElseIfStmt
//%type <nonTermVal> ElseStmt
//%type <nonTermVal> WhileStmt
//%type <nonTermVal> ReturnStmt
//%type <nonTermVal> ForStmt
//%type <nonTermVal> AssignStmt
%type <nonTermVal> Ids
%type <nonTermVal> IdList
//%type <nonTermVal> AccessIndex
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
//%type <nonTermVal> ExceptBlk
//%type <nonTermVal> DoStmt
//%type <nonTermVal> ExceptBlks
//%type <nonTermVal> FinalBlk

%start Prog

%%

Prog : Pack Impt PROGRAM ID ';' ProgBody '.' { printf("Prog\n"); } ;

Pack : { printf("Pack(empty)\n"); }
	 | PACKAGE ID ';' { printf("Pack(PACKAGE)\n"); } ;

Impt : { printf("Impt(empty)\n"); }
	 | IMPORT STRING_LITERAL Impts { printf("Impt(IMPORT)\n"); } ;

Impts : { printf("Impts(empty)\n"); } 
	  | ';' Impt  { printf("Impts(;)\n"); } ;

ProgBody : ConstDefPart ClassDefPart VarDeclPart MethDefPart StmtsPart { printf("ProgBody\n"); } ;

ConstDefPart : { printf("ConstDefPart(empty)\n"); }
	| CONSTS ConstDef { printf("ConstDefPart(CONSTS)\n"); } ;

ConstDef : ID '=' Const ConstDefs { printf("ConstDef(ID)\n"); } ;

ConstDefs : { printf("ConstDefs(empty)\n"); }
	| ';' ConstDef { printf("ConstDefs(;)\n"); } ;

Const : Num { $$.val = $1.val; printf("Const(Num)\n"); }
	| Ids { $$.val = $1.val; printf("Const(Ids)\n"); }
	| STRING_LITERAL { $$.val = "String"; printf("Const(STRING_LITERAL)\n"); }
	| BOOLEAN_LITERAL { $$.val = "Boolean"; printf("Const(BOOLEAN_LITERAL)\n"); }
	| SignedConst { $$.val = $1.val; printf("Const(SignedConst)\n"); }
	| ArrayLit { $$.val = "Array"; printf("Const(ArrayLit)\n"); }
	| NULL_TOK { $$.val = "NULL"; printf("Const(NULL_TOK)\n"); } ;

SignedConst : Sign Const { $$.val = $2.val; printf("SignedConst\n"); } ;

Num : INT_LITERAL { $$.val = "Integer"; printf("Num(INT_LITERA\nL)"); }
	| FLOAT_LITERAL { $$.val = "Float"; printf("Num(FLOAT_LITERAL)\n"); } ;

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

MethHead : ID '(' ParSec ')' MethType MethHeads {} ;

MethType : {}
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

MethDefPart : | METHODS MethDef ;

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

Ids : ID IdList AccessIndex {
    $$.id = strcat($1.strVal, $2.id);
    /* Resolver accessindex antes $$.val = get_val(symtable, $$.id)[AccessIndex]; */
    /*$$.val = get_val(symtable, $$.id); TODO: Implementar o método get_val*/ }
	| THIS IdList AccessIndex {
        /*
          PROBLEMA Como resolver o this?
          SOLUÇÃO1 Usar algum método da hashtable que devolve o escopo da chamada e
                     trasnformar o this em um "escopo_this"
         */
    } ;

IdList : { $$.id = ""; /* Rever */ }
	| '.' ID MethCall IdList {
        $$.id = strcat(".", $2.id);
        /* Resolver MethCall */
        $$.id = strcat($$.id, $3.id);
    };

AccessIndex : 
	| ArrayLit AccessIndex ;

MethCall : { $$.id = ""; /* Rever */ }
	| '(' ExpList ')' {
		$$.id = "";//TODO: Verify if each Exp in ExpList match method types
		//Sugestion: handle method as if it was a attibute by its return type
		//The difference between a method and attribute is a list of param types
	};

Exp : TermoLogico LogicExp { switch($2.sym){
	case OR:
		$$.val = $1.val || $2.val;
		break;
	case XOR:	
		$$.val = $1.val * $2.val;
		break;
	case ASSIGN_SIGN:
		$$.val = ($1.val = $2.val);
		break;
	case '\0':
		$$.val = $1.val;
		break;
	default:
		break;
}} ;

LogicExp : OR Exp { $$.sym = OR ; $$.val = $2.val; printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| XOR Exp { $$.sym = XOR ;  $$.val = $2.val;}
	| ASSIGN_SIGN Exp {$$.sym = ASSIGN_SIGN; $$.val = $2.val;}
	| {$$.val = "" /*TODO: Resolver*/} ;

TermoLogico : FatorLogico TermoLogico1 { switch($2.sym){
	case AND:
		$$.val = $1.val && $2.val;
		break;
	case '\0':
		$$.val = $1.val;
		break;  
} };

TermoLogico1 : AND TermoLogico { $$.sym = AND; $$.val = $2.val; printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| {$$.val = ""/*TODO:Resolver*/};


FatorLogico : RelExp { $$.val = $1.val;}
	| NOT RelExp  {$$.sym = NOT ; $$.val = $2.val; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);};

RelExp : ArithExp Comparacao { switch($2.sym) {
    case '<':
        $$.val =  < Comparacao.val;
        break;
    case '>':
    	$$.val = ArithExp.val > Comparacao.val;
    	break;
    case LESS_EQ_SIGN:
    	$$.val = ArithExp.val <= Comparacao.val;
    	break;	
    case MORE_EQ_SIGN:
    	$$.val = ArithExp.val <= Comparacao.val;
    	break;
    case DOUB_EQ_SIGN:
    	RelExp.val = ArithExp.val == Comparacao.val;
    	break;
    case NEG_EQ_SIGNs:
    	RelExp.val = ArithExp.val != Comparacao.val;
    	break;
    default:
    	yyerror(Comparacao.sym);
    	break;
} } ;

Comparacao : '<' ArithExp { $$.sym = '<' ; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| '>' ArithExp { $$.sym = '>' ; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| LESS_EQ_SIGN ArithExp { $$.sym = LESS_EQ_SIGN ; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| MORE_EQ_SIGN ArithExp { $$.sym = MORE_EQ_SIGN ; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| DOUB_EQ_SIGN ArithExp { $$.sym = DOUB_EQ_SIGN ; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| NEG_EQ_SIGN ArithExp { $$.sym = NEG_EQ_SIGN ; $$.val = $2.val;}
	| { Comparacao.sym = '\0'; } ;

ArithExp : Termo ArithExp1  { switch($2.sym){
	case '+':
		$$.val = $1.val + $2.val;
		break;
	case '-':
		$$.val = $1.val - $2.val;
		break;
	default:
		yyerror($$.sym);
		break;
} };

ArithExp1 : '+' Termo ArithExp1 { $$.sym = '+'; $$.val = $2.val;printf("%i %i %s,%i\n", yylineno,}
	| '-' Termo ArithExp1 { $$.sym = '-'; $$.val = $2.val;colno,token_to_str($$.sym),$$.val);}
	| {$$.sym = '\0';};

Termo : Fator  Termo1 { switch($2.sym){
	case '*':
		$$.val = $1.val * $2.val;
		printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);
		break;
	case '/':
		$$.val = $1.val / $2.val;
		printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);
		break;
	case MOD:	
		$$.val = $1.val % $2.val;
		printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);
		break;
	default:
		yyerror($$.sym);
		break;
}} ;

Termo1 : '*' Fator Termo1 { $$.sym = '*';
						 $$.val = $2.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| '/' Fator Termo1 { $$.sym = '/'; 
						 $$.val = $2.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| MOD Fator Termo1 { $$.sym = MOD; 
						 $$.val = $2.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| {$$.val = "";/*TODO:Resolver*/};

Fator : Const { $$.val = $1.val;}
	| '(' ArithExp ')' { 
		$$.sym = '('; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val); 
		$$.val = $2.val ; 
		$$.sym = ')'; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);
    }
    ;

IncrStmt : DOUBLE_PLUS_SIGN ID { $$.sym = DOUBLE_PLUS_SIGN; 
								 $$.sym = ID; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);}
	| DOUBLE_MINUS_SIGN ID { $$.sym = DOUBLE_MINUS SIGN; 
							 $$.sym = ID; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);
                             }
    ;

ErrorStmt : RaiseStmt {$$.val = $1.val;}
	| TryBlk {$$.val = $1.val;}
    ;

RaiseStmt : RAISE Exp {$$.sym = RAISE; $$.val = $2.val;};

TryBlk : TRY StmtsPart EXCEPT ExceptBlk FinalBlk {
	$$.val = ""; // TODO: Retornar algo mais significante
};

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
