/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 10: Esempio di lista doppia circolare.
*/
#include<iostream>
#define MAX 15
using namespace std;

struct Nodo {
	int valore;
	Nodo* succ; 
	Nodo* prec;
};

class ListaDoppiaCircolare	{
public: 
	ListaDoppiaCircolare() {testa=NULL;} 
	~ListaDoppiaCircolare(); 
	void stampa(); 
	void inserisci(int val); 
	Nodo* head() {return testa;}
private: 
	Nodo* testa; 
};

ListaDoppiaCircolare::~ListaDoppiaCircolare()	{
	Nodo* iter;
	
	if (testa!=NULL) 
		iter=testa->succ; 
	else  
		return; 
	while(iter!=testa)	{
		Nodo* temp= iter->succ; 
		delete iter; 
		iter=temp; }
	delete testa;
}

void ListaDoppiaCircolare::stampa()
{
	if (testa==NULL) 
		cout << "Lista vuota, nulla da mostrare!" << endl; 
	else if (testa->succ==testa) 
		cout << "La lista contiene solo un elemento: " 
			<< testa->valore << endl; 	  
	else {
		Nodo* primo=testa;
		do  {
			cout << " " << primo->valore << "\t Successivo: "; 
			cout << primo->succ->valore;
			cout << "\t Precedente: " ;
			cout << primo->prec->valore << endl;
			primo=primo->succ;
		} while (primo!=testa);
		}
} 

void ListaDoppiaCircolare::inserisci(int val) 
{
	Nodo* nuovo= new Nodo; 
	
	nuovo->valore=val; 
	if (testa!=NULL) {
	/* 
		Se la lista non è vuota, l'inserimento viene sempre fatto 
	   	dopo la la testa attuale
	*/
		nuovo->succ=testa->succ;
		testa->succ=nuovo;
		nuovo->prec=testa;  
		nuovo->succ->prec=nuovo; 
		}
	else {
	/*	
		Se la lista è vuota inserire un nuovo nodo significa inserire la 
		testa, che punterà a se stessa, sia per il successivo che 
		per il precedente 
	*/
		nuovo->succ=nuovo; 
		nuovo->prec=nuovo;
		testa=nuovo; 
		}
}

int main()
{	ListaDoppiaCircolare lista;
	
	for(int i=MAX;i>0;i--) 
		lista.inserisci(i*10); 
	lista.stampa();
	return 0;	
}