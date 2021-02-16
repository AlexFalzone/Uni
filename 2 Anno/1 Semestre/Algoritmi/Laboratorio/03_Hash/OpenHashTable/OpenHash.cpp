#include <iostream>
#include<math.h>
using namespace std;

template <class T> class HashTable
{
public:
	virtual HashTable<T>* insertKey(T x) = 0;
	virtual int searchKey(T x) = 0;
	virtual HashTable<T>* deleteKey(T x) = 0;
	virtual void print() = 0;
};

template <class T> class OpenHashTable : public HashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;	
	virtual OpenHashTable<T>* insertKey(T x) = 0;
	virtual OpenHashTable<T>* deleteKey(T x) = 0;
    virtual int searchKey(T x) = 0;
	int tableSize;
	int keyCounter;
	T** table;	
	T* deleted;

public:

	OpenHashTable<T>(int tableSize)
	{		
		this->deleted = new T();
		table = new T* [tableSize];
		for (int i = 0; i < tableSize; i++)
			table[i] = NULL;
		this->keyCounter = 0;
		this->tableSize = tableSize;
	}	
	
	void increaseKeyCounter()
	{
		keyCounter++;
	}

	void decreaseKeyCounter()
	{
		keyCounter--;
	}

	T* getDeleted()
	{
		return deleted;
	}

	int getTableSize() 
	{
		return tableSize;
	}		

	int getKeyCounter() 
	{
		return keyCounter; 
	}	

	T** getTable()
	{
		return table;
	}
};



template <class T> class StandardOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
	
public:
	StandardOpenHashTable<T>(int tableSize) : OpenHashTable<T>(tableSize) {}	

	StandardOpenHashTable<T>* insertKey(T x)
	{		
		if (this->getKeyCounter() == this->getTableSize())
			return this;
		int i = 0;
		while (i < this->getTableSize())
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL || this->getTable()[hash] == this->getDeleted())
			{
				this->getTable()[hash] = new T(x);
				this->increaseKeyCounter();
				return this;
			}
			i++;
		}
		return this;
	}


	int searchKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return -1;
		int iterator = 0;
		while (iterator < this->getTableSize())
		{
			int hash = computeHashFunction(x, iterator);	
			if (this->getTable()[hash] == NULL)
				return -1;
			if (this->getTable()[hash] != this->getDeleted() && *(this->getTable()[hash]) == x)
				return hash;
			iterator++;
		}
		return -1;
	}


	StandardOpenHashTable<T>* deleteKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return this;
		int position = searchKey(x);
		if (position > -1)
		{
			delete this->getTable()[position];
			this->getTable()[position] = this->getDeleted();
			this->decreaseKeyCounter();
			return this;
		}
		return this;
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i] != this->getDeleted() && this->getTable()[i] )
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};



template <class T> class NonStandardOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
public:
	NonStandardOpenHashTable<T>(int tableSize) : OpenHashTable<T>(tableSize) {}

	NonStandardOpenHashTable<T>* insertKey(T x)
	{
		if (this->getKeyCounter() == this->getTableSize())
			return this;
		int i = 0;
		while (i < this->getTableSize())
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL)
			{				
				this->getTable()[hash] = new T(x);
				this->increaseKeyCounter();
				return this;
			}
			i++;
		}
		return this;
	}

	int searchKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return -1;
		int iterator = 0;
		while (iterator < this->getTableSize())
		{			
			int hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] == NULL)
				return -1;
			if (*(this->getTable()[hash]) == x)
				return hash;
			iterator++;
		}
		return -1;
	}

	NonStandardOpenHashTable<T>* deleteKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return this;
		int iterator = 0;
		int hash = 0;
		while (iterator < this->getTableSize())
		{
			hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] != NULL && *(this->getTable()[hash]) == x)
			{
				delete this->getTable()[hash];	
				this->getTable()[hash] = NULL;
				this->decreaseKeyCounter();
				iterator++;
				for (; iterator < this->getTableSize(); iterator++)
				{					
					int hash2 = computeHashFunction(x, iterator);
					if (this->getTable()[hash2] == NULL)
						return this;
					this->getTable()[hash] = (this->getTable()[hash2]);
					this->getTable()[hash2] = NULL;
					hash = hash2;
				} 				
				return this;				
			}
			iterator++;
		}	
		return this;		
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i])
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};




template <class T> class LinearStandardOpenHashTable : public StandardOpenHashTable<T>
{
private:
	int computeHashFunction(T x, int i) 
	{		
		return (((int)x % this->getTableSize()) + i) % this->getTableSize();
	}
public:
	LinearStandardOpenHashTable(int tableSize) : StandardOpenHashTable<T>(tableSize) {}
};


template <class T> class LinearNonStandardOpenHashTable : public NonStandardOpenHashTable<T>
{
private:
	int computeHashFunction(T x, int i)
	{
		return (((int)x % this->getTableSize()) + i) % this->getTableSize();
	}
public:
	LinearNonStandardOpenHashTable(int tableSize) : NonStandardOpenHashTable<T>(tableSize) {}
};


template <class T> class QuadraticNonStandardOpenHashTable : public NonStandardOpenHashTable<T>
{
private:
	double c1 = 1 / 2;
	double c2 = 1 / 2;
	int computeHashFunction(T x, int i)
	{
		return ((int)(((int)x % this->getTableSize()) + c1*i+c2* pow(i,2))) % this->getTableSize();
	}
public:
	QuadraticNonStandardOpenHashTable(int tableSize) : NonStandardOpenHashTable<T>(tableSize) {}
};