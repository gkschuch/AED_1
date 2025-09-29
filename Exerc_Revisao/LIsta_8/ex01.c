#include <stdio.h>
/*
1. Crie uma função recursiva que receba um número inteiro positivo N e
calcule o somatório dos números de 1 a N.
*/

int SumToN(int n);
int main() {
  int n;
  int result;
  printf("Digite um valor para N: ");
  scanf("%d", &n);

  result = SumToN(n);
  printf("%d", result);
}

int SumToN(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return n + SumToN(n - 1);
}