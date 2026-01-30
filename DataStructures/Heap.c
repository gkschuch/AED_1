#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
	int				  val;
	struct QueueNode* pNext;
} QueueNode;

typedef struct {
	QueueNode* pFirst;
	QueueNode* pLast;
} Queue;

Queue* CreateQueue( void );
void   Push( Queue* pQueue, int val );
bool   Pop( Queue* pQueue, int* pVal );
void   printQueue( Queue* pQueue );
void   DestroyQueue( Queue* pQueue );

int main() {
	Queue* myQueue = CreateQueue();
	int	   tempVal;

	printf( "Inserindo elementos fora de ordem...\n" );
	Push( myQueue, 10 );
	Push( myQueue, 50 ); // Prioridade alta
	Push( myQueue, 20 );
	Push( myQueue, 90 ); // Prioridade maxima
	Push( myQueue, 5 );

	// A lista deve aparecer ordenada: 90 -> 50 -> 20 -> 10 -> 5
	printQueue( myQueue );

	printf( "\nRemovendo (deve sair do maior para o menor):\n" );
	while( Pop( myQueue, &tempVal ) ) {
		printf( "Removed: %d\n", tempVal );
	}

	DestroyQueue( myQueue );
	return 0;
}

Queue* CreateQueue( void ) {
	Queue* newQueue = ( Queue* )malloc( sizeof( Queue ) );
	if( newQueue != NULL ) {
		newQueue->pFirst = NULL;
		newQueue->pLast	 = NULL;
	}
	return newQueue;
}

void Push( Queue* pQueue, int val ) {
	QueueNode* newNode = ( QueueNode* )malloc( sizeof( QueueNode ) );
	if( newNode == NULL )
		return;

	newNode->val   = val;
	newNode->pNext = NULL;

	if( pQueue->pFirst == NULL || val > pQueue->pFirst->val ) {
		newNode->pNext = pQueue->pFirst;
		pQueue->pFirst = newNode;

		if( pQueue->pLast == NULL )
			pQueue->pLast = newNode;
	} else {
		QueueNode* current = pQueue->pFirst;

		while( current->pNext != NULL && current->pNext->val >= val ) {
			current = current->pNext;
		}

		newNode->pNext = current->pNext;
		current->pNext = newNode;

		if( newNode->pNext == NULL )
			pQueue->pLast = newNode;
	}
}

bool Pop( Queue* pQueue, int* pVal ) {
	QueueNode* pNode;
	if( pQueue->pFirst == NULL ) {
		return false;
	}

	pNode = pQueue->pFirst;
	*pVal = pNode->val;

	pQueue->pFirst = pQueue->pFirst->pNext;

	if( pQueue->pFirst == NULL ) {
		pQueue->pLast = NULL;
	}

	free( pNode );
	return true;
}

void printQueue( Queue* pQueue ) {
	printf( "Priority Queue: " );
	if( pQueue->pFirst == NULL ) {
		printf( "Empty\n" );
		return;
	}
	for( QueueNode* pNode = pQueue->pFirst; pNode != NULL; pNode = pNode->pNext ) {
		printf( "[%d] -> ", pNode->val );
	}
	printf( "NULL\n" );
}

void DestroyQueue( Queue* pQueue ) {
	int trash;
	while( pQueue->pFirst != NULL ) {
		Pop( pQueue, &trash );
	}
	free( pQueue );
}