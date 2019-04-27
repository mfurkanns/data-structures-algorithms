#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Kisi{
	
	int kimlikNo;
	char ad[30];
	char soyad[30];
	int *arkadaslar;
	int arkSayi;
	struct Kisi *sol,*sag;
		
	
}Kisi;

Kisi *kisiler=NULL;
int SIZE=0;


int menuGoster(){  // Menuyu gosteren fonksiyon.Kullanicinin secimi dondurulur.
	int b;
	printf("1.Insert New User\n");
	printf("2.Delete User\n");
	printf("3.Contains\n");
	printf("4.Friends\n");
	printf("5.Size\n");
	printf("6.Print Next\n");
	printf("7.Print Greater\n");
	printf("8.Print In Order\n");
	printf("0.Exit\n");
	printf("Lutfen islem seciniz :");
	scanf("%d",&b);
	return b;
}
Kisi *contains(Kisi *head,int kimlikNo){  // Kisinin agacta olup olmadigini bulan fonksiyondur.
										  //Parametre olarak ,agaci ve aranacak kimlik no'yu alir.
	Kisi *current=head;					  // Kisiyi buldugunda dondurur.Bulamazsa NULL dondurur.
	
	while(current!=NULL&&current->kimlikNo!=kimlikNo){
		if(current->kimlikNo>kimlikNo){
			current=current->sol;
		}
		else{
			current=current->sag;
		}
	}
	return current;
}

void insertNewUser(char ad[],char soyad[],int kimlikNo,int arkadaslar[],int arkSayi){
									 //Agaca yeni kisi ekler. Parametre olarak kisinin bilgilerini alir.
									 //Kisinin bilgileri Input.txt dosyasindan okunur.(Main'de bahsedilmiþtir)
									 //Bilgileri alinan kisi fonksiyonun icinde olusturulur.(newUser)
									 // Algoritmada gelen her eleman kimlik No'suna gore agaca yerlestirilir.
	int cik=1,i=0;					 
	Kisi *current,*parent,*newUser;	 
	newUser=(Kisi*)malloc(sizeof(Kisi));
		
	strcpy(newUser->ad,ad);
	strcpy(newUser->soyad,soyad);
	newUser->kimlikNo=kimlikNo;
	newUser->arkSayi=arkSayi;
	newUser->arkadaslar=(int*)malloc(arkSayi*sizeof(int));
	for(i=0;i<arkSayi;i++){
		newUser->arkadaslar[i]=arkadaslar[i];
	}
	newUser->sag=NULL;
	newUser->sol=NULL;
	
	if(kisiler==NULL){
		kisiler=newUser;
	}
	else{
		current=kisiler;
		while(cik){
			parent=current;
			
			if(current->kimlikNo>newUser->kimlikNo){
				current=current->sol;
				if(current==NULL){
					parent->sol=newUser;
					cik=0;
				}
			}
			else{
				current=current->sag;
				if(current==NULL){
					parent->sag=newUser;
					cik=0;
				}
			}
		}
	}	
}

void size(Kisi *head){	// Agacin icinde kac kisi oldugunu bulur. 
	if(head==NULL){		// SIZE agacta kisiyi gordugu zaman arttirilir. 
		return;
	}
	else{
		size(head->sol);
		SIZE++;
		size(head->sag);
	}
	
}

void inOrder(Kisi *head){	// Kisileri kimlik No'suna gore kucukten buyuge dogru yazdirir.
	if(head!=NULL){			// Parametre olarak agac veya alt agac alir.
		inOrder(head->sol);
		printf("Kisi ad = %s\n",head->ad);
		printf("Kisi soyad = %s\n",head->soyad);
		printf("Kimlik no = %d\n",head->kimlikNo);
		printf("\n");
		inOrder(head->sag);
	}
}

Kisi* minBul(Kisi *node){	// Verilen agacin en kucuk elemanini bulur ve dondurur.
	Kisi *current=node;		// Parametre olarak agac veya alt agac alir.
	while(current->sol!=NULL){
		current=current->sol;
	}
	return current;
}

Kisi* maxBul(Kisi *node){	// Verilen agacin en buyuk elemanini bulur ve dondurur.
	Kisi *current=node;		// Parametre olarak agac veya alt agac alir.
	while(current->sag!=NULL){
		current=current->sag;
	}
	return current;
}

Kisi* deleteUser(Kisi *head,int kimlikNo){	// Verilen kimlik No'lu kisiyi agactan siler.
	Kisi *current,*parent;					// Paremetre olarak agaci ve kimlik No'yu alir.
		// Eger kisinin sol nodu bossa,sag nodeunun en kucuk degeri ile silinecek node yer degistirir.(recursive olarak)
		// Eger kisinin sag nodeu bossa ,sol nodenun en buyuk degeri ile silinecek node yer degistirir.(recursive olarak)
		// Eger sag ve sol nodeu da bossa fonksiyon NULL dondurur.
		// Fonksiyon agacin, kisinin agactan silinmis halini dondurur.							
	if(head==NULL){			
		return head;
	}
	
	if(kimlikNo<head->kimlikNo){
		head->sol=deleteUser(head->sol,kimlikNo);
	}
	else if(kimlikNo>head->kimlikNo){
		head->sag=deleteUser(head->sag,kimlikNo);
	}
	else{
		if(head->sol==NULL){
			current=head->sag;
			return current;
		}
		else if(head->sag==NULL){
			current=head->sol;
			return current;
		}
		
		current=minBul(head->sag);
		
		strcpy(head->ad,current->ad);
		strcpy(head->soyad,current->soyad);
		head->kimlikNo=current->kimlikNo;
		head->arkSayi=current->arkSayi;
		head->arkadaslar=current->arkadaslar;
		head->sag=deleteUser(head->sag,current->kimlikNo);
	}
	return head;
}

void printNext(Kisi *head){	 // Kisinin alt agacinda bulunan elemanlari kucukten buyuge sirali sekilde ekrana yazdirir.
	inOrder(head->sol);		 // Parametre olarak kisi nodeunu alir.
	inOrder(head->sag);
}

void printGreater(Kisi *head,int kimlikNo){	// Kisinin , agacta bulunan kendisinden buyuk olan kisilerin bilgilerini ekrana yazdirir.
	if(head!=NULL){							// Parametre olarak agaci ve kisinin kimlik No'sunu alir.
		printGreater(head->sol,kimlikNo);	// Agacin icinde gezilir.Eger kimlik No kendisinden buyukse ekrana yazdirilir.
		if(head->kimlikNo>kimlikNo){
			printf("Kisi kimlik No = %d\n",head->kimlikNo);
			printf("Kisi Ad = %s\n",head->ad);
			printf("Kisi Soyad = %s\n",head->soyad);
			printf("\n");
		}
		printGreater(head->sag,kimlikNo);
	}
}


int main(){	
	int i,t,j=0,cik=1,secenek,kimlikNo,*arkadaslar=(int*)malloc(sizeof(int)*30),arkadasSayi=0;
	char ad[30],soyad[30],x,*b=(char*)malloc(sizeof(char)*30);
	Kisi *user,*user2;
	FILE *fp;
	
	secenek=menuGoster();
	while(cik){
		if(secenek==1){ //insert new user
			system("CLS");						// Ekrani temizler
			
			fp=fopen("Input.txt","r");		// Kisi bilgileri txt dosyasindan okunur.	
			x=fgetc(fp);					// Okuma islemi sirasinda dosyadan isim,soyisim,kimlik no,arkadas bilgileri uygun sekilde 
			while(!feof(fp)&&x!='\n'){		// dosyadan ilgili degskenlere yazilir.Ve insertNewUSer() fonksiyonuna parametre olarak aktarilir.
				arkadasSayi=0;
				arkadaslar=(int*)malloc(sizeof(int)*30);
				b=(char*)malloc(sizeof(char)*30);
				i=0;
				while(x!=','){
					b[i]=x;
					i++;
					x=fgetc(fp);
				}
				b[i]=NULL;
				kimlikNo=atoi(b);
				free(b);
				b=(char*)malloc(sizeof(char)*30);
				i=0;
				x=fgetc(fp);
				while(x!=' '){
					ad[i]=x;
					i++;
					x=fgetc(fp);
				}
				ad[i]=NULL;
				i=0;
				x=fgetc(fp);
				while(x!=','&&x!='\n'){
					soyad[i]=x;
					i++;
					x=fgetc(fp);
				}
				soyad[i]=NULL;
				j=0;
				if(x==','){ // Kisinin arkadasi olma durumu 			
					x=fgetc(fp);
					while(x!='\n'&&!feof(fp)){				
						i=0;
						b=(char*)malloc(sizeof(char)*30);
						while(x!='-'&&x!='\n'&&!feof(fp)){					
							b[i]=x;
							i++;
							x=fgetc(fp);
						}				
						b[i]=NULL;
						arkadaslar[j]=atoi(b);
						arkadasSayi++;			
						free(b);
						j++;
						if(x!='\n'){
							x=fgetc(fp);
						}
					}
					x=fgetc(fp);
					j=0;				
					insertNewUser(ad,soyad,kimlikNo,arkadaslar,arkadasSayi);	// Kisi agaca eklenir.		
					free(arkadaslar);
					arkadaslar=(int*)malloc(sizeof(int)*30);			
				}
				else{ // Kisinin hiç arkadasi olmama durumu 
					insertNewUser(ad,soyad,kimlikNo,arkadaslar,arkadasSayi);
					x=fgetc(fp);			
				}
			}	
			printf("Kisiler Eklenmmistir ..\n");
			secenek=menuGoster();
		}
		else if(secenek==2){	// DeleteUser
			system("CLS");
			
			printf("Silinecek kisinin kimlik No'sunu giriniz = ");
			scanf("%d",&kimlikNo);
			
			user=contains(kisiler,kimlikNo);	
			if(user==NULL){			// Kimlik No'su verilen kisinin agacta olup olmadigi kontrolu yapilir.
				printf("Kisi Bulunamadi .\n");	// Kisi eger agacta yoksa mesaj yazdiilir.
			}
			else{
				printf("Silinen Kisi\n");
				printf("------------\n");
				printf("Ad = %s\n",user->ad);
				printf("Soyad = %s\n",user->soyad);
				printf("Kimlik No = %d\n",user->kimlikNo);
				printf("\n");				
				kisiler=deleteUser(kisiler,kimlikNo);
				
			}			
			secenek=menuGoster();
		}
		else if(secenek==3){ //Contains
			system("CLS");
			printf("Agacta aranacak kisinin kimlik No'sunu giriniz = ");
			scanf("%d",&kimlikNo);
			user=contains(kisiler,kimlikNo);	
			if(user!=NULL){					// Kimlik No'su verilen kisinin agacta olup olmadigi kontrolu yapilir.
				printf("Kisi ad = %s\n",user->ad);
				printf("Kisi soyad = %s\n",user->soyad);
				printf("\n");
			}
			else{
				printf("Kisi bulunamadi .\n");	// Kisi eger agacta yoksa mesaj yazdiilir.
			}
			secenek=menuGoster();
		}
		else if(secenek==4){ //Friends
			system("CLS");
			
			printf("Arkadaslari aranacak kisinin kimlik No'sunu giriniz = ");
			scanf("%d",&kimlikNo);
			user=contains(kisiler,kimlikNo);
					
			if(user!=NULL){					// Kimlik No'su verilen kisinin agacta olup olmadigi kontrolu yapilir.
				for(t=0;t<user->arkSayi;t++){
					user2=contains(kisiler,user->arkadaslar[t]);
					if(user2!=NULL){
						printf("Arkadas Adi = %s\n",user2->ad);
						printf("Arkadas Soyadi = %s\n",user2->soyad);
						printf("Kimlik No = %d\n",user2->kimlikNo);
						printf("\n");
					}
				}	
			}
			else{
				printf("Kisi Bulunamadi .\n"); // Kisi eger agacta yoksa mesaj yazdiilir.
			}
			secenek=menuGoster();
		}
		else if(secenek==5){ // Size
			system("CLS");
			size(kisiler);			
			printf("Kisi sayisi = %d\n",SIZE);
			SIZE=0;			
			secenek=menuGoster();
		}
		else if(secenek==6){ // PrintNext
			system("CLS");
			
			printf("Kimlik No giriniz = ");
			scanf("%d",&kimlikNo);			
			user=contains(kisiler,kimlikNo);		
			
			if(user==NULL){			// Kimlik No'su verilen kisinin agacta olup olmadigi kontrolu yapilir.
				printf("Kisi Bulunamadi .\n");	// Kisi eger agacta yoksa mesaj yazdiilir.
			}
			else{
				printNext(user);
			}
			secenek=menuGoster();
		}
		else if(secenek==7){ // PrintGreater
			system("CLS");
			
			printf("Kimlik No giriniz = ");
			scanf("%d",&kimlikNo);			
			user=contains(kisiler,kimlikNo);
			if(user==NULL){				// Kimlik No'su verilen kisinin agacta olup olmadigi kontrolu yapilir.
				printf("Kisi Bulunamadi .\n");	// Kisi eger agacta yoksa mesaj yazdiilir.
			}
			else{
				printf("Kimlik No'su verilen kisiden buyuk olan kisiler\n");
				printf("-----------------------------------------------\n");
				printGreater(kisiler,kimlikNo);
			}
			secenek=menuGoster();
		}
		else if(secenek==8){ // InOrder
			system("CLS");
			inOrder(kisiler);
			secenek=menuGoster();
		}
		else if(secenek==0){	// Cikis
			system("CLS");
			printf("Gorusmek Uzere ...");
			cik=0;
		}
		else{	// Kullanicini Hatali Tuslama Yapma Durumu 
			printf("Hatali Tuslama Yaptiniz.Lutfen Tekrar Deneyin !\n");
			secenek=menuGoster();
		}
	}
	return 0 ;
}
