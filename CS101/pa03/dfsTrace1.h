#include "intVec.h"
#ifndef C101dfsTrace1
#define C101dfsTrace1

typedef struct DataNode * Data;

/*Constructors:*/

/* dfs()
 * precondition: myVec must not be null.
 * 				 n >= 0
 * postcondition: returns a 2D array matrix of length n.
 */
Data dfs(IntVec* myVec);


/*Access Functions*/

/* printDfs()
 * precondition: Data must have data, therefore there must be a non-empty myVec.
 *				 n >= 0
 * postcondition: prints out the information in Data.
 */
void printDfs(Data data);



#endif