#ifndef __TABLE_H__
#define __TABLE_H__
#include "stack.h"
#include "rules.h"
#include "body.h"
#include "definitions.h"
#include "expressions.h"
#include "utils.h"

struct Stack* stack;

void parse_table();
void table_to_stack(int line, int col);

#endif //__TABLE_H__
