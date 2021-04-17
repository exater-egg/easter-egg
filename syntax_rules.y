%{
#include <stdio.h>

int yylex(void);
int yyerror(char *s);
extern int yylineno;
extern int colno;
extern char * yytext;
char *token_to_str(int tok);

typedef struct nonTermStruct {
	enum token sym;
	void* val;
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

%type <nonTerm> Prog  Pack Impt Impts ProgBody ConstDefPart ConstDef ConstDefs
%type <nonTerm> Const SignedConst Num Sign ArrayLit ExpList ExpList1
%type <nonTerm> ClassDefPart ClassDef ClassInherance ClassDefs AttrDeclPart
%type <nonTerm> AttrInit AttrInits AttrDecl AttrVal AttrDecls MethDeclPart
%type <nonTerm> MethHead MethType MethHeads ParSec Param Params ParSecs
%type <nonTerm> VarDeclPart VarDef Var VarList VarAssign VarDefs MethDefPart
%type <nonTerm> MethDef MethDefs StmtsPart Stmts StmtsList Stmt IfStmt
%type <nonTerm> ElseIfStmt ElseStmt WhileStmt ReturnStmt ForStmt AssignStmt Ids
%type <nonTerm> IdList AccessIndex MethCall Exp LogicExp TermoLogico
%type <nonTerm> TermoLogico1 FatorLogico RelExp Comparacao ArithExp ArithExp1
%type <nonTerm> Termo Termo1 Fator IncrStmt ErrorStmt RaiseStmt TryBlk
%type <nonTerm> ExceptBlk DoStmt ExceptBlks FinalBlk

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

Const : Num { printf("Const(Num)\n"); }
	| Ids { printf("Const(Ids)\n"); }
	| STRING_LITERAL { printf("Const(STRING_LITERAL)\n"); }
	| BOOLEAN_LITERAL { printf("Const(BOOLEAN_LITERAL)\n"); }
	| SignedConst { printf("Const(SignedConst)\n"); }
	| ArrayLit { printf("Const(ArrayLit)\n"); }
	| NULL_TOK { printf("Const(NULL_TOK)\n"); } ;

SignedConst : Sign Const { printf("SignedConst\n"); } ;

Num : INT_LITERAL { printf("Num(INT_LITERA\nL)"); }
	| FLOAT_LITERAL { printf("Num(FLOAT_LITERAL)\n"); } ;

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

Ids : ID IdList AccessIndex 
	| THIS IdList AccessIndex ;

IdList : 
	| '.' ID MethCall IdList ;

AccessIndex : 
	| ArrayLit AccessIndex ;

MethCall : 
	| '(' ExpList ')' ;

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
		$$.val =$1.val;
		break;
	default:
		break;
}} ;

LogicExp : OR Exp { $$.sym = OR ; $$.val = $1.val; printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| XOR Exp { $$.sym = XOR ;  $$.val = $1.val;}
	| ASSIGN_SIGN Exp {$$.sym = ASSIGN_SIGN; $$.val = $1.val;}
	| ;

TermoLogico : FatorLogico TermoLogico1 { switch($2.sym){
	case AND:
		$$.val = $1.val && $2.val;
		break;
	case '\0':
		$$.val = $1.val;
		break;  
} };

TermoLogico1 : AND TermoLogico { $$.sym = AND; $$.val = $1.val; printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| ;


FatorLogico : RelExp { $$.val = $1.val;}
	| NOT RelExp  {$$.sym = NOT ; $$.val = $1.val; printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);};

}

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

Comparacao : '<' ArithExp { $$.sym = '<' ; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| '>' ArithExp { $$.sym = '>' ; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| LESS_EQ_SIGN ArithExp { $$.sym = LESS_EQ_SIGN ; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| MORE_EQ_SIGN ArithExp { $$.sym = MORE_EQ_SIGN ; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| DOUB_EQ_SIGN ArithExp { $$.sym = DOUB_EQ_SIGN ; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,
colno,token_to_str($$.sym),$$.val);}
	| NEG_EQ_SIGN ArithExp { $$.sym = NEG_EQ_SIGN ; $$.val = $1;}
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

ArithExp1 : '+' Termo ArithExp1 { $$.sym = '+'; $$.val = $1.val;printf("%i %i %s,%i\n", yylineno,}
	| '-' Termo ArithExp1 { $$.sym = '-'; $$.val = $1.val;colno,token_to_str($$.sym),$$.val);}
	| {$$.sym = '\0';};

Termo : Fator  Termo1 ;{ swith($2.sym){
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
}}

Termo1 : '*' Fator Termo1 { $$.sym = '*';
						 $$.val = $1.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| '/' Fator Termo1 { $$.sym = '/'; 
						 $$.val = $1.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| MOD Fator Termo1 { $$.sym = MOD; 
						 $$.val = $1.val;printf("%i %i %s,%i\n", yylineno, colno,token_to_str($$.sym),$$.val);}
	| ;

Fator : Const { $$.val = $1.val;}
	| '(' ArithExp ')' ;{ $$.sym = '('; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val); 
						$$.val = $1.val ; 
						$$.sym = ')'; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);}
}

IncrStmt : DOUBLE_PLUS_SIGN ID { $$.sym = DOUBLE_PLUS_SIGN; 
								 $$.sym = ID; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);}
	| DOUBLE_MINUS_SIGN ID { $$.sym = DOUBLE_MINUS SIGN; 
							 $$.sym = ID; printf("%i %i %s,%i\n", yylineno,colno,token_to_str($$.sym),$$.val);};
}

ErrorStmt : RaiseStmt {$$.val = $1.val;}
	| TryBlk {$$.val = $1.val;};
}

RaiseStmt : RAISE Exp {$$.sym = RAISE; $$.val = $1.val;};

TryBlk : TRY StmtsPart EXCEPT ExceptBlk FinalBlk ;

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
