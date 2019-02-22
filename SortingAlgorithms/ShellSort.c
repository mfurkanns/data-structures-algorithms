#include <stdio.h>


int main(){
	
	
	int n,i,j,*a,tmp,t,m;
	
	printf("enter the number of elements = ");
	scanf("%d",&n);
	
	a=(int*)calloc(n,sizeof(int));	
	
	for(i=0;i<n;i++){
		printf("%d.element = ",i+1);
		scanf("%d",&a[i]);
	}
	
	i=n/2;
	
	while(i!=0){
		for(j=i;j<n;j++){
			t=j-i;
			m=j;
			while(t>=0){
				if(a[m]<a[t]){
					tmp=a[m];
					a[m]=a[t];
					a[t]=tmp;
					m=t;			
				}
				t=t-i;
			}
		}
		i/=2;
	}
	
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}

	
	
	// complexity of shell sort : best case = n^(5/3) or n^(4/3) worst case = n^2 = n*n
	
	
	return 0 ;
}
