#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap( int* a, int* b ) {
	int temp = *a;
	*a		 = *b;
	*b		 = temp;
}

void printArray( int arr[], int size ) {
	for( int i = 0; i < size; i++ ) {
		printf( "%d ", arr[i] );
	}
	printf( "\n" );
}

bool isSorted( int arr[], int size ) {
	for( int i = 0; i < size - 1; i++ ) {
		if( arr[i] > arr[i + 1] ) {
			return false;
		}
	}
	return true;
}
/* Helper function to generate an array with random values
 * Tests the "Aleatório" (Random) case
 */
void generateRandomArray( int arr[], int size, int max_value ) {
	srand( time( NULL ) ); /* Seed the random number generator */
	for( int i = 0; i < size; i++ ) {
		arr[i] = rand() % max_value;
	}
}

/* Helper function to generate an array in descending order
 * Tests the "Inverso" (Reverse) case
 */
void generateReverseArray( int arr[], int size ) {
	for( int i = 0; i < size; i++ ) {
		arr[i] = size - i;
	}
}

/* Helper function to generate an array with mostly the same values
 * Tests the "Valores repetidos" (Repeated values) case [cite: 130]
 */
void generateRepeatedValuesArray( int arr[], int size, int repeated_value ) {
	for( int i = 0; i < size; i++ ) {
		/* 90% chance of being the repeated value, 10% chance of being random */
		if( rand() % 10 != 0 ) {
			arr[i] = repeated_value;
		} else {
			arr[i] = rand() % 100;
		}
	}
}
void quickSort( int data[], int left, int right ) {
	int mid, i, j;

	i	= left;
	j	= right;
	mid = data[( left + right ) / 2];

	do {
		while( data[i] < mid )
			i++;
		while( mid < data[j] )
			j--;

		if( i <= j ) {
			swap( &data[i], &data[j] );
			i++;
			j--;
		}
	} while( i <= j );

	if( left < j )
		quickSort( data, left, j );
	if( i < right )
		quickSort( data, i, right );
}