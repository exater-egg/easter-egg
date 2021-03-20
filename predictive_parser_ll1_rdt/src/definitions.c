#include "definitions.h"
#include "table.h"
#include "utils.h"

void Prog_to_stack(int col)
{
    switch (col)
    {
    case IMPORT:
    case PACKAGE:
    case PROGRAM:
        //Prog -> Pack Impt program id ; ProgBody dot
        stack_push(stack, '.');
        stack_push(stack, ProgBody);
        stack_push(stack, ';');
        stack_push(stack, ID);
        stack_push(stack, PROGRAM);
        stack_push(stack, Impt);
        stack_push(stack, Pack);
        break;
    
    default:
        error();
        break;
    }
}
void Pack_to_stack(int col){
    switch (col)
    {
    case IMPORT:
    case PROGRAM:
        break;
    case PACKAGE:
        stack_push(stack, ';');
        stack_push(stack, ID);
        stack_push(stack, PACKAGE);
        break;
    
    default:
        error();
        break;
    }
}
void Impt_to_stack(int col){
    switch (col)
    {
    case IMPORT:
        stack_push(stack, Impts);
        stack_push(stack, STRING_LITERAL);
        stack_push(stack, IMPORT);
        break;
    case PROGRAM:
        break;
    
    default:
        error();
        break;
    }
}
void Impts_to_stack(int col){
    switch (col)
    {
    case ';':
        stack_push(stack, Impt);
        stack_push(stack, ';');
        break;
    case IMPORT:
        stack_push(stack, Impts);
        stack_push(stack, STRING_LITERAL);
        stack_push(stack, IMPORT);
        break;
    case PROGRAM:
        break;
    
    default:
        error();
        break;
    }
}
void ProgBody_to_stack(int col){
    switch (col)
    {
    case METHODS:
    case VARIABLES:
    case CLASSES:
    case CONSTS:
        stack_push(stack, StmtsPart);
        stack_push(stack, MethDefPart);
        stack_push(stack, VarDeclPart);
        stack_push(stack, ClassDefPart);
        stack_push(stack, ConstDefPart);
        break;
    
    default:
        error();
        break;
    }
}
void ConstDefPart_to_stack(int col){
    switch (col)
    {
    case METHODS:
    case VARIABLES:
    case CLASSES:
        break;
    case CONSTS:
//ConstDefPart → consts ConstDef
        stack_push(stack, ConstDef);
        stack_push(stack, CONSTS);
        break;
    
    default:
        error();
        break;
    }
}
void ConstDef_to_stack(int col){
    switch (col)
    {
    case ID:
//ConstDef → id eqSign Const ConstDefs
        stack_push(stack, ConstDefs);
        stack_push(stack, Const);
        stack_push(stack, '=');
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void ConstDefs_to_stack(int col){
    switch (col)
    {
    case ';':
        stack_push(stack, ConstDef);
        stack_push(stack, ';');
        break;
    case METHODS:
    case VARIABLES:
    case CLASSES:
        break;
    
    default:
        error();
        break;
    }
}
void ClassDefPart_to_stack(int col){
    switch (col)
    {
    case METHODS:
    case VARIABLES:
        break;
    case CLASSES:
        stack_push(stack, ClassDef);
        stack_push(stack, CLASSES);
        break;
    
    default:
        error();
        break;
    }
}
void ClassDef_to_stack(int col){
    switch (col)
    {
    case ID:
        stack_push(stack, ClassDefs);
        stack_push(stack, MethDeclPart);
        stack_push(stack, AttrDeclPart);
        stack_push(stack, ClassInherance);
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void ClassInherance_to_stack(int col){
    switch (col)
    {
    case METHODS:
    case ATTRIBUTES:
        break;
    case '=':
        stack_push(stack, ID);
        stack_push(stack, '=');
        break;
    
    default:
        error();
        break;
    }
}
void ClassDefs_to_stack(int col){
    switch (col)
    {
    case ID:
        stack_push(stack, ClassDef);
        break;
    case METHODS:
    case VARIABLES:
        break;
    
    default:
        error();
        break;
    }
}
void AttrDeclPart_to_stack(int col){
    switch (col)
    {
    case METHODS:
        break;
    case ATTRIBUTES:
        stack_push(stack, AttrInit);
        stack_push(stack, ATTRIBUTES);
        break;
    
    default:
        error();
        break;
    }

}
void AttrInit_to_stack(int col){
    switch (col)
    {
    case ID:
        stack_push(stack, AttrInits);
        stack_push(stack, AttrDecl);
        stack_push(stack, ':');
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void AttrInits_to_stack(int col){
    switch (col)
    {
    case ';':
        stack_push(stack, AttrInit);
        stack_push(stack, ';');
        break;
    case METHODS:
        break;
    
    default:
        error();
        break;
    }
}
void AttrDecl_to_stack(int col){
    switch (col)
    {
    case ID:
        stack_push(stack, AttrDecls);
        stack_push(stack, AttrVal);
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void AttrVal_to_stack(int col){
    switch (col)
    {
    case ';':
    case METHODS:
    case ',':
        break;
    case '=':
        stack_push(stack, Const);
        stack_push(stack, '=');
        break;
    
    default:
        error();
        break;
    }
}
void AttrDecls_to_stack(int col){
    switch (col)
    {
    case ';':
    case METHODS:
        break;
    case ',':
        stack_push(stack, AttrDecl);
        stack_push(stack, ',');
        break;
    
    default:
        error();
        break;
    }
}
void MethDeclPart_to_stack(int col){
    switch (col)
    {
    case METHODS:
        //MethDeclPart → methods MethHead
        stack_push(stack, MethHead);
        stack_push(stack, METHODS);
        break;
    
    default:
        error();
        break;
    }
}
void MethHead_to_stack(int col){
    switch (col)
    {
    case ID:
        //MethHead → id ( ParSec ) MethType MethHeads	
        stack_push(stack, MethHeads);
        stack_push(stack, MethType);
        stack_push(stack, ')');
        stack_push(stack, ParSec);
        stack_push(stack, '(');
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void MethType_to_stack(int col){
    switch (col)
    {
    case ID:
    case ';':
    case METHODS:
    case VARIABLES:
        break;
    case ':':
        stack_push(stack, ID);
        stack_push(stack, ':');
    
    default:
        error();
        break;
    }
}
void MethHeads_to_stack(int col){
    switch (col)
    {
    case ID:
    case METHODS:
    case VARIABLES:
        break;
    case ';':
//MethHeads → ; MethHead
        stack_push(stack, MethHead);
        stack_push(stack, ';');
        break;

    default:
        error();
        break;
    }
}
void ParSec_to_stack(int col){
    switch (col)
    {
    case ID:
        //ParSec → id : Param ParSecs
        stack_push(stack, ParSecs);
        stack_push(stack, Param);
        stack_push(stack, ':');
        stack_push(stack, ID);
        break;
    case ')':
        break;
    
    default:
        error();
        break;
    }
}
void Param_to_stack(int col){
    switch (col)
    {
    case ID:
        //Param → id Params
        stack_push(stack, ID);
        stack_push(stack, Params);
        break;
    
    default:
        error();
        break;
    }
}
void Params_to_stack(int col){
    switch (col)
    {
    case ')':
    case ';':
        break;
    case ',':
        //Params → comma Param
        stack_push(stack, ',');
        stack_push(stack, Param);
        break;
    
    default:
        error();
        break;
    }
}
void ParSecs_to_stack(int col){
    switch (col)
    {
    case ')':
        break;
    case ';':
    //ParSecs → ; ParSec
        stack_push(stack, ParSec);
        stack_push(stack, ';');
        break;
    
    default:
        error();
        break;
    }
}
void VarDeclPart_to_stack(int col){
    switch (col)
    {
    case BEGIN_TOK:
    case METHODS:
        break;
    case VARIABLES:
    //VarDeclPart → VarKeywd VarDef
        stack_push(stack, VarDef);
        stack_push(stack, VarKeywd);
        break;
    
    default:
        error();
        break;
    }
}
void VarKeywd_to_stack(int col){
    switch (col)
    {
    case VARIABLES:
        stack_push(stack, VARIABLES);
        break;
    
    default:
        error();
        break;
    }
}
void VarDef_to_stack(int col){
    switch (col)
    {
    case ID:
        //VarDef → id : Var VarDefs
        stack_push(stack, VarDefs);
        stack_push(stack, Var);
        stack_push(stack, ':');
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void Var_to_stack(int col){
    switch (col)
    {
    case ID:
        //Var → id VarAssign VarList
        stack_push(stack, VarList);
        stack_push(stack, VarAssign);
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void VarList_to_stack(int col){
    switch (col)
    {
    case ';':
    case BEGIN_TOK:
    case METHODS:
        break;
    case ',':
    //VarList → comma Var
        stack_push(stack, Var);
        stack_push(stack, ',');
        break;
    
    default:
        error();
        break;
    }
}
void VarAssign_to_stack(int col){
    switch (col)
    {
    case ';':
    case ',':
    case BEGIN_TOK:
    case METHODS:
        break;
    case '=':
    //VarAssign → eqSign Exp
        stack_push(stack, Exp);
        stack_push(stack, '=');
    
    default:
        error();
        break;
    }
}
void VarDefs_to_stack(int col){
    switch (col)
    {
    case ';':
        //VarDefs → ; VarDef
        stack_push(stack, VarDef);
        stack_push(stack, ';');
        break;
    case BEGIN_TOK:
    case METHODS:
        break;
    
    default:
        error();
        break;
    }
}
void MethDefPart_to_stack(int col){
    switch (col)
    {
    case METHODS:
        //MethDefPart → methods MethDef
        stack_push(stack, MethDef);
        stack_push(stack, METHODS);
        break;
    
    default:
        error();
        break;
    }
}
void MethDef_to_stack(int col){
    switch (col)
    {
    case ID:
        //MethDef → id dot id VarDeclPart StmtsPart MethDefs
        stack_push(stack, MethDefs);
        stack_push(stack, StmtsPart);
        stack_push(stack, VarDeclPart);
        stack_push(stack, ID);
        stack_push(stack, '.');
        stack_push(stack, ID);
        break;
    
    default:
        error();
        break;
    }
}
void MethDefs_to_stack(int col){
    switch (col)
    {
    case ';':
        //MethDefs → ; MethDef
        stack_push(stack, MethDef);
        stack_push(stack, ';');
        break;
    case BEGIN_TOK:
        break;
    
    default:
        error();
        break;
    }
}
