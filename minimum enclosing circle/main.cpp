#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int x[20];				//x koordinatlar� bu diziye atanacak
int y[20];				//y koordinatlar� bu diziye atanacak
int i, n, j;
double X = 0, Y = 0;	//x ve y koordinatlar� her okundu�unda bu de�i�kenlere eklenecek
double uzaklik, uzaklik2, r;
int a, b = 20;

void dosya_acma_koordinatlari_okuma()
{
	char *kontrol;
	char str[100];
	FILE *dosya;
	dosya = fopen("C:\\Users\\JAN\\Desktop\\koordinat.txt", "r");		//dosya okuma modunda a��ld�
	fscanf(dosya, "%s", str);				//dosyadan okuma
	kontrol = strtok(str, ",");				//ilk virg�l� g�rene kadar olan k�sm� okuyup kontrole atad� ve virg�l� atlad�

	i = 0;
	while (kontrol != NULL)			
	{
    	x[i] = atoi(kontrol);				//kontrole atanan array i, int e �evirip x[i] ye atad�
   		kontrol = strtok(NULL, ",");		//Bir sonraki virg�le e kadar olan k�sm� al�p kontrole e atad�
   		X += x[i];
   		
   	 	y[i] = atoi(kontrol);	 			//kontrole atanan array i, int e �evirip y[i] ye atad�
   	 	kontrol = strtok(NULL, ",");		//Bir sonraki virg�le e kadar olan k�sm� al�p kontrole e atad�
		Y += y[i];
		
   		i++;		
	}
	
	n = i;								//n koordinat say�s�na e�it oldu
	fclose(dosya);						//dosya kapand�
}

void konsola_koordinat_yazma()
{
	for (i = 0; i < n; i++)							//koordinatlar� konsola yazd�rd�
  	  printf("%3d , %3d\n", x[i], y[i]);			
}

void cember_merkez_yaricap()
{
	X /= n;										//x koordinatlar� toplam�n� koordinat say�s�na b�ld�
  	Y /= n;										//y koordinatlar� toplam�n� koordinat say�s�na b�ld�
  	double kontrol_degiskeni = 0.1;
  	
  	for (i = 0; i < 10000; i++)							//Sonuca daha �ok yak�nla�mas� i�in 10000 kere �al��t�r�ld�
 	{
  		int f = 0;
    	uzaklik = (X - x[0])*(X - x[0]) + (Y - y[0])*(Y - y[0]);	//X,Y koordinat�n�n di�er noktalarla olan uzakl��� kar��la�t�r�lmak �zere baslang�� uzakl��� se�ildi
    	
    	for (j = 1; j < n; j++)
   		{
    		uzaklik2 = (X - x[j])*(X - x[j]) + (Y - y[j])*(Y - y[j]);		//Uzakl�k de�i�keni ile kar��la�t�r�lmak �zere bir sonraki noktayla olan uzakl�k hesapland�
    		
     		if (uzaklik < uzaklik2)
      		{
      			uzaklik = uzaklik2;
      			f = j;										//Uzakl��� fazla olan noktan�n indisi f ye atand�.
     		}
   		}
   		
   		X += (x[f] - X) * kontrol_degiskeni;				//f indisindeki x,y koordinat� X,Y koordinat�na kontrol degiskeni oran�nda yak�nlast�.
   		Y += (y[f] - Y) * kontrol_degiskeni;
   		kontrol_degiskeni *= 0.999;							//Her d�ng�de �emberin merkezine yak�nla�an koodinat�n yak�nla�ma oran� k���ld�.Limit gibi
 	}	
 	
 	r = sqrt(uzaklik);										//Uzakl���n karek�k� al�nd� ve r ye atand�.
}

void konsola_yaricap_merkez_yazdirma()					//merkez ve yar��ap� konsola yazd�rd�
{
 	printf("Merkez = {%.3lf, %.3lf}\n", X, Y);
 	printf("Yaricap = %.3lf", r); 
}

void koordinat_sistemi()
{	
	initwindow(831, 841);			//800x800 l�k pencere a�t�k, x ten 11 birim y den 21 birim eksik a�t��� i�in 811 e 822 lik a�t�k, 20 birim de grafi�in d���na bo�luk olmas� i�in
	line(400, 0, 400, 800);			//y d�zlemini �izdirdi
	line(0, 400, 800, 400);			//x d�zlemini �izdirdi
	
	int cizik;
	setcolor(8);
	for (cizik = 0; cizik < 41; cizik++)			
	{					
		if (cizik == 20)
			continue;
		line(0+20*cizik, 0, 0+20*cizik, 820);       //x koordinatlar� i�in boydan boya �izgiler �izdirdi
		line(0, 0+20*cizik, 820, 0+20*cizik);		//y koordinatlar� i�in boydan boya �izgiler �izdirdi
	}

	setcolor(15);
	char sayi[20];
	for (a = -20; a <= 20; a++)						//koordinat sistemine x de�erlerini girdirdi
	{
		if (a == 0)
		{
			b--;
			continue;
		}
		sprintf(sayi, "%d", a);
		settextstyle(SMALL_FONT, 0, 5);				//yaz� fontunu, y�n�n� ve boyutunu ayarlad�
		outtextxy(0+ (20-b)*20, 405, sayi);			//koordinat� ve girilecek yaz�y� ayarlad�
		b--;
	} 
	
	char sayi2[20];
	b = 20;
	for (a = 20; a >= -20; a--)						//koordinat sistemine y de�erlerini girdirdi
	{
		if (a == 0)
		{
			b--;
			continue;
		}
		sprintf(sayi2, "%d", a);
		settextstyle(SMALL_FONT, 0, 5);				//yaz� fontunu, y�n�n� ve boyutunu ayarlad�
		outtextxy(405, 0+ (20-b)*20, sayi2);		//koordinat� ve girilecek yaz�y� ayarlad�
		b--;
	}
	
	for (cizik = 0; cizik < 41; cizik++)					//x koordinatlar�na �izik att�rd�
		line(0+20*cizik, 397, 0+20*cizik, 403); 
		
	for (cizik = 0; cizik < 41; cizik++)					//y koordinatlar�na �izik att�rd�
		line(397, 0+ 20*cizik, 403, 0+ 20*cizik);
}

void cember_cizimi()
{
	setcolor(3);
	circle(400+ X*20, 400-Y*20, r*20);				//elde edilen merkeze ve yar��apa g�re daireyi �izdirdi
	
	for (i = 0; i < n; i++)								//girilen noktalar� ekrana �izdirdi
	{
		setcolor(4);
		setfillstyle(SOLID_FILL, 4);				//i�ini doldurdu ve rengini belirledi
		fillellipse(400+ 20*x[i], 400-20*y[i], 5, 5);	//x y koordinat� ve x y yar��ap�n� ayarlad�
	}
	
	{
		setcolor(14);									//yar��ap� �izdirdi
		setfillstyle(SOLID_FILL, 14);					//i�ini doldurdu ve boyutunu belirledi
		fillellipse(400+X*20, 400-Y*20, 5, 5);			//i�i dolu bir �ekilde merkezi �izdi
		line(400+X*20, 400-Y*20, 400+X*20+r*20, 400-Y*20);	//yar��ap� �izdi
	}
}

void grafige_yaricap_merkez_yazdirma()
{
	setcolor(10);
	settextstyle(SMALL_FONT, 0, 7);
	outtextxy(20, 20, "Yaricap: ");			//verilen koordinatlara Yar��ap: yazd�rd�			
	outtextxy(20, 50, "Merkez: ");			//verilen koordinatlara Merkez: yazd�rd�
	
	setcolor(15);
	char yaricap[10];
	char koordinat_x[10];
	char koordinat_y[10];
	sprintf(yaricap, "%lf", r);
	outtextxy(90, 20, yaricap);				//verilen koordinatlara yar��ap�n de�erini yazd�rd�
	
	sprintf(koordinat_x, "%.2lf", X);
	outtextxy(90, 50, koordinat_x);			//verilen koordinatlara merkezin x noktas�n� yazd�rd�
	
	outtextxy(130, 50, ",");				//verilen koordinatlara x ve y aras�na virg�l koydu
	
	sprintf(koordinat_y, "%.2lf", Y);
	outtextxy(140, 50, koordinat_y);		//verilen koordinatlara merkezin y noktas�n� yazd�rd�
}

int main()
{
    dosya_acma_koordinatlari_okuma();
    konsola_koordinat_yazma();
    cember_merkez_yaricap();
	konsola_yaricap_merkez_yazdirma();
	koordinat_sistemi();
	cember_cizimi();
	grafige_yaricap_merkez_yazdirma();
	
	getch();
	closegraph();
	return 0;
}
