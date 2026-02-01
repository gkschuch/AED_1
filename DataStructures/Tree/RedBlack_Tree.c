#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	RED,
	BLACK,
} Color;

typedef struct TreeNode {
	int				 data;
	Color			 color;
	struct TreeNode *left, *right, *parent;
} TreeNode;

TreeNode* getGrandParent( TreeNode* node );
TreeNode* getUncle( TreeNode* node );

void rotateLeft( TreeNode* node );
void rotateRight( TreeNode* node );

void fixRoot( TreeNode* node );
void checkParentColor( TreeNode* node );
void recolorRedUncle( TreeNode* node );
void rotateTriangleToLine( TreeNode* node );
void rotateLineAndRecolor( TreeNode* node );

TreeNode* createNode( int data );
void	  insert( TreeNode** root, int data );
void	  printInOrder( TreeNode* node );

int main() {
	TreeNode* root = NULL;

	printf( "--- Teste de Inserção Rubro-Negra ---\n" );

	int valores[] = { 1, 2, 3, 4, 5 };
	int n		  = sizeof( valores ) / sizeof( valores[0] );

	for( int i = 0; i < n; i++ ) {
		printf( "\nInserindo: %d", valores[i] );
		insert( &root, valores[i] );
	}

	printInOrder( root );

	return 0;
}

TreeNode* getGrandParent( TreeNode* node ) {
	if( ( node != NULL ) && ( node->parent != NULL ) )
		return node->parent->parent;
	return NULL;
}

TreeNode* getUncle( TreeNode* node ) {
	TreeNode* grandParent = getGrandParent( node );
	if( grandParent == NULL )
		return NULL;
	if( node->parent == grandParent->left )
		return grandParent->right;
	return grandParent->left;
}

void rotateLeft( TreeNode* node ) {
	TreeNode* pivot = node->right;
	node->right		= pivot->left;
	if( pivot->left != NULL )
		pivot->left->parent = node;
	pivot->parent = node->parent;
	if( node->parent != NULL ) {
		if( node == node->parent->left )
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	pivot->left	 = node;
	node->parent = pivot;
}
void rotateRight( TreeNode* node ) {
	TreeNode* pivot = node->left;
	node->left		= pivot->right;
	if( pivot->right != NULL )
		pivot->right->parent = node;
	pivot->parent = node->parent;
	if( node->parent != NULL ) {
		if( node == node->parent->left )
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	pivot->right = node;
	node->parent = pivot;
}

TreeNode* createNode( int data ) {
	TreeNode* node = ( TreeNode* )malloc( sizeof( TreeNode ) );
	node->data	   = data;
	node->color	   = RED;
	node->left = node->right = node->parent = NULL;
	return node;
}

void insert( TreeNode** root, int data ) {
	TreeNode* newNode = createNode( data );
	if( *root == NULL ) {
		*root = newNode;
	} else {
		TreeNode* current = *root;
		TreeNode* parent  = NULL;

		while( current != NULL ) {
			parent = current;
			if( data < current->data )
				current = current->left;
			else
				current = current->right;
		}

		newNode->parent = parent;
		if( data < parent->data )
			parent->left = newNode;
		else
			parent->right = newNode;
	}

	fixRoot( newNode );

	while( ( *root )->parent != NULL )
		*root = ( *root )->parent;
}

void printInOrder( TreeNode* node ) {
	if( node == NULL )
		return;
	printInOrder( node->left );
	printf( "%d(%s)\n", node->data, node->color == RED ? "R" : "B" );
	printInOrder( node->right );
}

void fixRoot( TreeNode* node ) {
	if( node->parent == NULL ) {
		node->color = BLACK;
	} else {
		checkParentColor( node );
	}
}

void checkParentColor( TreeNode* node ) {
	if( node->parent->color == BLACK ) {
		return;
	}
	recolorRedUncle( node );
}

void recolorRedUncle( TreeNode* node ) {
	TreeNode *uncle = getUncle( node ), *grandParent;
	if( ( uncle != NULL ) && ( uncle->color == RED ) ) {
		node->parent->color = BLACK;
		uncle->color		= BLACK;
		grandParent			= getGrandParent( node );
		grandParent->color	= RED;
		fixRoot( grandParent );
	} else {
		rotateTriangleToLine( node );
	}
}

void rotateTriangleToLine( TreeNode* node ) {
	TreeNode* grandParent = getGrandParent( node );
	if( ( node == node->parent->right ) && ( node->parent == grandParent->left ) ) {
		rotateLeft( node->parent );
		node = node->left;
	} else if( ( node == node->parent->left ) && ( node->parent == grandParent->right ) ) {
		rotateRight( node->parent );
		node = node->right;
	}
	rotateLineAndRecolor( node );
}

void rotateLineAndRecolor( TreeNode* node ) {
	TreeNode* grandParent = getGrandParent( node );
	if( ( node == node->parent->left ) && ( node->parent == grandParent->left ) ) {
		rotateRight( grandParent );
	} else {
		rotateLeft( grandParent );
	}
	node->parent->color = BLACK;
	grandParent->color	= RED;
}
