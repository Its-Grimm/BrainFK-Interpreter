#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
   char *data;
   int top;
   int capacity;
} Stack;

void initialize_stack(Stack *stack, int initial_capacity);
void resize_stack(Stack *stack);
void push(Stack *stack, char element);
char pop(Stack *stack);
void show(Stack *stack);
void free_stack(Stack *stack);

#endif
