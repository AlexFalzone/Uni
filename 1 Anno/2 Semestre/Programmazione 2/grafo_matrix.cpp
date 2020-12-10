#include<iostream>
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf 99999999

class Coda
{
private:
    int* arr; 
    int testa;
    int fine;
    int dim;

public:
    Coda(int dim)
    {
        this->dim = dim;
        testa = fine = -1;
        arr = new int[dim];
    }

    bool codaPiena() 
    {
        return (fine+1)%dim == testa;
    }  

    bool codaVuota()
    {
        return (testa == -1);
    }

    void enqueue(int val)
    {
        if (!codaPiena())
        {
            fine = (fine+1)%dim;
            arr[fine] = val;
            if (testa == -1)
            {
                testa = 0;
            }
        }
    }

    int dequeue()
    {
        if (!codaVuota())
        {
            int x = arr[testa];
            if (testa == fine)
            {
                testa = fine = -1;
            }
            else
            {
                testa = (testa+1)%dim;
            }
            return x;
        }
        return -1;
    }

};

template<class H>
class MGraph
{
private:
    int archi, nodi, max_nodi;
    int current_root;
    int** M; //matrice adiacenza
    H** matrix; //matrice indici

    int* color;
    int* pred;
    int* dist;
    int* rad;

    int* in;
    int* out;
    int time;


    int findIndex(H val)
    {
        for (int i = 0; i < nodi; i++)
        {
            if (*matrix[i] == val)
            {
                return i;
            }
        }
        return -1;
    }

    void _bfs(int v)
    {
        for (int i = 0; i < nodi; i++)
        {
            color[i] = W;
            dist[i] = inf;
            pred[i] = -1;
        }
        color[v] = G;
        dist[v] = 0;
        pred[v] = -1;
        Coda* coda = new Coda(nodi);
        coda->enqueue(v);
        while (!coda->codaVuota())
        {
            int x = coda->dequeue();
            for (int i = 0; i < nodi; i++)
            {
                if (M[x][i] == 1 && color[i] == W)
                {
                    color[i] = G;
                    dist[i] = dist[x] +1;
                    pred[i] = x;
                    coda->enqueue(i);
                }
            }
            color[x] = B;
        }
        for(int i=0; i<nodi; i++) 
        {
			cout << "[" << i << "]->";
			if(dist[i]==inf) cout << "inf." << endl;
			else cout << dist[i] << endl;
		}
		cout << endl;
    }

    int DFS_Visit(int v)
    {
        color[v] = G;
        in[v] = time++;
        rad[v] = current_root;
        int cycle = 0;
        for (int i = 0; i < nodi; i++)
        {
            if (M[v][i] == 1)
            {
                if (color[i] == W)
                {
                    pred[i] = v;
                    cycle |= DFS_Visit(i);
                }
                if (color[i] == G)
                {
                    cycle = 1;
                }
            }
        }
        color[v] = B;
        out[v] = time++;
        return cycle;
    }

    void sort(int *a, int n, int *k) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && k[a[j+1]]>k[a[j]]) {
					int t = a[j+1];
					a[j+1] = a[j];
					a[j] = t;
					j--;
				}
			}
		}

    /*void _printPath(int x)
    {
        if (x == -1)
        {
            return;
        }
        if (pred[x] == -1)
        {
            cout << *matrix[x] << " ";
        }
        else 
        {
			_printPath(pred[x]);
			cout << "->" << *matrix[x] << " "; 
		}
    }*/

public:
    MGraph(int dim)
    {
        max_nodi = dim;
        archi = nodi = 0;
        M = new int*[dim];
        matrix = new H*[dim];

        for (int i = 0; i < dim; i++)
        {
            matrix[i] = NULL;
            M[i] = new int[dim];
            for (int j = 0; j < dim; j++)
            {
                M[i][j] = 0;
            }
        }

        color = new int[dim];
        pred = new int[dim];
        dist = new int[dim];
        rad = new int[dim];

        in = new int[dim];
        out = new int[dim];
    }

    MGraph<H>* addNode(H val)
    {
        int x = findIndex(val);
        if ( (nodi < max_nodi) && (x == -1) )
        {
            matrix[nodi] = new H(val);
            nodi++;
        }
        return this;
    }

    MGraph<H>* addEdge(H u, H v)
    {
        int i = findIndex(u);
        int j = findIndex(v);
        if (i != -1 && j != -1 && M[i][j] == 0)
        {
            M[i][j] = 1;
            archi++;
        }
        return this;
    }

    void print()
    {
        for (int i = 0; i < nodi; i++)
        {
            cout << *matrix[i] << " : ";
            for (int j = 0; j < nodi; j++)
            {
                if (M[i][j])
                {
                    cout << *matrix[j] << "\t";
                }
            }
            cout << endl;
        }
    }

    void BFS(H val)
    {
        int i = findIndex(val);
        if (i != -1)
        {
            _bfs(i);
        }
    }

    /*void printPath(H val)
    {
        int i=findIndex(val);
		if (i>=0)
        {
            _printPath(i);
		}
		cout << endl;
    }*/
    
    int DFS()
    {
        for (int i = 0; i < nodi; i++)
        {
            color[i] = W;
            pred[i] = -1;
            rad[i] = 0;
        }
        time = 0;
        int cycle = 0;
        for (int i = 0; i < nodi; i++)
        {
            if (color[i] == W)
            {   
                current_root = i;
                cycle |= DFS_Visit(i);
            } 
        }
        for (int i = 0; i < nodi; i++)
        {
            cout << "[" << i << "] : " << out[i] << endl; 
        }
        return cycle;
    }

    void topSort()
    {
        int cycle = DFS();
        if (cycle)
        {
            cout << "Il grafo contiene un ciclo\n";
            return;
        }
        int* s = new int[nodi];
        for (int i = 0; i < nodi; i++)
        {
            s[i] = i;
            sort(s,nodi,out);
        }
        for (int i = 0; i < nodi; i++)
        {
            cout << "(" << in[i] << ", " << out[i] << ") ";
        }
        cout << endl;
    }
};

//Da aggiungere:
//scc


//Aggiunti:
//node
//edge
//stampa
//bfs
//printpath
//dfs
//top-sort


int main(int argc, char const *argv[])
{
    cout << "Scegli il tipo:\n1)int\n2)double\n3)char\n4)bool\n";
    int tipo; cin >> tipo;

    if (tipo == 1)//int
    {   
        MGraph<int>* gr = new MGraph<int>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                int dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    int dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    int dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else if (tipo == 2) //double
    {
        MGraph<double>* gr = new MGraph<double>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                double dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    double dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    double dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else if (tipo == 3) //char
    {
        MGraph<char>* gr = new MGraph<char>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                char dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    char dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    char dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        } 
    }
    else if (tipo == 4) //bool
    {
        MGraph<bool>* gr = new MGraph<bool>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                bool dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    bool dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    bool dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else
    {
        cout << "INPUT NON VALIDO!\n";
    }
    
    return 0;
}
