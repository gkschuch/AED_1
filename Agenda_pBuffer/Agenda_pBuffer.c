#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE sizeof(char) * 20
#define EMAIL_SIZE sizeof(char) * 30
#define AGE_SIZE sizeof(int)
#define PERSON_SIZE (NAME_SIZE + EMAIL_SIZE + AGE_SIZE)

#define INITIAL_SIZE ((sizeof(int) * 5) + PERSON_SIZE)
/*
    MEMORY LAYOUT:
    [offset 0]= (int*) pMenu
    [offset sizeof(int)]= (int*) pCount
    [offset sizeof(int)*2]= (int*) pI(para os loops)
    [offset sizeof(int)*3]= (int*) pJ(para os loops)
    [offset sizeof(int)*4]= (int*) pIndexFound
    [offset sizeof(int)*5] = buffer temporario dos nomes
*/

void menu();
// void addPerson(void *pBuffer);
// void removePerson(void *pBuffer);
// void searchPerson(void *pBuffer);
// void listAgenda(void *pBuffer);

int main() {
  void *pBuffer = malloc(INITIAL_SIZE);
  if (pBuffer == NULL) {
    printf("pBuffer: Memory Allocation failed\n");
    return 1;
  }
  while (1) {
    menu();
    printf("\nInsert a command: ");
    scanf("%d", (int *)pBuffer);
    switch (*(int *)pBuffer) {
    case 1:
      //   addPerson(pBuffer);
      break;
    case 2:
      //   removePerson(pBuffer);
      break;
    case 3:
      //   searchPerson(pBuffer);
      break;
    case 4:
      //   listAgenda(pBuffer);
      break;
    case 5:
      printf("CLOSING AGENDA...\n");
      free(pBuffer);
      printf("pBuffer: Memory freed\n");
      return 0;
      break;
    default:
      printf("ERROR: Unknown command\n");
      break;
    }
  }
}

void menu() {
  printf("-----------AGENDA pBuffer-----------\n\n");
  printf("\t1) ADD PERSON(NAME, EMAIL, AGE)\n");
  printf("\t2) REMOVE PERSON\n");
  printf("\t3) SEARCH PERSON (by name)\n");
  printf("\t4) LIST AGENDA\n");
  printf("\t5) QUIT\n");
}