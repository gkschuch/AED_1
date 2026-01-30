#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
	int	 ra;
	char name[50];
} Student;

typedef struct {
	Student students[MAX];
	int		top;
	int		base;
	int		limit;
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

	for( int i = 0; i < MAX; i++ ) {
		printf( "\n--- Student %d ---\n", i + 1 );
		printf( "Name: " );
		scanf( " %49s", studentToAdd.name );
		printf( "RA: " );
		scanf( " %d", &studentToAdd.ra );
		Push( &stack, &studentToAdd );
	}

	printf( "\nIs It empty? %s\n", Empty( &stack ) ? "true" : "false" );
	printf( "Is It full? %s\n", Full( &stack ) ? "true" : "false" );

	printf( "\nListing Stack (and emptying it):\n" );
	ListStack( &stack );

	return 0;
}

void Reset( Stack* stack ) {
	stack->limit = MAX;
	stack->base	 = 0;
	stack->top	 = 0;
}

bool Empty( Stack* stack ) {
	return stack->top == 0;
}

bool Full( Stack* stack ) {
	return stack->top == MAX;
}

bool Push( Stack* stack, Student* student ) {
	if( !Full( stack ) ) {
		stack->students[stack->top] = *student;
		stack->top++;
		return true;
	}
	return false;
}

void Pop( Stack* stack, Student* student ) {
	if( stack->top == 0 )
		return;
	stack->top--;
	*student = stack->students[stack->top];
}

void ListStack( Stack* stack ) {
	while( !Empty( stack ) ) {
		Student student;
		Pop( stack, &student );
		printf( "%d - %s\n", student.ra, student.name );
	}
}