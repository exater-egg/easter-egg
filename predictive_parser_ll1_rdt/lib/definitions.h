#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include "rules.h"
#include "stack.h"
#include "table.h"
#include "tokens.h"
#include "utils.h"

void Prog_to_stack(int col);

void Pack_to_stack(int col);

void Impt_to_stack(int col);

void Impts_to_stack(int col);

void ProgBody_to_stack(int col);

void ConstDefPart_to_stack(int col);

void ConstDef_to_stack(int col);

void ConstDefs_to_stack(int col);

void ClassDefPart_to_stack(int col);

void ClassDef_to_stack(int col);

void ClassInherance_to_stack(int col);

void ClassDefs_to_stack(int col);

void AttrDeclPart_to_stack(int col);

void AttrInit_to_stack(int col);

void AttrInits_to_stack(int col);

void AttrDecl_to_stack(int col);

void AttrVal_to_stack(int col);

void AttrDecls_to_stack(int col);

void MethDeclPart_to_stack(int col);

void MethHead_to_stack(int col);

void MethType_to_stack(int col);

void MethHeads_to_stack(int col);

void ParSec_to_stack(int col);

void Param_to_stack(int col);

void Params_to_stack(int col);

void ParSecs_to_stack(int col);

void VarDeclPart_to_stack(int col);

void VarKeywd_to_stack(int col);

void VarDef_to_stack(int col);

void Var_to_stack(int col);

void VarList_to_stack(int col);

void VarAssign_to_stack(int col);

void VarDefs_to_stack(int col);

void MethDefPart_to_stack(int col);

void MethDef_to_stack(int col);

void MethDefs_to_stack(int col);

#endif
