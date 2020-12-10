/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 6: Rimozione di un elemento da una lista concatenata.   
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
	void Rimuovi(int val); 
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

void ListaSemplice::Rimuovi(int indice)
{
	Nodo* prec; 
	Nodo* current; 
	
	if (this->testa==NULL) 
		cout << "Lista vuota: impossibile rimuovere elementi \n"; 
	else if (this->testa->valore==indice) {
/* Se l'elemento da eliminare è in testa basterà spostare la testa 
all'elemento successivo e liberare memoria*/
		prec=this->testa; 
		this->testa=this->testa->succ; 
		delete prec;
		}
	else	{
/*Nel caso più generale abbiamo bisogno di due puntatori uno per la 
posizione corrente ed uno per quella precedente alla corrente*/ 
		prec=this->testa;
		current=this->testa->succ; 
		while ((current!=NULL) && (current->valore!=indice)) {
	/* Scrivendo la condizione nella forma logicamente equivalente 
		(current->valore!=indice) && (current!=NULL) 
		Il programma darebbe errore di segmentazione nel caso in cui 
		l'elemento da rimuovere non fosse nella lista. 
	*/ 
			prec=prec->succ; 
			current=current->succ;
			}
		if (current!=NULL)	{
			prec->succ=current->succ; 
			delete current; 
			}	
		else 
			cout << "Elemento non presente nella lista!" << endl; 
		}
} 

int main()
{	
	ListaSemplice lista;

	for(int i=MAX;i>0;i--) 
		lista.inserisci_in_testa(i); 
	lista.stampa();
	cout << "Inserire un intero da eliminare nella lista: "; 
	int val;
	cin >> val; 
	lista.Rimuovi(val);
	lista.stampa();
	return 0;	
}