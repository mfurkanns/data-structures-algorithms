#include <stdio.h>
#include <stdlib.h>
#define N 50
#define M 150
typedef struct Queue{
	
	int value[M];
	int rear;
	
}Queue;

int isEmpty(Queue *q)
{
	if(q->rear==0)
		return 1;
	else
		return 0;
}

void enQueue(Queue *q,int x)
{
	if(q->rear!=M)
	{
		q->value[q->rear]=x;
		q->rear++;
	}
}

int deQueue(Queue *q)
{
	int i,x;
	if(!isEmpty(q))
	{
		x=q->value[0];
		
		for(i=1;i<=q->rear;i++)
		{
			q->value[i-1]=q->value[i];
		}
		return x;
	}
}


void breadthFirstSearch(int graph[][N],int source,int destination){
	
	int *valid,cik=0,i,j,x;
	Queue *q;
	q->rear=0;
	
	valid = (int*)malloc(sizeof(int)*N);
	
	enQueue(q,source);
	valid[source]=1;
	
	while(cik&&!isEmpty(q))
	{
		x=deQueue(q);
		
		if(x==destination)
		{
			printf("Destination (%d) is found !\n",x);
			cik=0;
		}
		else
		{
			printf("%d ->",x);
			for(i=0;i<N;i++)
			{
				if(graph[x][i]==1&&valid[x]==0)
				{
					enQueue(q,i);
					valid[x]=1;					
				}
			}
		}
	}
	if(isEmpty(q))
		printf("Couldn't be reached !\n");
	
}


