#include <stdio.h>
#include "stack.h"

#define MEMORY_ARRAY_SIZE 30000

// Prototypes
void initialize_memory_arr(int *memory_arr);


// Const global variables
const int memory_arr_size = MEMORY_ARRAY_SIZE;
const char operator_list[8] = {
   // Pointer Manipulation Operators
   '>', // Increases memory pointer (moves the pointer to the right 1 block)
   '<', // Decreases memory pointer (moves the pointer to the left 1 block)
   // Value Manipulation Operators
   '+', // Increases value stored at the block pointed to by the memory pointer
   '-', // Decreases value stored at the block pointed to by the memory pointer
   // Loop Operators
   '[', // Like C while(cur_block_value != 0) loop.
   ']', // If block currently pointed to's value is not zero, jump back to [
   // I/O Operators
   ',', // Like C getchar(). input 1 character. (like scanf("%c", var))
   '.'  // Like C putchar(). print 1 character to the console (like printf)
};


int main() {
   int ptr_loc = 0;

   // Array of memory blocks
   int memory_arr[memory_arr_size];
   initialize_memory_arr(memory_arr);

   // memory pointer that moves to another block with > & < and initialize it to the first memory block
   int *memory_addr_ptr = &memory_arr[ptr_loc];


   char instruction_array[1000];
   FILE *bf_file = fopen("./bf-program.bf", "r");

   // Build instruction array


   char user_input;
   if (user_input == '>') {
      if (ptr_loc == MEMORY_ARRAY_SIZE - 1) {
	 memory_addr_ptr = &memory_arr[0];
	 ptr_loc = 0;
      }
      else {
	 memory_addr_ptr++;
	 ptr_loc++;
      }
   }
   else if (user_input == '<') {
      if (memory_addr_ptr == 0) {
	 memory_addr_ptr = &memory_arr[MEMORY_ARRAY_SIZE - 1];
	 ptr_loc = MEMORY_ARRAY_SIZE - 1;
      }
      else {
	 memory_addr_ptr--;
	 ptr_loc--;
      }
   }
   else if (user_input == '+') {
      if ((*memory_addr_ptr) == 255) {
	 (*memory_addr_ptr) = 0;
      }
      else {
	 (*memory_addr_ptr)++;
      }
   }
   else if (user_input == '-') {
      if ((*memory_addr_ptr) == 0) {
	 (*memory_addr_ptr) = 255;
      }
      else {
	 (*memory_addr_ptr)--;
      }
   }
   else if (user_input == '[') {
      // [ & ] together are equivalent to, but not equal to, "while (*memory_addr_ptr != 0) {}"
      // How do implement considering can have nested instructions inside of loops
   }
   else if (user_input == ']') {
      // And how do implement this too
      // Maybe have detection that detects both [ & ] for program to compile properly,
      // then makes the instructions inside the [] go inside a loop?
   }
   else if (user_input == ',') {
      int ascii_val = 0;
      scanf("%d", &ascii_val);
      if (ascii_val >= 0 && ascii_val <= 255) {
	 *memory_addr_ptr = ascii_val;
      }
   }
   else if (user_input == '.') {
      printf("%c", *memory_addr_ptr);
   }
   else {
      printf("%c", user_input);
   }

   return 0;
}

void initialize_memory_arr(int *memory_arr) {
   for (int i = 0; i < memory_arr_size; i++) {
      memory_arr[i] = 0;
   }
}
