#include <stdio.h>
#include <string.h>
#define MAX 100

int xx;
typedef struct{			// stacki bir struct olarak tanýmlayabiliriz
	int item[MAX];		
	int top;		
}Stack;
void initStack(Stack *s){	// stack dolmaya 0.bolumden baslar
	s->top=0;
}
int isEmpty(Stack *s){	// stackin bos olup olmadýgýný kontrol eden fonksiyon
	if(s->top==0)
		return 1;
	else
		return 0;
}
int isFull(Stack *s){	// stackin dolu olup olmadýgýný kontrol eden fonksiyon
	if(s->top==MAX)
		return 1;
	else
		return 0;
}
int push(int x,Stack *s){	//stacke eleman atan fonksiyon
	if(isFull(s))
		return 0;
	else{
		s->item[s->top]=x;
		s->top++;
		return 1;
	}
}
int pop(Stack *s,int x){	// stackten eleman cikartan fonksiyon
	if(isEmpty(s))
		return 0;
	else{
		--s->top;
		x = s->item[s->top];
		return x;
	}
}
int peek(Stack *s,int x){	// stackin en ustundeki elemani gosteren fonksiyon
	int adr;
	if(isEmpty(s))
		return 0;
	else{
		adr = s->top-1;
		x = s->item[adr];
		return x;
	}
}
int sayicek(char dizi[],int i){		// bir stringin icindeki sayiyi ceken ve donduren fonksiyon
	int j,k=i,carp=1,top=0,deg;	
	while(i<strlen(dizi)){
		if(dizi[i]<=57&&dizi[i]>=48){
			i++;	
		}
		else break;		
	}
	xx=i-1;
	for(j=i-1;k<=j;j--){		
		deg=(dizi[j]-48)*carp;		
		top=top+deg;
		carp=10*carp;	
	}
	return top;	
}
void stackGoster(Stack *s){		// sayi stackini gosteren fonksiyon
	int i;
	printf("Sayi stack =");
	for(i=0;i<s->top;i++){
		printf("%d ",s->item[i]);
	}
	printf("\n");
}
void stackGoster2(Stack *s){	// sembol stackini gosteren fonksiyon
	int i;	
	printf("Sembol stack = ");
	for(i=0;i<s->top;i++){
		printf("%c ",s->item[i]);// stackGoster'den farkli olarak elemanlari char olarak yazdirir
	}
	printf("\n");
}

int main(){
	
	Stack *sayi_stack,*sembol_stack;
	sayi_stack=(Stack*)calloc(sizeof(Stack),1);
	sembol_stack=(Stack*)calloc(sizeof(Stack),1);
	char ifade[MAX];
	int i=0,j,p;
	int d1,d2,sonuc,x;
	
	printf("ifadeyi giriniz = ");
	scanf("%s",&ifade);
	
	while(i<strlen(ifade)){		// ifadenin icinde dolasilmaya baslanir
		if(ifade[i]<=57&&ifade[i]>=48){	// karakter eger sayi ise
			p=sayicek(ifade,i);			// sayi ile basladigi yerden itibaren sayi cekilir
			i=xx;		// sayi cekildikten sonra kalinan yer indise atanir 
			push(p,sayi_stack);	// sayi stacke yollanir
			printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));				
		}
		else{	// karakter eger sayi degil ise
			if(ifade[i]=='('){	// karakter eger ( ise
				push('(',sembol_stack);	// ( sembolu stacke atilir
				printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));
			}
			else if(ifade[i]==')'){		// karakter eger ) ise			
				while(peek(sembol_stack,i)!='('){ // ( sembolunu gorene kadar sembol stacki bosaltilir
					p=pop(sembol_stack,p);	// stackten sembol cekilir
					if(p=='*'){	// cekilen sembol eger * ise
						d1=pop(sayi_stack,d1); //sayi stackinden 1. eleman cekilir
						d2=pop(sayi_stack,d2); // sayi stackinden 2.eleman cekilir
						sonuc=d2*d1;	// dikkat islemin 1. elemani d2 olmak zorundadir
						push(sonuc,sayi_stack);	//sonuc sayi stackine atilir
						printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));						
					}
					else if(p=='/'){	// cekilen sembol eger / ise ilgili islemler yapilir				
						d1=pop(sayi_stack,d1);
						d2=pop(sayi_stack,d2);
						sonuc=d2/d1;
						push(sonuc,sayi_stack);
						printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));
					}
					else if(p=='+'){		// cekilen sembol eger + ise ilgili islemler yapilir			
						d1=pop(sayi_stack,d1);
						d2=pop(sayi_stack,d2);
						sonuc=d2+d1;
						push(sonuc,sayi_stack);
						printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));
					}
					else{			// cekilen sembol eger - ise ilgili islemler yapilir			
						d1=pop(sayi_stack,d1);
						d2=pop(sayi_stack,d2);
						sonuc=d2-d1;
						push(sonuc,sayi_stack);
						printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));
					}
				}
				pop(sembol_stack,p); // en son ( sembolu stackten atilir
			}
			else{ // +-*/ ise
				if(peek(sembol_stack,p)=='('||isEmpty(sembol_stack)){ //stack bossa veya ( varsa
					push(ifade[i],sembol_stack); // sembol direk eklenir
					printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));
				}
				else if((peek(sembol_stack,p)=='+'||peek(sembol_stack,p)=='-')&&(ifade[i]=='*'||ifade[i]=='/')){ 
				// eger, stackte yeni gelecek olan islemden  dusuk oncelikli islem varsa orn: stack=(+),yeni islem=(*)
					push(ifade[i],sembol_stack); // direk sembol stacke eklenir
					printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));
				}
				else if((peek(sembol_stack,p)=='*'||peek(sembol_stack,p)=='/')&&(ifade[i]=='*'||ifade[i]=='/')){
				// eger stackte, yeni gelecek olan islemle  esit oncelikli islem varsa orn: stack(*),yeni islem=(/)
					while(peek(sembol_stack,p)!='('&&sembol_stack->top!=0&&(peek(sembol_stack,p)!='+'&&peek(sembol_stack,p)!='-')){
					// kendisinden daha dusuk oncelikli islem gorene kadar sembol stacki bosaltilir.
						x=pop(sembol_stack,p);
						if(x=='*'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2*d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));
						}
						if(x=='/'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2/d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}						
					}
					push(ifade[i],sembol_stack); // sembol eklenir
					printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));					
				}				
				else if((peek(sembol_stack,p)=='+'||peek(sembol_stack,p)=='-')&&(ifade[i]=='+'||ifade[i]=='-')){
				// eger stackte, yeni gelecek olan islemle  esit oncelikli islem varsa orn: stack(-),yeni islem=(+)
					while(peek(sembol_stack,p)!='('&&sembol_stack->top!=0){
					// sembol stacki, ( sembolunu gorene kadar ya da bos olana kadar bosaltilir
						x=pop(sembol_stack,p);
						if(x=='+'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2+d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else if(x=='-'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2-d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else if(x=='/'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2/d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else{
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2*d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
					}
					push(ifade[i],sembol_stack); // sembol stacke eklenir
					printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));
				}
				else if((peek(sembol_stack,p)=='*'||peek(sembol_stack,p)=='/')&&(ifade[i]=='+'||ifade[i]=='-')){
					// eger stackte, yeni gelecek olan islemden  yuksek oncelikli islem varsa orn: stack(/),yeni islem=(-)
					while(peek(sembol_stack,p)!='('&&sembol_stack->top!=0){
						// sembol stacki, ( sembolunu gorene kadar ya da bos olana kadar bosaltilir
						x=pop(sembol_stack,p);
						if(x=='+'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2+d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else if(x=='-'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2-d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else if(x=='/'){
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2/d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
						else{
							d1=pop(sayi_stack,p);
							d2=pop(sayi_stack,p);
							sonuc=d2*d1;
							push(sonuc,sayi_stack);
							printf("Stacke eklenen sayi = %d\n",peek(sayi_stack,p));							
						}
					}
					push(ifade[i],sembol_stack); // sembol stacke eklenmistir
					printf("Stacke eklenen sembol = %c\n",peek(sembol_stack,p));
				}
			}
		}
		stackGoster(sayi_stack); // sayi stacki ekrana yazdirilir
		stackGoster2(sembol_stack); // sembol stacki ekrana yazdirilir
		printf("\n");		
		i++;	// dongu indisi arttirilir
	} 
 	// sayi ve sembol stackleri onceliklerine uygun sekilde doldurulmus veya bosaltilmistir
 	// simdi ise stacklerdeki sayi ve islemlere gore sonuc bulma var
	while(!(isEmpty(sayi_stack))&&!(isEmpty(sembol_stack))){
	// iki stackten birisi bosalana kadar islemler devam eder
		x=pop(sembol_stack,p); // sembol stackinden islem operatoru cekilir
		if(x=='*'){ // islem * ise gerekli islemler yapilir
			d1=pop(sayi_stack,p);
			d2=pop(sayi_stack,p);
			sonuc=d2*d1;
			push(sonuc,sayi_stack); // islemin sonucu sayi stackinde saklanir
		}
		else if(x=='/'){ // islem / ise gerekli islemler yapilir
			d1=pop(sayi_stack,p);
			d2=pop(sayi_stack,p);
			sonuc=d2/d1;
			push(sonuc,sayi_stack); // islemin sonucu sayi stackinde saklanir
		}
		else if(x=='+'){ // islem + ise gerekli islemler yapilir
			d1=pop(sayi_stack,p);
			d2=pop(sayi_stack,p);
			sonuc=d2+d1;
			push(sonuc,sayi_stack); // islemin sonucu sayi stackinde saklanir
		}
		else{ // islem - ise gerekli islemler yapilir
			d1=pop(sayi_stack,p);
			d2=pop(sayi_stack,p);
			sonuc=d2-d1;
			push(sonuc,sayi_stack); // islemin sonucu sayi stackinde saklanir
		}
	}	
	printf("\nsonuc = %d\n",peek(sayi_stack,p));
	
	return 0;
}
