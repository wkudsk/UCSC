#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "minPQ.h"


struct MinPQNode
{
	int numVertices;
	int numPQ;
	int minVertex;
	int* status;
	int* parent;
	int oo;
	double* fringeWgt;
};

void findMin(MinPQ pq)
{
	int v;
	double minWgt;

	minWgt = pq->oo;
	for(v = 1; v <= pq->numVertices; v++)
	{
		if(pq->status[v] == FRINGE)
		{
			if(pq->fringeWgt[v] < minWgt)
			{
				pq->minVertex = v;
				fprintf(stdout, "v =%d\n", v);
				minWgt = pq->fringeWgt[v];
			}
		}
	}
	return;
}


/* ***************** Access functions */

/** isEmpty (what are the preconditions, if any? Replace this question with your comments.)
*/
int isEmptyPQ(MinPQ pq)
{
	if(pq->numPQ == 0) return 1;
	else return 0;
} 

/** getMin (what are the preconditions, if any? Replace this question with your comments.)
*/
int getMin(MinPQ pq)
{
	if(pq->minVertex == -1) findMin(pq);
	return pq->minVertex;
}
/** getStatus (what are the preconditions, if any? Replace this question with your comments.)
*/
int getStatus(MinPQ pq, int id)
{
	return pq->status[id];
}

/** getParent (what are the preconditions, if any? Replace this question with your comments.)
*/
int getParent(MinPQ pq, int id)
{
	return pq->parent[id];
}

/** getPriority (what are the preconditions, if any? Replace this question with your comments.)
*/
double getPriority(MinPQ pq, int id)
{
	return pq->fringeWgt[id];
}


/* ***************** Manipulation procedures */

/** delMin (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void delMin(MinPQ pq)
{
	int oldMin = getMin(pq);
	fprintf(stdout, "oldMin = %d\n", oldMin);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;
	return;
}

/** insertPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void insertPQ(MinPQ pq, int id, double priority, int par)
{
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->status[id] = FRINGE;
	pq->minVertex = -1;
	pq->numPQ++;
	return;

}

/** decreaseKey (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void decreaseKey(MinPQ pq, int id, double priority, int par)
{
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->minVertex = -1;
	return;
}


/* ***************** Constructors */

/** createPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[])
{
	MinPQ pq = malloc(sizeof(struct MinPQNode));
	pq->oo = 1.0/0.0;
	pq->numVertices = n; 
	pq->numPQ = 0;
	pq->minVertex = -1;
	pq->status = status;
	pq->parent = parent;
	pq->fringeWgt = priority;
	return pq;
}


