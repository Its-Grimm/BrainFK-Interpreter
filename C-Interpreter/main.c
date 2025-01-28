#include <stdio.h>
#include "stack.h"

#define MEMORY_ARRAY_SIZE 30000

// Prototypes
void initialize_memory_arr(int *memory_arr);


// Const global variables
const int memory_arr_size = MEMORY_ARRAY_SIZE;
const char operator_list[8] = {
   // Pointer Manipulation Operators
   '>', // Increases memory pointer, or moves the pointer to the right 1 block.
   '<', // Decreases memory pointer, or moves the pointer to the left 1 block.
   // Value Manipulation Operators
   '+', // Increases value stored at the block pointed to by the memory pointer
   '-', // Decreases value stored at the block pointed to by the memory pointer
   // Loop Operators
   '[', // Like c while(cur_block_value != 0) loop.
   ']', // If block currently pointed to's value is not zero, jump back to [
   // I/O Operators
   ',', // Like C getchar(). input 1 character.
   '.'  // Like C putchar(). print 1 character to the console
};


int main() {
   Stack instruction_stack;
   Stack *stack_addr = &instruction_stack;
   initialize_stack(stack_addr, 1);


   int memory_arr[memory_arr_size];
   initialize_memory_arr(memory_arr);
   for (int i = 0; i <= 10; i++) {
      printf("Memory value at %d: %d\n", i, memory_arr[i]);
   }


   return 0;
}

void initialize_memory_arr(int *memory_arr) {
   for (int i = 0; i < memory_arr_size; i++) {
      memory_arr[i] = 0;
   }
}
