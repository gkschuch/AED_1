#include <stdio.h>
#include <stdlib.h>

struct Node {
	int			 data;
	struct Node* next;
};

struct Node* merge( struct Node* left, struct Node* right ) {
	struct Node* result = NULL;

	if( left == NULL )
		return right;
	else if( right == NULL )
		return left;

	if( left->data <= right->data ) {
		result		 = left;
		result->next = merge( left->next, right );
	} else {
		result		 = right;
		result->next = merge( left, right->next );
	}

	return result;
}

void splitList( struct Node* source, struct Node** frontRef, struct Node** backRef ) {
	struct Node* fast;
	struct Node* slow;
	slow = source;
	fast = source->next;

	while( fast != NULL ) {
		fast = fast->next;
		if( fast != NULL ) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef  = slow->next;

	slow->next = NULL;
}

void mergeSort( struct Node** headRef ) {
	struct Node* head = *headRef;
	struct Node* left;
	struct Node* right;

	if( ( head == NULL ) || ( head->next == NULL ) ) {
		return;
	}

	splitList( head, &left, &right );

	mergeSort( &left );
	mergeSort( &right );

	*headRef = merge( left, right );
}

void push( struct Node** headRef, int newData ) {
	struct Node* newNode = ( struct Node* )malloc( sizeof( struct Node ) );
	newNode->data		 = newData;
	newNode->next		 = ( *headRef );
	( *headRef )		 = newNode;
}

void printList( struct Node* node ) {
	while( node != NULL ) {
		printf( "%d ", node->data );
		node = node->next;
	}
	printf( "\n" );
}

int main() {
	struct Node* head = NULL;

	push( &head, 10 );
	push( &head, 82 );
	push( &head, 9 );
	push( &head, 3 );
	push( &head, 43 );
	push( &head, 27 );
	push( &head, 38 );

	printf( "Original Linked List: \n" );
	printList( head );

	mergeSort( &head );

	printf( "Sorted Linked List: \n" );
	printList( head );

	return 0;
}