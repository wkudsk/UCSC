#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "loadWgtGraph.h"
#include "adjWgtVec.h"
#include "minPQ.h"

void printTree(int task, int s, int n, int* status, int* parent, double* fringeWgt)
{
	if(task == 'D') fprintf(stdout, " Dijkstra's Algorithm with Start Vertex: %d\n", s);
	if(task == 'P') fprintf(stdout, " Primm's Algorithm with Start Vertex: %d\n", s);
	fprintf(stdout, " V  status  fringeWgt  parent\n");
	for(int i = 1; i <= n; i++)
	{
		if(status[i] == UNSEEN) fprintf(stdout, "%2d     %22c\n", i, status[i]);
		else fprintf(stdout, "%2d  %6c   %8.2lf   %5d\n", i, status[i], fringeWgt[i], parent[i]);
	}
}