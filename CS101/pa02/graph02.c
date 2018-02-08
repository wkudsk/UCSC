#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"
#include "loadGraph.h"

//initial portion of main function that reads input and output is taken from a handout from Sesh's CMPS12B 
//class last quarter. Once it gets to the while loop, all the code is original.
int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	char str[256]; /* char array to store str from input file */
   

   //Checks to make sure that the program was passed an input and output
	if( argc != 2)
   {
		printf("Usage: %s <input file>\n", argv[0]);
   	exit(EXIT_FAILURE);
   }

   /* open input file for reading */
   in = fopen(argv[1], "r");
   if( in==NULL )
   {
   	printf("Unable to read from file %s\n", argv[1]);
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
       
        
      //if this is the first line of input, do something different than the other lines.
      if(first && (int)str[0] >= 48 && (int)str[0] <= 57)
      {

         length = ((int)str[0] - 48);
         //if the number is greater than 9, add the second number.
         if((int)str[1] >= 48 && (int)str[1] <= 57)
         {
            length = (length*10) + ((int)str[1] - 48);
         }
         first = false;
         myVec = malloc(sizeof(IntVec)*(length + 1)); //myVec is an array.
         

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
            pointA = (pointA*10) + ((int)str[1] - 48);
            int k = k + 1;
         }

         int pointB = (int)str[k] - 48;
         
         if((int)str[k+1] >= 48 && (int)str[k+1] <= 57)
         {
            pointB = (pointB*10) + ((int)str[1] - 48);
            int k = k + 1;
         }            
         //A little bit more work has to be done for weight since its a float, and also because 
         //if there is a blank space it must be read as 0. Weight isnt saved anywhere in this program so this part is unimportant.
         float weight;
         if(str[5] == '.')
         {
            weight = str[4] - 48;
            weight = weight + (float)((str[6] - 48)/10);
         }
            
         else
         {
            weight = 0.0;
         }

         //push the edge to the vector array, and then increment m.
         intVecPush(myVec[pointA], pointB);
         m++;
      }
      else
      {
      	 printf("Incorrect input format, see line %s\n", str);
      	 exit(EXIT_FAILURE);
      }      
  }

//Step 1, print out the original matrix
printAdjVerts(myVec, length, m);

//Step 2, print out the AdjMatrix
if(length <= 12)
{
   int** adjMatrix = makeAdjMatrix(myVec, length);
   printAdjMatrix(adjMatrix, length);
}
//Step 3, make the transpose and print
IntVec* tVec = transposeGraph(myVec, length);
printAdjVerts(tVec, length, m);

//Step 4, print out the AdjMatrix of transpose
if(length <= 12)
{
   int** adjTMatrix = makeAdjMatrix(tVec, length);   
   printAdjMatrix(adjTMatrix, length); 
}

//Step 5, make transpose of transpose, aka original.
IntVec* originalVec = transposeGraph(tVec, length);
printAdjVerts(originalVec, length, m);

//Step 6, make the AdjMatrix of original graph again.
if(length <= 12)
{
   int** adjOriginalMatrix = makeAdjMatrix(originalVec, length);
   printAdjMatrix(adjOriginalMatrix, length);
}

	
   fclose(in);
   return(EXIT_SUCCESS);
}
