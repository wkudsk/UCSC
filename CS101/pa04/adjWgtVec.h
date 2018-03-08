/* adjWgtVec.h
 * (what is the overall purpose of this file? Replace question with your text)
 */

#ifndef C101AdjWgtVec
#define C101AdjWgtVec
/* Multiple typedefs for the same type are an error in C. 
 * The above ifndef and define prevent multiple copies of code below.
 */

typedef struct AdjWgtVecNode * AdjWgtVec;

typedef struct AdjWgtStruct
    {
    int to;
    double wgt;
    }
    AdjWgt;


/** adjWgtInitCap: initial capacity after adjWgtMakeEmptyVec() */
static const int adjWgtInitCap = 4;

/* Access functions
 */

/** adjWgtTop()
 * (what are the preconditions? Replace question with your text)
 */
AdjWgt adjWgtTop(AdjWgtVec myVec);

/** adjWgtData()
 * precondition: 0 <= i < adjWgtSize(myVec).
 */
AdjWgt adjWgtData(AdjWgtVec myVec, int i);

/** adjWgtSize()
 * precondition: myVec has been constructed.
 */
int adjWgtSize(AdjWgtVec myVec);

/** adjWgtCapacity()
 * precondition: myVec has been constructed.
 */
int adjWgtCapacity(AdjWgtVec myVec);

/* Constructors
 */

/** adjWgtMakeEmptyVec()
 * preconditions: none.
 * postconditions: Let /return be the value returned by adjWgtMakeEmptyVec().
 *    Then adjWgtCapacity(/return) == 4, adjWgtSize(/return) == 0).
 */
AdjWgtVec adjWgtMakeEmptyVec(void);


/* Manipulation Procedures
 */

/** adjWgtVecPush()
 * precondition: myVec has been constructed.
 * postconditions: Let /sz/ = adjWgtSize(myVec) before the call.
 *                 Let /cap/ = adjWgtCapacity(myVec) before the call.
 *    Then after the call, adjWgtSize(myVec) == /sz/+1,
 *        and adjWgtTop(myVec) == newE and adjWgtData(myVec, /sz/) == newE.
 *    Also, for all 0 <= i < /sz/: adjWgtData(myVec, i) is unchanged.
 *    Also, if (/sz/+1) > /cap/, then after the call,
 *        adjWgtCapacity(myVec) = 2 * /cap/.
 *    otherwise, adjWgtCapacity(myVec) is unchanged.
 */
void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE);

/** adjWgtVecPop()
 * precondition: myVec has been constructed and adjWgtSize(myVec) > 0.
 * postconditions: Let /sz/ = adjWgtSize(myVec) before the call.
 *                 Let /cap/ = adjWgtCapacity(myVec) before the call.
 *    Then after the call, adjWgtSize(myVec) == /sz/-1,
 *        adjWgtTop(myVec) == adjWgtData(/sz/-2).
 *    Also, for all 0 <= i < /sz/-1: adjWgtData(myVec, i) is unchanged.
 *    Also, adjWgtCapacity(myVec) is unchanged.
 */
void adjWgtVecPop(AdjWgtVec myVec);


#endif
