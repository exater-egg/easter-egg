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
        break;
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
    case END_TOK:
        break;
    default:
        Stmt(); StmtsList(); break;
    }
}
// StmtsList -> | ; Stmt StmtsList .
// Follow(StmtsList) = [END_TOK]
void StmtsList(void)
{
    switch (tok)
    {
    case END_TOK:
        break;
    case ';':
        eat(';'); Stmt(); StmtsList(); break;
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
        break;
    case IF:
        IfStmt();
        break;
    case WHILE:
        WhileStmt();
        break;
    case FOR:
        ForStmt();
        break;
    case RETURN:
        ReturnStmt();
        break;
    case DOUBLE_PLUS_SIGN:
    case DOUBLE_MINUS_SIGN:
        IncrStmt();
        break;
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
    case NULL_TOK:
    case '(':
        Exp();
    default:
        error();
    }
}
//IfStmt -> if Exp then StmtsPart ElseIfStmt .
void IfStmt(void){
    switch (tok){
    case IF:
        eat(IF); Exp(); eat(THEN); StmtsPart(); ElseIfStmt(); break;
    default:
        error();
    } 

}
//ElseIfStmt -> ElseStmt | elseif StmtsPart ElseIfStmt.
void ElseIfStmt(void){
    switch (tok)
    {
    case ELSEIF:
        eat(ELSEIF); StmtsPart(); ElseIfStmt(); break;
    case ELSE:
        ElseStmt(); break;
    default:
        error();
    }
}
//ElseStmt -> | else StmtsPart .
void ElseStmt(void){
    switch (tok)
    {
    case ELSE:
        eat(ELSE); StmtsPart(); break;
    default:
        error();
    }
}
//WhileStmt -> while Exp do StmtsPart .
void WhileStmt(void){
    switch (tok)
    {
    case WHILE:
        eat(WHILE); Exp(); eat(DO); StmtsPart(); break;
    default:
        error();
    }
}
//ReturnStmt -> return Exp .
void ReturnStmt(void){
    switch (tok)
    {
    case RETURN:
        Exp();
        break;
    default:
        error();
    }
}
//ForStmt -> for AssignStmt to Exp do StmtsPart .
void ForStmt(void){
    switch (tok)
    {
    case FOR:
        AssignStmt(); eat(TO); Exp(); eat(DO); StmtsPart();
        break;
    default:
        error();
    }
}
//AssignStmt -> Ids attrSign Exp .
void AssignStmt(void){
    switch (tok)
    {
    case ID:
    case THIS:
        Ids(); eat(ASSIGN_SIGN); Exp(); break;
    default:
        error();
    }
}
//Ids -> id IdList | this IdList .
void Ids(void){
    switch (tok)
    {
    case ID:
        eat(ID); IdList(); break;
    case THIS:
        eat(THIS); IdList(); break;
    default:
        error();
    }
}
//IdList -> | dot id .
// follow(IdList) = [assignSign]
void IdList(void){
    switch (tok)
    {
    case '.':
        eat('.'); eat(ID); break;
    case ASSIGN_SIGN:
        break;
    default:
        error();
    }
}
//IncrStmt -> incSign id | decSign id .
void IncrStmt(void){
    switch (tok)
    {
    case DOUBLE_PLUS_SIGN:
        eat(DOUBLE_PLUS_SIGN); eat(ID); break;
    case DOUBLE_MINUS_SIGN:
        eat(DOUBLE_MINUS_SIGN); eat(ID); break;
    default:
        error();
    }
}
//ErrorStmt -> RaiseStmt | TryBlk .
void ErrorStmt(void){
    switch (tok)
    {
    case RAISE:
        RaiseStmt(); break;
    case TRY:
        TryBlk(); break;
    default:
        error();
    }
}
//RaiseStmt -> raise Exp .
void RaiseStmt(void){
    switch (tok)
    {
    case RAISE:
        eat(RAISE); Exp(); break;
    default:
        error();
    }
}
//TryBlk -> try StmtsPart except ExceptBlk FinalBlk.
void TryBlk(void){
    switch (tok)
    {
    case TRY:
        eat(TRY); StmtsPart(); eat(EXCEPT); ExceptBlk(); FinalBlk(); break;
    default:
        error();
    }
}
//ExceptBlk -> on id DoStmt ExceptBlks .
void ExceptBlk(void){
    switch (tok)
    {
    case ON:
        eat(ON); eat(ID); DoStmt(); ExceptBlks(); break;
    default:
        error();
    }
}
//DoStmt -> | do StmtsPart .
// follow(DoStmt) = ["on", "finally", ';', "end"]
void DoStmt(void){
    switch (tok)
    {
    case DO:
        StmtsPart(); break;
    case ON:
    case FINALLY:
    case ';':
    case END_TOK:
        break;
    default:
        error();
    }
}
//ExceptBlks -> | ExceptBlk .
// follow(ExceptBlks) = ["finally", ';' "end"]
void ExceptBlks(void){
    switch (tok)
    {
    case ON:
        ExceptBlk(); break;
    case FINALLY:
    case ';':
    case END_TOK:
        break;
    default:
        error();
    }
}
//FinalBlk -> | finally StmtsPart .
// follow(FinalBlk) = [';', "end"]
void FinalBlk(void){
    switch (tok)
    {
    case FINALLY:
        StmtsPart(); break;
    case ';':
    case END_TOK:
        break;
    default:
        error();
    }
}
