#ifndef C101priority04
#define C101priority04

void greedyTree(AdjWgtVec* myVec, int task, int s, int n, int* status, int* parent, double* fringeWgt);

void updateFringe(MinPQ pq, AdjWgtVec myVec, int v);

void calcPriority();

void printOutput();

#endif