#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Que{
	int dizi[MAX];
	int front;
	int rear;
}Que;


int isEmpty(Que *q){
	if(q->rear==-1)
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

void enQueue(Que *q,int x){
	
	if(isEmpty(q)){
		q->front=0;
		q->rear++;
		q->dizi[q->rear]=x;
	}
	else{
		q->rear++;
		q->dizi[q->rear]=x;
	}
}

int deQueue(Que *q){
	int x;
	if(isEmpty(q))
		printf("Queue is empty !");
	else{
		x=q->dizi[q->front];
		q->dizi[q->front]=NULL;
		q->front++;
	}
	return x;
}

void print(Que *q){
	
	int i;	
	for(i=q->front;i<=q->rear;i++){
		printf("%d ",q->dizi[i],i);
	}	
	printf("\n");
}

int main(){
	
	int i=0,n,x;
	Que *dizi=(Que*)calloc(sizeof(Que),1);
	
	dizi->front=-1;
	dizi->rear=-1;
	
	
	printf("Enter the number of queue = ");
	scanf("%d",&x);
	
	for(i=0;i<x;i++){
		printf("%d.Element = ",i+1);
		scanf("%d",&n);
		enQueue(dizi,n);
		
	}
	
	print(dizi);
	
	n=deQueue(dizi);
	
	print(dizi);
	
	
	
	return 0 ;
}
