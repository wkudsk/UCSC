#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"

//initial portion of main function that reads input and output is taken from a handout from Sesh's CMPS12B 
//class last quarter. Once it gets to the while loop, all the code is original.
int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	FILE* out; /* file handle for output */
	char str[256]; /* char array to store str from input file */
   

   //Checks to make sure that the program was passed an input and output
	if( argc != 3 )
   {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
   	exit(EXIT_FAILURE);
   }

   /* open input file for reading */
   in = fopen(argv[1], "r");
   if( in==NULL )
   {
   	printf("Unable to read from file %s\n", argv[1]);
   	exit(EXIT_FAILURE);
   }

  	/* open output file for writing */
   out = fopen(argv[2], "w");
   if( out==NULL )
   {
   	printf("Unable to write to file %s\n", argv[2]);
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
         length = str[0] - 48;
         first = false;
         myVec = malloc(sizeof(IntVec)*length+1); //myVec is an array.
         
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
         int pointB = (int)str[2] - 48;
            
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
      	 printf("Incorrect input format.\n");
      	 exit(EXIT_FAILURE);
      }      
  }

   //this prints output to a text file. This does its best to follow the format of graph.java
   //n is the number of vertices
   //m is the number of edges
   fprintf(out, "n = %u\n", length);
   fprintf(out, "m = %u\n", m);
   for(int i = 1; i <= length; i++)
   {
      //takes one of the vecs and then prints all of the edges from it.
      IntVec Vec = myVec[i];
      if(intSize(Vec) != 0)
      {
         fprintf(out, "%i: [", i);
         for(int j = intSize(Vec) - 1; j >= 0; j--)
         {
            
            if(j != 0)fprintf(out,  "%i, ", intData(Vec, j));
            else fprintf(out,  "%i", intData(Vec, j));
         }
         fprintf(out, "%s\n", "]");
      }
      else
      {
         fprintf(out, "%u NULL\n", i);
      }
   }

	
   fclose(in);
   fclose(out);
   return(EXIT_SUCCESS);
}
