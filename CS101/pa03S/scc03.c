#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"
#include "loadGraph.h"
#include "dfsTrace1.h"
#include "dfsPhase2.h"

void printGraph(IntVec* myVec, int length, int m)
{
   //Step 1, print out the original matrix
   printAdjVerts(myVec, length, m);

   //Step 2, print out the AdjMatrix
   if(length <= 12)
   {
      int** adjMatrix = makeAdjMatrix(myVec, length);
      printAdjMatrix(adjMatrix, length);
   }

}

void findSCCs(IntVec* myVec, int length, int m)
{
   //Step 1, Make transpose
   IntVec* tVec = transposeGraph(myVec, length);

   //Step 2, run dfs to get a data set, and print out the data.
   Data data = makeEmptyDataSet(length);
   for(int v = 1; v <= length; v++)
   {
      data = dfs(myVec, data, length, v);
   }
   finishStk1 finishStack = getStack(data);
   
   //This is where I print the data set.
   dfsPrint(data, length);

   //This is where I print the stack
   stackPrint(finishStack);


   //Step 3, print the transpose
   printAdjVerts(tVec, length, m);

   //Step 4, print out the AdjMatrix of transpose
   if(length <= 12)
   {
     int** adjTranMatrix = makeAdjMatrix(tVec, length);   
     printAdjMatrix(adjTranMatrix, length); 
   }

   //This is where I create the SCC data set, using the finish stack.
   SCC dataT = makeEmptySCCSet(length);
   while(!isEmpty(finishStack))
   {
      int popInt = popStack(finishStack);
      dataT = dfsPhase2(tVec, dataT, length, popInt);
   }
   //this is where I print the SCC data set
   sccPrint(dataT,length);
}

//initial portion of main function that reads input and output is taken from a handout from Sesh's CMPS12B 
//class last quarter. Once it gets to the while loop, all the code is original.
int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	char str[256]; /* char array to store str from input file */
   bool undirected;
   int argin = 1;

   //Checks to make sure that the program was passed an input and output
	if( argc > 3 && argc <= 1)
   {
		fprintf(stderr, "Usage: %s <input file> with a potential flag: <-U>\n", argv[0]);
   	exit(EXIT_FAILURE);
   }
   
   if(strcmp((argv[argin]), "-U") == 0)
   {
      undirected = true;
      argin++;
   }
   else
   {
      undirected = false;
   }

   /* open input file for reading */
   in = fopen(argv[argin], "r");
   if( in==NULL )
   {
   	fprintf(stderr, "Unable to read from file %s\n", argv[argin]);
   	exit(EXIT_FAILURE);
   }

   

   //initialize the array of IntVecs as well as a counter, m, that counts edges.
   IntVec* myVec;
   bool first = true;
   //length is the length of the array given in the first input, this is also n
   int length = 0;
   int m = 0;
   while( fgets(str, 256, in) != NULL )
   {
      //if this is the first element in the input, then find the size of the array.
      if(first && ((int)str[0] >= 48 && (int)str[0] <= 57))
      {

         length = ((int)str[0] - 48);
         //if the number is greater than 9, add the second number.
         if((int)str[1] >= 48 && (int)str[1] <= 57)
         {
            length = (length*10) + ((int)str[1] - 48);
         }
         first = false;
         myVec = malloc(sizeof(IntVec)*(length+1)); //myVec is an array.
         

         //This fills the array with empty IntVecs.
         for(int k = 0; k <= length; k++)
         {
            myVec[k] = intMakeEmptyVec();
         }
      }
	
      //Makes sure that proper format is used.
      else if((int)str[0] >= 48 && (int)str[0] <= 57)
      {
         
         //Store the non-ascii values in pointA and pointB.
         int pointA = (int)str[0] - 48;
         int k = 2;
         if((int)str[1] >= 48 && (int)str[1] <= 57)
         {
            pointA = (pointA*10) + (str[1] - 48);
            k = k + 1;
         }

         int pointB = (int)str[k] - 48;

         if((int)str[k+1] >= 48 && (int)str[k+1] <= 57)
         {
            pointB = (pointB*10) + ((int)str[k+1] - 48);
         }            

         //push the edge to the vector array, and then increment m.
         intVecPush(myVec[pointA], pointB);
         if(undirected)
         {
            intVecPush(myVec[pointB], pointA);
         }
         m++;
      }
      else
      {
      	 fprintf(stderr, "Incorrect input format, see line: %s\n", str);
      	 exit(EXIT_FAILURE);
      }      
   }

   
   printGraph(myVec, length, m);
   findSCCs(myVec, length, m);


   fclose(in);
   return(EXIT_SUCCESS);
}