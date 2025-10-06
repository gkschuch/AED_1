#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

ListNode *createList(int arr[], int size) {
  if (size == 0)
    return NULL;
  ListNode *head = (ListNode *)malloc(sizeof(ListNode));
  head->val = arr[0];
  ListNode *current = head;
  for (int i = 1; i < size; i++) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->val = arr[i];
    current->next = newNode;
    current = newNode;
  }
  current->next = NULL;
  return head;
}

void printList(ListNode *node) {
  while (node != NULL) {
    printf("%d -> ", node->val);
    node = node->next;
  }
  printf("NULL\n");
}

void freeList(ListNode *head) {
  ListNode *current = head;
  while (current != NULL) {
    ListNode *nextNode = current->next;
    free(current);
    current = nextNode;
  }
}

ListNode *middleNode(ListNode *head) {
  int count = 0;

  for (ListNode *current = head; current != NULL; current = current->next) {
    count++;
  }
  int middleIndex = count / 2;

  ListNode *middleNode = head;
  for (int i = 0; i < middleIndex; i++) {
    middleNode = middleNode->next;
  }

  return middleNode;
}

int main() {
  int arr1[] = {1, 2, 3, 4, 5};
  int size1 = sizeof(arr1) / sizeof(arr1[0]);

  ListNode *head1 = createList(arr1, size1);

  printf("Lista original: ");
  printList(head1);

  ListNode *middle1 = middleNode(head1);

  printf("Lista a partir do no do meio: ");
  printList(middle1);

  freeList(head1);

  return 0;
}