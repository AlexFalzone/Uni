/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 1: Creare una pila usando array
*/
#include<iostream>

using namespace std;

const int MaxDimPila=100; 

typedef int TipoDato; 

class Pila {
private: 
	TipoDato VettorePila[MaxDimPila]; 
	int cima; 	
public:
	Pila(); //Costruttore della pila
	void Push(TipoDato elemento); //Inserisce un elemento nella pila
	TipoDato Pop();  //Estrae un elemento dalla pila
	void StampaPila(); 
	int PilaVuota(); // Verifica se la pila è piena
	int PilaPiena(); // Verifica se la pila è vuota
}; 

Pila::Pila(void) : cima(-1) {}; 

int Pila::PilaPiena() 
{
	if (cima==(MaxDimPila-1)) 
		return 1;
	else return 0;
}

int Pila::PilaVuota() 
{
	if (cima==-1) 
		return 1;
	else return 0;
}

void Pila::Push(TipoDato x)
{
	if (PilaPiena()) {
		cerr << "Stack Overflow" << endl; 
		exit(1);  }
	else 	{
		cima++; 
		VettorePila[cima]=x; 
		}
}
		
TipoDato Pila::Pop()
{	TipoDato x;
	
	if (PilaVuota()) {
		cerr << "Stack Underflow" << endl; 
		exit(1);  }
	else 	{ 
		x=VettorePila[cima];
		cima--;
		return x; 
	}
}
		

void Pila::StampaPila()
{
	int i=cima;
	if (PilaVuota()) 
		cout << "Pila vuota!" << endl; 
	else 	{
		for(int i=cima; i>=0; i--)
			cout << "Posizione " << i << " : " << VettorePila[i] << endl; 
			}
}		
	 

int main()
{
	Pila p;
	
	p.StampaPila(); 
	p.Push(4); 
	p.Push(8); 
	p.Push(16); 
	p.StampaPila(); 
	TipoDato x=p.Pop(); 
	p.StampaPila();
	return 0;	
}