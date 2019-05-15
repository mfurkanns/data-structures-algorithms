#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Que{
	int dizi[MAX];
	int rear;
}Que;


int isEmpty(Que *q){
	
	if(q->rear==0)
		return 1;
	else
		return 0;	
}


int isFull(Que *q){
	
	if(q->rear==MAX)
		return 1;
	else
		return 0;
}

void enQueue(Que *q,int a){
	
	if(isFull(q)){
		printf("Queue is full !\n");
	}
	else{
		q->dizi[q->rear]=a;
		q->rear++;
	}
}

int deQueue(Que *q){
	int i,item;
	if(isEmpty(q))
		return 0;  // if there is no any 0 in the queue
	else{
		item=q->dizi[0];
		for(i=1;i<=q->rear;i++){
			q->dizi[i-1]=q->dizi[i];
		}
		q->rear--;
		return item;
	}
	
}

void print(Que *q){
	
	int i;	
	for(i=0;i<q->rear;i++){
		printf("%d ",q->dizi[i]);
	}	
	printf("\n");
}

int main(){
	
	Que *q=(Que*)malloc(sizeof(Que));
	
	q->rear=0;
	
	enQueue(q,1);
	enQueue(q,2);
	enQueue(q,3);
	enQueue(q,4);
	
	print(q);
	
	deQueue(q);
	deQueue(q);
	
	print(q);
	
	
	
	
	return 0 ;
}
