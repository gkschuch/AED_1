#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *restoreString(char *s, int *indices, int indicesSize) {
  char *result = (char *)malloc(sizeof(char) * (indicesSize + 1));
  for (int i = 0; i < indicesSize; i++)
    result[indices[i]] = s[i];

  result[indicesSize] = '\0';
  return result;
}

int main() {
  char *s = "codeleet";
  int indices[] = {4, 5, 6, 7, 0, 2, 1, 3};

  int size = strlen(s);

  char *result = restoreString(s, indices, size);

  if (result != NULL)
    printf("%s\n", result);

  free(result);
  return 0;
}