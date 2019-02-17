#include <stdio.h>
#include <math.h>


//this code prints prime numbers till the number which you entered


int main(){
	
	int n,i,nn,*a,j;
	
	printf("enter a number = ");
	scanf("%d",&n);
	nn=sqrt(n);

	a=(int*)malloc(sizeof(int)*(n+1));
	
	
	for(i=1;i<=n;i+=2){
		a[i]=0;
	}
	a[2]=0;
	
	for(i=4;i<=n;i+=2){
		a[i]=1;
	}
	
	for(i=3;i<=nn;i+=2){
		
		if(a[i]==0){
			for(j=i*i;j<=n;j=j+i*2){
				a[j]=1;
			}
		}
	}
	
	printf("2 ");
	for(i=3;i<=n;i+=2){
		if(a[i]==0){
			printf("%d ",i);
		}
	}
	
	
	
	
	return 0;
}
