/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Liste

Esercizio 5: Creare una coda usando array circolari senza il campo addizionale 
num_elementi.
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
public:
	Coda(); //Costruttore della pila
	void Enqueue(TipoDato elemento); //Inserisce un elemento nella coda
	TipoDato Dequeue();  //Estrae un elemento dalla coda
	void StampaCoda();
	TipoDato Testa(); // Legge l'elemento in testa alla coda senza estrarlo 
	int CodaVuota() {return (testa==-1);} // Verifica se la coda è vuota
	int CodaPiena() {return ((fine +1) % MaxDimCoda ==testa);} // Verifica se la coda è piena
}; 

Coda::Coda(void) : testa(-1), fine(-1) {}; 

void Coda::Enqueue(TipoDato x) 
{	
	if (this->CodaPiena())
		cerr << "Coda piena! \n";  	
	else {  
		fine=(fine + 1) % MaxDimCoda;
		cout << "Valore fine in Enqueue : " << fine << endl; 
		VettoreCoda[fine]=x;
		if (testa==-1) testa++;
		/* 	Se quello in corso è il primo inserimento la testa viene spostata 
			alla posizione 0
		*/
		}
}

TipoDato Coda::Testa()
{
	cout << "Testa: " << testa << "\t Fine: " << fine << endl; 
}


TipoDato Coda::Dequeue()
{	int x;
	
	if (CodaVuota()) {
		cerr << "Coda Vuota!" << endl; 
		return -1;  }
	else 	{ 
		x=VettoreCoda[testa];
		testa=(testa+1) % MaxDimCoda;
		cout << "valore testa= " << testa << endl;
		if ((testa-1) % MaxDimCoda == fine) 
			testa=fine=-1;
	/*	Se a seguito dell'inserimento il valore di testa supera 
		quello di fine allora abbiamo svuotato la coda e possiamo 
		far scattare la condizione di coda vuota.
	*/
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
		cout << "Posizione " << x << " : " << VettoreCoda[i% MaxDimCoda] << endl;
		}
}		
	 

int main()
{
	Coda coda;
	
	int x=coda.Dequeue(); 
	for (int i=0; i<MaxDimCoda; i++) 
		coda.Enqueue((i+1)*10); 
	coda.StampaCoda();
	coda.Enqueue(4); 
	cout <<endl;
	for (int i=0; i<MaxDimCoda-1; i++) 
		x=coda.Dequeue();  
	coda.StampaCoda();
	cout<<endl;
	for (int i=0; i<MaxDimCoda-1; i++)
		coda.Enqueue((i+1)*4);
	cout<<endl;	
	coda.StampaCoda();
	return 0;	
}