#include "table.h"
#include "stack.h"
#include "rules.h"
#include "body.h"
#include "definitions.h"
#include "expressions.h"
#include "utils.h"
#define RULES_START 255 // Rules starts at 255 and tokens go up to 255

void parse_table()
{
    stack = create_stack(1024);
    stack_push(stack, Prog);
    while (!stack_is_empty(stack))
    {
        enum rules symbol = stack_pop(stack);
        if (symbol < RULES_START)// If it is a terminal
            eat(symbol); // Compares symbol in table with the token
        else // Non Terminal
            table_to_stack(symbol, tok);
    }
    
}
void table_to_stack(int line, int col)
{
    switch (line)
    {
    case Prog: Prog_to_stack(col);break;
    case Pack: Pack_to_stack(col);break;
    case Impt: Impt_to_stack(col);break;
    case ProgBody: ProgBody_to_stack(col);break;
	case ConstDefPart: ConstDefPart_to_stack(col);break;
	case ConstDef: ConstDef_to_stack(col);break;
	case ConstDefs: ConstDefs_to_stack(col);break;
	case ClassDefPart: ClassDefPart_to_stack(col);break;
	case ClassDef: ClassDef_to_stack(col);break;
	case ClassInherance: ClassInherance_to_stack(col);break;
	case ClassDefs: ClassDefs_to_stack(col);break;
	case AttrDeclPart: AttrDeclPart_to_stack(col);break;
	case AttrInit: AttrInit_to_stack(col);break;
	case AttrInits: AttrInits_to_stack(col);break;
	case AttrDecl: AttrDecl_to_stack(col);break;
	case AttrVal: AttrVal_to_stack(col);break;
	case AttrDecls: AttrDecls_to_stack(col);break;
	case MethDeclPart: MethDeclPart_to_stack(col);break;
	case MethHead: MethHead_to_stack(col);break;
	case MethType: MethType_to_stack(col);break;
	case MethHeads: MethHeads_to_stack(col);break;
	case ParSec: ParSec_to_stack(col);break;
	case Param: Param_to_stack(col);break;
	case Params: Params_to_stack(col);break;
	case ParSecs: ParSecs_to_stack(col);break;
	case VarDeclPart: VarDeclPart_to_stack(col);break;
	case VarKeywd: VarKeywd_to_stack(col);break;
	case VarDef: VarDef_to_stack(col);break;
	case Var: Var_to_stack(col);break;
	case VarList: VarList_to_stack(col);break;
	case VarAssign: VarAssign_to_stack(col);break;
	case VarDefs: VarDefs_to_stack(col);break;
	case MethDefPart: MethDefPart_to_stack(col);break;
	case MethDef: MethDef_to_stack(col);break;
	case MethDefs: MethDefs_to_stack(col);break;
	case Const: Const_to_stack(col);break;
	case SignedConst: SignedConst_to_stack(col);break;
	case Num: Num_to_stack(col);break;
	case Sign: Sign_to_stack(col);break;
	case ArrayLit: ArrayLit_to_stack(col);break;
	case ExpList: ExpList_to_stack(col);break;
	case ExpList_1: ExpList_1_to_stack(col);break;
	case Ids: Ids_to_stack(col);break;
	case IdList: IdList_to_stack(col);break;
	case AccessIndex: AccessIndex_to_stack(col);break;
	case MethCall: MethCall_to_stack(col);break;
	case Exp: Exp_to_stack(col);break;
	case LogicExp: LogicExp_to_stack(col);break;
	case TermLogic: TermLogic_to_stack(col);break;
	case TermLogic_1: TermLogic_1_to_stack(col);break;
	case FactorLogic: FactorLogic_to_stack(col);break;
	case LogicAtom: LogicAtom_to_stack(col);break;
	case RelExp: RelExp_to_stack(col);break;
	case Comparactive: Comparactive_to_stack(col);break;
	case ArithExp: ArithExp_to_stack(col);break;
	case ArithExp_1: ArithExp_1_to_stack(col);break;
	case Term: Term_to_stack(col);break;
	case Term_1: Term_1_to_stack(col);break;
	case Factor: Factor_to_stack(col);break;
	case StmtsPart: StmtsPart_to_stack(col);break;
	case Stmts: Stmts_to_stack(col);break;
	case StmtsList: StmtsList_to_stack(col);break;
	case Stmt: Stmt_to_stack(col);break;
	case IfStmt: IfStmt_to_stack(col);break;
	case ElseIfStmt: ElseIfStmt_to_stack(col);break;
	case ElseStmt: ElseStmt_to_stack(col);break;
	case WhileStmt: WhileStmt_to_stack(col);break;
	case ReturnStmt: ReturnStmt_to_stack(col);break;
	case ForStmt: ForStmt_to_stack(col);break;
	case AssignStmt: AssignStmt_to_stack(col);break;
	case IncrStmt: IncrStmt_to_stack(col);break;
	case ErrorStmt: ErrorStmt_to_stack(col);break;
	case RaiseStmt: RaiseStmt_to_stack(col);break;
	case TryBlk: TryBlk_to_stack(col);break;
	case ExceptBlk: ExceptBlk_to_stack(col);break;
	case DoStmt: DoStmt_to_stack(col);break;
	case ExceptBlks: ExceptBlks_to_stack(col);break;
	case FinalBlk: FinalBlk_to_stack(col);break;
    
    default:
        error();
        break;
    }
}
