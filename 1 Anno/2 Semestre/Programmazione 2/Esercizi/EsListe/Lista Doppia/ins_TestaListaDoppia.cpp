/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 7: Liste doppiamente concatenate, inserimento in testa.   
*/
#include<iostream>
#define MAX 15

using namespace std;

struct Nodo {
	int valore;
	Nodo* succ; 
	Nodo* prec;
};

class ListaDoppia	{
public: 
	ListaDoppia() {testa=NULL;} 
	~ListaDoppia(); 
	void stampa(); 
	void inserisci_testa(int val); 
private: 
	Nodo* testa; 
};

ListaDoppia::~ListaDoppia()	{
	Nodo* iter=this->testa; 
	
	while(iter!=NULL)	{
		Nodo* temp= iter->succ; 
		delete iter; 
		iter=temp; 
	}
}

void ListaDoppia::stampa()
{
	Nodo* primo=this->testa; 
	
	while (primo!=NULL) {
		cout << " " << primo->valore << "\t Successivo: "; 
		if(primo->succ!=NULL) 
			cout << primo->succ->valore;
		else 
			cout << "NULL"; 	 
		cout << "\t Precedente: " ;
		if(primo->prec!=NULL)
			cout << primo->prec->valore << endl;
		else cout << "NULL \n";  
		primo=primo->succ;
		}
} 

void ListaDoppia::inserisci_testa(int val) 
{
	Nodo* nuovo= new Nodo; 
	
	nuovo->valore=val; 
	if (this->testa!=NULL) {
		nuovo->succ=this->testa;
		this->testa->prec=nuovo; 
		this->testa=nuovo;
		}
	else {
		nuovo->succ=NULL; 
		this->testa=nuovo; 
		nuovo->prec=NULL; 
		}
}

int main()
{	
	ListaDoppia lista;
	
	for(int i=MAX;i>0;i--) 
		lista.inserisci_testa(i); 
	lista.stampa();
	return 0;	
}