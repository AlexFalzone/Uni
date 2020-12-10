/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 2: Creare una lista che contiene gli elementi 1,2 e 3.
Usiamo strutture invece delle classi. Inseriamo gli elementi in testa. 
*/
#include<iostream>

using namespace std;

struct Elemento {
	int valore;
	struct Elemento* succ; 
};

struct lista {
	Elemento* testa;
};	

void stampa(lista L)
{
	while (L.testa!=NULL) {
		cout << " " << L.testa->valore << endl;
		L.testa=L.testa->succ;
		}
} 

void inserisci(lista& L,int val) 
{
	Elemento* nuovo= new Elemento; 
	
	nuovo->valore=val; 
	nuovo->succ=L.testa; 
	L.testa=nuovo;
}


int main()
{	
	lista L;

	inserisci(L,1);
	inserisci(L,2);
	inserisci(L,3);
	stampa(L);
	return 0;	
}