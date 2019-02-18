#include <stdio.h>


int main(){
	
	int n,i,j,*a,tmp,xchg;
	
	printf("enter number of element = ");
	scanf("%d",&n);
	
	a=(int*)calloc(n,sizeof(int));
	
	for(i=0;i<n;i++){
		printf("%d.element = ",i+1);
		scanf("%d",&a[i]);
	}
	i=0;
	xchg=1;
	while(i<=(n-2)&&xchg){
		xchg=0;
		for(j=0;j<(n-1);j++){
			if(a[j]>a[j+1]){
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				xchg=1;
			}
		}
		i++;
	}
	
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	
	
	// complexity of bubble sort = best case : n , worst case : n*n  
	
	
	
	
	return 0;
}
