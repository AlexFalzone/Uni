/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Alberi

Esercizio 3: Cancellazione in alberi binari di ricerca.
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
	void Trapianta(Nodo* u, Nodo* v); 
	Nodo* Find(Tipo x);
	void Cancella(Nodo* z);
	Nodo* Minimo(Nodo* x);
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
	cout << "Vista Inorder: ";
	visitaInorder(radice); 
	cout << endl; 
}

void albero:: Trapianta(Nodo* u, Nodo* v)	{
	if (u->padre==NULL) radice=v; 			// u è la radice
	else if (u==u->padre->left) 			// u è figlio sinistro
       u->padre->left=v;
	else u->padre->right=v; 
	if (v!=NULL) 						// aggiorniamo il padre di v 
 		v->padre=u->padre; 
}

Nodo* albero::Minimo(Nodo* x)	{
	Nodo* min=x; 
	
	while(min->left != NULL) min=min->left; 
	return min; 
}
	
void albero::Cancella(Nodo* z)	{
	Nodo* y; 

	if (z->left==NULL) Trapianta(z,z->right); 	// z non ha figlio sinistro
	else if (z->right==NULL) 			
       Trapianta(z,z->left);
	else	{ 
	 	y=Minimo(z->right);
 		if (y->padre!=z) 	{			// Caso 3 più generale 
 			Trapianta(y,y->right);
 			y->right=z->right; 
 			y->right->padre=y;  }
 		Trapianta(z,y);
 		y->left=z->left;
 		y->left->padre=y;
		}
	delete z;
}

Nodo* albero::Find(Tipo x)	{
	Nodo* iter=radice; 
	
	while ((iter!= NULL) && (x!=iter->val))   {
 		if (x < iter->val)  iter=iter->left;
 		else iter=iter->right; 	}
	return iter;
}


int main()
{
	albero tree;
	
	tree.Insert(26); 
	tree.Insert(15); 
	tree.Insert(37); 
	tree.Insert(2); 
	tree.Insert(48); 
	tree.Insert(19); 
	tree.Insert(16); 
	tree.Insert(17); 
	/* Non inserendo gli ultimi due valori si farà una cancellazione
	di tipo 3a, inserendoli verrà fatta una cancellazione di tipo 3
	generale*/
	tree.stampa(); 
	Nodo* elem=tree.Find(15);
	cout << "Elemento da cancellare : " << elem->val << endl; 
	tree.Cancella(elem);
	tree.stampa();
	cout << endl;
	return 0;	
}
