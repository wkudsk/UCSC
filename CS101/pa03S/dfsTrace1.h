#include "intVec.h"

#ifndef C101dfsTrace1
#define C101dfsTrace1

typedef struct DataNode * Data;
typedef struct StackNode * finishStk1;

/* Constructors */

/* makeEmptyStack()
 * precondition: n > 0
 * postcondition: initializes an empty stack that can have things pushed into it.
 */
finishStk1 makeEmptyStack(int n);

/* makeEmptyDataSet()
 * precondition: There must be a corresponding IntVec* to go with Data.
 *				 n >= 0
 * postcondition: give an empty data struct that can be filled with dfs()
 */
Data makeEmptyDataSet(int n);


/* dfs()
 * precondition: graph must not be null.
 * 				 n >= 0, v >= 1
 * 				 makeEmptyDataSet() must be called before this can be called.
 * postcondition: returns a struct called Data that contains arrays with the color,
 *				  dTime, fTime, and parent for each vector.
 */
Data dfs(IntVec* graph, Data data, int n, int v);

/* Manipulation Procedures */

/* pushStack()
 * precondition: finishStack is initialized with makeEmptyStack().
 * 				 vec > 0.
 * postcondition: vec is now in finishStack->stack[finishStack->size].
 */
void pushStack(finishStk1 finishStack, int vec);



/* popStack()
 * precondition: finishStack is initialized with makeEmptyStack().
 * 				 finishStack->size > 0.
 * postcondition: size is decremented making the last value unaccessible.
 *				  the last value is returned to user.
 */
int popStack(finishStk1 finishStack);


/*Access Functions*/

/* isEmpty()
 * precondition: finishStack is initialized with makeEmptyStack().
 * postcondition: returns a bool that tells you if the stack is empty or not.
 */
bool isEmpty(finishStk1 finishStack);


/* getStack()
 * precondition: dfs() id run for a proper graph, creating a Data struct.
 * postcondition: returns the finishStack that was stored in the Data struct.
 */
finishStk1 getStack(Data data);

/* dfsPrint()
 * precondition: Data must have data, therefore there must be a non-empty intVec.
 *				 n >= 0
 * postcondition: prints out the information in Data.
 */
void dfsPrint(Data data, int n);

/* stackPrint()
 * precondition: dfs() and getStack has been run, finishStack.size == n
 * postcondition: the finishStack is printed to console.
 */
void stackPrint(finishStk1 finishStack);

#endif