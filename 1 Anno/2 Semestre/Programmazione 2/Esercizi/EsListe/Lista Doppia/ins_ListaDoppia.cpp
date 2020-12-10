/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 8: Liste doppiamente concatenate, inserimento in una posizione
determinata.   
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
	void inserisci(Nodo* prec, Nodo* succ, int val);
	void inserisci_in_coda(Nodo* p, int val);
	Nodo* head() {return testa;}
	//void Rimuovi(int val); 
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

void ListaDoppia::inserisci(Nodo* precedente, Nodo* successivo, int val)
{
	Nodo* nuovo=new Nodo; 
	
	nuovo->valore=val;
	nuovo->prec=precedente; 
	nuovo->succ=successivo; 
	precedente->succ=nuovo; 
	successivo->prec=nuovo; 
}						


void ListaDoppia::inserisci_in_coda(Nodo* coda, int val)
{
	Nodo* nuovo=new Nodo; 
	
	nuovo->valore=val;
	nuovo->succ=NULL; 
	nuovo->prec=coda; 
	coda->succ=nuovo; 
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
	if (lista.head()->valore > x) 
	/* Se l'elemento da inserire è il minimo va inserito in testa */ 
		lista.inserisci_in_testa(x); 
	else	{
		Nodo* p;
		p=lista.head();
		while ((p->succ!=NULL) && (p->succ->valore <=x))
	/* 	Le due condizioni scritte nell'ordine contrario causerebbero errori 
		nel caso in cui si raggiungesse un valore NULL, poiché in tal caso
		la condizione p->succ->valore <= x non avrebbe senso */
			p=p->succ; 
		if (p->succ!=NULL) 
			lista.inserisci(p,p->succ,x);
		else 
			lista.inserisci_in_coda(p,x);
			}
	lista.stampa();	
	return 0; 
}