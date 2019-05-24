#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define N 3000

typedef struct Kelime{	// Kelimelerin tutulaca�� struct yap�s� olu�turulur.
	
	char kelime[5];
	int ind;
	
}Kelime;

typedef struct Que{		// BFS te kuyruk yap�s� kullanaca��z.
	
	int dizi[MAX];
	int rear;
	
}Que;

int isEmpty(Que *q){	// Kuyru�un bo� olup olmad��� d�nd�r�l�r.
	if(q->rear==0)
		return 1;
	else
		return 0;
}       

int isFull(Que *q){		// Kuyru�un dolu olup olmad��� d�nd�r�l�r.
	if(q->rear==MAX)
		return 1;
	else
		return 0;
}      

int enQueue(Que *q,int x){		// Kuyru�a yeni eleman ekler.
	
	if(isFull(q)==1){
		return 0;
	}
	else{
		q->dizi[q->rear]=x;
		q->rear++;
		return 1;
	}
}

int deQueue(Que *q){		// Kuyruktan eleman ��kar ve ��kan eleman d�nd�r�l�r.
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

int compare(char s1[5],char s2[5]){		// Verilen 5 harfli iki stringin ka� hanesinin farkl� oldu�u d�nd�r�l�r.
	
	int i,fark=0;
	
	for(i=0;i<5;i++){
		if(s1[i]!=s2[i]){
			fark++;
		}
	}
	return fark;
}

int bul(Kelime *sozcukler,char s1[5],int xx){		// Verilen 5 harfli stringin graph�n ka��nc� hanesine ait oldu�u d�nd�r�l�r.
	
	int i;
	
	for(i=0;i<xx;i++){
		if(!strcmp(sozcukler[i].kelime,s1)){
			return i;
		}
	}
	return -1; // E�er verilen kelime graphta yoksa -1 d�nd�r�l�r.
}

void breadthFirst(int **graph,Kelime *sozcukler,int source,int destination,int xx){// BFS'nin yap�ld��� yerdir. 
	// Parametre olarak graph�,kelimelerin oldu�u diziyi, kelimenin graphtaki yeri ve o kelimeden t�retilecek olan kelimenin graftaki yeri .
	
	Que *q=(Que*)malloc(sizeof(Que));	// Kuyruk olu�turulur.
	q->rear=0;
	int girdiMi[xx],cik=1;		// Node'un kuyru�a girip girmedi�ini kontrol etti�imiz bir dizi mevcut.
	int v,i;
	for(i=0;i<xx;i++){			// �lk ba�ta dizi s�f�rlan�r.��nk� hen�z kuyru�a giren yok .
		girdiMi[i]=0;
	}
	enQueue(q,source);			// �lk kelimenin graphtaki yeri kuyru�a eklenir.
	girdiMi[source]=1;			// Kuyru�a girdi�i i�in kontrol dizimizin ilgili indisi 1 yap�l�r.Yani kuyru�a girdi�i i�aretlenir.
	
	while(!isEmpty(q)&&cik){	// Kuyruk tamamen bo�alana kadar veya ��k�� d���m�ne ula�ana kadar d�ng�de kal�n�r.
	
		v=deQueue(q);			// Kuyruktan eleman ��kart�l�r.
		
		if(!strcmp(sozcukler[v].kelime,sozcukler[destination].kelime)){		// Kuyruktan ��kan kelimenin t�retilecek olan kelime olup olmad��� kontrol edilir.
			printf("%s    Donusturuldu !\n",sozcukler[v].kelime);				// E�er bulunduysa yazd�r�l�r.
			cik=0;							// Ve donguden c�k�lmas� i�in cik = 0 yap�l�r.
			return ;
		}
		else{										// E�er t�retilecek kelime de�ilse 
			printf("%s ->",sozcukler[v].kelime); 	// Kelime ekrana yazd�r�l�r.
			for(i=0;i<xx;i++){					// O kelimenin kom�ular�n�n bulundu�u dizi gezilir.
				if(graph[v][i]==1){					// E�er kom�usu ise
					if(girdiMi[i]==0){				// Ve kuyru�a girmediyse
						enQueue(q,i);				// Kuyru�a eklenir.
						girdiMi[i]=1;				// Kuyru�a girdi�i i�aretlenir.
					}
				}
			}
		}
	}
	
	if(isEmpty(q))			// E�er kuyruk bo� ise kelime bulunamam��t�r.
		printf("Donusum yok !\n");
}

void donusum(int **graph,Kelime *sozcukler,char s1[5],char s2[5],int xx){	// D�n���m�n yap�laca�� fonksiyondur.
	
	int source,destination;
	
	source=bul(sozcukler,s1,xx);	// Verilen kelimelerin graphtaki ka��nc� node oldu�u bulunur.
	destination=bul(sozcukler,s2,xx);	// Verilen kelimelerin graphtaki ka��nc� node oldu�u bulunur.
	
	if(source==-1||destination==-1){ // E�er verilen kelimelerden birisi graphta yoksa Bulunamadi yaz�s� yazd�r�l�r.
		printf("Hatali kelime girisi yaptiniz !\n");
	}
	else
	{
		breadthFirst(graph,sozcukler,source,destination,xx);	// BFS fonksiyonuna gerekli parametreler verilip i�lem ger�ekle�tirilir.
	}
}

int main(){	
	
	int i,j,n,x,kk;
	char a[5],xx,s1[5],s2[5];	
	FILE *fp;
		
	int **graph;	// Adjacency matris
	
	Kelime *sozcukler;	// Kelimelerin oldu�u yer
	
	sozcukler = (Kelime*)malloc(sizeof(Kelime)*N); // 2415 adet kelime mevcuttur.
	
	graph = (int**)malloc(sizeof(int*)*N);		// Matris allocate edilir.
	for(i=0;i<N;i++){
		graph[i]=(int*)malloc(sizeof(int)*N);
	}
	
	fp=fopen("kelime.txt","r");
	j=0;
	while(!feof(fp)){	// Dosyan�n sonuna kadar okuma yap�l�r.
		fread(sozcukler[j].kelime,sizeof(char),5,fp); // 5 karakter okunur.
		xx=fgetc(fp);
		j++; 			// Toplam kelime say�s� tutulur.
		
	}	
	kk=j;
	printf("Kelime sayisi = %d\n",j);
	for(i=0;i<kk;i++){
		for(j=0;j<kk;j++){
			if(compare(sozcukler[i].kelime,sozcukler[j].kelime)==1){ // E�er stringler aras�nda sadece 1 fark varsa kom�uluk ili�kisi kurulur.
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
