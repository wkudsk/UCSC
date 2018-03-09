#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "minPQ.h"

struct MinPQNode
{
	int numVertices;
	int numPQ;
	int minVertex;
	int* status;
	int* parent;
	double oo;
	double* fringeWgt;
};

int findMin(MinPQ pq)
{
	int v;
	double minWgt;
	int minV = -1;
	minWgt = pq->oo;
	for(v = 1; v <= pq->numVertices; v++)
	{
		if(pq->status[v] == FRINGE)
		{
			if(pq->fringeWgt[v] < minWgt)
			{
				minV = v;
				minWgt = pq->fringeWgt[v];
			}
		}
	}
	return minV;
}


/* ***************** Access functions */

int isEmptyPQ(MinPQ pq)
{
	if(pq->numPQ == 0) return 1;
	else return 0;
} 

int getMin(MinPQ pq)
{
	if(pq->minVertex == -1) pq->minVertex = findMin(pq);
	return pq->minVertex;
}

int getStatus(MinPQ pq, int id)
{
	return pq->status[id];
}


int getParent(MinPQ pq, int id)
{
	return pq->parent[id];
}


double getPriority(MinPQ pq, int id)
{
	return pq->fringeWgt[id];
}


/* ***************** Manipulation procedures */

void delMin(MinPQ pq)
{
	int oldMin = getMin(pq);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;
	return;
}

void insertPQ(MinPQ pq, int id, double priority, int par)
{
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->status[id] = FRINGE;
	pq->minVertex = -1;
	pq->numPQ++;
	return;

}

void decreaseKey(MinPQ pq, int id, double priority, int par)
{
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->minVertex = -1;
	return;
}


/* ***************** Constructors */

MinPQ createPQ(int n, int status[], double priority[], int parent[])
{
	MinPQ pq = malloc(sizeof(struct MinPQNode));
	pq->oo = INFINITY;
	pq->numVertices = n; 
	pq->numPQ = 0;
	pq->minVertex = -1;
	pq->status = status;
	pq->parent = parent;
	pq->fringeWgt = priority;
	return pq;
}


