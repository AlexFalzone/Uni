/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento

Esercizio 6: Implementazione del quicksort
(usando la procedura partition)
*/

#include<iostream>
using namespace std;

void scambia (int& a, int& b) 
{  
	int aux=a; 
	a=b; 
   	b=aux; 
}   

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}


int partition(int a[],int p,int r){
	int pivot=a[r];
	int i=p-1; 
	for (int j=p;j<r;j++) 
		if (a[j] <= pivot) {
			i++; scambia(a[i],a[j]);
			}  
	scambia(a[i+1],a[r]);
	return i+1;
}

void quicksort(int a[], int sinistra, int destra) //Ordina a[sinistra:destra]
{
	if (sinistra < destra) {
		int q=partition(a,sinistra,destra); 
		quicksort(a,sinistra,q-1);
		quicksort(a,q+1,destra);
	}
	
}	

void quicksort(int a[], int n)	{
	quicksort(a,0,n-1);
	}
	
	
int main() 
{	int n;
	int a[20]={12,3,6,5,131,7,43,89,54,34,11,21,13,4,90,15,16,71,19,31};
	int b[2]={3,1};
	
	cout << "Vettore iniziale \n"; 
	Stampa(a,20);
	quicksort(a,20);
	quicksort(b,2); 
	cout << endl << "Vettore ordinato " << endl; 
	Stampa(a,20); 
	Stampa(b,2);
}
