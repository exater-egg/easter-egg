#include "definitions.h"

// Prog → Pack Impt program id ; ProgBody dot .
void Prog(void)
{
    switch (tok)
    {
    case PACKAGE:
    case IMPORT:
    case PROGRAM:
        Pack();
        Impt();
        eat(PROGRAM);
        eat(ID);
        eat(';');
        ProgBody();
        eat('.');
        return;

        // no follows

    default:
        error();
        return;
    }
}

// Pack → | package id ; .
void Pack(void)
{
    switch (tok)
    {
    case PACKAGE:
        eat(PACKAGE);
        eat(ID);
        eat(';');
        return;

    // follows - nullable
    case IMPORT:
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

// Impt → | import strLit Impts .
void Impt(void)
{
    switch (tok)
    {
    case IMPORT:
        eat(IMPORT);
        eat(STRING_LITERAL);
        Impts();
        return;

    // follows - nullable
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

// Impts → | ; Impt .
void Impts(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        Impt();
        return;

    // follows - nullable
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

// ProgBody → ConstDefPart ClassDefPart VarDeclPart MethDefPart StmtsPart .
void ProgBody(void)
{
    switch (tok)
    {
    case CONSTS:
    case CLASSES:
    case METHODS:
    case VARIABLES:
        ConstDefPart();
        ClassDefPart();
        VarDeclPart();
        MethDefPart();
        StmtsPart();
        return;

    // follows - non-nullable
    case '.':
        error();
        return;

    default:
        error();
        return;
    }
}

// ConstDefPart → | consts ConstDef .
void ConstDefPart(void)
{
    switch (tok)
    {
    case CONSTS:
        eat(CONSTS);
        ConstDef();
        return;

    // follows - nullable
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// ConstDef → id eqSign Const ConstDefs .
void ConstDef(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat('=');
        Const();
        ConstDefs();
        return;

    // follows - non-nullable
    case CLASSES:
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// ConstDefs → | ; ConstDef .
void ConstDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        ConstDef();
        return;

    // follows - nullable
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// Const -> Num | id | strLit | SignedConst | ArrayLit | null .
void Const(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        return;
    case STRING_LITERAL:
        eat(STRING_LITERAL);
        return;
    case NULL_TOK:
        eat(NULL_TOK);
        return;
    case INT_LITERAL:
    case FLOAT_LITERAL:
        Num();
        return;
    case '+':
    case '-':
        SignedConst();
        return;
    case '[':
        ArrayLit();
        return;

    // TODO follows - non-nullable
    // 	* / mod plus minus less major lesseq majoreq eqeq ! ) and or xor to then do end ; comma begin classes variables var methods
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// SignedConst → Sign Const .
void SignedConst(void)
{
    switch (tok)
    {
    case '+':
    case '-':
        Sign();
        Const();
        return;

    // follows - non-nullable
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

//Num → intLit | floatLit .
void Num(void)
{
    switch (tok)
    {
    case INT_LITERAL:
        eat(INT_LITERAL);
        return;
    case FLOAT_LITERAL:
        eat(FLOAT_LITERAL);
        return;

    // follows - non-nullable
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// Sign → plusSign | minusSign .
void Sign(void)
{
    switch (tok)
    {
    case '+':
        eat('+');
        return;
    case '-':
        eat('-');
        return;

    // follows - nullable
    case ID:
    case STRING_LITERAL:
    case INT_LITERAL:
    case FLOAT_LITERAL:
        error();
        return;

    default:
        error();
        return;
    }
}

// ClassDefPart → | classes ClassDef .
void ClassDefPart(void)
{
    switch (tok)
    {
    case CLASSES:
        eat(CLASSES);
        ClassDef();
        return;

    // follows - nullable
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// ClassDef → id ClassInherance AttrDeclPart MethDeclPart ClassDefs .
void ClassDef(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        ClassInherance();
        AttrDeclPart();
        MethDeclPart();
        ClassDefs();
        return;

    // follows - non-nullable
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// ClassInherance → | eqSign id .
void ClassInherance(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        eat(ID);
        return;

    // follows - nullable
    case ATTRIBUTES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// ClassDefs → | ClassDef .
void ClassDefs(void)
{
    switch (tok)
    {
    case ID:
        ClassDef();
        return;

    // follows - nullable
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// AttrDeclPart → | attributes AttrInit .
void AttrDeclPart(void)
{
    switch (tok)
    {
    case ATTRIBUTES:
        eat(ATTRIBUTES);
        AttrInit();
        return;

    // follows - nullable
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// AttrInit → id : AttrDecl AttrInits.
void AttrInit(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat(':');
        AttrDecl();
        AttrInits();
        return;

    // follows - non-nullable
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// AttrInits → | ; AttrInit .
void AttrInits(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        AttrInit();
        return;

    // follows - nullable
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// AttrDecl → id AttrVal AttrDecls .
void AttrDecl(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        AttrVal();
        AttrDecls();
        return;

    // follows - non-nullable
    case ';':
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// AttrVal → | eqSign Const .
void AttrVal(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        Const();
        return;

    // follows - nullable
    case ',':
    case ';':
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// AttrDecls → | comma AttrDecl .
void AttrDecls(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        AttrDecl();
        return;

    // follows - nullable
    case ';':
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// MethDeclPart → methods MethHead .
void MethDeclPart(void)
{
    switch (tok)
    {
    case METHODS:
        eat(METHODS);
        MethHead();
        return;

    // follows - non-nullable
    case ID:
    case VARIABLES:
        error();
        return;

    default:
        error();
        return;
    }
}

// MethHead → id ( ParSec ) MethType MethHeads .
void MethHead(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat('(');
        ParSec();
        eat(')');
        MethType();
        MethHeads();
        return;

    // follows - non-nullable
    case VARIABLES:
    case METHODS:
        error();
        return;

    default:
        error();
        return;
    }
}

// MethType → | : id .
void MethType(void)
{
    switch (tok)
    {
    case ':':
        eat(':');
        eat(ID);
        return;

    // follows - nullable
    case ';':
    case ID:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// MethHeads → | ; MethHead .
void MethHeads(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        MethHead();
        return;

    // follows - nullable
    case ID:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// ParSec → | id : Param ParSecs .
void ParSec(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat(':');
        Param();
        ParSecs();
        return;

    // follows - nullable
    case ')':
        return;

    default:
        error();
        return;
    }
}

// Param → id Params .
void Param(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        Params();
        return;

    // follows - non-nullable
    case ';':
    case ')':
        error();
        return;

    default:
        error();
        return;
    }
}

// Params → | comma Param .
void Params(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        Param();
        return;

    // follows - nullable
    case ';':
    case ')':
        return;

    default:
        error();
        return;
    }
}

// ParSecs → | ; ParSec .
void ParSecs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        ParSec();
        return;

    // follows - nullable
    case ')':
        return;

    default:
        error();
        return;
    }
}

// VarDeclPart → | VarKeywd VarDef .
void VarDeclPart(void)
{
    switch (tok)
    {
    case VARIABLES:
        eat(VARIABLES);
        VarDef();
        return;

    // follows - nullable
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// VarDef → id : Var VarDefs .
void VarDef(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat(':');
        Var();
        VarDefs();
        return;

    // follows - non-nullable
    case METHODS:
    case BEGIN_TOK:
        error();
        return;

    default:
        error();
        return;
    }
}

// Var → id VarAssign VarList .
void Var(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        VarAssign();
        VarList();
        return;

    // follows - non-nullable
    case ';':
    case METHODS:
    case BEGIN_TOK:
        error();
        return;

    default:
        error();
        return;
    }
}

// VarList → | comma Var .
void VarList(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        Var();
        return;

    // follows - nullable
    case ';':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// VarAssign → | eqSign Exp .
void VarAssign(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        Exp();
        return;

    // follows - nullable
    case ',':
    case ';':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// VarDefs → | ; VarDef .
void VarDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        VarDef();
        return;

    // follows - nullable
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// MethDefPart → methods MethDef .
void MethDefPart(void)
{
    switch (tok)
    {
    case METHODS:
        eat(METHODS);
        MethDef();
        return;

    // follows - non-nullable
    case BEGIN_TOK:
        error();
        return;

    default:
        error();
        return;
    }
}

// MethDef → id dot id VarDeclPart StmtsPart MethDefs .
void MethDef(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat('.');
        eat(ID);
        VarDeclPart();
        StmtsPart();
        MethDefs();
        return;

    // follows - non-nullable
    case BEGIN_TOK:
        error();
        return;

    default:
        error();
        return;
    }
}

// MethDefs → | ; MethDef .
void MethDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        MethDef();
        return;

    // follows - nullable
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}
