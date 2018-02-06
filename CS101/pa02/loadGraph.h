#include "intVec.h"
#ifndef C101loadGraph
#define C101loadGraph

/*Constructors:*/

/* makeAdjMatrix()
 * precondition: myVec must not be null.
 * 				 n >= 0
 * postcondition: returns a 2D array matrix of length n.
 */
int** makeAdjMatrix(IntVec* myVec, int n);

/* transposeGraph()
 * precondition: need to have an original graph.
 *				 n >= 0
 * postcondition: returns an array of IntVecs in which (a,b) -> (b,a).
 */
IntVec* transposeGraph(IntVec* origGraph, int n);

/*Access Functions*/

/* printAdjVerts()
 * precondition: origGraph needs to be constructed. 
 *		 		 length & m >= 0.
 * postcondition: a formatted adjcency list printed to console.
 */
void printAdjVerts(IntVec* origGraph, int length, int m);

/* printAdjMatrix()
 * precondition: adjMatrix must be construction. 
 * 				 n >= 0.
 * postcondition: a formatted matrix printed to console.
 */
void printAdjMatrix(int** adjMatrix, int n);

#endif