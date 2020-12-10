/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento

Esercizio 7: Ricerca binaria (versione ricorsiva)
*/

#include<iostream>
using namespace std;
#define N 21

int ricerca_binaria(int a[], int chiave, int sin, int des) 
// a contiene n elementi, chiave è l'elemento cercato
{	if (sin==des)
	//Caso base della ricorsione
	{	if (chiave==a[sin]) 
			return sin; 
		else return -1;
	}
	int centro=(sin+des)/2; 
	if (chiave<= a[centro]) 
		return ricerca_binaria(a, chiave, sin, centro);
	else return ricerca_binaria(a, chiave, centro+1, des);
}

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}

int main()
{
	int vettore[]={2,3,5,7,8,10,13,14,18,21,23,25,26,27,34,44,51,52,53,55,61};
	int chiave, posizione;
	
	cout << "Inserire un elemento da cercare nel vettore :";
	cin >> chiave; 
	posizione=ricerca_binaria(vettore,chiave,0,N-1);
	if ((posizione+1)) 
		cout << "L'elemento cercato è in posizione " << posizione <<endl;
	else
		cout << "L'elemento cercato non è presente nel vettore" << endl;
	return 0;
}
