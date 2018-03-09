/* minPQ.h MinPQ is a priority queue that will keep track of the status, priority and parent of each vertex.
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/* isEmpty()
 * precondition: pq must be initialized.
 * postcondition: returns whether or not pq is empty in the form of a zero or one.
 */
int isEmptyPQ(MinPQ pq); 

/* getMin()
 * precondition: pq must have values in it (not empty).
 * postcondition: returns the value with the lowest priority. 
 */
int getMin(MinPQ pq);

/* getStatus()
 * precondition: pq must have been initialized with numVertices > 0.
 * postcondition: returns the status of a vertex in the form of 't', 'u', or 'f'.
 */
int getStatus(MinPQ pq, int id);

/* getParent()
 * precondition: pq must have been initialized with numVertices > 0.
 * postcondition: returns the parent of a vertex in the form of an int. If the vertex is a root, returns -1.
 */
int getParent(MinPQ pq, int id);

/* getPriority()
 * precondition: pq must have been initialized with numVertices > 0.
 * postcondition: returns the priority of a vertex in the form of a double.
 */
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/* delMin()
 * precondition: pq size must be greater than 0.
 * postcondition: the smallest priority is forgotten and the size of pq is decremented. 
 */
void delMin(MinPQ pq);

/* insertPQ()
 * precondition: pq must be initialized, parent, id and priority > 0
 * postcondition: pq updates the position id in its arrays to have a new parent: par, and weight: priority.
 */
void insertPQ(MinPQ pq, int id, double priority, int par);

/* decreaseKey()
 * precondition: pq must be initialized and id must already exist in pq.
 * postcondition: changes the vertex id in pq to a new priority and parent based on new information discovered.
 */
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/* createPQ()
 * precondition: n > 0 and status, priority and parent are already initialized to size n+1.
 * postcondition: a MinPQ struct that will hold and change information related to status, priority and parent.
 */
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif
