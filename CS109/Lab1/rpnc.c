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
 * This code might be found on https://github.com/wkudsk because that is my github account, however that repo should be private and inaccessible.
 */

/*
 * Stack struct implemented with the help of code from Allen Van Gelder's Winter Quarter 2018 CMPS101 course.
 * https://classes.soe.ucsc.edu/cmps101/Winter18/
 * There's a size which is in a sense the stack pointer
 * Capacity keeps track of how much space must be allocated. If the size reaches the capacity,
 * the stack must realloc.
 * finally arr is an arraylist of ints that are stored as part of the algorithm
 */
typedef struct stackStruct
{
	int size;
	int* arr;
	int capacity;
} * Stack;

/* makeStack()
 * precondition: none.
 * postcondition: new Stack struct in created and returned.
 * Constructs a new stack and returns it
 * It does not need any parameters to create the stack.
 * If you want an initial capacity larger than 4, you can change it here.
 */
Stack makeStack()
{
	Stack stack = malloc(sizeof(struct stackStruct));
	stack->capacity = 4;
	stack->size = 0;
	stack->arr = malloc(sizeof(int)*stack->capacity);
	return stack;
}

/* push()
 * precondition: none.
 * postcondition: new element in the stack found at arr[size - 1]
 * This takes in the stack you're pushing to, as well as the new element that's going in.
 * If size reaches capacity, the arraylist is reallocated with double the capacity.
 * This push method was implemented in a similar fashion as Gelder's IntVec push function from his Winter Quarter 2018 CMPS101 course.
 * https://classes.soe.ucsc.edu/cmps101/Winter18/Handouts/standardVec.txt
 */
void push(Stack stack, int i)
{
	//if size reaches capacity, double the size of capacity and realloc arr.
	if(stack->size == stack->capacity)
	{
		stack->capacity = (stack->capacity)*2;
		stack->arr = realloc(stack->arr, sizeof(int)*(stack->capacity));
	}
	//add the new value to data.
	stack->arr[stack->size] = i;
	stack->size++;
}

/* pop()
 * precondition: stack should NOT be empty.
 * postcondition: stack has one less element and that element is returned.
 * Takes in the stack you're popping from.
 * Returns the element that was popped.
 * 
 */
int pop(Stack stack)
{
	stack->size--;
	int val = stack->arr[stack->size];
	//Set stack->arr[stack->size] to 0 for garbage collection reasons.
	stack->arr[stack->size] = 0;
	return val;
}

/* peek()
 * precondition: stack should NOT be empty.
 * postconition: the element at the top of the stack is returned. Stack is not modified.
 * This function is not used in this program, only implemented because it's potentially useful.
 */
int peek(Stack stack)
{
	stack->size--;
	int val = stack->arr[stack->size];
	stack->size++;
	return val;
}

/* isEmpty()
 * precondition: stack must have been created.
 * postcondition: 0 or 1 is returned indicated whether or not is empty.
 * isEmpty is not used in this program, only implemented because it's potentially useful.
 */
bool isEmpty(Stack stack)
{
	if(stack->size == 0) return true;
	else return false;
}

/* stackFree()
 * precondition: stack must have been created.
 * postcondition: stack is freed.
 */
void stackFree(Stack stack)
{
	stack->size = 0;
	free(stack->arr);
    free(stack);
}

/* exponent()
 * precondition: y and x are integers
 * postcondition: returns base y raised to the power of x
 * Something was up with math.h, so I implemented my own function.
 */
int exponent(int y, int x)
{
	int z = 1;
	for(int i = 0; i < x; i++)
	{
		z = z * y;
	}
	return z;
}

/* isOperation()
 * precondition: char i is a number between 0 and 127
 * postcondition: returns a bool telling you if the character was an operator.
 */
bool isOperation(char i)
{
	if(i == '+' || i == '-' || i == '/' || i == '*' || i == '^') return true;
	else return false;
}

/* completeOperation()
 * precondition: stack must have at least two entries, c must be an operator
 * postcondition: a new element is pushed onto the stack.
 * The new element is created from two operands being operated on by c, the operator.
 */
void completeOperation(Stack stack, char c)
{
	int result = -1;
	int x = pop(stack);
	int y = pop(stack);
	if(c == '*') result = x * y;
	if(c == '+') result = x + y;
	if(c == '-') result = y - x;
	if(c == '/') result = y / x;
	if(c == '^') result = exponent(y, x);
	push(stack, result);
}

/* main()
 * bulk of the code, this is where everything comes together.
 * makes sure to pass in an argv[1] in order for the code to work properly.
 */
int main(int argc, char* argv[])
{ 
	//Checks to make sure that the program was passed an input and output
	if( argc != 2 )
	{
		printf("Usage: %s <input file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char* str = argv[1]; /* char array to store str from input */

	//stack is a array based stack that will hold operands.
	Stack stack = makeStack();

	//Loops throught the elements from the stdin
	for(int i = 0; i < strlen(str) && str[i] != ':'; i++)
	{
		//Checks to see if the element is a number.
		if((int)str[i] >= 48 && (int)str[i] <= 57)
		{
			int val = 0;
			//This while loop keeps grabbing information until it reaches a whitespace break.
			//The purpose of this is to catch numbers larger than one digit.
			while((int)str[i] >= 48 && (int)str[i] <= 57)
			{
			val = val * 10;
			val += (int)(str[i] - 48);
			i++;
			}

			push(stack, val);
		}
		//Checks to see if the element is an operator.
		else if(isOperation(str[i]))
		{
			completeOperation(stack, str[i]);
		}
	}

	//this prints the final element left in the array, which should be the answer to the expression.
	int final = pop(stack);
	fprintf(stdout, "%d\n", final);

	//Free memory and terminate program.
	stackFree(stack);
	return(0);
}

