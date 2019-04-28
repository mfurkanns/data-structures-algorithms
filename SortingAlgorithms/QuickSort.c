#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int partition(int arr[],int p,int r)
{
	int i,j,tmp,pivot;
	
	pivot=arr[p];
	i=p;
	j=r;
	
	while(i<j)
	{
		while(arr[i]<=pivot)
			i++;
			
		while(arr[j]>pivot)
			j--;
			
		tmp=arr[i];
		arr[i]=arr[j];
		arr[j]=tmp;
	}
	tmp=arr[i];
	arr[i]=arr[j];
	arr[j]=tmp;

	tmp=arr[j];
	arr[j]=arr[p];
	arr[p]=tmp;
	
	return j;
}

void quickSort(int arr[],int p,int r)
{
	int s;
	if(p<r)
	{
		s=partition(arr,p,r);
		quickSort(arr,p,s-1);
		quickSort(arr,s+1,r);		
	}
}

int main(){
	srand(time(NULL));
	
	int array[10],k=10,i;
	
	for(i=0;i<k;i++)
		array[i]=rand()%100+1;
	
	printf("Unsorted array :\n");	
	for(i=0;i<k;i++)
		printf("%d ",array[i]);	
	printf("\n");
	quickSort(array,0,k-1);
	
	printf("\n");
	printf("Sorted array :\n");	
	for(i=0;i<k;i++)
		printf("%d ",array[i]);		
					// Complexity of QuickSort : Worst Case = N*N
					//			     Best Case = N*logN
	return 0;
}
