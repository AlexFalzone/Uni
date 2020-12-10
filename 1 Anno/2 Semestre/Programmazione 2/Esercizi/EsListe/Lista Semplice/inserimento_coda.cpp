/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 4: Inserimento di elementi in coda invece che in testa.   
*/
#include<iostream>

using namespace std;

struct Nodo {
	int valore;
	Nodo* succ; 
};

class ListaSemplice	{
public: 
	ListaSemplice() {testa=NULL;} 
	~ListaSemplice(); 
	void stampa(); 
	void inserisci_in_coda(int val); 
private: 
	Nodo* testa; 
};

ListaSemplice::~ListaSemplice()	{
	Nodo* iter=this->testa; 
	
	while(iter!=NULL)	{
		Nodo* temp= iter->succ; 
		delete iter; 
		iter=temp; 
	}
}

void ListaSemplice::stampa()
{
	Nodo* iter=this->testa; 
	
	while (iter!=NULL) {
		cout << " " << iter->valore << endl;
		iter=iter->succ;
		}
} 


void ListaSemplice::inserisci_in_coda(int val) 
{
	Nodo* nuovo= new Nodo;
	Nodo* iter=this->testa;
	
	if (this->testa==NULL) {
	/* Se la lista è vuota il primo elemento inserito in coda 
	sarà quello che si trova in testa alla lista */
		nuovo->valore=val; 
		nuovo->succ=NULL; 
		this->testa=nuovo;
		}
	else {
		while (iter->succ!=NULL) 
			iter=iter->succ; 
		nuovo->valore=val; 
		nuovo->succ=NULL; 
		iter->succ=nuovo;
		}
}

int main()
{	
	ListaSemplice lista;

	lista.inserisci_in_coda(20);
	lista.inserisci_in_coda(15);
	lista.inserisci_in_coda(10);
	lista.stampa();
	lista.inserisci_in_coda(5);
	lista.stampa();
	return 0;	
}