#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"intVec.h"

int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	FILE* out; /* file handle for output */
	char str[256]; /* char array to store str from input file */
   bool first = true;


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

      intVec* myVec;
      int i = 0;
   	while( fgets(str, 256, in) != NULL )
   	{
         if(first)
         {
            int length = str[0] - 48;
            first = false;
            myVec = (intVec*) malloc(sizeof(intVec)*length); //myVec is an array.
         

            for(int k = 0; k < length; k++)
            {
               myVec[k] = intmakeEmptyVec();
            }
         }
         else
         {
            int pointA = str[0] - 48;
            int pointB = str[2] - 48;
            float weight;
            if(str[5] == '.')
            {
               weight = str[4] - 48;
               weight = weight + (float)(str[6]/10);
            }
         }
     	}
}