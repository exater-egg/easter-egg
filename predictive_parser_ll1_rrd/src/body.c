#include "body.h"

//StmtsPart->begin Stmts end.
void StmtsPart(void)
{
    switch (tok)
    {
    case BEGIN_TOK:
        eat(BEGIN_TOK);
        Stmts();
        eat(END_TOK);
        return;
    default:
        error();
    }
}
//Stmts -> | Stmt StmtsList .
// Follow(Stmts) = [END_TOK]
void Stmts(void)
{
    switch (tok)
    {
    case IF:
    case WHILE:
    case FOR:
    case RETURN:
    case DOUBLE_PLUS_SIGN:
    case DOUBLE_MINUS_SIGN:
    case RAISE:
    case TRY:
    case NOT:
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        Stmt();
        StmtsList();
        return;
    case END_TOK:
        return;
    default:
        error();
        return;
    }
}
// StmtsList -> | ; Stmt StmtsList .
// Follow(StmtsList) = [END_TOK]
void StmtsList(void)
{
    switch (tok)
    {
    case END_TOK:
        return;
    case ';':
        eat(';');
        Stmt();
        StmtsList();
        return;
    default:
        error();
    }
}
// Stmt -> IfStmt | WhileStmt | ForStmt |  ReturnStmt | Exp | IncrStmt | ErrorStmt .
// Follow(Stmt) = [if, while, for, return, incSign, decSign, raise, try, not, (, boollit, id]
void Stmt(void)
{
    switch (tok)
    {
    case END_TOK:
    case ';':
        return;
    case IF:
        IfStmt();
        return;
    case WHILE:
        WhileStmt();
        return;
    case FOR:
        ForStmt();
        return;
    case RETURN:
        ReturnStmt();
        return;
    case DOUBLE_PLUS_SIGN:
    case DOUBLE_MINUS_SIGN:
        IncrStmt();
        return;
    case RAISE:
    case TRY:
        ErrorStmt();
    case NOT:
    case BOOLEAN_LITERAL:
    case '-':
    case '+':
    case STRING_LITERAL:
    case FLOAT_LITERAL:
    case INT_LITERAL:
    case ID:
    case THIS:
    case NULL_TOK:
    case '(':
    case '[':
        Exp();
    default:
        error();
    }
}
//IfStmt -> if Exp then StmtsPart ElseIfStmt .
void IfStmt(void)
{
    switch (tok)
    {
    case IF:
        eat(IF);
        Exp();
        eat(THEN);
        StmtsPart();
        ElseIfStmt();
        return;
    default:
        error();
    }
}
//ElseIfStmt -> ElseStmt | elseif StmtsPart ElseIfStmt.
void ElseIfStmt(void)
{
    switch (tok)
    {
    case ELSEIF:
        eat(ELSEIF);
        StmtsPart();
        ElseIfStmt();
        return;
    case ELSE:
        ElseStmt();
        return;
    case ';':
    case END_TOK:
        return;
    default:
        error();
    }
}
//ElseStmt -> | else StmtsPart .
void ElseStmt(void)
{
    switch (tok)
    {
    case ELSE:
        eat(ELSE);
        StmtsPart();
        return;
    case ';':
    case END_TOK:
    default:
        error();
    }
}
//WhileStmt -> while Exp do StmtsPart .
void WhileStmt(void)
{
    switch (tok)
    {
    case WHILE:
        eat(WHILE);
        Exp();
        eat(DO);
        StmtsPart();
        return;
    default:
        error();
    }
}
//ReturnStmt -> return Exp .
void ReturnStmt(void)
{
    switch (tok)
    {
    case RETURN:
        eat(RETURN);
        Exp();
        return;
    default:
        error();
    }
}
//ForStmt -> for AssignStmt to Exp do StmtsPart .
void ForStmt(void)
{
    switch (tok)
    {
    case FOR:
        AssignStmt();
        eat(TO);
        Exp();
        eat(DO);
        StmtsPart();
        return;
    default:
        error();
    }
}
//AssignStmt -> Ids attrSign Exp .
void AssignStmt(void)
{
    switch (tok)
    {
    case ID:
    case THIS:
        Ids();
        eat(ASSIGN_SIGN);
        Exp();
        return;
    default:
        error();
    }
}
//IncrStmt -> incSign id | decSign id .
void IncrStmt(void)
{
    switch (tok)
    {
    case DOUBLE_PLUS_SIGN:
        eat(DOUBLE_PLUS_SIGN);
        eat(ID);
        return;
    case DOUBLE_MINUS_SIGN:
        eat(DOUBLE_MINUS_SIGN);
        eat(ID);
        return;
    default:
        error();
    }
}
//ErrorStmt -> RaiseStmt | TryBlk .
void ErrorStmt(void)
{
    switch (tok)
    {
    case RAISE:
        RaiseStmt();
        return;
    case TRY:
        TryBlk();
        return;
    default:
        error();
    }
}
//RaiseStmt -> raise Exp .
void RaiseStmt(void)
{
    switch (tok)
    {
    case RAISE:
        eat(RAISE);
        Exp();
        return;
    default:
        error();
    }
}
//TryBlk -> try StmtsPart except ExceptBlk FinalBlk.
void TryBlk(void)
{
    switch (tok)
    {
    case TRY:
        eat(TRY);
        StmtsPart();
        eat(EXCEPT);
        ExceptBlk();
        FinalBlk();
        return;
    default:
        error();
    }
}
//ExceptBlk -> on id DoStmt ExceptBlks .
void ExceptBlk(void)
{
    switch (tok)
    {
    case ON:
        eat(ON);
        eat(ID);
        DoStmt();
        ExceptBlks();
        return;
    default:
        error();
    }
}
//DoStmt -> | do StmtsPart .
// follow(DoStmt) = ["on", "finally", ';', "end"]
void DoStmt(void)
{
    switch (tok)
    {
    case DO:
        StmtsPart();
        return;
    case ON:
    case FINALLY:
    case ';':
    case END_TOK:
        return;
    default:
        error();
    }
}
//ExceptBlks -> | ExceptBlk .
// follow(ExceptBlks) = ["finally", ';' "end"]
void ExceptBlks(void)
{
    switch (tok)
    {
    case ON:
        ExceptBlk();
        return;
    case FINALLY:
    case ';':
    case END_TOK:
        return;
    default:
        error();
    }
}
//FinalBlk -> | finally StmtsPart .
// follow(FinalBlk) = [';', "end"]
void FinalBlk(void)
{
    switch (tok)
    {
    case FINALLY:
        StmtsPart();
        return;
    case ';':
    case END_TOK:
        return;
    default:
        error();
    }
}
