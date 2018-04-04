#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * Reverse Polish Notation (RPN) Calculator
 *
 * Accepts a single argument in RPN, evaluates it and prints the answer to stdout.
 * 
 * Returns -1 on error, 0 otherwise.
 *
 * William Kudsk (wkudsk) Lab1 for CMPS109 in C.
 * initial portion of main function that reads input and output is taken from a handout from Sesh's CMPS12B
 * class from fall quarter 2017. Once it gets to the while loop, all the code is original.
 * This code might be found on https://github.com/wkudsk because that is my github account. I will work on making it private.
 */

typedef struct stackStruct
{
   int size;
   int* arr;
   int capacity;
} * Stack;

Stack makeStack()
{
   Stack stack = malloc(sizeof(struct stackStruct));
   stack->capacity = 4;
   stack->size = 0;
   stack->arr = malloc(sizeof(int)*stack->capacity);
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

bool isOperation(char i)
{
   if(i == 42 || i == 43 || i == 45 || i == 47) return true;
   else return false;
}

void completeOperation(Stack stack, char c)
{
	int result = -1;
	int x = pop(stack);
	int y = pop(stack);
	if((int)c == 42) result = x * y;
	if((int)c == 43) result = x + y;
	if((int)c == 45) result = y - x;
	if((int)c == 47) result = y / x;
	push(stack, result);
}

int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	char str[256]; /* char array to store str from input file */

   //Checks to make sure that the program was passed an input and output
	if( argc != 2 )
   {
		printf("Usage: %s <input file>\n", argv[0]);
   	exit(EXIT_FAILURE);
   }

   /* open input file for reading */
   in = fopen(argv[1], "r");
   //if( in==NULL )
   //{
   	//printf("Unable to read from file %s\n", argv[1]);
   	//exit(EXIT_FAILURE);
   //}


   while( fgets(str, 256, in) != NULL )
   {
   		Stack stack = makeStack();
    	for(int i = 0; i < strlen(str); i++)
    	{

        	if((int)str[i] >= 48 && (int)str[i] <= 57)
        	{
        		int val = 0;
        		while((int)str[i] >= 48 && (int)str[i] <= 57)
         		{
         			val = val * 10;
         			val += (int)(str[i] - 48);
         			i++;
         		}

         		push(stack, val);
        	}

        	else if(isOperation(str[i]))
        	{
         		completeOperation(stack, str[i]);
        	}
        }

    int final = pop(stack);
    fprintf(stdout, "%d\n", final);
   }
   
   fclose(in);
   return(0);
}

