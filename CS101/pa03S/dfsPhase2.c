#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"
#include "dfsTrace1.h"
#include "dfsPhase2.h"

//This struct holds a data set of all values 
struct SCCNode
{
	char* color;
	int* dTime;
	int* fTime;
	int* parent;
	int counter;
	int* root;
};

/*Constructors*/

//Allocates memory for a scc struct.
SCC makeEmptySCCSet(int n)
{

	SCC scc = malloc(sizeof(struct SCCNode));
	scc->color = malloc((n+1)*sizeof(char));
	scc->dTime = malloc((n+1)*sizeof(int));
	scc->fTime = malloc((n+1)*sizeof(int));
	scc->parent = malloc((n+1)*sizeof(int));
	scc->root = malloc((n+1)*sizeof(int));
	
	//Counter must start at one, this variable will be used to keep track
	//of dTime and fTime.
	scc->counter = 1;

	//Initializes the arrays with 0's and white's.
	//They will be changed to their proper numbers in dfs()
	for(int k = 0; k <= n; k++)
	{
		scc->dTime[k] = 0;
		scc->fTime[k] = 0;
		scc->color[k] = 'W';
		scc->parent[k] = -1;
		scc->root[k] = 0;
	}

	return scc;
}

//This is the most important part of this assignment.
SCC dfsPhase2(IntVec* graph, SCC scc, int n, int i)
{
	IntVec vec = graph[i];
	//if the point is black or gray, then there is no point in looking at it yet.
	if(scc->color[i] == 'W')
	{	
		//if the point has yet to be visited, enter in its discovery time, increment counter, and look for the points inside.
		scc->dTime[i] = scc->counter;
		scc->color[i] = 'G';
		scc->counter++;
		//while the inside is not empty, try to find the points and recursively store their information.
		while(intSize(vec) != 0)
		{
			
			int edge = intData(vec, intSize(vec));
			//once the edege is stored, pop it from the original IntVec so that you don't visit it twice.
			intVecPop(vec);
			if(scc->color[edge] == 'W') 
			{
				//if you find a new edge, store its parent, then move to recursion.
				scc->parent[edge] = i;
				int root = i;
				while(root != -1)
				{
					scc->root[edge] = root;
					root = scc->parent[root];
				}
				scc = dfsPhase2(graph, scc, n, edge);
			}
			
		}
		//once you're done with an edge, turn it black, store finish time, and increment counter.
		scc->fTime[i] = scc->counter;
		scc->color[i] = 'B';
		scc->counter++;
		if(scc->parent[i] == -1) scc->root[i] = i;		

	}
	return scc;
}

/*Manipulation Procedures*/


void sccPrint(SCC scc, int n)
{
	fprintf(stdout, " V   color2 dTime2 fTime2 parent2 dfstRoot2\n");
	for(int i = 1; i <= n; i++)
	{
		fprintf(stdout, "%2u%8c%7u%7u%7d%6d\n",i, scc->color[i], scc->dTime[i], scc->fTime[i], scc->parent[i], scc->root[i]);
	}
}
