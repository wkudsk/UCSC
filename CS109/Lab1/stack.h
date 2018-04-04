#ifndef CS109Stack
#define CS109Stack

typedef struct stackStruct * Stack;

Stack makeStack();

void push(Stack stack, int i);

int pop(Stack stack);

int peek(Stack stack);

int isEmpty(Stack stack);
#endif