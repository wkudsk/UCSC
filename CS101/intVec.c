#include "intVec.h"

struct IntVecNode
{
	int* data;
	int sz;
	int capacity;
};

int intTop(IntVec myVec)
{
	return myVec->data[sz];
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
	myVec->capacity = 4
	myVec->data = malloc(sizeof(int)*capacity); 
	myVec->sz = 0;
	
}

IntVec intMakeEmptyVecN(int np1)
{
	
}

void intVecPush(IntVec myVec, int newE)
{
	if(sz == capacity)
	{
		myVec->data = realloc(sizeof(int)*capacity*2);
		capacity = capacity * 2;
	}
	sz++;
	myVec->data[sz] = newE;
}

void intVecPop(IntVec myVec)
{
	sz--;
}