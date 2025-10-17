#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strStr(char *haystack, char *needle) {

  int haystackLen = strlen(haystack);
  int needleLen = strlen(needle);

  for (int i = 0; i <= haystackLen - needleLen; i++) {
    int j;
    for (j = 0; j < needleLen; j++)
      if (haystack[i + j] != needle[j])
        break;
    if (j == needleLen)
      return i;
  }
  return -1;
}

int main() {
  char *haystack = "sadbutsad";
  char *needle = "sad";
  int indexFirstOccurence = strStr(haystack, needle);

  printf("%d", indexFirstOccurence);
}