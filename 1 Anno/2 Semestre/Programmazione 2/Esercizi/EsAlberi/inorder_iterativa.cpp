/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Alberi

Esercizio 4: Versione iterativa (usando stack) della procedura inorder.
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
	void Inorder_Iterativa();
	void stampa();
private: 
	Nodo* radice; 
};

struct item {
	Nodo* Elemento;
	item* succ;
};

class Pila{
private: 
	item *p;
public: 	
	Pila() {p=NULL;}
	~Pila(); 
	bool PilaVuota() {return !p;}
	Nodo* PrimoElemento() { if (p!=NULL) return p->Elemento;}
	void Push(Nodo* x); 
	Nodo* Pop();
	void CancellaNodo(); 
	void StampaPila();  
};

Pila::~Pila() {
	item* pnodo; 
	
	while(p!=0)	{
		pnodo=p; 
		p=p->succ;
		delete pnodo; 
		}
}

void Pila::Push(Nodo* x)
{	
	item* aux=new item; 
	
	aux->Elemento=x; 
	if(p) aux->succ=p;
	else aux->succ=NULL;
	/* Senza questo else c'è il rischio di errori di segmentazione */
	p=aux;
}	

void Pila::CancellaNodo()
{	item* pnodo; 
 	
 	if (p) {
 		pnodo=p; 
 		p=p->succ; 
 		delete pnodo; 
 		}
}

Nodo* Pila::Pop() {
	Nodo* e; 
	
	e=PrimoElemento(); 
	CancellaNodo(); 
	return e; 
}

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
	cout << "\n Vista Inorder ricorsiva: "; 
	visitaInorder(radice); 
	cout << "\n Vista Inorder Iterativa: "; 
	Inorder_Iterativa(); 
	cout << endl;
}

void albero::Inorder_Iterativa() {

  Pila stack;
  Nodo* current = radice;
  
  bool done = false;
  while (!done) {
    if (current) {
      stack.Push(current);
      current = current->left;
    	} 
    else if (stack.PilaVuota()) 
        done = true;
    else {
        current = stack.Pop();
        cout << current->val << "\t";
        current = current->right;
    	  }
    }
}


int main()
{
	albero tree;
	
	tree.Insert(6); 
	tree.Insert(5); 
	tree.Insert(7); 
	tree.Insert(2); 
	tree.Insert(8); 
	tree.Insert(5); 
	tree.stampa();
	tree.Insert(54); 
	tree.stampa();
	cout << endl;
	return 0;	
}