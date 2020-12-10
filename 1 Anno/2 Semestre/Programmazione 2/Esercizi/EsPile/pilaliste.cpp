/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 2: Creazione di una lista usando liste dinamiche.   
*/
#include<iostream>

using namespace std;

class Nodo {
public:
	int valore;
	Nodo* succ;
		
	Nodo(int x) {valore=x; succ=NULL;} //Costruttore
	~Nodo(){} // Distruttore
	void Assegna(int x) {valore=x;} //Assegna il valore x al nodo 
	Nodo* Successivo() {return succ;} // Restituisce il successivo 
	void AssegnaSuccessivo(Nodo* p) {succ=p;} 
	// Concatena p al nodo 
};

class Pila{
private: 
	Nodo *p;
public: 	
	Pila() {p=NULL;}
	void SvuotaPila() {p=NULL;}
	bool PilaVuota() {return !p;}
	int PrimoElemento() { if (p!=NULL) return p->valore;}
	void Push(int x); 
	int Pop();
	void CancellaNodo(); 
	void StampaPila(); 
	~Pila();  
};

void Pila::StampaPila()		{
	Nodo* pnodo=p; 
	
	if (pnodo==NULL) 
		cout << "Lista vuota!" << endl;
	while(pnodo!=NULL) {
		cout << pnodo->valore << endl; 
		pnodo=pnodo->Successivo(); 
	}
}
	
void Pila::Push(int x)
{	
	Nodo* aux=new Nodo(x); 
	
	if(p) aux->AssegnaSuccessivo(p);
	p=aux;
}	

void Pila::CancellaNodo()
{	Nodo* pnodo; 
 	
 	if (p) {
 		pnodo=p; 
 		p=p->Successivo(); 
 		delete pnodo; 
 		}
}

int Pila::Pop() {
	int e; 
	
	e=PrimoElemento(); 
	CancellaNodo(); 
	return e; 
}
	
Pila::~Pila() {
	Nodo* pnodo; 
	
	while(p!=0)	{
		pnodo=p; 
		p=p->Successivo();
		delete pnodo; 
		}
}

int main()
{	
	Pila p; 

	p.Push(5); 
	p.Push(7);
	p.Push(11); 
	p.StampaPila();
	while (!p.PilaVuota())	{
		cout << p.PrimoElemento() << "\t"; 
		p.Pop();
		}
	cout << endl;
	p.Push(13); 
	p.Push(17); 
	p.StampaPila(); 
	p.~Pila(); 
	p.StampaPila();
	return 0;	
}