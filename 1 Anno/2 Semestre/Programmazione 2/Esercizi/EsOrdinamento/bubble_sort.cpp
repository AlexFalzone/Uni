/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento e ricerca

Esercizio 3: Ordinamento a bolle.
*/
#include<iostream>
using namespace std;

void scambia (int& a, int& b) 
{  
	int aux=a; 
	a=b; 
   	b=aux; 
}   
    
    
//Ordiniamo in senso non decrescente 

void BubbleSort (int a[], int n)
{
	int j,aux,iterazione; 
	for (iterazione=0;iterazione<n-1;iterazione++) 	
		for (j=0; j<n-iterazione-1; j++) 
		if (a[j] > a[j+1])
			scambia(a[j],a[j+1]);
}

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}

int main()
{
int vettore[20]={12,3,6,5,131,7,43,89,54,34,11,21,13,4,90,15,16,71,19,31};

int i; 
cout << "Vettore iniziale \n"; 
Stampa(vettore,20);
BubbleSort(vettore,20); 
cout << endl << "Vettore ordinato " << endl; 
Stampa(vettore,20); 
}