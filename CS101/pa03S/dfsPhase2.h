#include "intVec.h"
#ifndef C101dfsPhase2
#define C101dfsPhase2

typedef struct SCCNode * SCC;


SCC makeEmptySCCSet(int n);

SCC dfsPhase2(IntVec* graph, SCC scc, int n, int i);

void sccPrint(SCC scc, int n);

#endif