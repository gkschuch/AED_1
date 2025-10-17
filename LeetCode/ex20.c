#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Define Stack struct
typedef struct {
  char *characters;
  int top;
  int capacity;
} Stack;

Stack *createStack(int capacity);

void freeStack(Stack *stack);

bool isEmpty(Stack *stack);

bool isFull(Stack *stack);
bool push(Stack *stack, char item);
bool pop(Stack *stack, char *pItem);

bool isValid(char *s);

int main() {
  char *string = "()[]{}";
  if (isValid(string)) {
    printf("Is valid");
  } else {
    printf("Is not valid");
  }
}
// Create and Initialize a new Stack
Stack *createStack(int capacity) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->characters = (char *)malloc(stack->capacity * sizeof(char));
  return stack;
}
// Checks if the stack is empty
bool isEmpty(Stack *stack) { return stack->top == -1; }
// Checks if the stack is full
bool isFull(Stack *stack) { return stack->top == stack->capacity - 1; }

// Removes a item from the stack
// Returns 'true' in success, 'false' if the stack is empty
// The removed item is found in the variable 'pItem'
bool pop(Stack *stack, char *pItem) {
  if (isEmpty(stack))
    return false;
  *pItem = stack->characters[stack->top--];
  return true;
}

// Insert a new item in the stack
// Returns 'true' in success, 'false' if the stack is full
bool push(Stack *stack, char item) {
  if (isFull(stack))
    return false;
  stack->characters[++stack->top] = item;
  return true;
}
// Free the memory allocated for stack
void freeStack(Stack *stack) {
  if (stack == NULL)
    return;
  if (isEmpty(stack)) {
    free(stack->characters);
    free(stack);
    return;
  }
  char dummyItem;
  pop(stack, &dummyItem);
  freeStack(stack);
}

bool isValid(char *s) {
  int len = strlen(s);
  if (len == 0)
    return true;
  // A valid String needs an even number of characters
  if (len % 2 != 0)
    return false;
  Stack *stack = createStack(len);
  for (int i = 0; i < len; i++) {
    char c = s[i];
    // If is a Open brackets
    if (c == '(' || c == '{' || c == '[') {
      // Push an item to the stack
      // If the stack is Full, it frees the stack
      if (!push(stack, c)) {
        freeStack(stack);
        return false;
      }
      //   If it is a Close brackets
    } else {
      char topChar; // Variable to get the pop value

      //   Removes the top value  from the stack
      // if the stack is empty, it frees the stack
      if (!pop(stack, &topChar)) {
        freeStack(stack);
        return false;
      }
      //   If the current value "c = s[i]" is a closing bracket(')', '}', ']')
      //  And the top value of the stack is not the respective opening
      //  value('(', '{', '[') It frees the stack and returns False
      if (c == ')' && topChar != '(') {
        freeStack(stack);
        return false;
      }
      if (c == '}' && topChar != '{') {
        freeStack(stack);
        return false;
      }
      if (c == ']' && topChar != '[') {
        freeStack(stack);
        return false;
      }
    }
  }
  bool result = isEmpty(stack);
  freeStack(stack);
  return result;
}