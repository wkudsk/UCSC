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
	if(task == 'D') fprintf(stdout, " Dijkstra's Algorithm starting at vertex %d\n", s);
	if(task == 'P') fprintf(stdout, " Primm's Algorithm starting at vertex %d\n", s);
	fprintf(stdout, " V  fringeWgt  parent  status\n");
	for(int i = 1; i <= n; i++)
	{
		if(status[i] == UNSEEN) fprintf(stdout, "%2d     %22c\n", i, status[i]);
		else fprintf(stdout, "%2d   %8.2lf   %5d  %6c\n", i, fringeWgt[i], parent[i], status[i]);
	}
}