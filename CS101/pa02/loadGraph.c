#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "loadGraph.h"
#include "intVec.h"

int** makeAdjMatrix(IntVec* myVec, int n)
{
	//get the length of the array, so that the adjacency matrix can have the same length.
	int** adjMatrix = malloc((n+1)*sizeof(int*));

	for(int i = 0; i <= n; i++)
	{
		adjMatrix[i] = malloc((n+1)*sizeof(int));
		for(int j = 0; j <= n; j++)
		{
			adjMatrix[i][j] = 0;
		}
		
	}

	//this populates the rest of the matrix with 0's.
	for(int i = 0; i <=n; i++)
	{
		//Take an IntVec, put a 1 at the matrix for each edge.
		if(i != 0)
		{
			IntVec Vec = myVec[i];
			for(int j = 1; j <= intSize(Vec); j++)
			{
				int vector = intData(Vec, j);
				adjMatrix[i][vector] = 1;
			}
		}	
	}
	
	return adjMatrix;
}

IntVec* transposeGraph(IntVec* origGraph, int n)
{
	IntVec* newVec = malloc(sizeof(IntVec)*(n+1)); //newVec is an array.
	for(int i = 0; i <= n; i++)
	{
		newVec[i] = intMakeEmptyVec();   
	}

	for(int a = 1; a <= n; a++)
	{
		if(intSize(origGraph[a]) != 0)
		{
			for(int j = 1; j <= intSize(origGraph[a]); j++)
			{
				int b = intData(origGraph[a], j);
				intVecPush(newVec[b], a);
			}	
		}
	}

	return newVec;
}

void printAdjVerts(IntVec* origGraph, int length, int m)
{
	//this prints output to a text file. This does its best to follow the format of graph.java
    //length is the number of vertices
    //m is the number of edges
    fprintf(stdout, "n = %u\n", length);
    fprintf(stdout, "m = %u\n", m);
    
	for(int i = 1; i <= length; i++)
	{
       //takes one of the vecs and then prints all of the edges from it.
       IntVec Vec = origGraph[i];
       if(intSize(Vec) != 0)
       {
          fprintf(stdout, "%i  [", i);
          for(int j = intSize(Vec); j > 0; j--)
          {
            
            if(j-1 != 0) fprintf(stdout,  "%i, ", intData(Vec, j));
            else fprintf(stdout,  "%i", intData(Vec, j));

          }
          fprintf(stdout, "%s\n", "]");
       }
       else
       {
          fprintf(stdout, "%u NULL\n", i);
       }
    }
}

void printAdjMatrix(int** adjMatrix, int n)
{
	
	fprintf(stdout, "   ");
	for(int i = 1; i <= n; i++)
	{
		fprintf(stdout, "  %u", i);
	}

	fprintf(stdout, "\n   ");
	for(int i = 1; i <= n; i++)
	{
		fprintf(stdout, "---");
	}	

	fprintf(stdout, "\n");

	for(int i = 1; i <= n; i++)
	{
		fprintf(stdout, "%u :", i);
		for(int k = 1; k <= n; k++)
		{
			fprintf(stdout, "  %u", adjMatrix[i][k]);
		}
		fprintf(stdout, "\n");
	}
}
