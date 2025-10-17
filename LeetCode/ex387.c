#include <stdio.h>

int firstUniqChar(char *s) {
  for (int i = 0; s[i] != '\0'; i++) {
    int isUnique = 1;
    for (int j = 0; s[j] != '\0'; j++)
      if (i != j && s[i] == s[j]) {
        isUnique = 0;
        break;
      }

    if (isUnique)
      return i;
  }
  return -1;
}
int main() {
  char *string = "leetcode";
  int indexNotRepeatingChar = firstUniqChar(string);
  printf("%d", indexNotRepeatingChar);
}