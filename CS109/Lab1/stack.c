#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stack.h"

struct stackStruct
{
	int size;
	int* arr;
	int capacity;
};

Stack makeStack()
{
	Stack stack = malloc(sizeof(struct stackStruct));
	stack->capacity = 4;
	stack->size = 0;
	stack->arr = malloc(sizeof(int)*capacity);
	return stack;
}

/*This push method was implemented in a similar fashion as Gelder's IntVec push function from his CS101 course*/
void push(Stack stack, int i)
{
	if(stack->size == stack->capacity)
	{

		stack->capacity = (stack->capacity)*2;
		stack->arr = realloc(stack->arr, sizeof(int)*(stack->capacity));
	}
	//add the new value to data.
	stack->arr[stack->size] = i;
	stack->size++;
}

int pop(Stack stack)
{
	stack->size--;
	int val = stack->arr[stack->size];
	stack->arr[stack->size] = 0;
	return val;
}

int peek(Stack stack)
{
	stack->size--;
	int val = stack->arr[stack->size];
	stack->size++;
	return val;
}

int isEmpty(Stack stack)
{
	if(stack->size == 0) return 1;
	else return 0;
}