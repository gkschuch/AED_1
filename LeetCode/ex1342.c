#include <stdio.h>
int numberOfSteps(int num) {
  int steps = 0;
  do {
    if (num % 2 == 0) {
      num = num / 2;
    } else {
      num = num - 1;
    }
    steps++;
  } while (num > 0);
  return steps;
}
int main() {
  int num = 14;
  int steps = numberOfSteps(num);
  printf("%d", steps);
}