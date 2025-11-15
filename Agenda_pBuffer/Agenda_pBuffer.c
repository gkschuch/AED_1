#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao do espaco para os buffers temporarios para o nome e email
#define NAME_SIZE 20
#define EMAIL_SIZE 30

// MACROS para as variaveis do tipo inteiro para controle
#define MENU( pBuffer ) ( ( int* )( pBuffer ) )
#define COUNT( pBuffer ) ( ( int* )pBuffer + 1 )
#define I( pBuffer ) ( ( int* )pBuffer + 2 )
#define USED_DATA( pBuffer ) ( ( int* )pBuffer + 3 )
#define TOTAL_PERSON_SIZE( pBuffer ) ( ( int* )pBuffer + 4 )

#define INT_COUNT ( 5 )
// definicao para o espaco das variaveis inteiras de controle
#define INT_AREA_SIZE ( sizeof( int ) * INT_COUNT )

// MACROS para os buffers temporarios(nome email e idade)
#define TEMP_START( pBuffer ) ( ( void* )( ( int* )pBuffer + INT_COUNT ) )
#define TEMP_NAME( pBuffer ) ( ( char* )TEMP_START( pBuffer ) )
#define TEMP_EMAIL( pBuffer ) ( ( char* )TEMP_START( pBuffer ) + NAME_SIZE )
#define TEMP_AGE( pBuffer ) ( ( int* )( ( char* )TEMP_EMAIL( pBuffer ) + EMAIL_SIZE ) )

// definicao para o espaco das variaveis temporarias
#define TEMP_AREA_SIZE ( NAME_SIZE + EMAIL_SIZE + sizeof( int ) )

// Comeco da area de armazenagem de dados
#define DATA_START_AREA ( INT_AREA_SIZE + TEMP_AREA_SIZE )

// Definicao dos prototipos das funcoes

void menu( void* pBuffer );
void initBuffer( void** pBufferPtr );

void addPerson( void** pBufferPtr );
void removePerson( void** pBufferPtr );
void searchPerson( void* pBuffer );
void listAgenda( void* pBuffer );

// Funcao auxiliar para  mover para o proximo registro
void moveToNextPerson( char** pCurrentPersonPtr );

int main() {
	void* pBuffer;

	initBuffer( &pBuffer );
	while( 1 ) {
		menu( pBuffer );
		switch( *MENU( pBuffer ) ) {
		case 1:
			addPerson( &pBuffer );
			break;
		case 2:
			removePerson( &pBuffer );
			break;
		case 3:
			searchPerson( pBuffer );
			break;
		case 4:
			listAgenda( pBuffer );
			break;
		case 5:
			printf( "CLOSING AGENDA...\n" );
			free( pBuffer );
			printf( "pBuffer: Memory freed\n" );
			return 0;
		}
	}
}

void initBuffer( void** pBufferPtr ) {
	*pBufferPtr = calloc( 1, DATA_START_AREA ); //  espaco para as variaveis de controle e o buffer temporario
	// Utilizacao do calloc, por causa que ele ja zera todos os bytes dele

	if( *pBufferPtr == NULL ) {
		printf( "pBuffer: Memory Allocation failed\n" );
		exit( 1 );
	}
	*USED_DATA( *pBufferPtr ) = DATA_START_AREA; // local para o comeco da area de dados
}

void menu( void* pBuffer ) {
	do {
		printf( "-----------AGENDA pBuffer-----------\n\n" );
		printf( "\t1) ADD PERSON(NAME, EMAIL, AGE)\n" );
		printf( "\t2) REMOVE PERSON\n" );
		printf( "\t3) SEARCH PERSON (by name)\n" );
		printf( "\t4) LIST AGENDA\n" );
		printf( "\t5) QUIT\n" );
		printf( "\nInsert a command: " );
		scanf( " %d", MENU( pBuffer ) );
	} while( *MENU( pBuffer ) < 1 || *MENU( pBuffer ) > 5 );
}

void addPerson( void** pBufferPtr ) {
	void* pBuffer = *pBufferPtr;
	void* newBuffer;

	printf( "Person to add\n" );
	printf( "\tInsert Name: " );
	scanf( " %[^\n]", TEMP_NAME( pBuffer ) );
	printf( "\tInsert Email: " );
	scanf( " %[^\n]", TEMP_EMAIL( pBuffer ) );
	printf( "\tInsert Age: " );
	scanf( " %d", TEMP_AGE( pBuffer ) );

	//  Layout Calculo:               TAMANHO NOME(+ \0) +                     TAMNHO EMAIL(+ \0) +                   TAMNHO INTEIRO
	*TOTAL_PERSON_SIZE( pBuffer ) = ( strlen( TEMP_NAME( pBuffer ) ) + 1 ) + ( strlen( TEMP_EMAIL( pBuffer ) ) + 1 ) + sizeof( int );

	// Realloc para o novo espaco, com o espaco para armazenar 1 pessoa
	newBuffer = realloc( pBuffer, *USED_DATA( pBuffer ) + *TOTAL_PERSON_SIZE( pBuffer ) );

	// Verificação de falha do realloc
	if( newBuffer == NULL ) {
		printf( "pBuffer: Memory Reallocation Failed." );
		return;
	}
	// Acerta os ponteiros
	*pBufferPtr = newBuffer;
	pBuffer		= newBuffer;

	/*
	LAYOUT DE ARMAZENAMENTO: NOME | E-MAIL | IDADE
	LOGICA PARA AS COPIAS:
	Vou ate a ultimo byte armazenado(USED_DATA), copio o nome temporario
	Depois eu atualizo o USED_DATA(para conter ja a quantidade do nome), para o email,
	depois faco a mesma coisa com email, para eu armazenar a idade, e pulo para o final da do inteiro
	*/

	//            Destino                                origem                    numero de bytes
	memcpy( ( char* )pBuffer + *USED_DATA( pBuffer ), TEMP_NAME( pBuffer ), strlen( TEMP_NAME( pBuffer ) ) + 1 );
	//  USED_DATA = USED_DATA + tamanho do nome + \0
	*USED_DATA( pBuffer ) += strlen( TEMP_NAME( pBuffer ) ) + 1;

	//            Destino                                origem                    numero de bytes
	memcpy( ( char* )pBuffer + *USED_DATA( pBuffer ), TEMP_EMAIL( pBuffer ), strlen( TEMP_EMAIL( pBuffer ) ) + 1 );
	//  USED_DATA = USED_DATA + tamanho do email + \0
	*USED_DATA( pBuffer ) += strlen( TEMP_EMAIL( pBuffer ) ) + 1;

	//            Destino                                origem                    numero de bytes
	memcpy( ( char* )pBuffer + *USED_DATA( pBuffer ), TEMP_AGE( pBuffer ), sizeof( int ) );
	//  USED_DATA = USED_DATA + tamanho do inteiro
	*USED_DATA( pBuffer ) += sizeof( int );

	// Incrementa a quantidade de pessoas
	( *COUNT( pBuffer ) )++;
}

void removePerson( void** pBufferPtr ) {
	void* pBuffer = *pBufferPtr;
	void* newBuffer;
	// Testa se a agenda esta vazia
	if( *COUNT( pBuffer ) == 0 ) {
		printf( "ERROR: Agenda is empty\n" );
		return;
	}
	// Insere o nome para remover
	printf( "\tInsert Name: " );
	scanf( " %[^\n]", TEMP_NAME( pBuffer ) );

	//  Cria os ponteiros
	char* pReader	= pBuffer + DATA_START_AREA; // Ponteiro para percorrer a lista
	char* pMoveTo	= NULL;						 // Ponteiro para o destino(Pessoa que eu quero remover)
	char* pMoveFrom = NULL;						 // Ponteiro para a origem(Pessoa seguinte da que eu quero remover)

	for( *I( pBuffer ) = 0; *I( pBuffer ) < *COUNT( pBuffer ); ( *I( pBuffer ) )++ ) {
		// Acha a proximo endereco para a origem e sai do loop
		if( pMoveTo != NULL && pMoveFrom == NULL ) {
			pMoveFrom = pReader;
			break;
		}
		// Teste para encontrar o nome que eu quero remover
		if( pMoveTo == NULL && strcmp( TEMP_NAME( pBuffer ), pReader ) == 0 ) {
			pMoveTo = pReader; //

			//O tamanho da pessoa(para o realloc)  = Tamanho nome     +             Tamanho do E-mail                         +  Tamanho da Idade(inteiro)
			*TOTAL_PERSON_SIZE( pBuffer ) = ( strlen( pReader ) + 1 ) + ( strlen( pReader + ( strlen( pReader ) + 1 ) ) + 1 ) + sizeof( int );
		}

		// Avança o leitor para o próximo registro
		moveToNextPerson( &pReader );
	}
	//Teste para ver se encontrou o nome na agenda
	if( pMoveTo == NULL ) {
		printf( "ERROR: %s not found\n", TEMP_NAME( pBuffer ) );
		return;
	}

	if( pMoveFrom != NULL ) {
		// Endereco do final de toda a area de dados
		char* pEnd = ( char* )pBuffer + *USED_DATA( pBuffer );
		// Ele move toda a parte seguinte ao nome que eu quero remover(pMoveFrom ate pEnd)
		// para a posicao do nome que eu quero remover(pMoveTo)
		memmove( pMoveTo, pMoveFrom, pEnd - pMoveFrom );
		// Usa o memmove por causa que as areas da memoria de origem e destino vao se sobrepor
	}
	// Diminuo dos bytes usados o tamanho da pessoa removida
	*USED_DATA( pBuffer ) -= *TOTAL_PERSON_SIZE( pBuffer );
	( *COUNT( pBuffer ) )--; //Decremento da quantidade de pesoas

	// Realloc para o novo tamanho(sem a pessoa removida)
	newBuffer = realloc( pBuffer, *USED_DATA( pBuffer ) );

	if( newBuffer == NULL ) {
		printf( "WARN: realloc to shrink failed, but data is safe.\n" );
	} else {
		// Só atualiza os ponteiros e capacidade se o realloc for bem-sucedido
		*pBufferPtr = newBuffer;
		pBuffer		= newBuffer;
	}

	printf( "SUCCESS: %s was removed.\n", TEMP_NAME( pBuffer ) );
}

void searchPerson( void* pBuffer ) {
	//   Check if COUNT is equal to 0
	if( *COUNT( pBuffer ) == 0 ) {
		printf( "ERROR: Agenda is empty\n" );
		return;
	}
	printf( "\tInsert Name: " );
	scanf( " %[^\n]", TEMP_NAME( pBuffer ) );
	//  Criar um ponteiro para percorrer pela os dados
	char* pReader = pBuffer + DATA_START_AREA;

	// loop para percorrer todas as pessoas na agenda
	for( *I( pBuffer ) = 0; *I( pBuffer ) < *COUNT( pBuffer ); ( *I( pBuffer ) )++ ) {
		// Teste para ver se o nome que eu quero buscar esta na agenda
		// Se estiver ele printa os dados da pessoa
		if( strcmp( TEMP_NAME( pBuffer ), pReader ) == 0 ) {
			char* pName	 = pReader;
			char* pEmail = pName + strlen( pName ) + 1;
			char* pAge	 = pEmail + strlen( pEmail ) + 1;

			// Imprime os dados usando os ponteiros locais
			printf( "Name: %s\n", pName );
			printf( "Email: %s\n", pEmail );
			printf( "Age: %d\n", *( ( int* )pAge ) );
			printf( "\n" );
			return;
		}
		// Pula para a proxima registro
		moveToNextPerson( &pReader );
	}
	// Se percorer toda a agenda e nao enocontrar printa que nao foi encontrado na agenda
	printf( "ERROR: %s not found\n", TEMP_NAME( pBuffer ) );
}

void listAgenda( void* pBuffer ) {
	//   Testa se a agenda esta vazia
	if( *COUNT( pBuffer ) == 0 ) {
		printf( "ERROR: Agenda is empty\n" );
		return;
	}
	//  Criar um ponteiro para percorrer pela os dados
	char* pReader = pBuffer + DATA_START_AREA;
	printf( "\t AGENDA LIST (%d)\n", *COUNT( pBuffer ) );

	// loop para percorrer todas as pessoas na agenda
	for( *I( pBuffer ) = 0; ( *I( pBuffer ) ) < *COUNT( pBuffer ); ( *I( pBuffer ) )++ ) {
		// Define ponteiros locais para cada campo da pessoa
		char* pName	 = pReader;
		char* pEmail = pName + strlen( pName ) + 1;
		char* pAge	 = pEmail + strlen( pEmail ) + 1;

		// Imprime os dados usando os ponteiros locais
		printf( "Name: %s\n", pName );
		printf( "Email: %s\n", pEmail );
		printf( "Age: %d\n", *( ( int* )pAge ) );
		printf( "\n" );

		moveToNextPerson( &pReader );
	}
}

void moveToNextPerson( char** pCurrentPersonPtr ) {
	char* pPerson = *pCurrentPersonPtr;
	//Avança sobre o Nome (string + '\0')
	pPerson += strlen( pPerson ) + 1;

	//Avança sobre o E-mail (string + '\0')
	pPerson += strlen( pPerson ) + 1;

	//Avança sobre a Idade (int)
	pPerson += sizeof( int );

	//Atualiza o ponteiro original
	*pCurrentPersonPtr = pPerson;
}