/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento e ricerca

Esercizio 1: Ordinamento per scambio.
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

void OrdScambia (int a[], int n)
{
	int i,j; 
	for (i=0;i<n-1;i++) 	
		for (j=i+1; j<n; j++) 
		if (a[i] > a[j])
			scambia(a[i],a[j]);
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
OrdScambia(vettore,20); 
cout << endl << "Vettore ordinato " << endl; 
Stampa(vettore,20); 
}