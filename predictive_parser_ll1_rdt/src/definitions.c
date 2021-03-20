#include "definitions.h"
#include "table.h"

void Prog_to_stack(int col)
{
    switch (col)
    {
    case IMPORT:
    case PACKAGE:
        break;
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
        stack_push(stack, ConstDefs);
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
}
void ClassDef_to_stack(int col){
}
void ClassInherance_to_stack(int col){
}
void ClassDefs_to_stack(int col){
}
void AttrDeclPart_to_stack(int col){

}
void AttrInit_to_stack(int col){

}
void AttrInits_to_stack(int col){

}
void AttrDecl_to_stack(int col){

}
void AttrVal_to_stack(int col){

}
void AttrDecls_to_stack(int col){

}
void MethDeclPart_to_stack(int col){

}
void MethHead_to_stack(int col){

}
void MethType_to_stack(int col){

}
void MethHeads_to_stack(int col){

}
void ParSec_to_stack(int col){

}
void Param_to_stack(int col){

}
void Params_to_stack(int col){

}
void ParSecs_to_stack(int col){

}
void VarDeclPart_to_stack(int col){

}
void VarKeywd_to_stack(int col){

}
void VarDef_to_stack(int col){

}
void Var_to_stack(int col){

}
void VarList_to_stack(int col){

}
void VarAssign_to_stack(int col){

}
void VarDefs_to_stack(int col){

}
void MethDefPart_to_stack(int col){

}
void MethDef_to_stack(int col){

}
void MethDefs_to_stack(int col){

}
