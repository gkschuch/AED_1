#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fizzBuzz(int n, int *returnSize) {
  char **answer = (char **)malloc(n * sizeof(char *));
  if (answer == NULL) {
    *returnSize = 0;
    return NULL;
  }

  for (int i = 0; i < n; i++) {
    int current_number = i + 1;

    answer[i] = (char *)malloc(12 * sizeof(char));
    if (answer[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(answer[j]);
      }
      free(answer);
      *returnSize = 0;
      return NULL;
    }

    if (current_number % 3 == 0 && current_number % 5 == 0) {
      strcpy(answer[i], "FizzBuzz");
    } else if (current_number % 3 == 0) {
      strcpy(answer[i], "Fizz");
    } else if (current_number % 5 == 0) {
      strcpy(answer[i], "Buzz");
    } else {
      sprintf(answer[i], "%d", current_number);
    }
  }

  *returnSize = n;
  return answer;
}

int main() {
  int n = 15;
  int resultSize = 0;
  char **result = fizzBuzz(n, &resultSize);
  for (int i = 0; i < resultSize; i++) {
    printf("%d: %s\n", i + 1, result[i]);
  }
  for (int i = 0; i < resultSize; i++) {
    free(result[i]);
  }
  free(result);

  return 0;
}