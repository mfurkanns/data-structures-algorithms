#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void merge(int arr[],int p,int q,int r)
{
	int *b,n,i,j,k;
	
	n=r-p+1;
	b=(int*)malloc(sizeof(int)*n);
	i=p; j=q+1; k=0;
	
	while(i<=q&&j<=r)
	{
		if(arr[i]<arr[j])
			b[k++]=arr[i++];
		else
			b[k++]=arr[j++];
	}

	while(i<=q)
		b[k++]=arr[i++];		
	while(j<=r)
		b[k++]=arr[j++];
	
	for(i=p,k=0;i<=r;i++,k++)
		arr[i]=b[k];
	
	free(b);
}

void mergeSort(int arr[],int p,int r)
{
	int q;
	
	if(p<r)
	{
		q=(p+r)/2;
		mergeSort(arr,p,q);
		mergeSort(arr,q+1,r);
		merge(arr,p,q,r);
	}
}

int main(){
	srand(time(NULL));
	
	int dizi[10],i,m,k=10;
	
	for(i=0;i<k;i++)
		dizi[i]=rand()%100+1;
	
	
	printf("Unsorted array :\n");
	for(i=0;i<k;i++)
		printf("%d ",dizi[i]);
	
	printf("\n");
	
	mergeSort(dizi,0,9);
	printf("Sorted array :\n");
	for(i=0;i<k;i++)
		printf("%d ",dizi[i]);
					// Complexity of MergeSort : N*logN
	
	return 0;
}
