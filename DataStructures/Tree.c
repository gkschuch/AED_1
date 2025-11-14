#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int val);
TreeNode *insertNode(TreeNode *node, int val);
void printInOrder(TreeNode *node);
void printPreOrder(TreeNode *node);
void printPostOrder(TreeNode *node);

void freeTree(TreeNode *root);

int main() {
  TreeNode *root = NULL;

  root = insertNode(root, 10);
  root = insertNode(root, 5);
  root = insertNode(root, 15);
  root = insertNode(root, 3);
  root = insertNode(root, 7);

  printf("In-Order Traversal: \n");
  printInOrder(root);
  printf("\n");
  printf("Pre-Order Traversal: \n");
  printPreOrder(root);
  printf("\n");
  printf("Post-Order Traversal: \n");
  printPostOrder(root);
  printf("\n");
  freeTree(root);
  return 0;
}

// Cria um novo nodo
TreeNode *createNode(int val) {
  TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

  newNode->val = val;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// Insere um nodo na arvore
TreeNode *insertNode(TreeNode *node, int val) {
  if (node == NULL) {
    return createNode(val);
  }
  if (val < node->val) {
    node->left = insertNode(node->left, val);
  } else {
    node->right = insertNode(node->right, val);
  }
  return node;
}

// Printa em ordem(left,root, right)
void printInOrder(TreeNode *node) {
  if (node == NULL)
    return;
  printInOrder(node->left);
  printf("%d\n", node->val);
  printInOrder(node->right);
}
// Printa em Pre-ordem(Root,left,right)
void printPreOrder(TreeNode *node) {
  if (node == NULL)
    return;
  printf("%d\n", node->val);
  printPreOrder(node->left);
  printPreOrder(node->right);
}

// Printa em Pos ordem'(left, right, root)
void printPostOrder(TreeNode *node) {
  if (node == NULL)
    return;
  printPostOrder(node->left);
  printPostOrder(node->right);
  printf("%d\n", node->val);
}

//  Limpa todos os nodos da arvore(em pos ordem)
void freeTree(TreeNode *root) {
  if (root == NULL)
    return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}