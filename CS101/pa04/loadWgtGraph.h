#include "adjWgtVec.h"
#ifndef C101loadWgtGraph
#define C101loadWgtGraph

/*Constructors:*/

/* makeAdjMatrix()
 * precondition: myVec must not be null.
 * 				 n >= 0
 * postcondition: returns a 2D array matrix of length n.
 */
int** makeAdjMatrix(AdjWgtVec* myVec, int n);

/* transposeGraph()
 * precondition: need to have an original graph.
 *				 n >= 0
 * postcondition: returns an array of AdjWgtVecs in which (a,b) -> (b,a).
 */
AdjWgtVec* transposeGraph(AdjWgtVec* origGraph, int n);

/*Access Functions*/

/* printAdjVerts()
 * precondition: origGraph needs to be constructed. 
 *		 		 length & m >= 0.
 * postcondition: a formatted adjcency list printed to console.
 */
void printAdjVerts(AdjWgtVec* origGraph, int length, int m);

/* printAdjMatrix()
 * precondition: adjMatrix must be construction. 
 * 				 n >= 0.
 * postcondition: a formatted matrix printed to console.
 */
void printAdjMatrix(int** adjMatrix, int n);

#endif