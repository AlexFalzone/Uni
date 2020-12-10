/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 4: Creare una coda usando array circolari
*/
#include<iostream>

using namespace std;

const int MaxDimCoda=10; 

typedef int TipoDato; 

class Coda {
private: 
	TipoDato VettoreCoda[MaxDimCoda]; 
	int testa;
	int fine; 
	int num_elementi;	
public:
	Coda(); //Costruttore della pila
	void Enqueue(TipoDato elemento); //Inserisce un elemento nella coda
	TipoDato Dequeue();  //Estrae un elemento dalla coda
	void StampaCoda();
	TipoDato Testa(); // Legge l'elemento in testa alla coda senza estrarlo 
	int CodaVuota() {return (num_elementi==0);} // Verifica se la coda è vuota
	int CodaPiena() {return (num_elementi==MaxDimCoda);} // Verifica se la coda è piena
}; 

Coda::Coda(void) : testa(0), fine(-1), num_elementi(0) {}; 

void Coda::Enqueue(TipoDato x) 
{	
	if (this->CodaPiena())
		cerr << "Coda piena! \n";  	
	else {  
		fine=(fine + 1) % MaxDimCoda; 
		VettoreCoda[fine]=x;
		num_elementi++;
		}
}

TipoDato Coda::Testa()
{
	return testa;  
}


TipoDato Coda::Dequeue()
{	int x;
	
	if (CodaVuota()) {
		cerr << "Coda Vuota!" << endl; 
		return -1;  }
	else 	{ 
		x=VettoreCoda[testa];
		testa=(testa+1) % MaxDimCoda;
		num_elementi--;
		return x; 
		}
}
		

void Coda::StampaCoda()
{
	int i=testa, x=0;
	if (CodaVuota()) 
		cout << "Coda vuota!" << endl; 
	else 	{
		while ((i % MaxDimCoda)!=fine) {
			cout << "Posizione " << x << " : " << VettoreCoda[i % MaxDimCoda] << endl; 
			x++; i++; 
			} 
	/* Il ciclo precedente salterebbe l'ultima posizione della coda. Per questo 
		aggiungiamo una ulteriore istruzione cout per scrivere l'ultimo elemento 
	*/
		cout << "Posizione " << x << " : " << VettoreCoda[i% MaxDimCoda] << endl;
		}
}		
	 

int main()
{
	Coda coda;
	
	int x=coda.Dequeue(); 
	for (int i=0; i<MaxDimCoda; i++) 
		coda.Enqueue((i+1)*10); 
	cout << endl; 
	coda.StampaCoda();
	coda.Enqueue(4); 
	for (int i=0; i<MaxDimCoda-1; i++) 
		x=coda.Dequeue(); 
	cout << endl;  
	coda.StampaCoda();
	cout << endl;
	for (int i=0; i<MaxDimCoda-1; i++)
		coda.Enqueue((i+1)*4);
	coda.StampaCoda();
	return 0;	
}