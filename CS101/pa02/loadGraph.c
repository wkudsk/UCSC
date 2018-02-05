#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "loadGraph.h"
#include "intVec.h"

int** makeAdjMatrix(IntVec* myVec)
{
	int n = sizeof(myVec)/sizeof(struct IntVecNode);
	int** adjMatrix = malloc((n+1)*sizeof(int*));

	for(int i = 0; i <= n; i++)
	{
		adjMatrix[i] = malloc((n+1)*sizeof(int));
		IntVec Vec = myVec[i];
		for(int j = 0; j <= initSize(Vec); j++)
		{
			int vector = intData(Vec, j);
			adjMatrix[i][vector] = 1;
		}
	}
	for(int i = 0; i <=n; i++)
	{
		for(int j = 0; j <=n; j++)
		{
			if(adjMatrix[i][j] != 1)
			{
				adjMatrix[i][j] = 0;
			}
		}
	}


	return adjMatrix;
}

IntVec* transposeGraph(IntVec* origGraph, int n)
{

}

void printAdjVerts(IntVec* origGraph)
{
	//this prints output to a text file. This does its best to follow the format of graph.java
   //n is the number of vertices
   //m is the number of edges
   fprintf(stdout, "n = %u\n", length);
   fprintf(stdout, "m = %u\n", m);
   for(int i = 1; i <= length; i++)
   {
      //takes one of the vecs and then prints all of the edges from it.
      IntVec Vec = origGraph[i];
      if(intSize(Vec) != 0)
      {
         fprintf(stdout, "%i: [", i);
         for(int j = intSize(Vec) - 1; j >= 0; j--)
         {
            
            if(j != 0)fprintf(stdout,  "%i, ", intData(Vec, j));
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

void printAdjMatrix(int** adjMatrix)
{

}