#include <iostream>

using namespace std;
template <class T> class Nodo;


template <class T> struct elem{
	Nodo<T>* dato;
	elem<T>* succ;
};

template <class T> class Pila{
	private:
		elem<T>* testa;
	public:
		Pila(){
			testa=NULL;
		}
		void push(Nodo<T>* val){
			elem<T>* nuovo=new elem<T>;
			nuovo->dato=val;
			nuovo->succ=testa;
			testa=nuovo;
		}
		Nodo<T>* pop(){
			Nodo<T>* tmp=testa->dato;
			elem<T>* muori=testa;
			testa=testa->succ;
			delete muori;
		//	cout<<tmp->getVal()<<" ";
			return tmp;
		}
		bool pilaVuota(){
			return testa==NULL;
		}
};


template <class T> class Nodo{
	private:
		Nodo<T>* padre;
		Nodo<T>* sx;
		Nodo<T>* dx;
		T val;
	public:
		Nodo(T val){
			this->val=val;
			padre=NULL;
			sx=NULL;
			dx=NULL;
		}
		T getVal(){
			return val;
		}
		void setVal(T val){
			this->val=val;
		}
		Nodo<T>* getPadre(){
			return padre;
		}
		Nodo<T>* getSx(){
			return sx;
		}
		Nodo<T>* getDx(){
			return dx;
		}
		void setPadre(Nodo<T>* padre){
			this->padre=padre;
		}
		void setSx(Nodo<T>* sx){
			this->sx=sx;
		}
		void setDx(Nodo<T>* dx){
			this->dx=dx;
		}
};

template <class H> class Albero{
	private:
		Nodo<H>* root;
		
		Nodo<H>* minimo(Nodo<H>* x){//deve essere richiamata su nodi non nulli, per questo la impostiamo private
			while(x->getSx()!=NULL) x=x->getSx();//si sposta a sinistra finche' puo', quello dara' il minimo
			return x;
 		}	
		void trapianta(Nodo<H>* u,Nodo<H>* v){//la trapianta ci consente di spostare sottoalberi, rimpiazza 
											  //un  sottoalbero di radice u con uno di radice v
			if(u->getPadre()==NULL) root=v;//se il sottoalbero da rimpiazzare non ha padre � la radice
			else if(u==u->getPadre()->getSx()) u->getPadre()->setSx(v);//se il sottoalbero da rimpiazzare e' figlio sinistro va 
																	   //collegato in questo modo
			else u->getPadre()->setDx(v);//analoga cosa se e' figlio destro
			
			if(v) v->setPadre(u->getPadre());//se il sostituto del nostro nodo non e' null allora ne settiamo il padre
			
			//una cosa importante e' che la trapianta ci consente di trapiantare sottoalberi nulli
		}
		Nodo<H>* massimo(Nodo<H>* x){//analoga alla procedura di minimo
			while(x->getDx()!=NULL) x=x->getDx();
			return x;
		}
		int calcolaAltezza(Nodo<H>* x){//l'altezza di un albero � la distanza dalla radice al nodo pi� lontano
			if(!x) return -1;//se il nodo e' nullo ritorniamo -1 perche' dobbiamo compensare la chiamata extra
			int s=calcolaAltezza(x->getSx());//calcoliamo l'altezza del sottoalbero sinistro
			int d=calcolaAltezza(x->getDx());//calcoliamo l'altezza del sottoalbero destro
			
			if(s>d) return 1+s;//ritorniamo il valore del sottoalbero piu' profondo +1 che sarebbe il nodo attuale
			else return 1+d;
		}
		void inOrder(Nodo<H>* x){
			if(x){
				inOrder(x->getSx());
				cout<<x->getVal()<<" ";
				inOrder(x->getDx());
			}
		}
		void preOrder(Nodo<H>* x){
			if(x){
				cout<<x->getVal()<<" ";
				preOrder(x->getSx());
				preOrder(x->getDx());
			}
		}
		void postOrder(Nodo<H>* x){
			if(x){
				postOrder(x->getSx());
				postOrder(x->getDx());
				cout<<x->getVal()<<" ";
			}
		}
	
	public:
		Albero(){
			root=NULL;//il costruttore si occupa solo di inizializzare la root a null
		}
		Nodo<H>* getRoot(){
			return root;//la root e' privata quindi abbiamo bisogno di un metodo getter
		}
		void insert(H val){
			Nodo<H>* tmp=root;
			Nodo<H>* prec=NULL;
			
			while(tmp!=NULL ){//partiamo dalla radice e ci spostiamo in base al valore
				prec=tmp;
				if(val< tmp->getVal()) tmp=tmp->getSx();//se val e' minore del valore del nodo sara' suo figlio sinistro
				else tmp=tmp->getDx();					//altrimenti sara' suo figlio destro
			}
			
			Nodo<H>* nuovo=new Nodo<H>(val);
			nuovo->setPadre(prec);//il padre del nuovo nodo e' prec(potrebbe essere anche null)
			
			if(prec==NULL )root=nuovo;//se prec e' null non siamo entrati nel ciclo quindi stiamo inserendo la root
			else if(val< prec->getVal()) prec->setSx(nuovo);//se val e' minore del valore di suo padre sara' figlio sinistro
			else prec->setDx(nuovo);//altrimenti sara' suo figlio destro 
		}
		void inOrder(){
			this->inOrder(root);//per evitare di poter chiamare la funzione su nodi che non sono la root si usa questo stratagemma
			cout<<endl;
		}
		void preOrder(){
			preOrder(root);//per evitare di poter chiamare la funzione su nodi che non sono la root si usa questo stratagemma
			cout<<endl;
		}
		void postOrder(){
			postOrder(root);//per evitare di poter chiamare la funzione su nodi che non sono la root si usa questo stratagemma
			cout<<endl;
		}	
		Nodo<H>* ricerca(H val){
			Nodo<H>* tmp=root;//la nostra ricerca parte dalla radice
			while(tmp!=NULL && tmp->getVal()!=val){//ci fermiamo se troviamo il nodo o se esso non c'e' e quindi tmp diventa null
				if(val< tmp->getVal()) tmp=tmp->getSx();//se il valore cercato e' minore del nodo ci spostiamo a sinistra
				else tmp=tmp->getDx();//se il valore cercato e' maggiore del nodo ci spostiamo a destra
			}
			return tmp;//ritorniamo il nodo d'arrivo che potrebbe essere null se il valore non e' presente
		}
		Nodo<H>* ricercaRicorsiva(Nodo<H>* x, H val){
			if(!x) return NULL;//caso base il nodo e' nullo e quindi l'elemento non e' presente
			else if(x->getVal()==val) return x;//altro caso base, abbiamo trovato il nodo desiderato
			else if(val < x->getVal()) return ricercaRicorsiva(x->getSx(),val);//il valore e' minore del nodo esaminato quindi ci spostiamo a sinistra
			else return ricercaRicorsiva(x->getDx(),val);//il valore e' maggiore quindi ci spostiamo a destra
		} 
		void cancella(H val){
			Nodo<H>* del=ricerca(val);
			if(del){
				if(del->getSx()==NULL) trapianta(del,del->getDx());//se il nodo da eliminare non ha figlio sinistro, il suo figlio destro 
																   //viene trapiantato al suo posto
				else if(del->getDx()==NULL) trapianta(del,del->getSx());//se il nodo non ha figlio destro, il suo figlio sinistro � 
																		//e' trapiantato al suo posto
				else{
					Nodo<H>* min=minimo(del->getDx());//in questo caso il nodo ha entrambi i figli, quindi cerchiamo il suo successore nel
													  //suo sottoalbero destro, poiche' siamo sicuri che esiste
					if(min!=del->getDx()){//se il successore del nodo da eliminare non e' suo figlio dobbiamo spostarlo senza
										  //scombussolare l'albero, quindi trapiantiamo il suo figlio destro al suo posto
						trapianta(min,min->getDx());
						min->setDx(del->getDx());//il figlio destro del successore deve essere il sottoalbero destro del nodo da eliminare
						min->getDx()->setPadre(min);//facciamo anche il n�collegamento dal basso verso l'alto, cambiando il padre della
													//radice del sottoalbero destro
					}
					trapianta(del,min);//trapiantiamo il successore al posto del nodo da eliminare
					min->setSx(del->getSx());//colleghiamo il sottoalbero sinistro
					min->getSx()->setPadre(min);//settiamo il padre del sottoalbero sinistro, come nel caso del sottoalbero destro
					
				}
				delete del;
			}
		}
		Nodo<H>* successore(H val){
			Nodo<H>* tmp=ricerca(val);
			if(tmp){
				//il successore e' il minimo tra le chiavi piu' grandi del nodo
				Nodo<H>* succ;
				if(tmp->getDx()) succ=minimo(tmp->getDx());//se esiste ill sottoalbero destro il successore e' il minimo
				else{//altrimenti e' il primo nodo antenato di tmp che ha come figlio sinistro un antenato di tmp
					while(tmp->getPadre()!=NULL && tmp->getPadre()->getDx()==tmp) tmp=tmp->getPadre();
					succ=tmp->getPadre();
				}
				return succ;
			}
		}
		Nodo<H>* predecessore(H val){
			Nodo<H>* tmp=ricerca(val);
			Nodo<H>* succ=NULL;
			//il predecessore e' l'inverso del successore sostanzialmente
			if(tmp){
				if(tmp->getSx()!=NULL) succ=massimo(tmp->getSx());
				else{ 
					while(tmp->getPadre()!=NULL && tmp->getPadre()->getSx()==tmp) tmp=tmp->getPadre();
					succ=tmp->getPadre();
				} 
			}
			return succ;
		}
		int altezza(){
			return calcolaAltezza(root);
		}
		void iterativePreOrder(){
			Nodo<H>* tmp=root;
			Pila<H> stack;
			stack.push(tmp);//mettiamo la radice nello  stack
			while(!stack.pilaVuota()){//finquando ci sono elementi nello stack
				tmp=stack.pop();//prendiamo l'ultimo elemnto, lo stampiamo e poi inseriamo dx e sx
				cout<<tmp->getVal()<<" ";
				if(tmp->getDx()) stack.push(tmp->getDx());
				if(tmp->getSx()) stack.push(tmp->getSx());
			}
			cout<<endl;
		}
		void iterativeInOrder(){
			Nodo<H>* curr=root;
			Pila<H> stack;//utilizziamo una pila per stabilire l'ordine di stampa dei nodi
			bool done=false;//variabile per stabilire se abbiamo finitp
			while(!done){
				if(curr){	//se il nodo non e' nullo
					stack.push(curr);//ogni volta mettiamo il nodo in cima alla pila
					curr=curr->getSx();//e ci spostiamo a sinistra
				}
				else if(stack.pilaVuota()){
					done=true;
				} 
				else{//quando il nodo e nullo ma ci sono elementi in pila
					
					curr=stack.pop();//prendiamo l'ultimo elemento in pila
					cout<<curr->getVal()<<" ";
					curr=curr->getDx();//ci spostiamo a destra del nodo appena stampato
				}
			}
			cout<<endl;
		}
		void iterativePostOrder(){
			Pila<H> pila_in,pila_out;
			Nodo<H>* tmp=root;
			pila_in.push(tmp);
			//usiamo il secondo stack come apposggio, li verrannno inserite le radici ogni volta,
			//nel primo stack inseriamo sinistra e destra della radice che poi diventeranno a loro vola le radici
			while(!pila_in.pilaVuota()){
				tmp=pila_in.pop();
				pila_out.push(tmp);
				if(tmp->getSx()) pila_in.push(tmp->getSx());
				if(tmp->getDx()) pila_in.push(tmp->getDx());
			}
			while(!pila_out.pilaVuota()){
				tmp=pila_out.pop();
				cout<<tmp->getVal()<<" ";
			}
			cout<<endl;
			
		}
		int profondita(H val){//e' la distanza da un nodo alla radice, ovvero la sua altezza sostanzialmente
			Nodo<H>* tmp=ricerca(val);
			if(tmp){
				int x=0;
				while(tmp->getPadre()!=NULL ){
					tmp=tmp->getPadre();
					x++;
				}
				return x;
			}
			return -1;
		}
};


int main(){
	Albero<int>* A=new Albero<int>;
	A->insert(7);A->insert(104);A->insert(2);A->insert(42);A->insert(1000);A->insert(100000);A->insert(50000000);
    cout << A->profondita(50000000) << endl;
	cout << A->successore(2);
	//Nodo<int>* el = A->ricerca(100000);
    cout << A->altezza();
	/*A->inOrder();
	A->iterativeInOrder();
	A->preOrder();
	A->iterativePreOrder();
	A->postOrder();
	A->iterativePostOrder();*/
	
	return 0;
}
