/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 3: Inserimento di elementi in un posto predeterminato.
Creiamo una lista contenente i numeri 5, 10 e 20. Quindi inseriamo 
15 tra 10 e 20.   
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
	void inserisci_in_testa(int val); 
	void inserisci(Nodo* precedente, Nodo* seguente, int val); 
	Nodo* RivelaTesta() {return testa;}
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
/*La parola chiave this identifica un puntatore che fa riferimento 
alla classe in questione. Esso è definito implicitamente (quindi non 
è necessario dichiararlo). 
this punta direttamente all’oggetto per il quale è stata richiamata 
la funzione membro
*/ 
	
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

void ListaSemplice::inserisci(Nodo* precedente, Nodo* seguente, int val)
{
	Nodo* nuovo= new Nodo; 
	
	nuovo->valore=val; 
	nuovo->succ=seguente; 
	precedente->succ=nuovo; 
}

int main()
{	
	ListaSemplice lista;
	Nodo* p;

	lista.inserisci_in_testa(20);
	lista.inserisci_in_testa(10);
	lista.inserisci_in_testa(5);
	lista.stampa();
	cout<<endl;
	p=lista.RivelaTesta();
	while ((p->valore!=10) && (p!=NULL)) p=p->succ; 
	//Inseriamo il nuovo elemento tra 10 e 20
	if (p!=NULL)
		lista.inserisci(p,p->succ,15);
	lista.stampa();
	return 0;	
}