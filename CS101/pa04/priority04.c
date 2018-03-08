#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "adjWgtVec.h"
#include "minPQ.h"
#include "loadWgtGraph.h"
#include "priority04.h"


void greedyTree(AdjWgtVec* myVec, int task, int s, int n, int* status, int* parent, double* fringeWgt)
{
   //make MinPQ
   status[s] = INTREE;
   parent[s] = -1;
   fringeWgt[s] = 0.0;
   MinPQ pq = createPQ(n, status, fringeWgt, parent);
   
   updateFringe(task, pq, myVec[s], s);
   
   while(isEmptyPQ(pq) == 0)
   {
      int v = getMin(pq);
      fprintf(stdout, "%d\n", v);
      delMin(pq);
      updateFringe(task, pq, myVec[v], v);
   }
   //end: Print output
}

void updateFringe(int task, MinPQ pq, AdjWgtVec myVec, int v)
{
   //check to see if djisktra's or primm's
   if(task == 'P')
   {
      AdjWgtVec remVec;
      remVec = myVec;
      while(adjWgtSize(remVec) > 0)
      {
         AdjWgt edge = adjWgtTop(remVec);
         int w = edge.to;
         fprintf(stdout, "%d\n", w);
         double newWgt = edge.wgt;
         fprintf(stdout, "%lf\n", newWgt);
         if(getStatus(pq, w) == UNSEEN)
         {
            insertPQ(pq, w, newWgt, v);
         }
         else if(getStatus(pq, w) == FRINGE)
         {
            if(newWgt < getPriority(pq, w)) decreaseKey(pq, w, newWgt, v);
         }
         adjWgtVecPop(remVec);  
      } 
   }
   else if(task == 'D')
   {
      double myDist = getPriority(pq, v);
      AdjWgtVec remVec;
      remVec = myVec;
      while(adjWgtSize(remVec) > 0)
      {
         AdjWgt edge = adjWgtTop(remVec);
         int w = edge.to;
         fprintf(stdout, "w = %d\n", w);
         double newDist = myDist + edge.wgt;
         if(getStatus(pq, w) == UNSEEN)
         {
            insertPQ(pq, w, newDist, v);
         }
         else if(getStatus(pq, w) == FRINGE)
         {
            if(newDist < getPriority(pq, w)) decreaseKey(pq, w, newDist, v);
         }
         adjWgtVecPop(remVec);  
      }
   }
   else
   { 
      fprintf(stderr, "Use flag -P or -D to decide whether or not to use Primm's or Djisktra's Algorithm.\n");
      exit(EXIT_FAILURE);
   }
   
   return;
}

void printOutput()
{

}

//initial portion of main function that reads input and stdoutput is taken from a handstdout from Sesh's CMPS12B 
//class last quarter. Once it gets to the while loop, all the code is original.
int main(int argc, char* argv[])
{
	FILE* in;  /* file handle for input */  
	char str[256]; /* char array to store str from input file */
   int task;            // 'P' or 'D'
   int s;             // start vertex
   int* status;
   int* parent;
   double* fringeWgt;

   int argin = 1;

   //Checks to make sure that the program was passed an input and stdoutput
	if( argc > 4 && argc <= 1)
   {
		fprintf(stderr, "Usage: %s <-P or -D> <int startVex> <input file>\n", argv[0]);
   	exit(EXIT_FAILURE);
   }
   
   if(strcmp((argv[argin]), "-P") == 0)
   {
      task = 'P';
      argin++;
   }

   else if(strcmp((argv[argin]), "-D") == 0)
   {
      task = 'D';
      argin++;
   }

   else
   {
      fprintf(stderr, "Use flag <-P> or <-D>\n");
      exit(EXIT_FAILURE);
   }
   
   s = (int)argv[argin][0] - 48;
   argin++;
   /* open input file for reading */
   in = fopen(argv[argin], "r");
   if( in==NULL )
   {
   	fprintf(stderr, "Unable to read from file %s\n", argv[argin]);
   	exit(EXIT_FAILURE);
   }

   

   //initialize the array of adjWgtVecs as well as a counter, m, that counts edges.
   AdjWgtVec* myVec;
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

         status = malloc(sizeof(int)*(length+1));
         parent = malloc(sizeof(int)*(length+1));
         fringeWgt = malloc(sizeof(double)*(length+1));
         myVec = malloc(sizeof(AdjWgtVec)*(length+1)); //myVec is an array.
         

         //This fills the array with empty adjWgtVecs.
         for(int k = 0; k <= length; k++)
         {
            myVec[k] = adjWgtMakeEmptyVec();
            parent[k] = -1;
            status[k] = UNSEEN;
            fringeWgt[k] = 1.0/0.0;
         }  
      }
	
      //Makes sure that proper format is used.
      else if((int)str[0] >= 48 && (int)str[0] <= 57)
      {
         
         //Store the non-ascii values in pointA and pointB.
         int pointA;
         int pointB;
         double weight;

         pointA = (int)str[0] - 48;
         int k = 2;
         if((int)str[1] >= 48 && (int)str[1] <= 57)
         {
            pointA = (pointA*10) + (str[1] - 48);
            k = k + 1;
         }

         pointB = (int)str[k] - 48;

         if((int)str[k+1] >= 48 && (int)str[k+1] <= 57)
         {
            pointB = (pointB*10) + ((int)str[k+1] - 48);
         }         
         
         k += 3;
         
         if(str[k] == '.')
         {
            weight = str[k-1] - 48;
            weight = weight + ((double)(str[k+1] - 48)/10.0);
         }
            
         else
         {
            weight = 0.0;
         }

         AdjWgt* edge = malloc(sizeof(AdjWgt));
         edge->to = pointB;
         edge->wgt = weight;
         //push the edge to the vector array, and then increment m.
         adjWgtVecPush(myVec[pointA], *edge);
         if(task == 'P')
         {
            edge->to = pointA;
            adjWgtVecPush(myVec[pointB], *edge);
         }
         m++;
      }
      else
      {
      	 fprintf(stderr, "Incorrect input format, see line: %s\n", str);
      	 exit(EXIT_FAILURE);
      }     
   }  

   greedyTree(myVec, task, s, length, status, parent, fringeWgt);
   
   fclose(in);
   return(EXIT_SUCCESS);

}