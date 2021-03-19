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
        printf("[ERROR] Prog\n");
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
        printf("[ERROR] Pack\n");
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
        printf("[ERROR] Impt\n");
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
        printf("[ERROR] Impts\n");
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
        printf("[ERROR] ProgBody\n");
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
        printf("[ERROR] ConstDefPart\n");
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
        printf("[ERROR] ConstDef\n");
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
        printf("[ERROR] ConstDefs\n");
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
        printf("[ERROR] ClassDefPart\n");
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
        printf("[ERROR] ClassDef\n");
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
        printf("[ERROR] ClassInheritance\n");
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
        printf("[ERROR] ClassDefs\n");
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
        printf("[ERROR] AttrDeclPart\n");
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
        printf("[ERROR] AttrInit\n");
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
        printf("[ERROR] AttrInits\n");
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
        printf("[ERROR] AttrDecl\n");
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
        printf("[ERROR] AttrVal\n");
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
        printf("[ERROR] AttrDecls\n");
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
        printf("[ERROR] MethDeclPart\n");
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
        printf("[ERROR] MethHead\n");
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
        printf("[ERROR] MethType\n");
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
        printf("[ERROR] MethHeads\n");
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
        printf("[ERROR] ParSec\n");
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
        printf("[ERROR] Param\n");
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
        printf("[ERROR] Params\n");
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
        printf("[ERROR] ParSecs\n");
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
        printf("[ERROR] VarDeclPart\n");
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
        printf("[ERROR] VarDef\n");
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
        printf("[ERROR] Var\n");
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
        printf("[ERROR] VarList\n");
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
        printf("[ERROR] VarAssign\n");
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
        printf("[ERROR] VarDefs\n");
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
        printf("[ERROR] MethDefPart\n");
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
        printf("[ERROR] MethDef\n");
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
        printf("[ERROR] MethDefs\n");
        error();
        return;
    }
}
