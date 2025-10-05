#include <stdio.h>
/*
2. Faca uma funcao recursiva que calcule e retorne o fatorial de um numero
inteiro N.
*/

int factorial(int n);

int main() {
  int num;
  int factorialResult;
  scanf("%d", &num);
  factorialResult = factorial(num);
  printf("Result of the factorial of %d: %d", num, factorialResult);
  return 0;
}

int factorial(int num) {
  if (num == 1 || num == 0)
    return 1;
  return num * factorial(num - 1);
}