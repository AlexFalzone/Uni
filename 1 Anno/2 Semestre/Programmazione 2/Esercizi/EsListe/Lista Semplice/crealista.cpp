/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 1: Creare una lista che contiene gli elementi 1,2 e 3
*/
#include<iostream>

using namespace std;

class Elemento {
public:
	int valore;
	Elemento* succ; 
	
	Elemento(Elemento* n, int d) : succ(n), valore(d) {}
};

void stampa(Elemento* p)
{
	Elemento* primo=p; 
	
	while (primo!=NULL) {
		cout << " " << primo->valore << endl;
		primo=primo->succ;
		}
} 


int main()
{
	Elemento* Primo=NULL;
	
	Primo=new Elemento(Primo,1);
	Primo=new Elemento(Primo,2);
	Primo=new Elemento(Primo,3);
	stampa(Primo);
	return 0;	
}
