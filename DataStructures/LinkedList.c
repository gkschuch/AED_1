#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int			 data;
	struct node* pNext;
} Node;

typedef struct {
	Node* pFirst;
} LinkedList;

void Reset( LinkedList* pList );
bool Push( LinkedList* pList, int data, unsigned int nIndex );
bool Pop( LinkedList* pList, Node** pNode, unsigned int nIndex );
void ListLinkedList( LinkedList* pList );

int main( int argc, char const* argv[] ) {
	LinkedList list;
	Reset( &list );

	Push( &list, 10, 0 );
	Push( &list, 20, 1 );
	Push( &list, 15, 1 );

	printf( "List: " );
	ListLinkedList( &list );

	Node* removedNode = NULL;
	if( Pop( &list, &removedNode, 1 ) ) {
		printf( "\nRemoved: %d", removedNode->data );
		free( removedNode );
	}

	printf( "\nFinal List: " );
	ListLinkedList( &list );

	return 0;
}

void Reset( LinkedList* pList ) {
	pList->pFirst = NULL;
}

bool Push( LinkedList* pList, int data, unsigned int nIndex ) {
	Node *pNewNode, *pCurrent, *pPrior;

	pNewNode		= ( Node* )malloc( sizeof( Node ) );
	pNewNode->data	= data;
	pNewNode->pNext = NULL;

	if( nIndex == 0 ) {
		pNewNode->pNext = pList->pFirst;
		pList->pFirst	= pNewNode;
		return true;
	}

	pCurrent = pList->pFirst;
	pPrior	 = NULL;
	int i	 = 0;

	while( i < nIndex && pCurrent != NULL ) {
		pPrior	 = pCurrent;
		pCurrent = pCurrent->pNext;
		i++;
	}

	if( i != nIndex ) {
		free( pNewNode );
		return false;
	}
	pPrior->pNext	= pNewNode;
	pNewNode->pNext = pCurrent;

	return true;
}

bool Pop( LinkedList* pList, Node** pNode, unsigned int nIndex ) {
	Node *pCurrent, *pPrior;

	if( pList->pFirst == NULL )
		return false;

	if( nIndex == 0 ) {
		*pNode		  = pList->pFirst;
		pList->pFirst = pList->pFirst->pNext;
		return true;
	}

	pCurrent = pList->pFirst;
	pPrior	 = NULL;
	int i	 = 0;

	while( i < nIndex && pCurrent != NULL ) {
		pPrior	 = pCurrent;
		pCurrent = pCurrent->pNext;
		i++;
	}

	if( !pCurrent )
		return false;

	pPrior->pNext = pCurrent->pNext;
	*pNode		  = pCurrent;

	return true;
}

void ListLinkedList( LinkedList* pList ) {
	Node* pCurrent = pList->pFirst;
	while( pCurrent != NULL ) {
		printf( "[%d] -> ", pCurrent->data );
		pCurrent = pCurrent->pNext;
	}
	printf( "NULL\n" );
}