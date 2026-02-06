#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

int dfs( struct TreeNode* node, int isLeft ) {
	if( node == NULL )
		return 0;

	if( node->left == NULL && node->right == NULL )
		return isLeft ? node->val : 0;

	return dfs( node->left, 1 ) + dfs( node->right, 0 );
}

int sumOfLeftLeaves( struct TreeNode* root ) {
	return dfs( root, 0 );
}