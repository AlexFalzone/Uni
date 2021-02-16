#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


//BinaryHeap template
template <class T> class MaxBinaryHeap 
{
private:
	T** hqueue;	

	int heapsize;

	int queuesize;

	int left(int i)
	{
		return i << 1; // 2i
	}

	int right(int i)
	{
		return (i << 1) | 1;  //2i-1
	}

	int parent(int i)
	{
		return i >> 1; // i/2
	}

	void swap(int i, int j)
	{
		T* tmp = hqueue[i];
		hqueue[i] = hqueue[j];
		hqueue[j] = tmp;
	}

	void heapify(int i)
	{		
		if (i > heapsize)
			return;		
		int l = left(i);
		int r = right(i);
		int v = i;
		if (l <= heapsize && compare(hqueue[v], hqueue[l]) < 0)
			v = l;
		if (r <= heapsize && compare(hqueue[v], hqueue[r]) < 0)
			v = r;
		if (v == i)
			return;
		swap(i, v);
		heapify(v);
	}

public:	
	MaxBinaryHeap(int size)
	{
		hqueue = new T * [size+1];
		queuesize = size+1;
		heapsize = 0;		
	}
	
	MaxBinaryHeap(T** V, int size)
	{
		hqueue = V;
		queuesize = size + 1;
		heapsize = size;
	}	

	void buildHeap()
	{
		for (int i = heapsize / 2; i > 0; i--)
			heapify(i);
	}

	T* extract()
	{
		if (heapsize == 0)
			return NULL;
		swap(1, heapsize);
		heapsize--;
		heapify(1);
		return hqueue[heapsize + 1];
	}

	T** getPriorityQueue() const
	{
		return hqueue;
	}

	void modify(int i, T k)
	{
		if (i<1 || i>heapsize)
			return;
		if (compare(hqueue[i], &k) >= 0)
			return;
		delete hqueue[i];
		hqueue[i] = new T(k);
		while (i > 1 && compare(hqueue[i], hqueue[parent(i)]) > 0)
		{
			swap(i, parent(i));
			i = parent(i);
		}
		return;
	}

	MaxBinaryHeap<T>* enqueue(T x)
	{
		if (heapsize == queuesize - 1)
			return this;
		heapsize += 1;
		hqueue[heapsize] = new T(x);
		int i = heapsize;
		while (i > 1 && compare(hqueue[i], hqueue[parent(i)]) > 0)
		{
			swap(i, parent(i));
			i = parent(i);
		}
		return this;
	}

	T* extractMax()
	{
		return extract();
	}

	void increaseKey(int i, T k)
	{
		return modify(i, k);
	}

	double compare(T* a, T* b)
	{
		return (*a) - (*b);
	}

	
	void print()
	{
		if (size()<1)
			return;		
		for (int i = 1; i <= this->size(); i++)									
				cout<<*hqueue[i]<<" ";				
		cout<< endl;
	}

	void print(ofstream& output)
	{
		if (heapsize < 1)
			return;
		for (int i = 1; i <= heapsize; i++)
		{
			output << *hqueue[i];
			if (i != heapsize)
				output << " ";
		}
	}

	void sort()
	{
		buildHeap();
		int node_number = heapsize;
		for (int i = 0; i < node_number; i++)
			extract();
		heapsize = node_number;
	}

	int size() const
	{
		return heapsize;
	}



};


/*
Si implementi una coda con priorità utilizzando la struttura dati MaxHeap Binario in cui la priorità di ogni elemento sia definita dalla
chiave dell'elemento stesso (chiavi maggiori identificano priorità superiori). Si fornisca il codice della procedura BuildMaxHeap in grado
di costruire un MaxHeap a partire da un array non ordinato di elementi.
Si fornisca in seguito il codice di un programma in grado di leggere da un file di input una sequenza di N elementi, costruire un MaxHeap 
attraverso la procedura BuildMaxHeap e stampare la configurazione finale dell'Heap.
*/

/*
L’input è suddiviso in 100 task, uno per ogni riga. Ogni riga del file di input è formata da 2+N elementi. Il primo elemento è una stringa 
che identifica il tipo di dato (H) che dovrà essere contenuto all'interno della coda con priorità. Il secondo elemento è un valore intero N,
il quale rappresenta il numero di elementi contenuti nell'array di input. Seguono N valori che rappresentano, nell'ordine dato, gli elementi 
contenuti dell'array di input.
*/


/*
L’output dovrà essere formato da 100 righe, una per ogni task. Ogni riga contiene N elementi i quali rappresentano le chiavi contenute nella coda 
con priorità dopo l'esecuzione della procedura BuildMaxHeap. La stampa degli elementi dovrà essere effettuata per livelli dell'Heap, 
dal livello più alto (la radice) al livello più basso (le foglie). Per ogni livello, i nodi devono essere stampati procedendo da sinistra verso 
destra.
*/

/*
N è un numero intero compreso tra 10 e 200.
Il tipo H può essere uno dei seguenti tipi di dato: int, double, bool, char.
*/


/*
input.txt:
bool 10 0 1 1 1 1 1 1 0 1 0
int 10 30 93 41 52 86 18 93 53 56 56
double 10 9.58 8.28 9.94 0.95 3.95 2.06 3.88 8.28 7.2 7.22

output.txt
1 1 1 1 1 1 1 0 0 0
93 86 93 56 56 18 41 53 52 30
9.94 8.28 9.58 8.28 7.22 2.06 3.88 0.95 7.2 3.95
*/

template <class T> void read(int size, ifstream &input, ofstream &output)
{
	T** arr = new T * [size + 1];
	for (int i = 0; i < size; i++)
	{
		T d;
		input >> d;
		arr[i + 1] = new T(d);
	}
	MaxBinaryHeap<T>* heap = new MaxBinaryHeap<T>(arr, size);
	heap->buildHeap();
	heap->print(output);
	output << endl;
	delete heap;
	delete [] arr;
	return;	
}


int main()
{
	ifstream input("Exercises/heap/build-maxHeap/input.txt");
	ofstream output("Exercises/heap/build-maxHeap/output.txt");	    
	string type;
	int operations;	
	while (input >> type)
	{
		if (type == "\n")
			continue;
		input >> operations; 
		if (type == "double")
			read<double>(operations, input, output);
		else if (type == "char")
			read<char>(operations, input, output);
		else
			read<int>(operations, input, output);
	}
	input.close();
	output.close();
	return 1;
}