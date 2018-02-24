#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"
#include "dfsTrace1.h"
#include "dfsPhase2.h"

struct DataNode
{
	finishStk1 finishStack;
	char* color;
	int* dTime;
	int* fTime;
	int* parent;
	int counter;
};

struct StackNode
{
	int* stack;
	int size;
	int capacity;
};

/*Constructors*/

finishStk1 makeEmptyStack(int n)
{
	finishStk1 finishStack = malloc(sizeof(struct StackNode));
	finishStack->size = 0;
	finishStack->capacity = n;
	finishStack->stack = malloc((n+1)*sizeof(int));

	return finishStack;
}


//Allocates memory for a Data struct.
Data makeEmptyDataSet(int n)
{

	Data data = malloc(sizeof(struct DataNode));
	data->color = malloc((n+1)*sizeof(char));
	data->dTime = malloc((n+1)*sizeof(int));
	data->fTime = malloc((n+1)*sizeof(int));
	data->parent = malloc((n+1)*sizeof(int));
	data->finishStack = makeEmptyStack(n);
	
	//Counter must start at one, this variable will be used to keep track
	//of dTime and fTime.
	data->counter = 1;

	//Initializes the arrays with 0's and white's.
	//They will be changed to their proper numbers in dfs()
	for(int k = 0; k <= n; k++)
	{
		data->dTime[k] = 0;
		data->fTime[k] = 0;
		data->color[k] = 'W';
		data->parent[k] = -1;
	}

	return data;
}


//This is the most important part of this assignment.
Data dfs(IntVec* graph, Data data, int n, int v)
{
	//Start by finding the vector at point V.
	IntVec vec = graph[v];
	//if the point is black or gray, then there is no point in looking at it yet.
	if(data->color[v] == 'W')
	{	
		//if the point has yet to be visited, enter in its discovery time, increment counter, and look for the points inside.
		data->dTime[v] = data->counter;
		data->color[v] = 'G';
		data->counter++;
	
		//while the inside is not empty, try to find the points and recursively store their information.
		while(intSize(vec) != 0)
		{	
			int edge = intData(vec, intSize(vec));
			//once the edege is stored, pop it from the original IntVec so that you don't visit it twice.
			intVecPop(vec);
			if(data->color[edge] == 'W')
			{	
				//if you find a new edge, store its parent, then move to recursion.
				data->parent[edge] = v;
				data = dfs(graph, data, n, edge);
			}
			
		}
		//once you're done with an edge, turn it black, store finish time, and increment counter.
		data->fTime[v] = data->counter;
		data->color[v] = 'B';
		data->counter++;
		pushStack(data->finishStack, v);
	}
	return data;
}

/* Manipulation Procedures */

void pushStack(finishStk1 finishStack, int vec)
{
	finishStack->stack[finishStack->size] = vec;
	finishStack->size++;
}

int popStack(finishStk1 finishStack)
{
	finishStack->size--;
	return finishStack->stack[finishStack->size];
}


/*Access Functions*/


bool isEmpty(finishStk1 finishStack)
{
	if(finishStack->size == 0)
	{
		return true;
	}
	else return false;
}

finishStk1 getStack(Data data)
{
	return data->finishStack;
}


void stackPrint(finishStk1 finishStack)
{
	fprintf(stdout, "%s", "FSTK:  ");
	int* fTime = finishStack->stack;
	for(int i = 0; i < finishStack->size; i++)
	{
		if(fTime[i] < 10) fprintf(stdout, "  %d", fTime[i]);
		else fprintf(stdout, " %d", fTime[i]);
	}
	fprintf(stdout, "%s\n", "");
}


void dfsPrint(Data data, int n)
{
	//all the print statements do the same thing, theyre just for formatting.
	//You can see an example of what this prints out in the README
	fprintf(stdout, "V   color dTime fTime  parent\n");
	for(int i = 1; i <= n; i++)
	{
		fprintf(stdout, "%u%8c%6u%6u%7d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
	}

}
