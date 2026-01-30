#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int	 ra;
	char name[50];
} Student;
typedef struct Node {
	Student		 data;
	struct Node* pNext;
} Node;

typedef struct {
	Node* top;
} Stack;

void Reset( Stack* stack );
bool Empty( Stack* stack );
bool Full();
bool Push( Stack* stack, Student* student );
void Pop( Stack* stack, Student* student );
void ListStack( Stack* stack );

int main() {
	Stack	stack;
	Student studentToAdd;

	Reset( &stack );

	printf( "Is It empty? %s\n", Empty( &stack ) ? "true" : "false" );
	printf( "Is It full? %s\n", Full() ? "true" : "false" );

	for( int i = 0; i < 5; i++ ) {
		printf( "\n--- Student %d ---\n", i + 1 );
		printf( "Name: " );
		scanf( " %49s", studentToAdd.name );
		printf( "RA: " );
		scanf( " %d", &studentToAdd.ra );

		if( !Push( &stack, &studentToAdd ) ) {
			fprintf( stderr, "Erro fatal de memória (malloc falhou).\n" );
			break;
		}
	}

	printf( "\nIs It empty? %s\n", Empty( &stack ) ? "true" : "false" );

	printf( "\nListing Stack (and emptying it):\n" );
	ListStack( &stack );
	return 0;
}

void Reset( Stack* pStack ) {
	pStack->top = NULL;
}

bool Empty( Stack* stack ) {
	return stack->top == NULL;
}

bool Full() {
	return false;
}

bool Push( Stack* pStack, Student* student ) {
	Node* newNode = ( Node* )malloc( sizeof( Node ) );
	if( newNode == NULL ) {
		printf( "ERROR: Failed Allocating new Node\n" );
		return false;
	}
	newNode->data = *student;

	newNode->pNext = pStack->top;
	pStack->top	   = newNode;
	return true;
}

void Pop( Stack* pStack, Student* student ) {
	if( Empty( pStack ) )
		return;
	Node* tempNode = pStack->top;
	*student	   = tempNode->data;
	pStack->top	   = tempNode->pNext;
	free( tempNode );
}

void ListStack( Stack* pStack ) {
	while( !Empty( pStack ) ) {
		Student s;
		Pop( pStack, &s );
		printf( "RA: %d - Name: %s\n", s.ra, s.name );
	}
}