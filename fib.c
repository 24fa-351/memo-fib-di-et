#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
unsigned long long int memo[MAX] = {0};

unsigned long long int fib_wrapper_iterative(int N)
{
   unsigned long long int x = 0;
   unsigned long long int y = 1;
   unsigned long long int next_int;

   if (N <= 0)
   {
      return 0;
   }
   if (N == 1)
   {
      return 1;
   }
   for (int i = 2; i <= N; i++)
   {
      next_int = x + y; // 'next_int' is assigned to the sum of x + y.
      x = y;            // 'x' value is assigned the 'y' value.
      y = next_int;     // 'y' value is assigned the 'next_int' value.
   }
   return y;
}

unsigned long long int fib_wrapper_recursive(int N)
{
   if (N <= 0)
   {
      return 0;
   }
   if (N == 1)
   {
      return 1;
   }

   if (memo[N] != -1)
   {
      return memo[N];
   }
   memo[N] = fib_wrapper_recursive(N - 1) + fib_wrapper_recursive(N - 2);
   return memo[N];
}

unsigned long long (*provider_function)(int N);

unsigned long long fib_recursive_provider(int N)
{
   if (N <= 0)
   {
      return 0;
   }
   if (N == 1)
   {
      return 1;
   }
   return (*provider_function)(N - 1) + (*provider_function)(N - 2);
}
unsigned long long (*actual_provider_function)(int N);

unsigned long long fib_recursive_memoize(int N)
{
   if (N < 1)
   {
      return 0;
   }
   if (memo[N] != 0)
   {
      // printf("index %d returning %llu from the cache\n", N, memo[N]);
      return memo[N];
   }
   memo[N] = (*actual_provider_function)(N);
   // printf("%llu", memo[N]);
   // printf("index %d returning %llu from the provider\n", N, memo[N]);
   return memo[N];
}

int main(int argc, char *argv[])
{
   char *number_command_line;
   char *method;

   if (argc < 2)
   {
      printf("Error: Not enough arguments.\n");
      number_command_line = "0";
      method = "r";
   }
   else
   {
      number_command_line = argv[1];
      method = argv[2];
   }

   provider_function = fib_recursive_memoize;
   actual_provider_function = fib_wrapper_iterative;

   int N = strtol(number_command_line, NULL, 10);

   if (method[0] == 'i')
   {
      actual_provider_function = fib_wrapper_iterative;
   }
   else if (method[0] == 'r')
   { // if 'r'(recursion) is the argument.
      actual_provider_function = fib_recursive_provider;
   }
   else
   {
      printf("failed... invalid input!");
      exit(1);
   }

   unsigned long long fib_value = (*provider_function)(N - 1);
   printf("%llu", fib_value);
   return 0;
}

// TODO: Adjust program and delete read from file.
// TODO: call fib_wrapper_recursive & fib_wrapper_iterative with characters 'I' and 'R'.
// TODO: Clean up code. Aline comments and delete extra text.