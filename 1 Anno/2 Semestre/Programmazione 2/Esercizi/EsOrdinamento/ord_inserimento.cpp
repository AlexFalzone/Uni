/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento e ricerca

Esercizio 2: Ordinamento per inserimento.
*/
#include<iostream>
using namespace std;

void Inserimento_Ordinato (int A[], int n) 
{  
	int i,j,valore;  
	for (i=1; i <n; i++) // i identifica il sottovettore A[0]..A[i] 
   	{	
   		valore=A[i];
   		j=i-1; // Attraversiamo il vettore partendo da A[i] e cercando la posizione j 
   			// dove inserire l'elemento destinazione
   		while (j>=0 && A[j]>valore) 
   			{
   				A[j+1]=A[j]; // Spostiamo gli elementi a destra per far spazio  
   				j--;		// all'elemento in posizione i 
   			}
   		A[j+1]=valore;
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
int vettore[20]={12,3,6,5,131,7,43,89,54,34,11,21,13,4,90,15,16,71,19,31};

int i; 
cout << "Vettore iniziale \n"; 
Stampa(vettore,20);
Inserimento_Ordinato(vettore,20); 
cout << endl << "Vettore ordinato " << endl; 
Stampa(vettore,20); 
return 0;
}