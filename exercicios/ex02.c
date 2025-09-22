#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
void addName(char **name);
void removeName(char **name);

int main() {
  char *names = NULL;
  while (1) {
    int op = menu();
    switch (op) {
    case 1:
      addName(&names);
      break;
    case 2:
      removeName(&names);
      break;
    case 3:
      printf("%s\n", names);
      break;
    case 4:
      free(names);
      exit(0);
      break;
    default:
      printf("Operation Unknown\n");
      break;
    }
  }
  return 0;
}
int menu(void) {
  int op = 0;
  printf("-- MENU:\n");
  printf("\t 1. Add name\n");
  printf("\t 2. Remove name\n");
  printf("\t 3. List\n");
  printf("\t 4. Exit\n");
  printf("-- Insert operation: ");
  scanf("%d", &op);

  getchar();

  return op;
}
void addName(char **listNames) {
  char nameToAdd[100];
  printf("Insert a name: ");
  fgets(nameToAdd, sizeof(nameToAdd), stdin);
  nameToAdd[strcspn(nameToAdd, "\n")] = 0;

  int oldLen = (*listNames == NULL) ? 0 : strlen(*listNames);
  int newNameLen = strlen(nameToAdd);

  const char *separator = " ";
  int separatorLen = (oldLen == 0) ? 0 : strlen(separator);

  int newSize = oldLen + separatorLen + newNameLen + 1;

  char *new_ptr = realloc(*listNames, newSize);
  *listNames = new_ptr;
  if (oldLen > 0) {
    strcat(*listNames, separator);
  }
  strcat(*listNames, nameToAdd);
}
void removeName(char **listNames) {
  char nameToRemove[100];
  printf("Insert a name to remove: ");
  fgets(nameToRemove, sizeof(nameToRemove), stdin);
  nameToRemove[strcspn(nameToRemove, "\n")] = 0;

  char *newListNames = NULL;
  char *listNamesCopy = strdup(*listNames);

  char *token = strtok(listNamesCopy, " ");

  while (token != NULL) {
    if (strcmp(token, nameToRemove) != 0) {
      int oldLenNew = (newListNames == NULL) ? 0 : strlen(newListNames);
      int tokenLen = strlen(token);
      int separatorLenNew = (oldLenNew == 0) ? 0 : strlen(" ");
      int newSize_new = oldLenNew + separatorLenNew + tokenLen + 1;

      char *temp_ptr = realloc(newListNames, newSize_new);
      newListNames = temp_ptr;

      if (oldLenNew > 0)
        strcat(newListNames, " ");
      strcat(newListNames, token);
    }
    token = strtok(NULL, " ");
  }

  free(listNamesCopy);
  free(*listNames);

  *listNames = newListNames;
}
