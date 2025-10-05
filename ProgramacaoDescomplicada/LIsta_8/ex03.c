#include <stdio.h>
/*
3. Escreva uma funcao recursiva que calcule a soma dos primeiros n cubos:
S(n) = 1^3 +2^3 + ... + n^3
*/

long long int sumOfCubes(int n) {
  if (n <= 1) {
    return n;
  } else {
    long long int cubeOfNum = (long long int)n * n * n;
    return cubeOfNum + sumOfCubes(n - 1);
  }
}

int main() {
  int number;

  printf("Enter a positive integer: ");
  scanf("%d", &number);

  if (number < 0) {
    printf("Please enter a positive number.\n");
  } else {
    long long int result = sumOfCubes(number);
    printf("The sum of the cubes from 1 to %d is: %lld\n", number, result);
  }

  return 0;
}