#include <iostream>

using namespace std;

#define B 0
#define G 5
#define N 10

class Pila{
	private:
		int *arr;
		int cima;
		int len;
	public:
		Pila(int len){
			this->len=len;
			arr=new int[len];
			cima=-1;
		}
		bool pilaVuota(){
			return cima==-1;
		}
		bool pilaPiena(){
			return cima==len-1;
		}
		void push(int val){
			if(!pilaPiena()){
				cima++;
				arr[cima]=val;
			}
		}
		int pop(){
			if(!pilaVuota()){
				int x=arr[cima];
				cima--;
				return x;
			}
			return -1;
		}
		
};

template <class H> class Mgraph{
	private:
		int dim;//il numero massimo di nodi che possono essere inseriti
		int n;//il numero attuale di vertici all'interno del grafo
		int m;//il numero attuale di archi all'interno del grafo
		int **M;//matrice di adiacenza
		H **K;//array delle etichette, usato come array di puntatori per vedere se � null il valore o meno
		int current_root;//la settiamo prima di avviare una visita in profondita'
		
		int **Tm;//matrice trasposta che useremo per la definizione del grafo trasposto
		
		Pila *stack;
		int *r;//array delle radici
		int *c;//array dei colori, un nodo puo' essere grigio, bianco o nero
		int *p;//array dei predecessori, se non esiste e' -1
		int *in;//array delle marche temporali in ingresso
		int *out;//array delle marche templorali in uscita
		int time;//contatore della marca temporale
		
		
		int findIndex(H val){//si occupa di cercare l'etichetta, se esiste ne ritorna l'indice altrimenti ritorna -1
			for(int i=0;i<n;i++)
				if(*K[i]==val) return i;
			
			return -1;
		}
		

		void DFSvisit(int x){
			c[x]=G;//il nodo appena visitato diventa grigio
			in[x]=time;//la sua marca temporale in ingresso viene registrata
			time++;//aumentiamo la marca temporale
			r[x]=current_root;//settiamo la radice del nodo corrente
			for(int i=0;i<n;i++){//scorriamo la lista di adiacenza del nodo
				if(M[x][i]==1 ){//se il nodo ha degli archi uscenti verso dei nodi bianchi allora li visitiamo
					if(c[i]==B){
						p[i]=x;
						DFSvisit(i);//la ricorsione una volta visitato i ci permette di fare backtracking e tornare al nodo che stavamo visitando
					}
				}
				
			}
			c[x]=N;//una volta visitata tutta la lista di adiacenza di un nodo esso diventa nero, quindi totalmente scoperto
			out[x]=time;//settiamo la marca temporale in uscita
			stack->push(x);//quando un nodo e' pushato nella pila vuol dire che e' stato visitato del tutto
			time++;
		}
		
	public:
		Mgraph(int dim){
			this->dim=dim;//impostiamo la dimensione
			n=0;//non ci sono nodi all'inizio
			m=0;//non ci sono archi
			K=new H*[dim];//creiamo un array di pointers ad etichette
			M=new int*[dim];
			Tm=new int*[dim];
			time=0;
			current_root=0;
			stack=NULL;
			
			//inizializzazione array
			r=new int[dim]; 
			c=new int[dim];
			
			p=new int[dim];
			in=new int[dim];
			out=new int[dim];
			
			for(int i=0;i<dim;i++){
				K[i]=NULL;//inizializiamo le etichette tutte nulle
				M[i]=new int[dim];//semplice allocazione di una matrice
				Tm[i]=new int[dim];
				for(int j=0;j<dim;j++){
					M[i][j]=0;//la matrice contiene gli archi, quindi non ce ne sono all'inizio
					Tm[i][j]=0;//inizializiamo la matrice trasposta a 0
				}
			}
		}
		
		Mgraph<H>* addNode(H val){//aggiunge un nodo all'array delle etichette
			int x=findIndex(val);
			if(n<dim && x==-1){//il nodo viene aggiunto se non e' presente nell'array e se c'e' spazio
				K[n]=new H(val);//istanziamo alla n-esima cella la nuova etichetta inserita
				n++;
			}
			return this;//ritorniamo un puntatore all'oggetto stesso per poter effettuare operazioni in cascata	
		}
		
		Mgraph<H>* addEdge(H u,H v){//aggiungiamo un arco nella matrice, usando le etichette
			int i=findIndex(u);//cerchiamo l'indice della prima etichetta
			int j=findIndex(v);//indice della seconda etichetta
			
			if(i!=-1 && j!=-1 && M[i][j]==0){//se entrambi i nodi esistono, e l'arco non e' presente possiamo procedere ad aggiungere l'arco
				M[i][j]=1;//abbiamo creato l'arco
				m++;//aumentiamo il contatore degli archi
			}
			
			return this;//ritorniamo un puntatore all'oggetto stesso per poter effettuare operazioni in cascata	
		}
		
		
		
		void DFS(){//la DFS non prende parametri poiche' si occupera' di visitare tutto il grafo usando lo stesso principio di colori della BFS
			for(int i=0;i<n;i++){//inizializzazione colori e precedenti
				c[i]=B;
				p[i]=-1;
				r[i]=0;
			}
			
			if(stack){//se c'e' una pila esistente la eliminiamo prima della DFS per evitare problemi
				delete stack;
				stack=NULL;
			} 
			stack=new Pila(dim);
			
			for(int i=0;i<n;i++){//visitiamo in profondita' tutti i nodi non ancora visitati
				if(c[i]==B){
					current_root=i;//tutti i nodi visitati da adesso saranno discendenti di i
					DFSvisit(i);
				}
			}
		}
		
		void trasposta(){
			for(int i=0;i<n;i++)
				for(int j=0;j<dim;j++)
					Tm[i][j]=M[j][i];
		}
		
		void DFStrasposta(){//creiamo la procedura di DFS per la trasposta
							//la variante sta nell'usare la pila affinche' 
							//la visita sia fatta in maniera uguale alla visita sulla matrice originale
							//sostanzialmente invertendo gli archi vediamo se dal nodo di partenza possiamo
							//raggiungere altri nodi essi faranno parte della stessa SCC
			for(int i=0;i<dim;i++){
				c[i]=B;
				r[i]=-1;//le radici sono fondamentali poiche' nodi con la stessa radice fanno parte della stessa SCC
			}
			while(!stack->pilaVuota()){//l'ordine di visita sara' corretto poiche' partiamo dall'ultimo nodo marcato
				int x=stack->pop();
				if(c[x]==B){
					current_root=x;
					TDFSvisit(x);
				}
			}
			
		}
		void TDFSvisit(int x){
			c[x]=G;
			r[x]=current_root;
			for(int i=0;i<n;i++){
				if(Tm[x][i] && c[i]==B)
					TDFSvisit(i);
			}
			c[x]=N;
		}
		void printSCC(){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++)
					if(r[j]==i) cout<<*K[j]<<"\t";
				cout<<endl;
			}
			
		}
};


int main(){
	Mgraph<char> *Gr = new Mgraph<char>(9) ;
    Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
    Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
    Gr->addNode('8');
    
    Gr->addEdge('0','8')->addEdge('0','1');
    Gr->addEdge('1','8');
    Gr->addEdge('2','4');
    Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
    Gr->addEdge('4','3');
    Gr->addEdge('6','5')->addEdge('7','0');
    Gr->addEdge('8','2');
    Gr->trasposta();
    Gr->DFS();
    Gr->DFStrasposta();
    Gr->printSCC();
    
	return 0;
}
