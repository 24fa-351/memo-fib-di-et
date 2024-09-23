#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
unsigned long long int memo[MAX] = {0};

unsigned long long int fib_wrapper_iterative(int N){
   unsigned long long int x = 0;
   unsigned long long int y = 1;
   unsigned long long int next_int;

   if(N <= 0){   // check to see if 'N' term is 0, the (0) term is 0.
      return 0;
   }
   if (N == 1){
      return 1;
   }

   if (memo[N] != -1){
      return memo[N];
   }
   // loop for fibonacci sequence
   // 'i' can not be 0 or 1
   for (int i = 2; i <= N; i++){
      next_int = x + y;      // 'next_int' is assigned to the sum of x + y.
      x = y;      // 'x' value is assigned the 'y' value.
      y = next_int;      // 'y' value is assigned the 'next_int' value.
      memo[i] = next_int;       // store result in the memo array.

   }
   return y;
}

unsigned long long int fib_wrapper_recursive(int N){
   if (N <= 0){    // check to see if 'N' term is 0, the (0) term is 0.
      return 0;
   }
   if (N == 1){   // check to see if 'N' term is 1. the (1) term is 0 + 1 = 1.
      return 1;
   }
      if (memo[N] != -1){
      return memo[N];
   }
   memo[N] = fib_wrapper_recursive(N - 1) + fib_wrapper_recursive(N - 2);
   return memo[N];
}

unsigned long long (*cache_function)(int N);

unsigned long long fib_recursive_provider(int N){
   if (N <= 0){    // check to see if 'N' term is 0, the (0) term is 0.
      return 0;
   }
   if (N == 1){   // check to see if 'N' term is 1. the (1) term is 0 + 1 = 1.
      return 1;
   }
   return (*cache_function)(N - 1) + (*cache_function)(N -2);
}

unsigned long long fib_recursive_memoize(int N){
      if (N < 1){
      return 0;
   }
      if (memo[N] != 0){ 
      printf("index %d returning %llu from the cache\n", N, memo[N]);
      return memo[N];
   }
   memo[N] = fib_recursive_provider(N);
   printf("index %d returning %llu from the provider\n", N, memo[N]);
   return memo[N];
}

int main(int argc, char *argv[]) 
{
   char *number_command_line = argv[1];
   char *method = argv[2];
   char *filename = argv[3];

   if (argc < 4) {
      printf("Error: Not enough arguments.\n");
      exit(1);
   }

   cache_function = fib_recursive_provider;

   int a_number;   // a_number is assigned to the argument inputted through the terminal.
   a_number = strtol ( number_command_line, NULL, 10 );
   int integer_read_from_file;

   FILE *fptr;   // creation of file pointer
   fptr = fopen ( filename,"r" );   // Open a file in read mode

   if( fptr == NULL) {   // Check if nothing is in file
      printf("file failed.\n");
      exit(1);
   }
   fscanf ( fptr, " %d", &integer_read_from_file );   // fscanf(); is reading and storing the character on the variable integer_read_from_file.
   // printf("I read this from the file %d\n", integer_read_from_file );
   fclose(fptr);    // Close the file

   int N;   // 'N' is the; sum = (a_number + integer_read_from_file)
   N = a_number + integer_read_from_file;

   if (method[0] == 'r') {   // if 'r'(recursion) is the argument.
      unsigned long long fib_value = (*cache_function)(N);
      printf("number found from recursion: %llu\n", fib_value);
   } else if (method[0] == 'i') {
      unsigned long long fib_value = fib_wrapper_iterative(N);      //if 'i'(iterative) is the argument.
      printf("number found from iterative: %llu\n", fib_value);
      } else {
      printf("failed... invalid input!");
      exit(1);
   }

   return 0;
}

// TODO: Adjust program and delete read from file.
// TODO: Delete fib_wrapper_recursive & fib_wrapper_iterative. 
// TODO: Figure out why cache_function is returning '0'. 
// TODO: Clean up code. Aline comments and delete extra text.