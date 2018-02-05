#include "intVec.h"
#ifndef C101loadGraph
#define C101loadGraph

int** makeAdjMatrix(IntVec* myVec, int n);

IntVec* transposeGraph(IntVec* origGraph, int n);

void printAdjVerts(IntVec* origGraph, int length, int m);

void printAdjMatrix(int** adjMatrix, int n);

#endif