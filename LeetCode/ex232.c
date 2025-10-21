#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
  int val;
  struct StackNode *pNext;
} StackNode;

typedef struct {
  StackNode *top;
} Stack;

typedef struct {
  Stack *s1;
  Stack *s2;
} MyQueue;

Stack *stackCreate(void);
void stackPush(Stack *s, int val);
bool stackEmpty(Stack *s);
int stackPop(Stack *s);
bool stackPeek(Stack *s, int *result);
void stackFree(Stack *s);

MyQueue *myQueueCreate(void);
void transfer(MyQueue *obj);
void myQueuePush(MyQueue *obj, int x);
bool myQueueEmpty(MyQueue *obj);
int myQueuePop(MyQueue *obj);
int myQueuePeek(MyQueue *obj);
void myQueueFree(MyQueue *obj);

int main() {
  MyQueue *q = myQueueCreate();

  myQueuePush(q, 1);
  printf("Pushed: 1\n");
  myQueuePush(q, 2);
  printf("Pushed: 2\n");

  int peekVal = myQueuePeek(q);
  printf("Peeked: %d (Expected: 1)\n", peekVal);

  int popVal = myQueuePop(q);
  printf("Popped: %d (Expected: 1)\n", popVal);

  myQueuePush(q, 3);
  printf("Pushed: 3\n");

  peekVal = myQueuePeek(q);
  printf("Peeked: %d (Expected: 2)\n", peekVal);

  popVal = myQueuePop(q);
  printf("Popped: %d (Expected: 2)\n", popVal);

  popVal = myQueuePop(q);
  printf("Popped: %d (Expected: 3)\n", popVal);

  bool empty = myQueueEmpty(q);
  printf("Is queue empty? %s (Expected: true)\n", empty ? "true" : "false");

  myQueueFree(q);
  printf("Queue freed.\n");

  return 0;
}

// Stack Data Structure Logic

Stack *stackCreate(void) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->top = NULL;
  return s;
}

void stackPush(Stack *s, int val) {
  StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
  newNode->val = val;
  newNode->pNext = s->top;
  s->top = newNode;
}

bool stackEmpty(Stack *s) {
  if (s->top == NULL)
    return true;
  return false;
}

int stackPop(Stack *s) {
  if (stackEmpty(s)) {
    fprintf(stderr, "Fatal Error: Attempted to pop from an empty stack.\n");
    exit(1);
  }
  StackNode *temp = s->top;
  int val = temp->val;
  s->top = s->top->pNext;
  free(temp);
  return val;
}

bool stackPeek(Stack *s, int *result) {
  if (stackEmpty(s))
    return false;
  *result = s->top->val;
  return true;
}

void stackFree(Stack *s) {
  while (!stackEmpty(s)) {
    stackPop(s);
  }
  free(s);
}

// Queue Data Structure Logic, using Stack
MyQueue *myQueueCreate(void) {
  MyQueue *obj = (MyQueue *)malloc(sizeof(MyQueue));
  obj->s1 = stackCreate();
  obj->s2 = stackCreate();
  return obj;
}

void transfer(MyQueue *obj) {
  while (!stackEmpty(obj->s1)) {
    stackPush(obj->s2, stackPop(obj->s1));
  }
}

void myQueuePush(MyQueue *obj, int x) {
  // Pushes new element to s1
  stackPush(obj->s1, x);
}

int myQueuePop(MyQueue *obj) {
  if (myQueueEmpty(obj)) {
    fprintf(stderr, "Fatal Error: Attempted to pop from an empty queue.\n");
    exit(1);
  }
  if (stackEmpty(obj->s2))
    transfer(obj);
  return stackPop(obj->s2);
}

int myQueuePeek(MyQueue *obj) {
  if (myQueueEmpty(obj)) {
    fprintf(stderr, "Fatal Error: Attempted to peek an empty queue.\n");
    exit(1);
  }
  if (stackEmpty(obj->s2)) {
    transfer(obj);
  }
  int returnedValue;
  stackPeek(obj->s2, &returnedValue);
  return returnedValue;
}

bool myQueueEmpty(MyQueue *obj) {
  if (stackEmpty(obj->s1) && stackEmpty(obj->s2))
    return true;
  return false;
}

void myQueueFree(MyQueue *obj) {
  stackFree(obj->s1);
  stackFree(obj->s2);
  free(obj);
}
