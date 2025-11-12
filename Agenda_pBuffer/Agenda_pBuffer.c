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
void removePerson(void **pBufferPtr);
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
      removePerson(&pBuffer);
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

  // Checa se a quantidadade de bytes usados(pUSed) + o total de bytes usados
  // para armazenar a pessoa(pTotalPersonSize) e maior que a
  // capacidade total do pBuffer(pCapacity)
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

void removePerson(void **pBufferPtr) {
  void *pBuffer = *pBufferPtr;
  void *newBuffer;
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  printf("\tInsert Name: ");
  scanf(" %[^\n]", pTempName(pBuffer));

  *pIndexFound(pBuffer) = -1; // pIndexFound = -1;
  char *pReader = pBuffer + DATA_START_OFFSET;
  char *pDestination = NULL;
  char *pOrigin = NULL;
  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; *pI(pBuffer) < *pCount(pBuffer); (*pI(pBuffer))++) {
    if (*pIndexFound(pBuffer) && strcmp(pTempName(pBuffer), pReader) == 0) {
      *pIndexFound(pBuffer) = *pI(pBuffer); // pIndexFound = pI;
      pDestination = pReader;
      // Tamanho do nome + tamanho do email(pReader move ate acabar o tamanho
      // nome) + sizeof(int)
      *pTotalPersonSize(pBuffer) =
          (strlen(pReader) + 1) +
          (strlen(pReader + (strlen(pReader) + 1)) + 1) + sizeof(int);
    }
    // Acha a proxima pessoa
    if (*pI(pBuffer) == *pIndexFound(pBuffer) + 1) {
      pOrigin = pReader;
    }

    pReader += strlen(pReader) + 1;
    pReader += strlen(pReader) + 1;
    pReader += sizeof(int);
  }

  if (*pIndexFound(pBuffer) == -1) {
    printf("ERROR: %s not found\n", pTempName(pBuffer));
    return;
  }
  char *pFim = (char *)pBuffer + *pUsed(pBuffer);
  if ((pFim - pOrigin) > 0) {
    memmove(pDestination, pOrigin, pFim - pOrigin);
  }
  *pUsed(pBuffer) -= *pTotalPersonSize(pBuffer);
  (*pCount(pBuffer))--;
  newBuffer = realloc(pBuffer, *pUsed(pBuffer));
  if (newBuffer == NULL) {
    printf("WARN: realloc to shrink failed, but data is safe.\n");
  } else {
    *pBufferPtr = newBuffer;
    pBuffer = newBuffer;
    *pCapacity(pBuffer) = *pUsed(pBuffer);
  }

  printf("SUCCESS: %s was removed.\n", pTempName(pBuffer));
}

void searchPerson(void *pBuffer) {
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  printf("\tInsert Name: ");
  scanf(" %[^\n]", pTempName(pBuffer));

  char *pReader = pBuffer + DATA_START_OFFSET;
  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; *pI(pBuffer) < *pCount(pBuffer); (*pI(pBuffer))++) {
    if (strcmp(pTempName(pBuffer), pReader) == 0) {
      printf("Name: %s\n", pReader);

      // Pula o Tamanho do Nome + \0
      pReader = pReader + strlen(pReader) + 1;
      printf("Email: %s\n", pReader);

      // Pula o Tamanho do Email + \0
      pReader = pReader + strlen(pReader) + 1;
      printf("Age: %d\n", *((int *)pReader));
      printf("\n");
      // Pula o tamanho do inteiro para o nome
      pReader = pReader + sizeof(int);
      return;
    }
    pReader += strlen(pReader) + 1;
    pReader += strlen(pReader) + 1;
    pReader += sizeof(int);
  }
  printf("ERROR: %s not found\n", pTempName(pBuffer));
}
void listAgenda(void *pBuffer) {
  //   Check if pCount is equal to 0
  if (*pCount(pBuffer) == 0) {
    printf("ERROR: Agenda is empty\n");
    return;
  }
  char *pReader = pBuffer + DATA_START_OFFSET;
  printf("\t AGENDA LIST (%d)\n", *pCount(pBuffer));
  //   for(int i = 0; i< count;i++);
  for (*pI(pBuffer) = 0; (*pI(pBuffer)) < *pCount(pBuffer); (*pI(pBuffer))++) {
    printf("Name: %s\n", pReader);

    // Pula o Tamanho do Nome + \0
    pReader += strlen(pReader) + 1;
    printf("Email: %s\n", pReader);

    // Pula o Tamanho do Email + \0
    pReader += strlen(pReader) + 1;
    printf("Age: %d\n", *((int *)pReader));
    printf("\n");
    // Pula o tamanho do inteiro para o nome
    pReader += sizeof(int);
  }
}