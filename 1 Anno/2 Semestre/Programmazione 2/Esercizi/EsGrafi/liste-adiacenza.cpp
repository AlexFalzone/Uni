/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Grafi

Esercizio 1: Rappresentazione di Grafi usando liste di adiacenza
*/

#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;


template <class T> struct Nodo {
	T valore;
	Nodo<T>* succ; 
};

template <class T> class Lista{
public: 
	Lista() {testa=NULL;} 
	~Lista(); 
	void print(); 
	void insert(T val); 
	Nodo<T>* RivelaTesta() {return testa;}
	Nodo<T>* search(int val);
private: 
	Nodo<T>* testa; 
};

template <class T> Lista <T> ::~Lista()	{
	Nodo<T>* iter=this->testa; 
	
	while(iter!=NULL)	{
		Nodo<T>* temp= iter->succ; 
		delete iter; 
		iter=temp; 
	}
}

template <class T> void Lista <T> ::print()
{
	Nodo<T>* iter=this->testa; 
	
	while (iter!=NULL) {
		cout << " " << iter->valore << "\t";
		iter=iter->succ;
	}
} 

template <class T> void Lista <T>::insert(T val) 
{
	Nodo<T>* nuovo= new Nodo<T>; 
	
	nuovo->valore=val; 
	nuovo->succ=this->testa; 
	this->testa=nuovo;
}

template <class T> Nodo<T>* Lista <T> ::search(int indice)
{
	Nodo<T>* p; 
	
	for (p=this->testa; p!=NULL; p=p->succ)
		if (p->valore==indice) 
			return p; 
	return NULL;
} 



template <class H> class LGraph {
	private:
		//int *c, *p, *d, *f;
		int len, n, m;
		/* 	n numero di nodi effettivo, 
			m numero di archi effettivo, 
			len numero massimo di nodi
		*/
		int t;
		H **K; //matrice indici
		Lista<int> **Adj;

		int findIndex(H x) {
		// Trova l'indice associato al nodo 
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
	
	public:
		LGraph(int len) {
			this->len = len;
			n = m = 0;
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			Adj = new Lista<int>*[len];
			for(int i=0; i<len; i++) Adj[i] = new Lista<int>();
		}

		LGraph<H>* addNode(H k) {
		// Aggiunge un nodo al grafo (se non già presente)
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}
		
		LGraph<H>* addEdge(H x, H y) {
		// Aggiunge un arco al grafo (se non già presente)
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!Adj[i]->search(j)) {
				Adj[i]->insert(j);
				m++;
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				Adj[i]->print();
				cout << endl;
			}
		}		
};



int main() {
	LGraph<char> *Gr = new LGraph<char>(9);
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0');
	Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	//Gr->SCC();	
	
}