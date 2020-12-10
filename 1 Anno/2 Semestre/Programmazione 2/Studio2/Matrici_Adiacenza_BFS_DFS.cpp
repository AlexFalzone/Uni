#include <iostream>
using namespace std;


//definiamo i colori da usare in BFS e DFS

#define B 0 	//nodo Bianco
#define G 5 	//nodo Grigio
#define N 10	//nodo Nero

#define inf 500


/*implementiamo una coda per l'uso della BFS, essa ci e' utile per inserire ed estrarre i nodi nell'ordine giusto
la coda conterra' solamente indici quindi non serve trattarla come un template*/

class Coda{
	private:
		int *arr;
		int dim;
		int testa;
		int fine;
	
	public:
		Coda(int dim){
			this->dim=dim;
			arr=new int[dim];
			testa=fine=-1;
		}
		bool codaPiena(){
			return (fine+1)%dim==testa;
		}
		bool codaVuota(){
			return testa==-1;
		}
		
		void enqueue(int x){
			if(!codaPiena()){
				fine=(fine+1)%dim;
				arr[fine]=x;
				if(testa==-1)testa=0;
			}
		}
		int dequeue(){
			if(!codaVuota()){
				int x=arr[testa];
				if(testa==fine) testa=fine=-1;
				else testa=(testa+1)%dim;
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
		
		//array utilizzati per la BFS
		int *c;//array dei colori, un nodo puo' essere grigio, bianco o nero
		int *p;//array dei predecessori, se non esiste e' -1
		int *d;//array delle distanze, contiene la distanza nodo radice
		
		//array e variabili usati per la DFS semplice(usiamo anche i colori e i precedenti)
		int *in;//array delle marche temporali in ingresso
		int *out;//array delle marche templorali in uscita
		int time;//contatore della marca temporale
		
		
		int findIndex(H val){//si occupa di cercare l'etichetta, se esiste ne ritorna l'indice altrimenti ritorna -1
			for(int i=0;i<n;i++)
				if(*K[i]==val) return i;
			
			return -1;
		}
		
		void BFS(int v){//e' una funzione private perche' potrebbe essere richiamata su nodi nulli, quindi la richiamiamo tramite
						//un altra funzione per evitare problemi di segmentazione, o un utilizzo scorretto						
			for(int i=0;i<n;i++){
				c[i]=B;//tutti i nodi sono bianchi all'inizio, prima di iniziare ad esplorare
				d[i]=inf;//impostiamo le distanze di ogni nodo dalla radice al massimo possibile, che rappresenta l'infinito
				p[i]=-1;//settiamo tutti i precedenti a -1 poiche' i nodi non hanno ancora precedenti
			}
			Coda nodi(n);//la coda rappresenta i nodi scoperti della quale dobbiamo ancora esaminare la lista di addiacenza
			c[v]=G;//scopriamo il nodo sulla quale chiamoamo la BFS
			d[v]=0;//il nodo dista 0 da se stesso
			nodi.enqueue(v);//il nodo grigio va inserito nella coda per esaminarne la lista di adiacenza
			while(!nodi.codaVuota()){//finche' ci sono nodi da esaminare 
				int x=nodi.dequeue();//rimuoviamo il nodo della quale dobbiamo esaminare la lista di adiacenza
				for(int i=0;i<n;i++){//lo usiamo per esaminare la lista di adiacenza del nodo 
					if(M[x][i]==1 && c[i]==B){//se abbiamo un arco verso un nodo bianco
						c[i]=G;//il nodo appena scoperto diventa grigio
						d[i]=d[x]+1;//la sua distanza dalla radice e' la distanza di x+1
						p[i]=x;//il suo precedente e' x poiche' e' stato scoperto scorrendo la sua lista di adiacenza
						nodi.enqueue(i);//inseriamo il nodo in coda cosi' che venga esaminato
					}
				}
				c[x]=N;//il nodo della quale abbiamo esaminato tutta la lista di adiacenza diventa nero
			}
		}
		
		void printPath(int index){//utilizzata per stampare il percorso da un nodo alla radice nel BFT
			if(index==-1) return;//se la funzione viene invocata su un indice negativo si blocca
			if(p[index]==-1) cout<<*K[index]<<" ";//se il nodo non ha un precedente allora non richiamiamo la funzione
			else {
				printPath(p[index]);//se il nodo ha un precedente stampiamo prima il precedente e poi il nodo stesso
				cout<<*K[index]<<" ";
			}
		}
		void DFSvisit(int x){
			c[x]=G;//il nodo appena visitato diventa grigio
			in[x]=time;//la sua marca temporale in ingresso viene registrata
			time++;//aumentiamo la marca temporale
			for(int i=0;i<n;i++){//scorriamo la lista di adiacenza del nodo
				if(M[x][i]==1 && c[i]==B){//se il nodo ha degli archi uscenti verso dei nodi bianchi allora li visitiamo
					p[i]=x;
					DFSvisit(i);//la ricorsione una volta visitato i ci permette di fare backtracking e tornare al nodo che stavamo visitando
				}
			}
			c[x]=N;//una volta visitata tutta la lista di adiacenza di un nodo esso diventa nero, quindi totalmente scoperto
			out[x]=time;//settiamo la marca temporale in uscita
			time++;
		}
		
	public:
		Mgraph(int dim){
			this->dim=dim;//impostiamo la dimensione
			n=0;//non ci sono nodi all'inizio
			m=0;//non ci sono archi
			K=new H*[dim];//creiamo un array di pointers ad etichette
			M=new int*[dim];
			time=0;
			
			//inizializzazione array 
			c=new int[dim];
			d=new int[dim];
			p=new int[dim];
			in=new int[dim];
			out=new int[dim];
			
			
			for(int i=0;i<dim;i++){
				K[i]=NULL;//inizializiamo le etichette tutte nulle
				M[i]=new int[dim];//semplice allocazione di una matrice
				for(int j=0;j<dim;j++){
					M[i][j]=0;//la matrice contiene gli archi, quindi non ce ne sono all'inizio
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
		
		void BFS(H val){//utilizziamo questa funzione di mezzo per evitare di chiamare la BFS su nodi nulli
			int i=findIndex(val);//cerchiamo l'etichetta
			if(i!=-1) BFS(i);//chiamiamo la BFS che prende un intero se l'etichetta esiste
		}
		void printPath(H val){
			int i=findIndex(val);//usiamo questa funzione come interfaccia della printPath
			if(i>=0) printPath(i);//se il nodo esiste chiamiamo la print path su di lui
			cout<<endl;
		}
		
		void DFS(){//la DFS non prende parametri poiche' si occupera' di visitare tutto il grafo usando lo stesso principio di colori della BFS
			for(int i=0;i<n;i++){//inizializzazione colori e precedenti
				c[i]=B;
				p[i]=-1;
			}
			for(int i=0;i<n;i++){//visitiamo in profondita' tutti i nodi non ancora visitati
				if(c[i]==B){
					DFSvisit(i);//se il nodo e' bianco iniziamo una visita in profondita'
				}
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
    Gr->addEdge('6','5');
    Gr->addEdge('8','2');
    
   Gr->BFS('0');
    Gr->printPath('7');
	Gr->DFS();
    return 0;
	
}
