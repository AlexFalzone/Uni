/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 3.1: Inserimento di elementi in un posto predeterminato.
Creiamo una lista contenente tre elementi. Quindi inseriamo un quarto elemento. 
Questa volta usiamo i templates.  
*/
#include<iostream>

using namespace std;

template <class T> struct Nodo {
	T valore;
	Nodo<T>* succ; 
};

template <class T> class ListaSemplice	{
public: 
	ListaSemplice() {testa=NULL;} 
	~ListaSemplice(); 
	void stampa(); 
	void inserisci_in_testa(T val); 
	Nodo<T>* RivelaTesta() {return testa;}
private: 
	Nodo<T>* testa; 
};

template <class T> ListaSemplice <T> ::~ListaSemplice()	{
	Nodo<T>* iter=this->testa; 
	
	while(iter!=NULL)	{
		Nodo<T>* temp= iter->succ; 
		delete iter; 
		iter=temp; 
	}
}

template <class T> void ListaSemplice <T> ::stampa()
{
	Nodo<T>* iter=this->testa; 
	
	while (iter!=NULL) {
		cout << " " << iter->valore << endl;
		iter=iter->succ;
		}
} 

template <class T> void ListaSemplice <T>::inserisci_in_testa(T val) 
{
	Nodo<T>* nuovo= new Nodo<T>; 
	
	nuovo->valore=val; 
	nuovo->succ=this->testa; 
	this->testa=nuovo;
}


int main()
{	
	ListaSemplice <char> lista;

	lista.inserisci_in_testa(100);
	lista.inserisci_in_testa(99);
	lista.inserisci_in_testa(97);
	lista.stampa();
	cout <<endl;
	lista.inserisci_in_testa(98);
	lista.stampa();
	return 0;	
}