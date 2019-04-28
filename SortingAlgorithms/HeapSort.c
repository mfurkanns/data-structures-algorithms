#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findBiggestChild(int HT[],int i,int n)
{
	if(2*i+2<n)
	{
		if(HT[2*i+1]<HT[2*i+2])
		{
			return 2*i+2;
		}
		else
		{
			return 2*i+1;	
		}
	}
	else if(2*i+1<n){
		return 2*i+1;
	}
	else
	{
		return 0;
	}	
}

void downHeap(int arr[],int n)
{
	int adr,i,tmp;
	
	i=0;
	adr=findBiggestChild(arr,i,n);
	
	while(adr!=0&&arr[i]<arr[adr])
	{
		tmp=arr[i];
		arr[i]=arr[adr];
		arr[adr]=tmp;
		
		i=adr;
		adr=findBiggestChild(arr,i,n);
	}	
}




void maxHeapify(int arr[],int n){
	
	int i,parent,tmp,j,adr;
	
	for(i=n-1;i>=1;i--)
	{
		parent=(i-1)/2;
		if(arr[i]>arr[parent])
		{
			j=i;
			while(parent>=0&&arr[j]>arr[parent])
			{
				tmp=arr[j];
				arr[j]=arr[parent];
				arr[parent]=tmp;
				
				int adr,z;
				z=j;
				adr=findBiggestChild(arr,z,n);
				while(adr!=0&&arr[z]<arr[adr])
				{
					tmp=arr[z];
					arr[z]=arr[adr];
					arr[adr]=tmp;
					
					z=adr;
					adr=findBiggestChild(arr,z,n);					
				}
				j=parent;
				parent=(j-1)/2;
			}	
		}	
	}
}

void heapSort(int arr[],int n)
{	
	int i,tmp,size,j;
	
	maxHeapify(arr,n);
	
	for(i=n-1;i>=1;i--)
	{
		tmp=arr[0];
		arr[0]=arr[i];
		arr[i]=tmp;
		downHeap(arr,i);
	// 	maxHeapify(arr,i);
		
	}
}

int main()
{
	
	srand(time(NULL));
	
	int n,*array,i,dizi[] = {4,10,7,3,5,7,3,7,7,1};
	int k=10;
	
	for(i=0;i<k;i++){
		dizi[i]=rand()%50+1;
	}
	printf("Unsorted array : \n");
	
	for(i=0;i<k;i++){
		printf("%d ",dizi[i]);
	}
	printf("\n");

	
	heapSort(dizi,k);
	printf("Sorted array :\n");
	for(i=0;i<k;i++){
		printf("%d ",dizi[i]);
	}
	 												// Complexity of HeapSort = n.logN
	return 0 ;
}
