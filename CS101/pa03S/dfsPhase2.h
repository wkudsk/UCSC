#include "intVec.h"
#ifndef C101dfsPhase2
#define C101dfsPhase2


//SCC will hold all important values for finding 
//Strong Connected Components of a graph.
typedef struct SCCNode * SCC;

/*Constructors*/


/* makeEmptySCCSet()
 * precondition: n > 0, where n is the amount of vertices
 * post condition: an empty SCCNode with everything initialized.
 */
SCC makeEmptySCCSet(int n);

/* dfsPhase2()
 * graph is the graph that you want to use to find SCC. (Usually a transpose of a original graph).
 * SCC starts off as empty, its how all the information is still stored through all the recursive calls.
 * int n is amount of vertices, and i is the vertex youre on.
 * precondition: n > 0, graph is a transpose, n >= i > 0.
 * postcondition: a data set that helps find SCC's of a graph.
 */
SCC dfsPhase2(IntVec* graph, SCC scc, int n, int i);


/*Access Functions*/


/* sccPrint()
 * precondition: dfsPhase2 was run properly, n > 0.
 * postcondition: SCC data sets is printed to console in proper format.
 */
void sccPrint(SCC scc, int n);

#endif