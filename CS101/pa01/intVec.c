#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"

struct IntVecNode
{
	int* data;
	int sz;
	int capacity;
};

int intTop(IntVec myVec)
{
	return myVec->data[(myVec->sz)-1];
}

int intData(IntVec myVec, int i)
{
	return myVec->data[i];
}

int intSize(IntVec myVec)
{
	return myVec->sz;
}

int intCapacity(IntVec myVec)
{
	return myVec->capacity;
}

IntVec intMakeEmptyVec(void)
{
	IntVec myVec = malloc(sizeof(struct IntVecNode));
	myVec->capacity = intInitCap;
	myVec->sz = 0;
	myVec->data = malloc(sizeof(int)*(myVec->capacity)); 
	return myVec;
}

IntVec intMakeEmptyVecN(int np1)
{
	IntVec myVec = malloc(sizeof(IntVec));
	myVec->capacity = np1;
	myVec->data = malloc(sizeof(int)*(myVec->capacity)); 
	myVec->sz = 0;

	return myVec;
		
}

void intVecPush(IntVec myVec, int newE)
{
	//if the array is at full capacity, double the capacity.
	
	if(myVec->sz == myVec->capacity)
	{

		myVec->capacity = (myVec->capacity)*2;
		myVec->data = realloc(myVec->data, sizeof(int)*(myVec->capacity));
	}
	//add the new value to data.
	myVec->data[myVec->sz] = newE;
	myVec->sz++;
	
}

void intVecPop(IntVec myVec)
{
	(myVec->sz)--;
	//we would free here if it was required.
}