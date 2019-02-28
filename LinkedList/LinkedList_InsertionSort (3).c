#include <stdio.h>
#include <stdlib.h>

typedef struct link{
	int value;
	struct link *next;
	struct link *prev;
}Node;

Node *create(){
	Node *news;
	news=malloc(sizeof(Node));
	news->next=NULL;
	news->prev=NULL;
	
	return news;
}

int main(){
	
	int i,n,a,tp,z;
	Node *p,*news,*k,*tmp;
	Node *head=(Node*)malloc(sizeof(Node));
	head->prev=NULL;
	
	printf("enter the number of elements = ");
	scanf("%d",&n);
	
	for(i=0;i<n;i++,p=p->next){
		printf("%d.element = ",i+1);
		scanf("%d",&a);
		
		news=create();
		
		if(i==0){
			p->value=a;
			news->prev=p;
			p->next=news;
			head=p;
			continue;
		}
		p->value=a;
		news->prev=p;
		p->next=news;		
	}
	
	for(p=head;p->next!=NULL;p=p->next){
		printf("%d ",p->value);
	}
	
//beginning of insertion sort
	head->prev=NULL;
	for(p=head->next;p->next!=NULL;p=p->next){
		
		tp=p->value;
		k=p->prev;
		
		while((k!=NULL)&&(k->value>tp)){
			
			k->next->value=k->value;
			k->value=tp;
			k=k->prev;			
		}		
	}
	
	printf("\n");
	
	for(p=head;p->next!=NULL;p=p->next){
		printf("%d ",p->value);
	}
	
	
	return 0;
}
