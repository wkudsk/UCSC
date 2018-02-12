#include "intVec.h"
#include "dfsTrace1.h"

struct DataNode
{
	int* graph;
	char* color;
	int* dTime;
	int* fTime;
	int* parent;
};

Data dfs(IntVec* graph, int n)
{
	Data data = malloc(sizeof(struct DataNode));
	data->graph = malloc((n+1)*sizeof(int));
	data->color = malloc((n+1)*sizeof(char));
	data->dTime = malloc((n+1)*sizeof(int));
	data->fTime = malloc((n+1)*sizeof(int));
	data->parent = malloc((n+1)*sizeof(int));

	IntVec* remVec = makeCopy(graph, n); //remVec is a copy of graph array.
         
    int counter = 1;


	while(remVec != NULL)
	{
		IntVec vec = remVec[i]
	}

	return data;
}

void dfsPrint(struct data, int n)
{

}

IntVec makeCopy(IntVec* graph, int n)
{
	IntVec* copyVec = malloc(sizeof(IntVec)*(n+1)); //remVec is an array.
         
    //This fills the array with empty IntVecs.
    for(int k = 0; k <= n; k++)
    {
    	copyVec[k] = intMakeEmptyVec();
    }

    for(int a = 1; a <= n; a++)
    {
    	for(int j = 1; j <= intSize(graph[a]); j++)
    	{
            int b = intData(graph[a], j);
            intVecPush(copyVec[a], b);
        }
    }

    return copyVec;
}