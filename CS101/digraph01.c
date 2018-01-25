#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intVec.h"

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

   //initialize the array of IntVecs as well as a counter.
   IntVec* myVec;
   bool first = true;
   int length = 0;
   while( fgets(str, 256, in) != NULL )
   {
      //if this is the first element in the input, then find the size of the array.
       
        

      if(first)
      {
         
         length = str[0] - 48;
         first = false;
         myVec = malloc(sizeof(IntVec)*length); //myVec is an array.
         
         //This fills the array with empy IntVecs.
         for(int k = 0; k <= length; k++)
         {
               
            myVec[k] = intMakeEmptyVec();
               
         }

      }



      else
      {
         
         //Store the non-ascii values in pointA and pointB.
         int pointA = (int)str[0] - 48;
         int pointB = (int)str[2] - 48;
            
         //A little bit more work has to be done for weight since its a float, and also because 
         //if there is a blank space it must be read as 0.
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

         intVecPush(myVec[pointA], pointB);
   
      }      
  	}

   for(int i = 0; i < length; i++)
   {
      IntVec Vec = myVec[i];
      if(intSize(Vec) != 0)
      {
         fprintf(out, "%i: ", i);
         for(int j = 1; j < intSize(Vec); j++)
         {
            //Prints to output file, still not entirely sure out to format output.
            fprintf(out,  "%i ", intData(Vec, j));
         }
         fprintf(out, "%s\n", "");
      }
   }


   fclose(in);
   fclose(out);
   return(EXIT_SUCCESS);
}