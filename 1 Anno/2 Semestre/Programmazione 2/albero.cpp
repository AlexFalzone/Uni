#include<iostream>
using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* padre;
    Nodo<H>* left;
    Nodo<H>* right;

public:
    Nodo(H val) :valore(val) {padre = left = right = NULL;}

    void setValore(H val) {valore = val;}
    void setPadre(Nodo<H>* val) {padre = val;}
    void setLeft(Nodo<H>* val) {left = val;}
    void setRight(Nodo<H>* val) {right = val;}

    H &getValore() {return valore;}
    Nodo<H>* &getPadre() {return padre;}
    Nodo<H>* &getLeft() {return left;}
    Nodo<H>* &getRight() {return right;}

};

template<class H>
class Tree
{
private:
    Nodo<H>* root;
    H peso;

    void trapianta(Nodo<H>* u, Nodo<H>* v)
    {
        if (u->getPadre() == NULL)
        {
            root = v;
        }
        else if (u->getPadre()->getLeft() == u)
        {
            u->getPadre()->getLeft() = v;
        }
        else
        {
            u->getPadre()->getRight() = v;
        }
        if (v != NULL)
        {
            v->setPadre(u->getPadre());
        }
    }

    void preOrder(Nodo<H>* x)
    {   
        if (x)
        {
            cout << x->getValore() << " ";
            preOrder(x->getLeft());
            preOrder(x->getRight());
            
        }
        
    }

    void inOrder(Nodo<H>* x)
    {   
        if (x)
        {
            inOrder(x->getLeft());
            cout << x->getValore() << " ";
            inOrder(x->getRight());
        }
    }

    //inorder per la natural fill
    void _inorder(Nodo<H>* p, H* vett, int& i)
    {
        if (p)
        {
            _inorder(p->getLeft(), vett, i);
            p->setValore(vett[i]);
            i++;
            _inorder(p->getRight(), vett, i);
        }
    }

    void postOrder(Nodo<H>* x)
    {   
        if (x)
        {
            postOrder(x->getLeft());
            postOrder(x->getRight());
            cout << x->getValore() << " ";
        }
    }

    int _foglie(Nodo<H>* p)
    {
        if (p == NULL)
        {
            return 0;
        }
        else
        {
            if ( (p->getLeft() == NULL) && (p->getRight() == NULL) )
            {
                return 1;
            }
            else
            {
                return ( _foglie( p->getLeft() ) + _foglie( p->getRight() ) );
            }
        }
    }

    int calcolaAltezza(Nodo<H>* x)  //l'altezza di un albero e la distanza dalla radice al nodo piu lontano
    {
		if(!x) return -1;//se il nodo e' nullo ritorniamo -1 perche' dobbiamo compensare la chiamata extra
		int s=calcolaAltezza(x->getLeft());//calcoliamo l'altezza del sottoalbero sinistro
		int d=calcolaAltezza(x->getRight());//calcoliamo l'altezza del sottoalbero destro
			
    	if(s>d) return 1+s;//ritorniamo il valore del sottoalbero piu' profondo +1 che sarebbe il nodo attuale
		else return 1+d;
	}

public:
    Tree() {root = NULL; peso = 0;}

    void ins(H val)
    {
        Nodo<H>* x = root;
        Nodo<H>* y = NULL;
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->getLeft() = nuovo->getRight() = NULL;
        while (x != NULL)
        {
            y = x;
            if (x->getValore() >= val)
            {
                x = x->getLeft();
            }
            else
            {
                x = x->getRight();
            }
        }
        nuovo->setPadre(y);
        if (y == NULL)
        {
            root = nuovo;
        }
        else if (y->getValore() >= val)
        {
            y->setLeft(nuovo);
        }
        else
        {
            y->setRight(nuovo);
        }
    }

    Nodo<H>* minimum(Nodo<H>* val)
    {
        Nodo<H>* min = val;
        while (min->getLeft() != NULL)
        {
            min = min->getLeft();
        }
        return min;
    }

    Nodo<H>* maximum(Nodo<H>* val)
    {
        Nodo<H>* max = val;
        while (max->getRight() != NULL)
        {
            max = max->getRight();
        }
        return max;
    }

    void canc(Nodo<H>* z)
    {
        Nodo<H>* y;
        if (z->getLeft() == NULL)
        {
            trapianta(z,z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            trapianta(z,z->getLeft());
        }
        else
        {
            y = minimum(z->getRight());
            if (y->getPadre() != z)
            {
                trapianta(y,y->getRight());
                y->getRight() = z->getRight();
                y->getRight()->getPadre() = y;
            }
            trapianta(z,y);
            y->getLeft() = z->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete z;
    }

    Nodo<H>* find(H val)
    {
        Nodo<H>* iter = root;
        while ( (iter != NULL) && (iter->getValore() != val) )
        {
            if (iter->getValore() > val)
            {
                iter = iter->getLeft();
            }
            else
            {
                iter = iter->getRight();
            }
        }
        return iter;
    }

    Nodo<H>* successor(H v)
    {
        Nodo<H>* iter = find(v);
        
        if (iter)
        {
            Nodo<H>* y;
            if (iter->getRight() != NULL)
            {
                y = minimum(iter->getRight());
            }
            else 
            {//altrimenti se il nodo non ha figli destri
                while ( (iter->getPadre() != NULL) && (iter->getPadre()->getRight() == iter) )
                {
                    iter = iter->getPadre();
                }
                y = iter->getPadre();
            }
            return y;
        }
    }

    Nodo<H>* predecessor(H v)
    {
        Nodo<H>* iter = find(v);
        
        if (iter)
        {
            Nodo<H>* y;
            if (iter->getLeft() != NULL)
            {
                y = maximum(iter->getLeft());
            }
            else 
            {//altrimenti se il nodo non ha figli destri
                while ( (iter->getPadre() != NULL) && (iter->getPadre()->getLeft() == iter) )
                {
                    iter = iter->getPadre();
                }
                y = iter->getPadre();
            }
            return y;
        }
    }

    H Peso(Nodo<H>* p)
    {
        peso+=p->getValore();
        if (p->getRight() != NULL)
        {
            Peso(p->getRight());
        }
        if (p->getLeft() != NULL)
        {
            Peso(p->getLeft());
        }
        return peso;
    }

    int foglie()
    {
        return _foglie(root);
    } 

    void natural_Fill(H* vett, int& i)
    {
        _inorder(root, vett, i);
    }

    int altezza()
    {
		return calcolaAltezza(root);
	}

    void visita_preOrder()
    {
        preOrder(root);
    }

    void visita_inOrder()
    {
        inOrder(root);
    }

    void visita_postOrder()
    {
        postOrder(root);
    }

};
   
   
//opzioni correnti:
//inserimento
//cancellazione
//foglie
//successore
//precedente
//Natural fill
//altezza

//Da aggiungere:
//peso



int main(int argc, char const *argv[])
{
    cout << "Scegli che tipo di albero vuoi creare: \n";
    cout << "1)int\n2)double\n3)char\n4)bool\n\n";
    int tipo; cin >> tipo;
    bool flag = true;
    bool vuota = true;
    
    if (tipo == 1) //int
    {
        Tree<int>* tr = new Tree<int>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                int dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    int dato_canc; cin >> dato_canc;
                    Nodo<int>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    int succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    int succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    int* vett = new int[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        int a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 2)//double
    {
        Tree<double>* tr = new Tree<double>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                double dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    double dato_canc; cin >> dato_canc;
                    Nodo<double>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    double succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    double succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    double* vett = new double[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        double a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 3)//char
    {
        Tree<char>* tr = new Tree<char>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                char dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    char dato_canc; cin >> dato_canc;
                    Nodo<char>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    char succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    char succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    char* vett = new char[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        char a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 4)//bool
    {
        Tree<bool>* tr = new Tree<bool>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                bool dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    bool dato_canc; cin >> dato_canc;
                    Nodo<bool>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    bool succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    bool succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    bool* vett = new bool[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        bool a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else
    {
        cout << "\nINPUT NON VALIDO!\n";
    }

    return 0;
}
