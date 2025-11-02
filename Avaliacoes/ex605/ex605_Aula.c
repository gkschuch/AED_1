#include <stdbool.h>
#include <stdio.h>
// Gabriel Karini Schuch
/*
    Restricoes:
    flowerbed[i] = 0 ou 1
    Não pode plantar flores adjacentes
    Logica para fazer:
    Vou fazer um loop do vetor flowerbed até terminar ele,
    Eu testo se a posicao i do vetor  for igual a 0
    se ela for igual a zero eu testo se o anterior e o proximo são iguais a zero
    ou se é o começo ou fim do vetor
    Se ambos forem verdade eu posso plantar

*/

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
  if (n == 0) {
    return true;
  }

  for (int i = 0; i < flowerbedSize; i++) {
    if (flowerbed[i] == 0) {

      if (((i == 0) || (flowerbed[i - 1] == 0)) &&
          ((i == flowerbedSize - 1) || (flowerbed[i + 1] == 0))) {
        flowerbed[i] = 1;
        n--;
        if (n == 0) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  int flowerbed[] = {0, 0, 1, 0, 1};
  int size = 5;
  int numFlowersToPlant = 1;

  if (canPlaceFlowers(flowerbed, size, numFlowersToPlant)) {
    printf("True");
  } else {
    printf("False");
  }
  for (int i = 0; i < size; i++) {
    printf("\n%d", flowerbed[i]);
  }
}