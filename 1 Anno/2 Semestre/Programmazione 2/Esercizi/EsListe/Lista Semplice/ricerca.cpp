/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 5: Ricerca di un elemento in una lista.   
*/
#include<iostream>
#define MAX 25

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
	void inserisci_in_testa(int val); 
	Nodo* Ricerca(int val); 
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

void ListaSemplice::inserisci_in_testa(int val) 
{
	Nodo* nuovo= new Nodo; 
	
	nuovo->valore=val; 
	nuovo->succ=this->testa; 
	this->testa=nuovo;
}

Nodo* ListaSemplice::Ricerca(int indice)
{
	Nodo* p; 
	
	for (p=this->testa; p!=NULL; p=p->succ)
		if (p->valore==indice) 
			return p; 
	return NULL;
} 

int main()
{	
	ListaSemplice lista;
	Nodo* index;

	for(int i=MAX; i>0; i--) 
		lista.inserisci_in_testa(i);
	lista.stampa();
	cout << "Inserire un intero da cercare nella lista: "; 
	int val;
	cin >> val; 
	index=lista.Ricerca(val);
	if (index!=NULL) 
		cout << "L'elemento è presente nella lista in posizione " << index->valore << endl; 
	else 
		cout << "l'elemento cercato non è in lista" << endl; 
	return 0;	
}