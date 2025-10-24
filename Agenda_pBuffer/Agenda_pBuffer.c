#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE sizeof(char) * 20
#define EMAIL_SIZE sizeof(char) * 30
#define AGE_SIZE sizeof(int)
#define PERSON_SIZE (NAME_SIZE + EMAIL_SIZE + AGE_SIZE)

#define INITIAL_SIZE ((sizeof(int) * 6) + PERSON_SIZE)
/*
        MEMORY LAYOUT:
    (int*)pBuffer + 0: pMenu
    (int*)pBuffer + 1: pCount
    (int*)pBuffer + 2: pCapacity
    (int*)pBuffer + 3: pI
    (int*)pBuffer + 4: pJ
    (int*)pBuffer + 5: pIndexFound
    Depois disso: Buffers temporários (PERSON_SIZE bytes)

    PERSON REGISTER LAYOUT:
    Name
    Email
    Age
*/

void menu();
void addPerson(void **pBufferPtr);
// void removePerson(void *pBuffer);
// void searchPerson(void *pBuffer);
// void listAgenda(void *pBuffer);

int main() {
  void *pBuffer = malloc(INITIAL_SIZE);
  if (pBuffer == NULL) {
    printf("pBuffer: Memory Allocation failed\n");
    return 1;
  }
  memset(pBuffer, 0, INITIAL_SIZE);

  *((int *)pBuffer + 1) = 0; // zera o contador de pessoas
  *((int *)pBuffer + 2) = 0; // zera a capacidade
  while (1) {
    menu();
    printf("\nInsert a command: ");
    scanf("%d", (int *)pBuffer);
    switch (*(int *)pBuffer) {
    case 1:
      addPerson(&pBuffer);
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

void addPerson(void **pBufferPtr) {
  void *pBuffer = *pBufferPtr;
  void *newBuffer;

  //     Count >= Capacity
  if (*((int *)pBuffer + 1) >= *((int *)pBuffer + 2)) {
    (*((int *)pBuffer + 2))++; // Capacity++;
    newBuffer = realloc(pBuffer,
                        INITIAL_SIZE + ((*((int *)pBuffer + 2)) * PERSON_SIZE));
    if (newBuffer == NULL) {
      printf("pBuffer: Error reallocating\n");
      (*((int *)pBuffer + 2))--; // Capacity--;
      return;
    }
    *pBufferPtr = newBuffer;
    pBuffer = newBuffer;
  }
  void *pTemp = ((int *)pBuffer + 6); // Avança até o campo buffers temporarios
                                      //   (Nome, email, e idade)
  printf("Person to add\n");
  printf("\tInsert Name: ");
  scanf(" %[^\n]", (char *)pTemp);
  printf("\tInsert Email: ");
  scanf(" %[^\n]", (char *)(pTemp + NAME_SIZE));
  printf("\tInsert Age: ");
  scanf(" %d", (int *)(pTemp + NAME_SIZE + EMAIL_SIZE));

  strcpy((char *)(pBuffer + INITIAL_SIZE +
                  ((*((int *)pBuffer + 1)) * PERSON_SIZE)),
         pTemp); // Copia Nome
  strcpy((char *)(pBuffer + INITIAL_SIZE +
                  ((*((int *)pBuffer + 1)) * PERSON_SIZE) + NAME_SIZE),
         pTemp + NAME_SIZE); // Copia Email
  *((int *)(pBuffer + INITIAL_SIZE + ((*((int *)pBuffer + 1)) * PERSON_SIZE) +
            NAME_SIZE + EMAIL_SIZE)) =
      *((int *)(pTemp + NAME_SIZE + EMAIL_SIZE));

  (*((int *)pBuffer + 1))++;
}