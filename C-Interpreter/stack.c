#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Define a stack structure
typedef struct Stack {
   char *data;   // Pointer to the stack array
   int top;      // Index of the top element
   int capacity; // Current capacity of the stack
} Stack;

void initialize_stack(Stack *stack, int initial_capacity) {
   stack->data = (char *)malloc(initial_capacity * sizeof(char));
   if (stack->data == NULL) {
      printf("\nMemory allocation failed!");
      exit(1);
   }
   stack->top = -1; // Stack is initially empty
   stack->capacity = initial_capacity;
}

void resize_stack(Stack *stack) {
   stack->capacity *= 2; // Double the capacity
   char *newData = (char *)realloc(stack->data, stack->capacity * sizeof(char));
   if (newData == NULL) {
      printf("\nMemory reallocation failed!");
      exit(1);
   }
   stack->data = newData;
}

void push(Stack *stack, char element) {
   if (stack->top == stack->capacity - 1) {
      resize_stack(stack); // Resize if the stack is full
   }
   stack->data[++stack->top] = element; // Add the element and increment top
}

char pop(Stack *stack) {
   if (stack->top == -1) {
      printf("\nStack underflow!");
      return '\0'; // Return a null character to indicate failure
   }
   return stack->data[stack->top--]; // Return the top element and decrement top
}

void show(Stack *stack) {
   if (stack->top == -1) {
      printf("\nStack is empty!");
      return;
   }
   printf("\nElements in the stack:\n");
   for (int i = stack->top; i >= 0; i--) {
      printf("%c\n", stack->data[i]);
   }
}

void free_stack(Stack *stack) {
   free(stack->data);
   stack->data = NULL;
   stack->top = -1;
   stack->capacity = 0;
}
