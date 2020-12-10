/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 9: Rimozione di un elemento da una liste doppiamente concatenata.   
L'esercizio è incompleto nel senso che manca il controllo sull'effettiva 
presenza dell'elemento da eliminare.
*/
#include<iostream>
#define MAX 15

using namespace std;

struct Nodo	{
	int valore; 
	Nodo* succ;
	Nodo* prec; 
};

class ListaDoppia {
public: 
	ListaDoppia()	{testa=NULL;}
	~ListaDoppia(); 
	void stampa(); 
	void inserisci_in_testa(int val);
	Nodo* head() {return testa;}
	void Rimuovi(int val); 
private:
	Nodo* testa; 
};

ListaDoppia::~ListaDoppia() {
	Nodo* aux=testa; 
	
	while(aux!=NULL)	{
		Nodo* temp=aux->succ; 
		delete aux; 
		aux=temp; }
}

void ListaDoppia::stampa()	{
	Nodo* iter=this->testa; 
	
	while(iter!=NULL)	{
	 	cout << " " << iter->valore << "\t Successivo: "; 
		if (iter->succ!=NULL)
			cout << iter->succ->valore;
		else cout << "NULL"; 
		cout << "\t Precedente: "; 
		if (iter->prec!=NULL) 
			cout << iter->prec->valore << endl;
		else cout << "NULL \n"; 
		iter=iter->succ; 
	}
}

void ListaDoppia::inserisci_in_testa(int val)
{
	Nodo* nuovo=new Nodo; 

	nuovo->valore=val; 
	if (this->testa!=NULL) 	{
		nuovo->prec=NULL;
		nuovo->succ=testa; 
		testa->prec=nuovo;
		testa=nuovo;
		}
	else	{
		testa=nuovo; 
		nuovo->succ=NULL; 
		nuovo->prec=NULL;
		}
}

void ListaDoppia::Rimuovi(int val)
{
	Nodo* preced;
	Nodo* current;  
	
	if (testa==NULL) 
		cout << "Lista vuota!" << endl; 
	else if (testa->valore==val){
	/* 	Se l'elemento da eliminare è in testa basterà spostare la testa 
		all'elemento successivo e liberare memoria
	*/
		current=testa; 
		testa=testa->succ; 
		testa->prec=NULL; 
		delete current; 
		}
	else {
		current=testa->succ; 
		while((current->succ!=NULL) && (current->valore!=val))
			current=current->succ; 
		if (current->valore==val) {
			preced=current->prec; 
			preced->succ=current->succ; 
			if (current->succ!=NULL) 
			/* Se il successivo di current è NULL, 
				non sarà necessario aggiornare il precedente
			*/
				current->succ->prec=preced; 
			delete current; 	
					}
			}
}						


int main()
{
	ListaDoppia lista;
	int x; 
		
	for(int i=MAX;i>0;i--) 
		lista.inserisci_in_testa(i*10);
	lista.stampa();
	cout << "Inserire un intero: "; 
	cin >> x;
	lista.Rimuovi(x);
	lista.stampa();	
	return 0; 
}