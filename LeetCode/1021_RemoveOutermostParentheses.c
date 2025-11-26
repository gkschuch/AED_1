#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int	  capacity;
	int	  top;
	char* characters;
} Stack;

Stack* createStack( int capacity ) {
	Stack* stack	  = ( Stack* )malloc( sizeof( Stack ) );
	stack->capacity	  = capacity;
	stack->top		  = -1;
	stack->characters = ( char* )malloc( stack->capacity * sizeof( char ) );
	return stack;
}

bool isEmpty( Stack* stack ) {
	return stack->top == -1;
}

bool isFull( Stack* stack ) {
	return stack->top == stack->capacity - 1;
}

bool pop( Stack* stack, char* pItem ) {
	if( isEmpty( stack ) )
		return false;
	*pItem = stack->characters[stack->top--];
	return true;
}

bool push( Stack* stack, char item ) {
	if( isFull( stack ) )
		return false;
	stack->characters[++stack->top] = item;
	return true;
}

void freeStack( Stack* stack ) {
	if( stack == NULL )
		return;
	if( isEmpty( stack ) ) {
		free( stack->characters );
		free( stack );
		return;
	}
	char dummyItem;
	pop( stack, &dummyItem );
	freeStack( stack );
}

char* removeOuterParentheses( char* s ) {
	int	   len	  = strlen( s );
	Stack* stack  = createStack( len );
	char*  result = ( char* )malloc( ( len + 1 ) * sizeof( char ) );
	int	   k	  = 0;
	for( int i = 0; i < len; i++ ) {
		char c = s[i];
		if( c == '(' ) {
			if( !isEmpty( stack ) )
				result[k++] = c;
			push( stack, c );
		} else { // c == ')'
			char temp;
			pop( stack, &temp );

			if( !isEmpty( stack ) )
				result[k++] = c;
		}
	}
	result[k] = '\0';
	freeStack( stack );
	return result;
}
int main() {
	char* string = "()()";

	printf( "%s\n", removeOuterParentheses( string ) );
}