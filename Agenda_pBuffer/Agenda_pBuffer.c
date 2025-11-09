#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20
#define EMAIL_SIZE 30

#define pMenu(pBuffer) ((int *)pBuffer)
#define pCount(pBuffer) ((int *)pBuffer + 1)
#define pI(pBuffer) ((int *)pBuffer + 2)
#define pJ(pBuffer) ((int *)pBuffer + 3)
#define pIndexFound(pBuffer) ((int *)pBuffer + 4)
#define pCapacity(pBuffer) ((int *)pBuffer + 5)
#define pUsed(pBuffer) ((int *)pBuffer + 6)
#define pTotalPersonSize(pBuffer) ((int *)pBuffer + 7)

#define HEADER_INT_COUNT (8)
#define HEADER_SIZE (sizeof(int) * HEADER_INT_COUNT)

#define pTempStart(pBuffer) ((void *)((int *)pBuffer + HEADER_INT_COUNT))
#define pTempName(pBuffer) ((char *)pTempStart(pBuffer))
#define pTempEmail(pBuffer) ((char *)pTempStart(pBuffer) + NAME_SIZE)
#define pTempAge(pBuffer) ((int *)((char *)pTempEmail(pBuffer) + EMAIL_SIZE))

#define TEMP_AREA_SIZE (NAME_SIZE + EMAIL_SIZE + sizeof(int))

#define DATA_START_OFFSET (HEADER_SIZE + TEMP_AREA_SIZE)

void menu();
void initBuffer(void **pBufferPtr);
void addPerson(void **pBufferPtr);
void removePerson(void *pBuffer);
void searchPerson(void *pBuffer);
void listAgenda(void *pBuffer);

int main() {
  void *pBuffer;

  initBuffer(&pBuffer);
  while (1) {
    menu();
    printf("\nInsert a command: ");
    scanf(" %d", pMenu(pBuffer));
    switch (*pMenu(pBuffer)) {
    case 1:
      addPerson(&pBuffer);
      break;
    case 2:
      removePerson(pBuffer);
      break;
    case 3:
      searchPerson(pBuffer);
      break;
    case 4:
      listAgenda(pBuffer);
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

void initBuffer(void **pBufferPtr) {
  *pBufferPtr =
      malloc(DATA_START_OFFSET); //  espaco para as variaveis estaticas

  // Verificação de falha do malloc
  if (*pBufferPtr == NULL) {
    printf("pBuffer: Memory Allocation failed\n");
    exit(1);
  }
  // Seta os valores iniciais
  *pCapacity(*pBufferPtr) =
      DATA_START_OFFSET;    // seta a capacidade inicial dos dados para 0
  *pCount(*pBufferPtr) = 0; // zera o contador de pessoas
  *pUsed(*pBufferPtr) =
      DATA_START_OFFSET; // local para o comeco da area de dados
  *pTotalPersonSize(*pBufferPtr) = 0;

  // Zera todos as variaveis de controle
  *(pMenu(*pBufferPtr)) = 0;
  *(pI(*pBufferPtr)) = 0;
  *(pJ(*pBufferPtr)) = 0;
  *(pIndexFound(*pBufferPtr)) = 0;
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

  printf("Person to add\n");
  printf("\tInsert Name: ");
  scanf(" %[^\n]",
        pTempName(pBuffer)); // Armazena no espaco temporario a string do nome
  printf("\tInsert Email: ");
  scanf(" %[^\n]",
        pTempEmail(pBuffer)); // Armazena no espaco temporario a string do email
  printf("\tInsert Age: ");
  scanf(" %d", pTempAge(pBuffer)); // Armazena no espaco temporario a idade

  //  Layout Calculo: TAMANHO NOME(+ \0) + TAMNHO EMAIL(+ \0) + TAMNHO INTEIRO
  *pTotalPersonSize(pBuffer) = (strlen(pTempName(pBuffer)) + 1) +
                               (strlen(pTempEmail(pBuffer)) + 1) + sizeof(int);

  if (*pUsed(pBuffer) + *pTotalPersonSize(pBuffer) > *pCapacity(pBuffer)) {
    *pCapacity(pBuffer) = *pUsed(pBuffer) + *pTotalPersonSize(pBuffer);

    newBuffer = realloc(pBuffer, *pCapacity(pBuffer));

    // Verificação de falha do realloc
    if (newBuffer == NULL) {
      printf("pBuffer: Memory Reallocation Failed.");
      return;
    }
    *pBufferPtr = newBuffer;
    pBuffer = newBuffer;
  }
  // Copia do nome
  memcpy((char *)pBuffer + *pUsed(pBuffer), pTempName(pBuffer),
         strlen(pTempName(pBuffer)) + 1);
  *pUsed(pBuffer) += strlen(pTempName(pBuffer)) + 1;

  // Copia do email
  memcpy((char *)pBuffer + *pUsed(pBuffer), pTempEmail(pBuffer),
         strlen(pTempEmail(pBuffer)) + 1);
  *pUsed(pBuffer) += strlen(pTempEmail(pBuffer)) + 1;

  // Copia da idade
  memcpy((char *)pBuffer + *pUsed(pBuffer), pTempAge(pBuffer), sizeof(int));
  *pUsed(pBuffer) += sizeof(int);

  (*pCount(pBuffer))++;
}

void removePerson(void *pBuffer) {
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  void *pTemp = ((int *)pBuffer + 6);
  printf("\tInsert Name: ");
  scanf(" %[^\n]", (char *)pTemp);

  *((int *)pBuffer + 5) = -1; // pIndexFound = -1;
  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; *pI(pBuffer) < *pCount(pBuffer); (*pI(pBuffer))++) {
    if (strcmp((char *)pTemp, (char *)(pBuffer + INITIAL_SIZE +
                                       ((*pI(pBuffer)) * PERSON_SIZE))) == 0) {
      *((int *)pBuffer + 5) = *pI(pBuffer); // pIndexFound = pI;
      break;
    }
  }
  if ((*((int *)pBuffer + 5)) == -1) {
    printf("ERROR: %s not found\n", (char *)pTemp);
    return;
  }

  for (*pI(pBuffer) = *((int *)pBuffer + 5);
       *pI(pBuffer) < *pCount(pBuffer) - 1; (*pI(pBuffer))++) {
    void *pDestination =
        (void *)(pBuffer + INITIAL_SIZE + ((*pI(pBuffer)) * PERSON_SIZE));
    *pJ(pBuffer) = (*pI(pBuffer)) + 1;

    void *pOrigin =
        (void *)(pBuffer + INITIAL_SIZE + ((*pJ(pBuffer)) * PERSON_SIZE));

    memcpy(pDestination, pOrigin, PERSON_SIZE);
  }
  (*pCount(pBuffer))--;
  printf("SUCCESS: %s was removed.\n", (char *)pTemp);
}

void searchPerson(void *pBuffer) {
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  void *pTemp = ((int *)pBuffer + 6);
  printf("\tInsert Name: ");
  scanf(" %[^\n]", (char *)pTemp);

  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; *pI(pBuffer) < *pCount(pBuffer); (*pI(pBuffer))++) {
    if (strcmp((char *)pTemp, (char *)(pBuffer + INITIAL_SIZE +
                                       ((*pI(pBuffer)) * PERSON_SIZE))) == 0) {
      printf("Name: ");
      printf("%s\n",
             (char *)(pBuffer + INITIAL_SIZE + ((*pI(pBuffer)) * PERSON_SIZE)));
      printf("E-mail: ");
      printf("%s\n", (char *)(pBuffer + INITIAL_SIZE +
                              ((*pI(pBuffer)) * PERSON_SIZE) + NAME_SIZE));
      printf("Age: ");
      printf("%d\n",
             *((int *)(pBuffer + INITIAL_SIZE + ((*pI(pBuffer)) * PERSON_SIZE) +
                       NAME_SIZE + EMAIL_SIZE)));
      printf("\n");
      return;
    }
  }
  printf("ERROR: %s not found\n", (char *)pTemp);
}
void listAgenda(void *pBuffer) {
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  void *pReader = (char *)pBuffer + DATA_START_OFFSET;
  printf("\t AGENDA LIST (%d)\n", *pCount(pBuffer));
  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; (*pI(pBuffer)) < *pCount(pBuffer); (*pI(pBuffer))++) {
    printf("Name: %s\n", (char *)pReader);

    // Pula o Tamanho do Nome + \0
    pReader = pReader + strlen((char *)pReader) + 1;
    printf("Email: %s\n", (char *)pReader);

    // Pula o Tamanho do Email + \0
    pReader = pReader + strlen((char *)pReader) + 1;
    printf("Age: %d\n", *((int *)pReader));
    printf("\n");
    // Pula o tamanho do inteiro para o nome
    pReader = pReader + sizeof(int);
  }
}