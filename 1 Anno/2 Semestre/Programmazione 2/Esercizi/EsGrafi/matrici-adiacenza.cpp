/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Grafi

Esercizio 2: Rappresentazione di Grafi usando matrici di adiacenza
*/
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;


#define inf len+1

template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo, 
			m numero di archi effettivo, 
			len numero massimo di nodi
		*/
		int **M;
		H **K;  //Contiene gli indici corrispondenti ai vari nodi
		
		int findIndex(H x) {
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
	public:
		MGraph(int len) {
			this->len = len;
			n = m = 0;
			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++) M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
		}
		
		MGraph<H>* addNode(H k) {
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}
		
		MGraph<H>* addEdge(H x, H y) {
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]) {
				M[i][j] = 1;
				m++;
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++) {
					if(M[i][j]) cout << *K[j] << "\t";
				} 
				cout << endl;
			}
		}
};		
		

int main() {
	MGraph<char> *Gr = new MGraph<char>(9);
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
}
