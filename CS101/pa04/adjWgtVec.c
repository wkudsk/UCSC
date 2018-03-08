#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "adjWgtVec.h"

struct AdjWgtVecNode
{
	AdjWgt* data;
	int sz;
	int capacity;
};

/* Access functions
 */

/** adjWgtTop()
 * (what are the preconditions? Replace question with your text)
 */
AdjWgt adjWgtTop(AdjWgtVec myVec)
{
	return myVec->data[myVec->sz];
}

/** adjWgtData()
 * precondition: 0 <= i < adjWgtSize(myVec).
 */
AdjWgt adjWgtData(AdjWgtVec myVec, int i)
{
	return myVec->data[i];
}

/** adjWgtSize()
 * precondition: myVec has been constructed.
 */
int adjWgtSize(AdjWgtVec myVec)
{
	return myVec->sz;
}

/** adjWgtCapacity()
 * precondition: myVec has been constructed.
 */
int adjWgtCapacity(AdjWgtVec myVec)
{
	return myVec->capacity;
}

/* Constructors
 */

/** adjWgtMakeEmptyVec()
 * preconditions: none.
 * postconditions: Let /return be the value returned by adjWgtMakeEmptyVec().
 *    Then adjWgtCapacity(/return) == 4, adjWgtSize(/return) == 0).
 */
AdjWgtVec adjWgtMakeEmptyVec(void)
{
	AdjWgtVec myVec = malloc(sizeof(struct AdjWgtVecNode));
	myVec->capacity = adjWgtInitCap;
	myVec->sz = 0;
	myVec->data = malloc(sizeof(struct AdjWgtStruct)*(myVec->capacity)); 
	return myVec;
}


/* Manipulation Procedures
 */

/** adjWgtVecPush()
 * precondition: myVec has been constructed.
 * postconditions: Let /sz/ = adjWgtSize(myVec) before the call.
 *                 Let /cap/ = adjWgtCapacity(myVec) before the call.
 *    Then after the call, adjWgtSize(myVec) == /sz/+1,
 *        and adjWgtTop(myVec) == newE and adjWgtData(myVec, /sz/) == newE.
 *    Also, for all 0 <= i < /sz/: adjWgtData(myVec, i) is unchanged.
 *    Also, if (/sz/+1) > /cap/, then after the call,
 *        adjWgtCapacity(myVec) = 2 * /cap/.
 *    otherwise, adjWgtCapacity(myVec) is unchanged.
 */
void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE)
{
	//if the array is at full capacity, double the capacity.
	myVec->sz++;
	if(myVec->sz == myVec->capacity)
	{

		myVec->capacity = (myVec->capacity)*2;
		myVec->data = realloc(myVec->data, sizeof(struct AdjWgtStruct)*(myVec->capacity));
	}
	
	//add the new value to data.
	myVec->data[myVec->sz] = newE;
}

/** adjWgtVecPop()
 * precondition: myVec has been constructed and adjWgtSize(myVec) > 0.
 * postconditions: Let /sz/ = adjWgtSize(myVec) before the call.
 *                 Let /cap/ = adjWgtCapacity(myVec) before the call.
 *    Then after the call, adjWgtSize(myVec) == /sz/-1,
 *        adjWgtTop(myVec) == adjWgtData(/sz/-2).
 *    Also, for all 0 <= i < /sz/-1: adjWgtData(myVec, i) is unchanged.
 *    Also, adjWgtCapacity(myVec) is unchanged.
 */
void adjWgtVecPop(AdjWgtVec myVec)
{
	(myVec->sz)--;
}
