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
	if( root->val == val ) {
		return root;
	}

	if( val < root->val ) {
		root->left = insertIntoBST( root->left, val );
	} else if( val > root->val ) {
		root->right = insertIntoBST( root->right, val );
	}
	return root;
}