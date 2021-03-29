%{
#include <stdio.h>
#include "tokens.h"

int yylex(void);
int yyerror(char *s);
extern int yylineno;
extern char * yytext;

%}

%union {
	int    iValue; 	/* integer value */
	char   cValue; 	/* char value */
	char * sValue;  /* string value */
	};

//%token <sValue> ID
//%token <iValue> NUMBER
//%token WHILE BLOCK_BEGIN BLOCK_END DO IF THEN ELSE SEMI ASSIGN

%start Prog

%type <sValue> stm

%%

Prog : Pack Impt program ID ';' ProgBody '.'
	;

Pack :  | PACKAGE ID ';' ;

Impt : | IMPORT strLit Impts ;

Impts :  | ';' Impt ;

ProgBody : ConstDefPart ClassDefPart VarDeclPart MethDefPart StmtsPart ;

ConstDefPart :  | CONSTS ConstDef ;

ConstDef : ID '=' Const ConstDefs ;

ConstDefs : | ';' ConstDef ;

Const : Num | Ids | strLit | boolLit | SignedConst | ArrayLit | null ;

SignedConst : Sign Const ;

Num : intLit | floatLit ;

Sign : plusSign | minusSign ;

ArrayLit : openBkt ExpList closeBkt ;

ExpList : | Exp ExpList' ;

ExpList' : | comma Exp ExpList' ;

ClassDefPart :  | classes ClassDef ;

ClassDef : id ClassInherance AttrDeclPart MethDeclPart ClassDefs ;

ClassInherance : | eqSign id ;

ClassDefs : | ClassDef ;

AttrDeclPart :  | attributes AttrInit ;

AttrInit : id : AttrDecl AttrInits;

AttrInits : | ';' AttrInit ;

AttrDecl : id AttrVal AttrDecls ;

AttrVal : | eqSign Const ;

AttrDecls : | comma AttrDecl ;

MethDeclPart : methods MethHead ;

MethHead : id ( ParSec ) MethType MethHeads ;

MethType : | : id ;

MethHeads : | ';' MethHead ;

ParSec : | id : Param ParSecs ;

Param : id Params ;

Params : | comma Param ;

ParSecs : | ';' ParSec ;

VarDeclPart :  | VarKeywd VarDef ;

VarKeywd : variables | var ;

VarDef : id : Var VarDefs ;

Var : id VarAssign VarList ;

VarList : | comma Var ;

VarAssign : | eqSign Exp ;

VarDefs : | ';' VarDef ;

MethDefPart : methods MethDef ;

MethDef : id dot id VarDeclPart StmtsPart MethDefs ;

MethDefs : | ';' MethDef ;

StmtsPart : begin Stmts end ;

Stmts : | Stmt StmtsList ;

StmtsList : | ';' Stmt StmtsList ;

Stmt : IfStmt | WhileStmt | ForStmt |  ReturnStmt | Exp | IncrStmt | ErrorStmt ;

IfStmt : if Exp then StmtsPart ElseIfStmt ;

ElseIfStmt : ElseStmt | elseif StmtsPart ElseIfStmt;

ElseStmt : | else StmtsPart ;

WhileStmt : while Exp do StmtsPart ;

ReturnStmt : return Exp ;

ForStmt : for AssignStmt to Exp do StmtsPart ;

AssignStmt : Ids attrSign Exp ;

Ids : id IdList AccessIndex | this IdList AccessIndex ;

IdList : | dot id MethCall IdList ;

AccessIndex : | ArrayLit AccessIndex ;

MethCall : | ( ExpList ) ;

Exp : TermoLogico LogicExp ;

LogicExp : or Exp | xor Exp | attrSign Exp | ;

TermoLogico : FatorLogico TermoLogico' ;

TermoLogico' : and TermoLogico | ;

FatorLogico : RelExp | not RelExp  ;

RelExp : ArithExp Comparacao ;

Comparacao : less ArithExp | major ArithExp | lesseq ArithExp | majoreq ArithExp | eqeq ArithExp | neq ArithExp | ;

ArithExp : Termo ArithExp' ;

ArithExp' : plusSign Termo ArithExp' | minusSign Termo ArithExp' | ;

Termo : Fator Termo' ;

Termo' : * Fator Termo' | / Fator Termo' | mod Fator Termo' | ;

Fator : Const | ( ArithExp ) ;

IncrStmt : incSign id | decSign id ;

ErrorStmt : RaiseStmt | TryBlk ;

RaiseStmt : raise Exp ;

TryBlk : try StmtsPart except ExceptBlk FinalBlk;

ExceptBlk : on id DoStmt ExceptBlks ;

DoStmt : | do StmtsPart ;

ExceptBlks : | ExceptBlk ;

FinalBlk : | finally StmtsPart ;

%%

int main (void) {
	return yyparse ( );
}

int yyerror (char *msg) {
	fprintf (stderr, "%d: %s at '%s'\n", yylineno, msg, yytext);
	return 0;
}
