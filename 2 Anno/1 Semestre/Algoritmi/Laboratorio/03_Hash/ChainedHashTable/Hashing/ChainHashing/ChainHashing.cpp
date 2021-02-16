#include<iostream> 
#include <list> 
using namespace std;

template <class T> class HashTable
{  		 
  public:	     	
	     virtual HashTable<T>* insertKey(T x)=0;
	     virtual HashTable<T>* deleteKey(T key)=0;		 
		 virtual int computeHashFunction(T x) = 0;
		 virtual int searchKey(T key) = 0;	
};


template <class T> class ChainedHashTable : public HashTable<T>
{
  private:
	       int slots;    // Number of slots 	
	       list<T> *table; 
		   int size;	
  public:
	ChainedHashTable<T>(int x)
	{
		this->slots = x;
		table = new list<T>[slots];
		size = 0;		
	}

	ChainedHashTable<T>* insertKey(T key)
	{
		int index = computeHashFunction(key);
		table[index].push_back(key);
		size++;
		return this;
	}


	ChainedHashTable<T>* deleteKey(T key)
	{		
		int index = computeHashFunction(key);
		int pos1 = -1;
		int pos2 = -1;
		searchKey(key, &pos1, &pos2);
		if (pos1 != -1)
		{
			list<T>::iterator i = table[pos1].begin();
			advance(i, pos2);
			table[pos1].erase(i);
			size--;
		}
		return this;
	}
	
	int searchKey(T key)
	{
		int index = computeHashFunction(key);
		list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
				return index;
		}
		return -1;	
	}

	void searchKey(T key, int* pos1, int* pos2)
	{
		int index = computeHashFunction(key);
		list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
			{
				*pos1 = index;
				*pos2 = distance(table[index].begin(), i);
				return;
			}
		}
		*pos1 = -1;
		*pos2 = -1;
		return;
	}

	int getSlotNumber()
	{
		return slots;
	}

	int getSize()
	{
		return size;
	}

	void printHashTable()
	{
		for (int i = 0; i < this->getSlotNumber(); i++) 
		{
			cout << i;
			for (auto x : table[i])
				cout << " --> [" << x <<"]";
			cout << endl;
		}
	}

};


template <class T> class DivisionChainedHashTable : public ChainedHashTable<T>
{
 private:
	int computeHashFunction(T x) 
	{
		int h = ((int)x % this->getSlotNumber());
		return h;
	}
 public:
	DivisionChainedHashTable<T>(int edge_number) : ChainedHashTable<T>(edge_number) {}
};


template <class T> class MultiplicationChainedHashTable : public ChainedHashTable<T>
{
private:
	double c;
	int computeHashFunction(T x) 
	{
		double y = x * c;
		double a = y - (int)y;
		int h = (int)(a * this->getSlotNumber());
		return h;
	}
public:
	MultiplicationChainedHashTable(int edge_number) : ChainedHashTable<T>(edge_number)
	{
		c = 0.7;
	}
};