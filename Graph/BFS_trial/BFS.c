#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define N 3000

typedef struct Kelime{	// Kelimelerin tutulacaðý struct yapýsý oluþturulur.
	
	char kelime[5];
	int ind;
	
}Kelime;

typedef struct Que{		// BFS te kuyruk yapýsý kullanacaðýz.
	
	int dizi[MAX];
	int rear;
	
}Que;

int isEmpty(Que *q){	// Kuyruðun boþ olup olmadýðý döndürülür.
	if(q->rear==0)
		return 1;
	else
		return 0;
}       

int isFull(Que *q){		// Kuyruðun dolu olup olmadýðý döndürülür.
	if(q->rear==MAX)
		return 1;
	else
		return 0;
}      

int enQueue(Que *q,int x){		// Kuyruða yeni eleman ekler.
	
	if(isFull(q)==1){
		return 0;
	}
	else{
		q->dizi[q->rear]=x;
		q->rear++;
		return 1;
	}
}

int deQueue(Que *q){		// Kuyruktan eleman çýkar ve çýkan eleman döndürülür.
	int x,i,item;
	if(isEmpty(q))
		return 0;
	else{
		item=q->dizi[0];
		for(i=1;i<=q->rear;i++){
			q->dizi[i-1]=q->dizi[i];
		}
		q->rear--;
	}
	return item;
}

int compare(char s1[5],char s2[5]){		// Verilen 5 harfli iki stringin kaç hanesinin farklý olduðu döndürülür.
	
	int i,fark=0;
	
	for(i=0;i<5;i++){
		if(s1[i]!=s2[i]){
			fark++;
		}
	}
	return fark;
}

int bul(Kelime *sozcukler,char s1[5],int xx){		// Verilen 5 harfli stringin graphýn kaçýncý hanesine ait olduðu döndürülür.
	
	int i;
	
	for(i=0;i<xx;i++){
		if(!strcmp(sozcukler[i].kelime,s1)){
			return i;
		}
	}
	return -1; // Eðer verilen kelime graphta yoksa -1 döndürülür.
}

void breadthFirst(int **graph,Kelime *sozcukler,int source,int destination,int xx){// BFS'nin yapýldýðý yerdir. 
	// Parametre olarak graphý,kelimelerin olduðu diziyi, kelimenin graphtaki yeri ve o kelimeden türetilecek olan kelimenin graftaki yeri .
	
	Que *q=(Que*)malloc(sizeof(Que));	// Kuyruk oluþturulur.
	q->rear=0;
	int girdiMi[xx],cik=1;		// Node'un kuyruða girip girmediðini kontrol ettiðimiz bir dizi mevcut.
	int v,i;
	for(i=0;i<xx;i++){			// Ýlk baþta dizi sýfýrlanýr.Çünkü henüz kuyruða giren yok .
		girdiMi[i]=0;
	}
	enQueue(q,source);			// Ýlk kelimenin graphtaki yeri kuyruða eklenir.
	girdiMi[source]=1;			// Kuyruða girdiði için kontrol dizimizin ilgili indisi 1 yapýlýr.Yani kuyruða girdiði iþaretlenir.
	
	while(!isEmpty(q)&&cik){	// Kuyruk tamamen boþalana kadar veya çýkýþ düðümüne ulaþana kadar döngüde kalýnýr.
	
		v=deQueue(q);			// Kuyruktan eleman çýkartýlýr.
		
		if(!strcmp(sozcukler[v].kelime,sozcukler[destination].kelime)){		// Kuyruktan çýkan kelimenin türetilecek olan kelime olup olmadýðý kontrol edilir.
			printf("%s    Donusturuldu !\n",sozcukler[v].kelime);				// Eðer bulunduysa yazdýrýlýr.
			cik=0;							// Ve donguden cýkýlmasý için cik = 0 yapýlýr.
			return ;
		}
		else{										// Eðer türetilecek kelime deðilse 
			printf("%s ->",sozcukler[v].kelime); 	// Kelime ekrana yazdýrýlýr.
			for(i=0;i<xx;i++){					// O kelimenin komþularýnýn bulunduðu dizi gezilir.
				if(graph[v][i]==1){					// Eðer komþusu ise
					if(girdiMi[i]==0){				// Ve kuyruða girmediyse
						enQueue(q,i);				// Kuyruða eklenir.
						girdiMi[i]=1;				// Kuyruða girdiði iþaretlenir.
					}
				}
			}
		}
	}
	
	if(isEmpty(q))			// Eðer kuyruk boþ ise kelime bulunamamýþtýr.
		printf("Donusum yok !\n");
}

void donusum(int **graph,Kelime *sozcukler,char s1[5],char s2[5],int xx){	// Dönüþümün yapýlacaðý fonksiyondur.
	
	int source,destination;
	
	source=bul(sozcukler,s1,xx);	// Verilen kelimelerin graphtaki kaçýncý node olduðu bulunur.
	destination=bul(sozcukler,s2,xx);	// Verilen kelimelerin graphtaki kaçýncý node olduðu bulunur.
	
	if(source==-1||destination==-1){ // Eðer verilen kelimelerden birisi graphta yoksa Bulunamadi yazýsý yazdýrýlýr.
		printf("Hatali kelime girisi yaptiniz !\n");
	}
	else
	{
		breadthFirst(graph,sozcukler,source,destination,xx);	// BFS fonksiyonuna gerekli parametreler verilip iþlem gerçekleþtirilir.
	}
}

int main(){	
	
	int i,j,n,x,kk;
	char a[5],xx,s1[5],s2[5];	
	FILE *fp;
		
	int **graph;	// Adjacency matris
	
	Kelime *sozcukler;	// Kelimelerin olduðu yer
	
	sozcukler = (Kelime*)malloc(sizeof(Kelime)*N); // 2415 adet kelime mevcuttur.
	
	graph = (int**)malloc(sizeof(int*)*N);		// Matris allocate edilir.
	for(i=0;i<N;i++){
		graph[i]=(int*)malloc(sizeof(int)*N);
	}
	
	fp=fopen("kelime.txt","r");
	j=0;
	while(!feof(fp)){	// Dosyanýn sonuna kadar okuma yapýlýr.
		fread(sozcukler[j].kelime,sizeof(char),5,fp); // 5 karakter okunur.
		xx=fgetc(fp);
		j++; 			// Toplam kelime sayýsý tutulur.
		
	}	
	kk=j;
	printf("Kelime sayisi = %d\n",j);
	for(i=0;i<kk;i++){
		for(j=0;j<kk;j++){
			if(compare(sozcukler[i].kelime,sozcukler[j].kelime)==1){ // Eðer stringler arasýnda sadece 1 fark varsa komþuluk iliþkisi kurulur.
				graph[i][j]=1;
				graph[j][i]=1;
			}
		}
	}
	
	printf("(Lutfen kelimeleri kelime.txt dosyasindan seciniz.)\n");
	printf("1.kelimeyi giriniz = ");
	scanf("%s",&s1);
	printf("2.kelimeyi giriniz = ");
	scanf("%s",&s2);
	
	donusum(graph,sozcukler,s1,s2,kk);

	return 0;
}
