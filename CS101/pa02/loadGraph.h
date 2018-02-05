#ifndef C101loadGraph
#define C101loadGraph

int** makeAdjMatrix(IntVec* myVec);

IntVec* transposeGraph(IntVec* origGraph, int n);

void printAdjVerts(IntVec* origGraph);

void printAdjMatrix(int** adjMatrix);

#endif