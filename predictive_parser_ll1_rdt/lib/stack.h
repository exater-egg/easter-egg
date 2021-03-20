#ifndef __STACK_H__
#define __STACK_H__

// A structure to represent a stack
struct Stack {
    int size;
    unsigned capacity;
    int* array;
};
struct Stack* create_stack(unsigned capacity);
int stack_is_full(struct Stack* stack);
int stack_is_empty(struct Stack* stack);
void stack_push(struct Stack* stack, int item);
int stack_pop(struct Stack* stack);
int stack_peek(struct Stack* stack);

#endif //__STACK_H__
