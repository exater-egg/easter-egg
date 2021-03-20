#include "stack.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 
struct Stack* create_stack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
int stack_is_full(struct Stack* stack)
{
    return stack->size == stack->capacity;
}
 
// Stack is empty when top is equal to -1
int stack_is_empty(struct Stack* stack)
{
    return stack->size == 0;
}
 
// Function to add an item to stack.  It increases top by 1
void stack_push(struct Stack* stack, int item)
{
    if (stack_is_full(stack))
        return;
    stack->array[stack->size++] = item;
}
 
// When empty, since all enum tokens and rules are positive, returns -1
int stack_pop(struct Stack* stack)
{
    if (stack_is_empty(stack))
        return -1;
    return stack->array[--stack->size];
}
 
int stack_peek(struct Stack* stack)
{
    if (stack_is_empty(stack))
        return INT_MIN;
    return stack->array[stack->size-1];
}
