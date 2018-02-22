#include "intVec.h"
#ifndef C101dfsTrace1
#define C101dfsTrace1

typedef struct DataNode * Data;

typedef struct StackNode * finishStk1;

/*Constructors*/

/* makeEmptyDataSet()
 * precondition: There must be a corresponding IntVec* to go with Data.
 *				 n >= 0
 * postcondition: give an empty data struct that can be filled with dfs()
 */
Data makeEmptyDataSet(int n);

finishStk1 makeEmptyStack(int n);

/* dfs()
 * precondition: graph must not be null.
 * 				 n >= 0, v >= 1
 * 				 makeEmptyDataSet() must be called before this can be called.
 * postcondition: returns a struct called Data that contains arrays with the color,
 *				  dTime, fTime, and parent for each vector.
 */
Data dfs(IntVec* graph, Data data, int n, int v);

Data dfsPhase2(IntVec* graph, Data data, int n, int i);

/* Manipulation Procedures*/



void pushStack(finishStk1 finishStack, int vec);


int popStack(finishStk1 finishStack);


/*Access Functions*/

bool isEmpty(finishStk1 finishStack);

finishStk1 getDataStack(Data data);


void stackPrint(finishStk1 finishStack);


/* dfsPrint()
 * precondition: Data must have data, therefore there must be a non-empty intVec.
 *				 n >= 0
 * postcondition: prints out the information in Data.
 */

void dfsPrint(Data data, int n);

#endif