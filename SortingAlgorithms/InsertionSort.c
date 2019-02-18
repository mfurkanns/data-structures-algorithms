#include <stdio.h>

int main(){
	
	int n=5,i,j,*a,tmp;
	
	printf("enter the number of element = ");
	scanf("%d",&n);
	
	a=(int*)calloc(n,sizeof(int));
	
	for(i=0;i<n;i++){
		printf("%d.element = ",i+1);
		scanf("%d",&a[i]);
	}
	
	for(i=1;i<n;i++){
		j=i-1;
		tmp=a[i];
		
		
		while(j>=0&&a[j]>tmp){			
			a[j+1]=a[j];
			j--;		
			
		}
		a[j+1]=tmp;
	}
	
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	
	
	// complexity of insertion sort = best case : n , worst case : n*n
	
	
	return 0 ;
}
