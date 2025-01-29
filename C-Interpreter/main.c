#include <stdio.h>

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


   // Where each instruction is written to, and will be "executed" from
   char instruction_array[1000];
   // Build instruction array
   FILE *bf_file = fopen("./bf-program.bf", "r");
   char instruction;
   int count = 0;
   while ((instruction = fgetc(bf_file)) != EOF) {
      instruction_array[count] = instruction;
      count++;
   }
   // Caps off the instruction arr so it knows when to stop reading
   instruction_array[count] = '\0';

   int execution_count = 0;
   char *instruction_ptr = instruction_array;
   while (*instruction_ptr != '\0') {
      // Will run through each instruction in the array through the decision tree below
      char curr_instruction = *instruction_ptr;
      // printf("Current instruction: %c\n", curr_instruction);

      if (curr_instruction == '>') {
	 if (ptr_loc == MEMORY_ARRAY_SIZE - 1) {
	    memory_addr_ptr = &memory_arr[0];
	    ptr_loc = 0;
	 }
	 else {
	    memory_addr_ptr++;
	    ptr_loc++;
	 }
	 // printf("Moved pointer to pos: %d\n", ptr_loc);
      }
      else if (curr_instruction == '<') {
	 if (ptr_loc == 0) {
	    memory_addr_ptr = &memory_arr[MEMORY_ARRAY_SIZE - 1];
	    ptr_loc = MEMORY_ARRAY_SIZE - 1;
	 }
	 else {
	    memory_addr_ptr--;
	    ptr_loc--;
	 }
	 // printf("Moved pointer to pos: %d\n", ptr_loc);
      }
      else if (curr_instruction == '+') {
	 if (*memory_addr_ptr == 255) {
	    (*memory_addr_ptr) = 0;
	 }
	 else {
	    (*memory_addr_ptr)++;
	 }
	 // printf("Incremented pos %d to %d\n", ptr_loc, *memory_addr_ptr);
      }
      else if (curr_instruction == '-') {
	 if (*memory_addr_ptr == 0) {
	    (*memory_addr_ptr) = 255;
	 }
	 else {
	    (*memory_addr_ptr)--;
	 }
	 // printf("Decremented pos %d to %d\n", ptr_loc, *memory_addr_ptr);
      }
      else if (curr_instruction == '[') {
	 // [ & ] together are equivalent to, but not equal to, "while (*memory_addr_ptr != 0) {}"
	 // How do implement considering can have nested instructions inside of loops
      }
      else if (curr_instruction == ']') {
	 // And how do implement this too
	 // Maybe have detection that detects both [ & ] for program to compile properly,
	 // then makes the instructions inside the [] go inside a loop?
      }
      else if (curr_instruction == ',') {
	 char ascii_val;
	 printf("Enter value: ");
	 scanf("%c", &ascii_val);
	 if ((int)ascii_val >= 0 && (int)ascii_val <= 255) {
	    *memory_addr_ptr = ascii_val;
	 }
      }
      else if (curr_instruction == '.') {
	 if (*memory_addr_ptr >= 32 && *memory_addr_ptr <= 255) {
	    printf("Ascii val at block %d with count %d:\t%c\n", ptr_loc, (*memory_addr_ptr), (char)(*memory_addr_ptr));
	 }
	 else {
	    printf("Ascii val at block %d with count %d:\tN/A\n", ptr_loc, *memory_addr_ptr);
	 }
      }
      else if (curr_instruction == ' ' || curr_instruction == '\n') {
      }
      else {
	 printf("%c", curr_instruction);
      }

      instruction_ptr++;
   }
   fclose(bf_file);
   return 0;
}

void initialize_memory_arr(int *memory_arr) {
   for (int i = 0; i < memory_arr_size; i++) {
      memory_arr[i] = 0;
   }
}
