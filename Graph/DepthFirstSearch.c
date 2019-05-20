#include <stdio.h>
#define N 20

typedef struct Stack{
	
	int value[N];
	int top;
	
}Stack;

int isFull(Stack *s)
{
	if(s->top==N)
		return 1;
	else
		return 0;
}

int isEmpty(Stack *s)
{
	if(s->top==0)
		return 1;
	else
		return 0;
}

void push(Stack *s,int x)
{
	if(!isFull(s))
	{
		s->value[s->top]=x;
		s->top++;
	}	
}

int pop(Stack *s)
{
	int val;
	
	if(!isEmpty(s))
	{
		val=s->value[s->top-1];
		s->top--;
		return val;
	}
}


void depthFirstSearch(int **graph,int source,int destination)
{
	int i,*valid,cik=1,val;
	valid=(int*)malloc(sizeof(int)*N);
	
	Stack *s;
	s=(Stack*)malloc(sizeof(Stack));
	s->top=0;
	
	for(i=0;i<N;i++)
	{
		valid[i]=0;
	}
	
	push(s,source);
	valid[source]=1;
	
	
	
	while(!isEmpty(s)&&cik)
	{
		val=pop(s);
		if(val==destination)
		{
			printf("%d Reached to the destination \n",val);
			cik=0;
			return;
		}
		else{
			printf("%d -> ",val);
			for(i=0;i<N;i++)
			{
				if(graph[val][i]==1){
					if(valid[i]==0){
						push(s,i);
						valid[i]=1;
					}
				}
			}	
		}
	}
	
	if(isEmpty(s))
		printf("Couldn't be reached !\n");
	
}


