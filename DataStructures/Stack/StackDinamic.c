#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int	 ra;
	char name[50];
} Student;

typedef struct {
	Student* students;
	int		 top;
	int		 limit;
} Stack;

void Reset( Stack* stack );
bool Empty( Stack* stack );
bool Full( Stack* stack );
bool Push( Stack* stack, Student* student );
void Pop( Stack* stack, Student* student );
void ListStack( Stack* stack );

int main( int argc, char const* argv[] ) {
	Stack	stack;
	Student studentToAdd;
	Reset( &stack );

	printf( "Is It empty? %s\n", Empty( &stack ) ? "true" : "false" );
	printf( "Is It full? %s\n", Full( &stack ) ? "true" : "false" );

	for( int i = 0; i < 5; i++ ) {
		printf( "\n--- Student %d ---\n", i + 1 );
		printf( "Name: " );
		scanf( " %49s", studentToAdd.name );
		printf( "RA: " );
		scanf( " %d", &studentToAdd.ra );

		if( !Push( &stack, &studentToAdd ) ) {
			fprintf( stderr, "Erro fatal de memória.\n" );
			break;
		}
	}

	printf( "\nIs It empty? %s\n", Empty( &stack ) ? "true" : "false" );

	printf( "\nListing Stack (and emptying it):\n" );
	ListStack( &stack );

	free( stack.students );

	return 0;
}

void Reset( Stack* stack ) {
	stack->students = NULL;
	stack->limit	= 0;
	stack->top		= 0;
}

bool Empty( Stack* stack ) {
	return stack->top == 0;
}

bool Full( Stack* stack ) {
	return false;
}

bool Push( Stack* stack, Student* student ) {
	if( stack->top == stack->limit ) {

		int newLimit = ( stack->limit == 0 ) ? 1 : stack->limit + 1;

		Student* temp = ( Student* )realloc( stack->students, newLimit * sizeof( Student ) );

		if( temp == NULL ) {
			printf( "Erro: Failed Reallocating!\n" );
			return false;
		}
		stack->students = temp;
		stack->limit	= newLimit;
	}

	stack->students[stack->top] = *student;
	stack->top++;

	return true;
}

void Pop( Stack* stack, Student* student ) {
	if( Empty( stack ) )
		return;

	stack->top--;
	*student = stack->students[stack->top];
}

void ListStack( Stack* stack ) {
	while( !Empty( stack ) ) {
		Student s;
		Pop( stack, &s );
		printf( "RA: %d - Name: %s\n", s.ra, s.name );
	}
}