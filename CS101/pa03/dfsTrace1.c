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

//Allocates memory for a Data struct.
Data makeEmptyDataSet(int n)
{
	Data data = malloc(sizeof(struct DataNode));
	data->graph = malloc((n+1)*sizeof(int));
	data->color = malloc((n+1)*sizeof(char));
	data->dTime = malloc((n+1)*sizeof(int));
	data->fTime = malloc((n+1)*sizeof(int));
	data->parent = malloc((n+1)*sizeof(int));
	
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
				if(data->color[edge] != 'B' && data->color[edge] != 'G')
				{	
					//if you find a new edge, store its parent, then move to recursion.
					data->parent[edge] = i;
					v = edge;
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
				return data;
			}

		}
	}

	return data;
}

/*Access Functions*/

void dfsPrint(Data data, int n)
{
	//all the print statements do the same thing, theyre just for formatting.
	//You can see an example of what this prints out in the README
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
