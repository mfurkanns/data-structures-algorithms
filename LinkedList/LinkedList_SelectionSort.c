#include <stdio.h>
#include <stdlib.h>


typedef struct link{
	int value;
	struct link *next;
	struct link *prev;
}Node;

Node *create(){
	Node *news;
	news=(Node*)malloc(sizeof(Node));
	news->next=NULL;
	news->prev=NULL;
	return news;
}

int main(){
	
	
	int i,n,a,min,tp;
	Node *p,*head,*dene,*tmp,*ind;
	
	printf("enter the number of elements = ");
	scanf("%d",&n);	
	
	for(i=0;i<n;i++,p=p->next){
		printf("%d.element = ",i+1);
		scanf("%d",&a);
		
		dene=create();
		if(i==0){
			p=malloc(sizeof(Node));
			p->value=a;
			dene->prev=p;
			p->next=dene;
			head=p;
			continue;
		}		
		p->value=a;
		dene->prev=p;
		p->next=dene;		
	}
	
	for(p=head;p->next!=NULL;p=p->next){
		printf("%d ",p->value);
	}
//beginning	of selection sort 
	for(p=head;p->next!=NULL;p=p->next){
		min=p->value;
		tmp=p;
		for(ind=p->next;ind->next!=NULL;ind=ind->next){
			if((ind->value)<min){
				min=ind->value;
				tmp=ind;
			}
		}
		tp=p->value;
		p->value=tmp->value;
		tmp->value=tp;		
	}	
	
	printf("\n");	
	for(p=head;p->next!=NULL;p=p->next){
		printf("%d ",p->value);
	}
	
	
	return 0;
}
