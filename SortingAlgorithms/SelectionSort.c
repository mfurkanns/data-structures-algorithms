#include <stdio.h>


int main(){
	
	
	int n,i,j,*a,min,minind;
	
	printf("enter the number of element = ");
	scanf("%d",&n);
	
	a=(int*)calloc(sizeof(int),n);
	
	for(i=0;i<n;i++){
		printf("%d.element = ",i+1);
		scanf("%d",&a[i]);
	}
	
	for(i=0;i<n-1;i++){
		min=a[i];
		minind=i;
		for(j=i+1;j<n;j++){
			if(a[j]<min){
				min=a[j];
				minind=j;
			}
		}
		a[minind]=a[i];
		a[i]=min;		
	}	
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	
	
	
	
	// complexity of selection sort = best case : n*n , worst case : n*n
	
	
	
	return 0;
}
