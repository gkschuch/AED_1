#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* createNode( int val ) {
	struct TreeNode* newNode = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	newNode->val			 = val;
	newNode->left			 = NULL;
	newNode->right			 = NULL;
	return newNode;
}

struct TreeNode* insertIntoBST( struct TreeNode* root, int val ) {
	if( root == NULL ) {
		return createNode( val );
	}

	if( val < root->val ) {
		root->left = insertIntoBST( root->left, val );
	} else if( val > root->val ) {
		root->right = insertIntoBST( root->right, val );
	}
	return root;
}

void inorderTraversal( struct TreeNode* root ) {
	if( root != NULL ) {
		inorderTraversal( root->left );
		printf( "%d ", root->val );
		inorderTraversal( root->right );
	}
}

void freeTree( struct TreeNode* root ) {
	if( root != NULL ) {
		freeTree( root->left );
		freeTree( root->right );
		free( root );
	}
}

int main() {
	struct TreeNode* root = NULL;
	int				 val  = 5;

	root = insertIntoBST( root, 4 );
	insertIntoBST( root, 2 );
	insertIntoBST( root, 7 );
	insertIntoBST( root, 1 );
	insertIntoBST( root, 3 );
	inorderTraversal( root );
	printf( "\n" );

	insertIntoBST( root, val );

	inorderTraversal( root );
	printf( "\n" );

	freeTree( root );

	return 0;
}