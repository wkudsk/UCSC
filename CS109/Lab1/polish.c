
/* William Kudsk (wkudsk) Lab1 for CMPS109 in C.
 * initial portion of main function that reads input and output is taken from a handout from Sesh's CMPS12B.
 * class from fall quarter 2017. Once it gets to the while loop, all the code is original.
 * This code might be found on https://github.com/wkudsk because that is my github account. I will work on making it private.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

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


   while( fgets(str, 256, in) != NULL )
   {
      for(int i = 0; i < len(str); i++)
      {
         if((int)str[i] >= 48 && (int)str[i] <= 57)
         {

         }
         else if(isOperation((int)str[i]))
         {

         }
      }
   }
   
   fclose(in);
   fclose(out);
   return(EXIT_SUCCESS);
}

bool isOperation(int i)
{
   if(i == 42 || i == 43 || i == 45 || i == 47) return true;
   else return false;
}