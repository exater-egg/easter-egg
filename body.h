#include "tokens.h"

//StmtsPart->begin Stmts end.
void StmtsPart(void);
//Stmts -> | Stmt StmtsList .
void Stmts(void);
// StmtsList -> | ; Stmt StmtsList .
void StmtsList(void);
// Stmt -> IfStmt | WhileStmt | ForStmt |  ReturnStmt | Exp | IncrStmt | ErrorStmt .
void Stmt(void);
//IfStmt -> if Exp then StmtsPart ElseIfStmt .
void IfStmt(void);
//ElseIfStmt -> ElseStmt | elseif StmtsPart ElseIfStmt.
void ElseIfStmt(void);
//ElseStmt -> | else StmtsPart .
void ElseStmt(void);
//WhileStmt -> while Exp do StmtsPart .
void WhileStmt(void);
//ReturnStmt -> return Exp .
void ReturnStmt(void);
//ForStmt -> for AssignStmt to Exp do StmtsPart .
void ForStmt(void);
//AssignStmt -> Ids attrSign Exp .
void AssignStmt(void);
//Ids -> id IdList | this IdList .
void Ids(void);
//IdList -> | dot id .
void IdList(void);
//IncrStmt -> incSign id | decSign id .
void IncrStmt(void);
//ErrorStmt -> RaiseStmt | TryBlk .
void ErrorStmt(void);
//RaiseStmt -> raise Exp .
void RaiseStmt(void);
//TryBlk -> try StmtsPart except ExceptBlk FinalBlk.
void TryBlk(void);
//ExceptBlk -> on id DoStmt ExceptBlks .
void ExceptBlk(void);
//DoStmt -> | do StmtsPart .
void DoStmt(void);
//ExceptBlks -> | ExceptBlk .
void ExceptBlks(void);
//FinalBlk -> | finally StmtsPart .
void FinalBlk(void);
