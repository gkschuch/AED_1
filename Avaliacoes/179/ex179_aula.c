#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( int aNum, int bNum ) {
	char ab[32], ba[32];
	sprintf( ab, "%d%d", aNum, bNum );
	sprintf( ba, "%d%d", bNum, aNum );
	return strcmp( ba, ab );
}

void swap( int* a, int* b ) {
	int temp = *a;
	*a		 = *b;
	*b		 = temp;
}

void quickSort( int data[], int left, int right ) {
	int i, j, mid;

	i	= left;
	j	= right;
	mid = data[( left + right ) / 2];

	do {
		while( compare( data[i], mid ) < 0 )
			i++;

		while( compare( mid, data[j] ) < 0 )
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

char* largestNumber( int* nums, int numsSize ) {
	if( numsSize == 0 )
		return "";

	quickSort( nums, 0, numsSize - 1 );

	if( nums[0] == 0 ) {
		char* res = ( char* )malloc( 2 );
		strcpy( res, "0" );
		return res;
	}

	char* numberString = ( char* )malloc( numsSize * 15 + 1 );
	int	  offset	   = 0;
	for( int i = 0; i < numsSize; i++ ) {
		offset += sprintf( numberString + offset, "%d", nums[i] );
	}
	return numberString;
}