#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORY_ARRAY_SIZE 30000
#define INSTRUCTION_MAX 10000

// Prototypes
void initialize_memory_arr(int *memory_arr);
void instruction_tree(char *instruction_ptr, int *memory_addr_ptr);


// Global variables
int memory_arr[MEMORY_ARRAY_SIZE]; // Holds all of the memory blocks
int ptr_loc = 0;                   // The pointer location of the current memory block
int count = 0;
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
   FILE *bf_file = fopen("./bf-program.bf", "r");
   if (bf_file == NULL) {
      perror("bf-program.bf could not be openned!");
      exit(1);
   }

   // Build instruction array
   initialize_memory_arr(memory_arr);
   // memory pointer that moves between blocks with > & < (initialized to the first memory block)
   int *memory_addr_ptr = &memory_arr[ptr_loc];

   // Where each instruction is written to and will be "executed" from
   char instruction_array[INSTRUCTION_MAX];
   // Pointer that moves through the instruction array (initialized to the first instruction in the list)
   char *instruction_ptr = &instruction_array[0];

   char instruction;
   while ((instruction = fgetc(bf_file)) != EOF) {
      if (instruction != '>' && instruction != '<' &&
          instruction != '+' && instruction != '-' &&
          instruction != '[' && instruction != ']' &&
          instruction != ',' && instruction != '.') {
	 continue;
      }
      instruction_array[count] = instruction;
      count++;
   }
   // Caps off the instruction arr so it knows when to stop reading
   instruction_array[count] = '\0';
   // printf("Instruction Array Size = %d\n", count);

   instruction_tree(instruction_ptr, memory_addr_ptr);

   fclose(bf_file);
   return 0;
}

void instruction_tree(char *instruction_ptr, int *memory_addr_ptr) {
   // Will run each instruction in the instruction array through the decision tree below
   while (*instruction_ptr != '\0') {
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
	 char loop_instruction_arr[INSTRUCTION_MAX];
	 char *loop_ptr = &loop_instruction_arr[0];

	 int instruction_count = 0;
	 // Used to check if the loop is valid (if the value of a mem block will go to 0 at any point)
	 int incr_or_decr_found = 0;
	 while (*instruction_ptr != ']') {
	    count--;
	    if (count <= 0 || instruction_count == INSTRUCTION_MAX - 1 || *instruction_ptr == '\0') {
	       printf("Compile failure: Reached EOF before matching \']\'\n");
	       exit(1);
	    }
	    if (instruction_ptr[0] == '[') {
	       instruction_ptr++;
	    }
	    if (*instruction_ptr == '+' || *instruction_ptr == '-') {
	       incr_or_decr_found = 1;
	    }
	    // printf("Current instructions at instruction %d: %c\n", instruction_count, *instruction_ptr);
	    loop_ptr[instruction_count] = *instruction_ptr;
	    instruction_ptr++;
	    instruction_count++;

	    if (*instruction_ptr == ']') {
	       // printf("Matching ] found!\n");
	    }
	    // sleep(1);
	 }
	 loop_ptr[instruction_count] = '\0';

	 // Infinite loop check
	 if (incr_or_decr_found == 0) {
	    printf("Compile error: Infinite loop\n");
	    exit(1);
	 }

	 // Set it back to the first instruction in the loop instruction array
	 loop_ptr = &loop_instruction_arr[0];
	 // printf("All loop instructions: %s\n", loop_ptr);

	 // Increment both the location of the loop instruction pointer and the original instruction pointer
	 // to make the instructions read to the main array too
	 while (*memory_addr_ptr != 0) {
	    //  Execute the instructions found inside the []
	    //  Recurse and run the loop instructions through the instruction tree
	    instruction_tree(loop_ptr, memory_addr_ptr);

	    // Prevent infinite loop runaway
	    // sleep(1);
	 }
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

      count--;
      instruction_ptr++;
   }
}

void initialize_memory_arr(int *memory_arr) {
   for (int i = 0; i < MEMORY_ARRAY_SIZE; i++) {
      memory_arr[i] = 0;
   }
}
