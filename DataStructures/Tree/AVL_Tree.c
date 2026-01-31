#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// Function Prototypes
int		  height( TreeNode* pRoot );
int		  balanceFactor( TreeNode* pRoot );
void	  SLR( TreeNode** pRoot ); // Single Left Rotation (RR Case)
void	  SRR( TreeNode** pRoot ); // Single Right Rotation (LL Case)
int		  balanceLeft( TreeNode** pRoot );
int		  balanceRight( TreeNode** pRoot );
int		  balance( TreeNode** pRoot );
int		  insertNode( TreeNode** pRoot, int val );
int		  deleteNode( TreeNode** pRoot, int val );
int		  isAVLtree( TreeNode* root );
void	  printInOrder( TreeNode* root );
TreeNode* getMinValueNode( TreeNode* node );

int main() {
	srand( time( 0 ) );
	TreeNode* root	   = NULL;
	int		  numNodes = 5;
	int		  insertedValues[5]; // Array to keep track of what we added

	printf( "--- Phase 1: Insertion ---\n" );
	printf( "Inserting: " );
	for( int i = 0; i < numNodes; i++ ) {
		int randomNumber  = rand() % 100;
		insertedValues[i] = randomNumber; // Store the value for later deletion
		printf( "%d ", randomNumber );
		insertNode( &root, randomNumber );
	}

	printf( "\nIn-order Traversal: " );
	printInOrder( root );
	printf( "\nIs it a valid AVL tree? %s\n", isAVLtree( root ) ? "YES" : "NO" );

	printf( "\n--- Phase 2: Deletion ---\n" );
	// Let's delete the first value we inserted (often the root or near it)
	int target = insertedValues[0];
	printf( "Deleting node with value: %d\n", target );

	if( deleteNode( &root, target ) ) {
		printf( "Node %d deleted successfully.\n", target );
	} else {
		printf( "Value %d not found in tree.\n", target );
	}

	printf( "In-order Traversal (after deletion): " );
	printInOrder( root );

	printf( "\nIs it still a valid AVL tree? %s\n", isAVLtree( root ) ? "YES" : "NO" );

	return 0;
}

// Returns the height of the node
int height( TreeNode* pRoot ) {
	if( pRoot == NULL )
		return 0;
	int leftHeight	= height( pRoot->left );
	int rightHeight = height( pRoot->right );
	return ( leftHeight > rightHeight ? leftHeight : rightHeight ) + 1;
}

// Returns the Balance Factor (LH - RH)
int balanceFactor( TreeNode* pRoot ) {
	if( pRoot == NULL )
		return 0;
	return height( pRoot->left ) - height( pRoot->right );
}

// Single Left Rotation (for Right-Right case)
void SLR( TreeNode** pRoot ) {
	TreeNode* pAux	  = ( *pRoot )->right;
	( *pRoot )->right = pAux->left;
	pAux->left		  = ( *pRoot );
	*pRoot			  = pAux;
}

// Single Right Rotation (for Left-Left case)
void SRR( TreeNode** pRoot ) {
	TreeNode* pAux	 = ( *pRoot )->left;
	( *pRoot )->left = pAux->right;
	pAux->right		 = ( *pRoot );
	*pRoot			 = pAux;
}

int balanceLeft( TreeNode** pRoot ) {
	int bfLeft = balanceFactor( ( *pRoot )->left );
	if( bfLeft >= 0 ) { // LL Case
		SRR( pRoot );
	} else { // LR Case
		SLR( &( ( *pRoot )->left ) );
		SRR( pRoot );
	}
	return 1;
}

int balanceRight( TreeNode** pRoot ) {
	int bfRight = balanceFactor( ( *pRoot )->right );
	if( bfRight <= 0 ) { // RR Case
		SLR( pRoot );
	} else { // RL Case
		SRR( &( ( *pRoot )->right ) );
		SLR( pRoot );
	}
	return 1;
}

int balance( TreeNode** pRoot ) {
	int bf = balanceFactor( *pRoot );
	if( bf > 1 )
		return balanceLeft( pRoot );
	if( bf < -1 )
		return balanceRight( pRoot );
	return 0;
}
TreeNode* getMinValueNode( TreeNode* node ) {
	TreeNode* current = node;
	while( current->left != NULL )
		current = current->left;
	return current;
}

int deleteNode( TreeNode** pRoot, int val ) {
	if( *pRoot == NULL )
		return 0;
	if( val < ( *pRoot )->val ) {
		deleteNode( &( ( *pRoot )->left ), val );
	} else if( val > ( *pRoot )->val ) {
		deleteNode( &( ( *pRoot )->right ), val );
	} else {
		if( ( *pRoot )->left == NULL || ( *pRoot )->right == NULL ) {
			TreeNode* temp = ( *pRoot )->left ? ( *pRoot )->left : ( *pRoot )->right;
			// Sem filhos
			if( temp == NULL ) {
				temp   = *pRoot;
				*pRoot = NULL;
			} else { // Com um filho
				**pRoot = *temp;
			}
			free( temp );
		} else {
			TreeNode* temp	= getMinValueNode( ( *pRoot )->right );
			( *pRoot )->val = temp->val;
			deleteNode( &( ( *pRoot )->right ), temp->val );
		}
	}
	if( *pRoot == NULL )
		return 1;

	balance( pRoot );
	return 1;
}

int insertNode( TreeNode** pRoot, int val ) {
	if( *pRoot == NULL ) {
		*pRoot			 = ( TreeNode* )malloc( sizeof( TreeNode ) );
		( *pRoot )->val	 = val;
		( *pRoot )->left = ( *pRoot )->right = NULL;
		return 1; // Height increased
	}

	if( val < ( *pRoot )->val ) {
		if( insertNode( &( ( *pRoot )->left ), val ) ) {
			balance( pRoot );
			return 1; // After balancing or checking, we assume height stabilizes
		}
	} else if( val > ( *pRoot )->val ) {
		if( insertNode( &( ( *pRoot )->right ), val ) ) {
			balance( pRoot );
			return 1;
		}
	}
	return 0; // Value exists or height didn't change
}

int isAVLtree( TreeNode* root ) {
	if( root == NULL )
		return 1;

	int bf = balanceFactor( root );
	if( bf > 1 || bf < -1 )
		return 0;

	return isAVLtree( root->left ) && isAVLtree( root->right );
}

void printInOrder( TreeNode* root ) {
	if( root != NULL ) {
		printInOrder( root->left );
		printf( "%d ", root->val );
		printInOrder( root->right );
	}
}