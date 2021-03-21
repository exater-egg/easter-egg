#include "body.h"
#include "table.h"
#include "tokens.h"
#include "rules.h"

void StmtsPart_to_stack(int col){
    switch (col)
    {
    case BEGIN_TOK:
        //StmtsPart → begin Stmts end
        stack_push(stack, END_TOK);
        stack_push(stack, Stmts);
        stack_push(stack, BEGIN_TOK);
        break;
    
    default:
        error();
        break;
    }
}
void Stmts_to_stack(int col){
    switch (col)
    {
    case ID:
    case TRY:
    case RAISE:
    case DOUBLE_MINUS_SIGN:
    case DOUBLE_PLUS_SIGN:
    case '(':
    case '-':
    case '+':
    case NOT:
    case THIS:
    case FOR:
    case RETURN:
    case WHILE:
    case IF:
    case '[':
    case FLOAT_LITERAL:
    case INT_LITERAL:
    case NULL_TOK:
    case BOOLEAN_LITERAL:
    case STRING_LITERAL:
        //Stmts → Stmt StmtsList
        stack_push(stack, StmtsList);
        stack_push(stack, Stmt);
        break;
    case END_TOK:
        break;
    
    default:
        error();
        break;
    }
}
void StmtsList_to_stack(int col){
    switch (col)
    {
    case ';':
        //StmtsList → ; Stmt StmtsList
        stack_push(stack, StmtsList);
        stack_push(stack, Stmt);
        stack_push(stack, ';');
        break;
    case END_TOK:
        break;
    
    default:
        error();
        break;
    }
}
void Stmt_to_stack(int col){
    switch (col)
    {
    case ID:
    case '(':
    case '-':
    case '+':
    case NOT:
    case THIS:
    case '[':
    case FLOAT_LITERAL:
    case INT_LITERAL:
    case NULL_TOK:
    case BOOLEAN_LITERAL:
    case STRING_LITERAL:
        //Stmt → Exp
        stack_push(stack, Exp);
        break;
    case TRY:
    case RAISE:
    //Stmt → ErrorStmt
        stack_push(stack, ErrorStmt);
        break;
    case DOUBLE_MINUS_SIGN:
    case DOUBLE_PLUS_SIGN:
        stack_push(stack, IncrStmt);
        break;
    case FOR:
        stack_push(stack, ForStmt);
        break;
    case RETURN:
        stack_push(stack, ReturnStmt);
        break;
    case WHILE:
        stack_push(stack, WhileStmt);
        break;
    case IF:
        stack_push(stack, IfStmt);
        break;
    
    default:
        error();
        break;
    }
}
void IfStmt_to_stack(int col){
    switch (col)
    {
    case IF:
        //IfStmt → if Exp then StmtsPart ElseIfStmt	
        stack_push(stack, ElseIfStmt);
        stack_push(stack, StmtsPart);
        stack_push(stack, THEN);
        stack_push(stack, Exp);
        stack_push(stack, IF);
        break;
    
    default:
        error();
        break;
    }
}
void ElseIfStmt_to_stack(int col){
    switch (col)
    {
    case ELSE:
    case ';':
    case END_TOK:
    //ElseIfStmt → ElseStmt
        stack_push(stack, ElseStmt);
        break;
    case ELSEIF:
    //ElseIfStmt → elseif StmtsPart ElseIfStmt
        stack_push(stack, ElseIfStmt);
        stack_push(stack, StmtsPart);
        stack_push(stack, ELSEIF);
        break;
    
    default:
        error();
        break;
    }
}
void ElseStmt_to_stack(int col){
    switch (col)
    {
    case ELSE:
        //ElseStmt → else StmtsPart	
        stack_push(stack, StmtsPart);
        stack_push(stack, ELSE);
        break;
    case ';':
    case END_TOK:
        break;
    
    default:
        error();
        break;
    }
}
void WhileStmt_to_stack(int col){
    switch (col)
    {
    case WHILE:
        //WhileStmt → while Exp do StmtsPart
        stack_push(stack, StmtsPart);
        stack_push(stack, DO);
        stack_push(stack, Exp);
        stack_push(stack, WHILE);
        break;
    
    default:
        error();
        break;
    }
}
void ReturnStmt_to_stack(int col){
    switch (col)
    {
    case RETURN:
    //ReturnStmt → return Exp
        stack_push(stack, Exp);
        stack_push(stack, RETURN);
        break;
    
    default:
        error();
        break;
    }
}
void ForStmt_to_stack(int col){
    switch (col)
    {
    case FOR:
    //ForStmt → for AssignStmt to Exp do StmtsPart
        stack_push(stack, StmtsPart);
        stack_push(stack, DO);
        stack_push(stack, Exp);
        stack_push(stack, TO);
        stack_push(stack, AssignStmt);
        stack_push(stack, FOR);
        break;
    
    default:
        error();
        break;
    }
}
void AssignStmt_to_stack(int col){
    switch (col)
    {
    case ID:
    case THIS:
    //AssignStmt → Ids attrSign Exp
        stack_push(stack, Exp);
        stack_push(stack, ASSIGN_SIGN);
        stack_push(stack, Ids);
        break;
    
    default:
        error();
        break;
    }
}
void IncrStmt_to_stack(int col){
    switch (col)
    {
    case DOUBLE_MINUS_SIGN:
    //IncrStmt → decSign id
        stack_push(stack, ID);
        stack_push(stack, DOUBLE_MINUS_SIGN);
        break;
    case DOUBLE_PLUS_SIGN:
    //IncrStmt → incSign id
        stack_push(stack, ID);
        stack_push(stack, DOUBLE_PLUS_SIGN);
        break;
    
    default:
        error();
        break;
    }
}
void ErrorStmt_to_stack(int col){
    switch (col)
    {
    case TRY:
    //ErrorStmt → TryBlk
        stack_push(stack, TryBlk);
        break;
    case RAISE:
    //ErrorStmt → RaiseStmt
        stack_push(stack, RaiseStmt);
        break;
    
    default:
        error();
        break;
    }
}
void RaiseStmt_to_stack(int col){
    switch (col)
    {
    case RAISE:
    //RaiseStmt → raise Exp
        stack_push(stack, Exp);
        stack_push(stack, RAISE);
        break;
    
    default:
        error();
        break;
    }
}
void TryBlk_to_stack(int col){
    switch (col)
    {
    case TRY:
    //TryBlk → try StmtsPart except ExceptBlk FinalBlk
        stack_push(stack, FinalBlk);
        stack_push(stack, ExceptBlk);
        stack_push(stack, EXCEPT);
        stack_push(stack, StmtsPart);
        stack_push(stack, TRY);
        break;
    
    default:
        error();
        break;
    }
}
void ExceptBlk_to_stack(int col){
    switch (col)
    {
    case ON:
    //ExceptBlk → on id DoStmt ExceptBlks
        stack_push(stack, ExceptBlks);
        stack_push(stack, DoStmt);
        stack_push(stack, ID);
        stack_push(stack, ON);
        break;
    
    default:
        error();
        break;
    }
}
void DoStmt_to_stack(int col){
    switch (col)
    {
    case FINALLY:
    case ON:
    case ';':
    case END_TOK:
        break;
    case DO:
    //DoStmt → do StmtsPart
        stack_push(stack, DO);
        stack_push(stack, StmtsPart);
        break;
    
    default:
        error();
        break;
    }
}
void ExceptBlks_to_stack(int col){
    switch (col)
    {
    case FINALLY:
    case END_TOK:
    case ';':
        break;
    case ON:
    //ExceptBlks → ExceptBlk
        stack_push(stack, ExceptBlk);
        break;
    
    default:
        error();
        break;
    }
}
void FinalBlk_to_stack(int col){
    switch (col)
    {
    case END_TOK:
    case ';':
        break;
    case FINALLY:
    //FinalBlk → finally StmtsPart
        stack_push(stack, StmtsPart);
        stack_push(stack, FINALLY);
        break;
    
    default:
        error();
        break;
    }
}
