// Gabriel Karini Schuch
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int				 val;
	struct ListNode* next;
};

typedef struct StackNode {
	struct ListNode*  listNodePtr;
	struct StackNode* next;
} StackNode;

typedef struct {
	StackNode* top;
} Stack;

Stack* createStack() {
	Stack* pStack = ( Stack* )malloc( sizeof( Stack ) );
	pStack->top	  = NULL;
	return pStack;
}

bool Push( Stack* pStack, struct ListNode* node ) {
	StackNode* newStackNode = ( StackNode* )malloc( sizeof( struct StackNode ) );
	if( newStackNode == NULL ) {
		return false;
	}
	newStackNode->listNodePtr = node;
	newStackNode->next		  = pStack->top;
	pStack->top				  = newStackNode;
	return true;
}

bool Empty( Stack* stack ) {
	return stack->top == NULL;
}

void Pop( Stack* pStack, struct ListNode** node ) {
	if( Empty( pStack ) )
		return;
	struct StackNode* tempNode = pStack->top;
	*node					   = tempNode->listNodePtr;
	pStack->top				   = tempNode->next;
	free( tempNode );
}

void reorderList( struct ListNode* head ) {
	if( head == NULL || head->next == NULL || head->next->next == NULL ) {
		return;
	}
	int				 listLen = 0;
	struct ListNode* current = head;
	Stack*			 stack	 = createStack();

	while( current != NULL ) {
		Push( stack, current );
		listLen++;
		current = current->next;
	}

	current = head;
	struct ListNode* nodeFromStack;

	for( int i = 0; i < listLen / 2; i++ ) {
		Pop( stack, &nodeFromStack );
		struct ListNode* temp = current->next;
		current->next		  = nodeFromStack;
		nodeFromStack->next	  = temp;
		current				  = temp;
	}
	current->next = NULL;
	free( stack );
}

int main() {
	struct ListNode* head = ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	head->val			  = 1;

	head->next		= ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	head->next->val = 2;

	head->next->next	  = ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	head->next->next->val = 3;

	head->next->next->next		 = ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	head->next->next->next->val	 = 4;
	head->next->next->next->next = NULL;

	reorderList( head );

	for( struct ListNode* i = head; i != NULL; i = i->next ) {
		printf( "%d\n", i->val );
	}
	free( head );
	return 0;
}