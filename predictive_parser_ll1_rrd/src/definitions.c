#include "definitions.h"

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

    default:
        error();
        return;
    }
}

void Pack(void)
{
    switch (tok)
    {
    case PACKAGE:
        eat(PACKAGE);
        eat(ID);
        eat(';');
        return;
    case IMPORT:
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

void Impt(void)
{
    switch (tok)
    {
    case IMPORT:
        eat(IMPORT);
        eat(STRING_LITERAL);
        Impts();
        return;
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

void Impts(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        Impt();
        return;
    case PROGRAM:
        return;

    default:
        error();
        return;
    }
}

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
    case '.':
        return;

    default:
        error();
        return;
    }
}

void ConstDefPart(void)
{
    switch (tok)
    {
    case CONSTS:
        eat(CONSTS);
        ConstDef();
        return;
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void ConstDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        ConstDef();
        return;
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case INT_LITERAL:
    case FLOAT_LITERAL:
        Num();
        return;
    case '+':
    case '-':
        SignedConst();
        return;
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void SignedConst(void)
{
    switch (tok)
    {
    case '+':
    case '-':
        Sign();
        Const();
        return;
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case ',':
    case ';':
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case ID:
    case STRING_LITERAL:
    case INT_LITERAL:
    case FLOAT_LITERAL:
        return;

    default:
        error();
        return;
    }
}

void ClassDefPart(void)
{
    switch (tok)
    {
    case CLASSES:
        eat(CLASSES);
        ClassDef();
        return;
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void ClassInherance(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        eat(ID);
        return;
    case ATTRIBUTES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void ClassDefs(void)
{
    switch (tok)
    {
    case ID:
        ClassDef();
        return;
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void AttrDeclPart(void)
{
    switch (tok)
    {
    case ATTRIBUTES:
        eat(ATTRIBUTES);
        AttrInit();
        return;
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void AttrInits(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        AttrInit();
        return;
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void AttrDecl(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        AttrVal();
        AttrDecls();
        return;
    case ';':
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void AttrVal(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        Const();
        return;
    case ',':
    case ';':
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void AttrDecls(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        AttrDecl();
        return;
    case ';':
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void MethDeclPart(void)
{
    switch (tok)
    {
    case METHODS:
        eat(METHODS);
        MethHead();
        return;
    case ID:
    case VARIABLES:
        return;

    default:
        error();
        return;
    }
}

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
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

void MethType(void)
{
    switch (tok)
    {
    case ':':
        eat(':');
        eat(ID);
        return;
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

void MethHeads(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        MethHead();
        return;
    case ID:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

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
    case ')':
        return;

    default:
        error();
        return;
    }
}

void Param(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        Params();
        return;
    case ';':
    case ')':
        return;

    default:
        error();
        return;
    }
}

void Params(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        Param();
        return;
    case ';':
    case ')':
        return;

    default:
        error();
        return;
    }
}

void ParSecs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        ParSec();
        return;
    case ')':
        return;

    default:
        error();
        return;
    }
}

void VarDeclPart(void)
{
    switch (tok)
    {
    case VARIABLES:
        eat(VARIABLES);
        VarDef();
        return;
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

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
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

void Var(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        VarAssign();
        VarList();
        return;
    case ';':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

void VarList(void)
{
    switch (tok)
    {
    case ',':
        eat(',');
        Var();
        return;
    case ';':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

void VarAssign(void)
{
    switch (tok)
    {
    case '=':
        eat('=');
        Exp();
        return;
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

void VarDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        VarDef();
        return;
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

void MethDefPart(void)
{
    switch (tok)
    {
    case METHODS:
        eat(METHODS);
        MethDef();
        return;
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

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
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

void MethDefs(void)
{
    switch (tok)
    {
    case ';':
        eat(';');
        MethDef();
        return;
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}
