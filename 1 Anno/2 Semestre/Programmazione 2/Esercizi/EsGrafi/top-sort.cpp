/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Grafi

Esercizio 5: Topological sort usando matrici di adiacenza
*/
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf len+1


template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo, 
			m numero di archi effettivo, 
			len numero massimo di nodi
		*/
		int **M; //Matrice di adiacenza
		int t;
		H **K;  // Matrice degli indici
		int *d, *p, *f, *c, *r;
		int current_root;
		//int lastBFSSource;
		
		
		int findIndex(H x) {
		// Associa un indice al nodo (se esiste)
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		void printPath(int x) {
			if(x==-1) return;
			if(p[x]==-1) cout << x; 
			else {
				printPath(p[x]);
				cout << "->" << x; 
			}
		}
		
		
		void sort(int *a, int n, int *k) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && k[a[j+1]]>k[a[j]]) {
					int t = a[j+1];
					a[j+1] = a[j];
					a[j] = t;
					j--;
				}
			}
		}
		
	public:
		MGraph(int len) {
			this->len = len;
			n = m = 0;
			d = new int[len]; /* vettore delle distanze 
								(dalla sorgente) 
								*/	
			p = new int[len]; // vettore dei precedenti
			f = new int[len]; //vettore distanze finali
			c = new int[len]; //vettore color
			r = new int[len]; // vettore delle radici
			
			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			//lastBFSSource = -1;
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
					if(M[i][j]) cout << *K[j] << " ";
				} 
				cout << endl;
			}
		}
		
		
		int DFSVisit(int v) {
			/* Modifichiamo la funzione facendole restituire 
			 	1 se il grafo contiene un ciclo
			 */
			int cycle = 0;
			c[v] = G;
			d[v] = t++;
			r[v] = current_root;
			for(int u=0; u<n; u++) {
				if(M[v][u]==1) {
					if(c[u]==W) {
						p[u]=v;
						cycle |= DFSVisit(u);
					}
					if(c[u]==G) cycle = 1;
				}
			}
			c[v] = B;
			f[v] = t++;
			return cycle;		
		}
		
		int DFS() {
		/*Come sopra, inoltre aggiungiamo alla fine 
			la stampa di f[] generato durante la visita */
			int cycle = 0;
			t = 0;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			for(int i=0; i<n; i++)
				if(c[i]==W) {
					current_root = i;
					cycle |= DFSVisit(i);
				}
			for(int i=0; i<n; i++)
				cout << "[" << i << "] : " << f[i] << endl;
			return cycle;
		}
		
		void topSort() {
			int cycle = DFS();
			if(cycle) {
				cout << "Il grafo contiene un ciclo\n";
				return;
			}
			int *s = new int[n];
			for(int i=0; i<n; i++) s[i] = i;
			sort(s,n,f);
			for(int i=0; i<n; i++) {
				cout << "(" << s[i] << ", " << f[s[i]] << ") ";
			}
			cout << endl;
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
	Gr->addEdge('4','3');//->addEdge('4','0');
	//Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	cout << endl; 
	Gr->topSort(); 
}