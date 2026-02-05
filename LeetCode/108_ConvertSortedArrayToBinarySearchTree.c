#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};
struct TreeNode* buildBST( int* nums, int left, int right ) {
	if( left > right ) {
		return NULL;
	}

	int mid = left + ( right - left ) / 2;

	struct TreeNode* newNode = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	newNode->val			 = nums[mid];

	newNode->left  = buildBST( nums, left, mid - 1 );
	newNode->right = buildBST( nums, mid + 1, right );

	return newNode;
}

struct TreeNode* sortedArrayToBST( int* nums, int numsSize ) {
	if( numsSize == 0 )
		return NULL;
	return buildBST( nums, 0, numsSize - 1 );
}

void printInOrder( struct TreeNode* node ) {
	if( node == NULL )
		return;
	printInOrder( node->left );
	printf( "%d\n", node->val );
	printInOrder( node->right );
}
int main() {
	int				 nums[]	  = { 1, 2, 3, 4, 5, 6, 7 };
	int				 numsSize = 7;
	struct TreeNode* tree	  = sortedArrayToBST( nums, numsSize );

	printInOrder( tree );
	return 0;
}
