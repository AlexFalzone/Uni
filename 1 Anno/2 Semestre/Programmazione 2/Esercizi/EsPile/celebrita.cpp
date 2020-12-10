/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 3: Esercizio della celebrità risolto usando le pile.   
*/
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define INVITATI 30

using namespace std;

class Invitato {
private:
	bool celebrita;
	int posizione;
public: 
	void Inizializza(bool val, int pos) {celebrita=val; posizione=pos;} 
	bool ECelebrita() { return celebrita;}
	bool conosce(Invitato);
	int RivelaPos() {return posizione;}
};

bool Invitato::conosce(Invitato a)
{
	
	if (a.ECelebrita()) return 1;
	else return 0; 
}

void Init(Invitato a[]) 
{	
	srand(time(NULL));
	int indice=rand() % INVITATI;
	cout << "Valore casuale: " << indice << endl;  
	for (int i=0; i<INVITATI;i++)
		if (i==indice) a[i].Inizializza(1,i); 
		else a[i].Inizializza(0,i);
}
 
class Nodo {
public: 
	Invitato p; 
	Nodo* succ; 
	
	Nodo(Invitato x) {p=x; succ=NULL;} //Costruttore
	~Nodo(){} // Distruttore
	//void Assegna(int x) {valore=x;} //Assegna il valore x al nodo 
	Nodo* Successivo() {return succ;} // Restituisce il successivo 
	void AssegnaSuccessivo(Nodo* p) {succ=p;} 
	// Concatena p al nodo 
};

class Pila{
public: 
	Nodo* pp; 
	
	Pila() {pp=NULL;}
	bool PilaVuota() {return !pp;}
	bool SoloUno() {if ((pp!=NULL) && (pp->Successivo()==NULL)) return 1; else return 0;}
	Invitato PrimoElemento() { if (pp!=NULL) return pp->p;}
	void Push(Invitato x); 
	Invitato Pop();
	void CancellaNodo(); 
	~Pila();  
};
	
void Pila::Push(Invitato x)
{	
	Nodo* aux=new Nodo(x); 
	
	if(pp) aux->AssegnaSuccessivo(pp);
	pp=aux;
}	

void Pila::CancellaNodo()
{	Nodo* pnodo; 
 	
 	if (pp) {
 		pnodo=pp; 
 		pp=pp->Successivo(); 
 		delete pnodo; 
 		}
}

Invitato Pila::Pop() {
	Invitato e; 
	
	e=PrimoElemento(); 
	CancellaNodo(); 
	return e; 
}
	
Pila::~Pila() {
	Nodo* pnodo; 
	
	while(pp!=0)	{
		pnodo=pp; 
		pp=pp->Successivo();
		delete pnodo; 
		}
}

int main()
{	
	Pila p; 
	Invitato A[INVITATI];
	Invitato celeb;

	Init(A); 
	for(int i=0; i<INVITATI; i++)
		p.Push(A[i]);
	celeb=A[0];
	while (!p.SoloUno())	{
		Invitato A1, A2; 
		
		A1=p.Pop();
		A2=p.Pop(); 
		if (A1.conosce(A2))
			{	p.Push(A2);
				celeb=A2;	
			}
		else if (A2.conosce(A1)) 
			{	p.Push(A1);
				celeb=A1; 
			} 
	}
	cout << "La celebrità è : " << celeb.RivelaPos() << endl;
	return 0;	
}