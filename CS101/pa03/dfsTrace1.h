#include "intVec.h"
#ifndef C101dfsTrace1
#define C101dfsTrace1

typedef struct DataNode * Data;

/*Constructors*/

Data makeEmptyDataSet(int n);

/* dfs()
 * precondition: myVec must not be null.
 * 				 n >= 0
 * postcondition: returns a 2D array matrix of length n.
 */
Data dfs(IntVec* graph, Data data, int n, int v, int counter);

IntVec* makeCopy(IntVec* graph, int n);

/* Manipulation Procedures*/

/*Access Functions*/

/* printDfs()
 * precondition: Data must have data, therefore there must be a non-empty myVec.
 *				 n >= 0
 * postcondition: prints out the information in Data.
 */
void dfsPrint(Data data, int n);



#endif