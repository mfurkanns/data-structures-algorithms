#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100

int HT[MAX];

void insert(int HT[],int *n,int value)
{
	int i,tmp,parent;
	
	if(*n==0){
		HT[0]=value;
		*n=*n+1;
	}
	else{
		HT[*n]=value;	
		i=*n;
		*n=*n+1;
		parent=(i-1)/2;		
		while(i>=1&&HT[i]<HT[parent]) // HT[i]<HT[parent] - for minHeap , HT[i]>HT[parent] - for maxHeap
		{			
			tmp=HT[i];
			HT[i]=HT[parent];
			HT[parent]=tmp;
			i=parent;
			parent=(i-1)/2;
		}
	}
}

int findSmallestChild(int HT[],int i,int *n)
{
	if(2*i+2<*n){
		if(HT[2*i+1]<HT[2*i+2])
		{
			return 2*i+1;
		}
		else
		{
			return 2*i+2;	
		}
	}
	else if(2*i+1<*n){
		return 2*i+1;
	}
	else
	{
		return 0;
	}	
}

int removeMin(int HT[],int *n)
{
	int min,i,adr,tmp;
	
	if(n==0)
		return -1;
	min=HT[0];
	*n=*n-1;
	HT[0]=HT[*n];
	HT[*n]=min;
	
	i=0;
	adr=findSmallestChild(HT,i,n);
	while(adr!=0&&HT[i]>HT[adr]){
		tmp=HT[i];
		HT[i]=HT[adr];
		HT[adr]=tmp;
		i=adr;
		adr=findSmallestChild(HT,i,n);
	}
	printf("Element removed from tree successfully.\n");
	return min;
}

void printTree(int HT[],int *n)
{
	int i=0;
	for(i=0;i<*n;i++){
		printf("%d ",HT[i]);
	}
	printf("\n");
}

int main()
{
	srand(time(NULL));
	
	int i,k,min,*n;
	*n=0;
	
	for(i=0;i<15;i++)
	{
		k=rand()%10+1;
		insert(HT,n,k);
	}
	
	printf("\n");
	printTree(HT,n);
	printf("Number of elements = %d\n",*n);
	
	min=removeMin(HT,n);
	printf("Removed element(min element) = %d\n",min);
	printf("\n");
	printf("New tree : \n");
	printTree(HT,n);
	
	printf("\nNumber of elements = %d\n",*n);
	
	return 0;
}
