/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Alberi

Esercizio 1: Creare albero binario.
*/
#include<iostream>

using namespace std;

const int MaxDimTree=100; 

typedef int Tipo;

struct Nodo {
	Tipo val;
	Nodo* left; 
	Nodo* right; 
	Nodo* padre; 
};

class albero {
public: 
	albero() : radice(NULL) {}; 
	void Insert(Tipo valore);
	void visitaInorder(Nodo* p);
	void stampa();
private: 
	Nodo* radice; 
};

void albero::Insert(Tipo valore) {
	Nodo* nuovo= new Nodo; 
	Nodo* x=radice, *y=NULL; 
	
	nuovo->val=valore;
	nuovo->left=nuovo->right=NULL;
	/* Senza questa inizializzazione si possono avere errori di segmentazione
	*/
	while(x!=NULL) {
		y=x; 
		if (valore < x->val) x=x->left; 
		else x=x->right; 
		}
	nuovo->padre=y; 
	if (y==NULL) radice=nuovo; 
	//In tal caso l'albero è vuoto
	else if (valore < y->val) y->left=nuovo; 
	else y->right=nuovo; 
}

void albero:: visitaInorder(Nodo* p)	{
	if (p!=NULL) {
		visitaInorder(p->left); 
		cout << p->val << "\t";
		visitaInorder(p->right); 
		}
}	 

void albero:: stampa() {
	cout << endl;
	visitaInorder(radice); 
}


int main()
{
	albero tree;
	
	tree.Insert(6); 
	tree.stampa(); 
	tree.Insert(5); 
	tree.stampa(); 
	tree.Insert(7); 
	tree.stampa(); 
	tree.Insert(2); 
	tree.stampa(); 
	tree.Insert(8); 
	tree.stampa(); 
	tree.Insert(5); 
	tree.stampa(); 
	cout << endl;
	return 0;	
}