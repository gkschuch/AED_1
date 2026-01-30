#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* createNode( int val );
TreeNode* insertNode( TreeNode* node, int val );
bool	  searchTree( TreeNode* node, int val );
TreeNode* findMin( TreeNode* node );
TreeNode* deleteNode( TreeNode* root, int val );
void	  printInOrder( TreeNode* node );
void	  printPreOrder( TreeNode* node );
void	  printPostOrder( TreeNode* node );

void freeTree( TreeNode* root );

int main() {
	TreeNode* root = NULL;

	// Build the tree
	root = insertNode( root, 10 );
	root = insertNode( root, 5 );
	root = insertNode( root, 15 );
	root = insertNode( root, 3 );
	root = insertNode( root, 7 );
	root = insertNode( root, 12 );
	root = insertNode( root, 18 );

	printf( "Original In-Order: " );
	printLevelOrder( root );
	printf( "\n" );

	// Test Deletion
	printf( "Deleting 15 (Node with two children)...\n" );
	root = deleteNode( root, 15 );

	printf( "Updated In-Order:  " );
	printLevelOrder( root );
	printf( "\n" );

	freeTree( root );
	return 0;
}

// Cria um novo nodo
TreeNode* createNode( int val ) {
	TreeNode* newNode = ( TreeNode* )malloc( sizeof( TreeNode ) );

	newNode->val   = val;
	newNode->left  = NULL;
	newNode->right = NULL;
	return newNode;
}

// Insere um nodo na arvore
TreeNode* insertNode( TreeNode* node, int val ) {
	if( node == NULL ) {
		return createNode( val );
	}
	if( node->val == val ) {
		return node;
	}
	if( val < node->val ) {
		node->left = insertNode( node->left, val );
	} else {
		node->right = insertNode( node->right, val );
	}
	return node;
}

// Printa em ordem(left,root, right)
void printInOrder( TreeNode* node ) {
	if( node == NULL )
		return;
	printInOrder( node->left );
	printf( "%d\n", node->val );
	printInOrder( node->right );
}
// Printa em Pre-ordem(Root,left,right)
void printPreOrder( TreeNode* node ) {
	if( node == NULL )
		return;
	printf( "%d\n", node->val );
	printPreOrder( node->left );
	printPreOrder( node->right );
}

// Printa em Pos ordem'(left, right, root)
void printPostOrder( TreeNode* node ) {
	if( node == NULL )
		return;
	printPostOrder( node->left );
	printPostOrder( node->right );
	printf( "%d\n", node->val );
}

//  Limpa todos os nodos da arvore(em pos ordem)
void freeTree( TreeNode* root ) {
	if( root == NULL )
		return;
	freeTree( root->left );
	freeTree( root->right );
	free( root );
}

bool searchTree( TreeNode* node, int val ) {
	if( node == NULL )
		return false;

	if( val == node->val )
		return true;

	if( val < node->val )
		return searchTree( node->left, val );
	else
		return searchTree( node->right, val );
}
TreeNode* findMin( TreeNode* node ) {
	TreeNode* current = node;
	while( current && current->left != NULL ) {
		current = current->left;
	}
	return current;
}
TreeNode* deleteNode( TreeNode* root, int val ) {
	if( root == NULL )
		return root;
	if( val < root->val )
		deleteNode( root->left, val );
	else if( val > root->val )
		deleteNode( root->right, val );
	else {
		if( root->left == NULL ) {
			TreeNode* temp = root->right;
			free( root );
			return temp;
		} else if( root->right == NULL ) {
			TreeNode* temp = root->left;
			free( root );
			return temp;
		}
		TreeNode* temp = findMin( root->right );
		root->val	   = temp->val;
		root->right	   = deleteNode( root->right, root->val );
	}
	return root;
}
