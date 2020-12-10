/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento e ricerca

Esercizio 4: Ordinamento a bolle versione ottimizzata: eliminiamo 
iterazioni inutili quando ci rendiamo conto che il vettore è già ordinato.

*/
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<time.h>
using namespace std;

#define MAX 1000

void scambia (int& a, int& b) 
{  
	int aux=a; 
	a=b; 
   	b=aux; 
}   

void inizializza(int a[],int n)    
{
	//randomize();
	for (int i=0; i<n;i++) 
		a[i]=rand() % 10000 + 1; 
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


void BubbleSortOtt (int a[], int n)
{
	int j,aux,iterazione; 
	bool flag=true; 
	
	for (iterazione=0;iterazione<n-1 && flag;iterazione++) 
	{	flag=false;
		// QUi flag sta ad indicare che non è ancora stato fatto alcuno scambio	
		for (j=0; j<n-iterazione-1; j++) 
		if (a[j] > a[j+1])
		{	flag=true; 
			scambia(a[j],a[j+1]);
		}
	}
}

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}

int main()
{
int vettore[MAX];

int i, inizio, fine; 
inizializza(vettore,MAX);
cout << "Vettore iniziale \n"; 
Stampa(vettore,MAX);
inizio=clock(); 
// cout << "tempo di Inizio " << inizio << "\n";
BubbleSortOtt(vettore,MAX); 
fine=clock(); 
// cout << "tempo di fine " << fine << "\n";
cout << endl << "Vettore ordinato " << endl; 
Stampa(vettore,MAX); 
cout << "Tempo richiesto " << fine-inizio << endl;
cin.get();
inizio=clock(); cout << "Riordino con Bubble Sort non ottimizzato \n" ;
BubbleSort(vettore,MAX);
fine=clock(); 
// cout << "tempo di fine " << fine << "\n"; 
cout << "Tempo richiesto " << fine-inizio << endl;
cin.get();
inizio=clock(); cout << "Riordino con Bubble Sort ottimizzato \n";
BubbleSortOtt(vettore,MAX);
fine=clock(); 
//cout << "tempo di fine " << fine << "\n"; 
cout << "Tempo richiesto " << fine-inizio << endl;
}