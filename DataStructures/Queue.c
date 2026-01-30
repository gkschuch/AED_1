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

	Push( myQueue, 10 );
	Push( myQueue, 20 );
	Push( myQueue, 30 );

	printQueue( myQueue );

	if( Pop( myQueue, &tempVal ) ) {
		printf( "Removed: %d\n", tempVal );
	}

	printQueue( myQueue );

	DestroyQueue( myQueue );
	return 0;
}

Queue* CreateQueue( void ) {
	Queue* newQueue	 = ( Queue* )malloc( sizeof( Queue ) );
	newQueue->pFirst = NULL;
	newQueue->pLast	 = NULL;
	return newQueue;
}

void Push( Queue* pQueue, int val ) {
	QueueNode* newNode = ( QueueNode* )malloc( sizeof( QueueNode ) );
	if( newNode == NULL )
		return;

	newNode->val   = val;
	newNode->pNext = NULL;

	if( pQueue->pLast != NULL ) {
		pQueue->pLast->pNext = newNode;
	} else {
		pQueue->pFirst = newNode;
	}

	pQueue->pLast = newNode;
}

bool Pop( Queue* pQueue, int* pVal ) {
	QueueNode* pNode;
	if( pQueue->pFirst == NULL ) {
		printf( "Empty Queue\n" );
		return false;
	}

	pNode = pQueue->pFirst;
	*pVal = pQueue->pFirst->val;

	pQueue->pFirst = pQueue->pFirst->pNext;

	if( pQueue->pFirst == NULL ) {
		pQueue->pLast = NULL;
	}

	free( pNode );

	return true;
}

void printQueue( Queue* pQueue ) {
	printf( "Queue: " );
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