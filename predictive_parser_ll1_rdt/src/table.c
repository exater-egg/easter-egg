#include "table.h"
#include "stack.h"
#include "rules.h"
#include "../../lib/utils.h"
#define RULES_START 255 // Rules starts at 255 and tokens go up to 255

struct Stack* stack;

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
void table_to_stack(int line, int col){
    switch (line)
    {
    case Prog:
        Prog_to_stack(col);
        break;
    case Pack:
        // TODO
        break;
    case Impt:
        // TODO
        break;
    case ProgBody:
        // TODO
        break;
    
    default:
        error();
        break;
    }
}

void Prog_to_stack(int col)
{
    switch (col)
    {
    case IMPORT:
        break;
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
