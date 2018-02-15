#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"
#include "dfsTrace1.h"

struct DataNode
{
	int* graph;
	char* color;
	int* dTime;
	int* fTime;
	int* parent;
	int counter;
};

/*Constructors*/

Data makeEmptyDataSet(int n)
{
	Data data = malloc(sizeof(struct DataNode));
	data->graph = malloc((n+1)*sizeof(int));
	data->color = malloc((n+1)*sizeof(char));
	data->dTime = malloc((n+1)*sizeof(int));
	data->fTime = malloc((n+1)*sizeof(int));
	data->parent = malloc((n+1)*sizeof(int));
	data->counter = 1;
	for(int k = 0; k <= n; k++)
	{
		data->dTime[k] = 0;
		data->fTime[k] = 0;
		data->color[k] = 'W';
		data->parent[k] = -1;
	}

	return data;
}


Data dfs(IntVec* graph, Data data, int n, int v)
{
	//Start by finding the vector at point V.
	for(int i = v; i <= n; i++)
	{
		IntVec vec = graph[i];
		//if the point is black or gray, then there is no point in looking at it yet.
		if(data->color[i] != 'B' && data->color[i] != 'G')
		{	
			//if the point has yet to be visited, enter in its discovery time, increment counter, and look for the points inside.
			data->dTime[i] = data->counter;
			data->color[i] = 'G';
			data->counter++;
		}
		//while the inside is not empty, try to find the points and recursively store their information.
		if(data->color[i] != 'B')
		{
			while(intSize(vec) != 0)
			{
				
				int edge = intData(vec, intSize(vec));
				//once the edege is stored, pop it from the original IntVec so that you don't visit it twice.
				intVecPop(vec);
				//if you find a new edge, store its parent, then move to recursion.
				data->parent[edge] = i;
				if(data->color[edge] != 'B')
				{	
					v = edge;
					fprintf(stdout, "Entering recursion for %u\n", v);
					data = dfs(graph, data, n, v);
				}
				
			}
			//once you're done with an edge, turn it black, store finish time, and increment counter.
			data->fTime[i] = data->counter;
			data->color[i] = 'B';
			data->counter++;

			//if the vector has a parent, the for loop needs to go back to the parent, instead of continuing with the array.
			if(data->parent[i] != -1)
			{
				i = data->parent[i];
			}

		}
	}
	return data;
}


IntVec* makeCopy(IntVec* graph, int n)
{
	IntVec* copyVec = malloc(sizeof(IntVec)*(n+1)); //remVec is an array.
         
    //This fills the array with empty IntVecs.
    for(int k = 0; k <= n; k++)
    {
    	copyVec[k] = intMakeEmptyVec();
    }

    for(int a = 1; a <= n; a++)
    {
    	for(int j = 1; j <= intSize(graph[a]); j++)
    	{
            int b = intData(graph[a], j);
            intVecPush(copyVec[a], b);
        }
    }

    return copyVec;
}

/*Manipulation Procedures*/

/*Access Functions*/

void dfsPrint(Data data, int n)
{
	fprintf(stdout, "V   color dTime fTime  parent\n");
	for(int i = 1; i <= n; i++)
	{
		if(data->dTime[i] <= 9 && data->fTime[i] <= 9)
		{	
			if(data->parent[i] < 0)fprintf(stdout, "%u       %c     %u     %u    %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
			else fprintf(stdout, "%u       %c     %u     %u     %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
		}
		else if(data->dTime[i] <= 9 && data->fTime[i] > 9) 
		{
			if(data->parent[i] < 0) fprintf(stdout, "%u       %c     %u    %u    %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
			else fprintf(stdout, "%u       %c     %u    %u     %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
		}
		else if(data->dTime[i] > 9 && data->fTime[i] <= 9)
		{
			if(data->parent[i] < 0) fprintf(stdout, "%u       %c    %u    %u    %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
			else fprintf(stdout, "%u       %c    %u    %u     %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
		}
		else
		{
			if(data->parent[i] < 0) fprintf(stdout, "%u       %c    %u    %u    %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
			else fprintf(stdout, "%u       %c    %u    %u     %d\n",i, data->color[i], data->dTime[i], data->fTime[i], data->parent[i]);
		}
	}

}
