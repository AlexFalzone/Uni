#include<iostream>
using namespace std;

template<class H>
class Nodo
{
private:
    H* key;
    Nodo<H>* succ;

public:
    Nodo(H k)
    {
        key = new H(k);
        succ = NULL;
    }
    void set_key(H* in) {key = in;}
    H* get_key() {return key;}
    void set_succ(Nodo<H>* next) {succ = next;}
    Nodo<H>* get_succ() {return succ;}
};

template<class H>
class LList
{
private:
    Nodo<H>* head;

public:
    LList() :head(NULL) {}  //costruttore
    LList<H>* ins(H x);
    LList<H>* canc(H x);
    H* search(H x);
    void print();

    Nodo<H>* get_head() {return head;}
    void set_head(Nodo<H>* in) {head = in;}
};

template<class H> 
LList<H>* LList<H>::ins(H x)
{
    Nodo<H>* aux = new Nodo<H>(x);

    if (head == NULL)
    {
        head = aux;
    }
    else if (*head->get_key() > x)
    {
        aux->set_succ(head);
        head = aux;
    }
    else
    {
        Nodo<H>* iter = get_head();
        Nodo<H>* preiter = iter;

        while ( (iter != NULL) && (x > *iter->get_key()) )
        {
            preiter = iter;
            iter = iter->get_succ();   
        }
        if (iter != NULL)
        {
            aux->set_succ(iter);
            preiter->set_succ(aux);
        }
        else 
        {
            preiter->set_succ(aux);
        }
    }
    return this;
}

template<class H>
void LList<H>::print()
{
    Nodo<H>* iter = get_head();

    while (iter != NULL)
    {
        cout << *iter->get_key() << "\t";
        iter = iter->get_succ();
    }
    cout << endl;
}

template<class H>
LList<H>* LList<H>::canc(H x)
{
    Nodo<H>* iter = get_head();

    if (head)
    {
        if (*head->get_key() == x)
        {
            set_head(head->get_succ());
            delete iter;
        }
        else
        {
            Nodo<H>* aux = get_head();
            while ( (iter != NULL) && (*iter->get_key() != x) )
            {
                aux = iter;
                iter = iter->get_succ();
            }
            if (iter)
            {
                aux->set_succ(iter->get_succ());
                delete iter;
            }
        }
    }
    return this;
}

template<class H>
H* LList<H>::search(H x)
{
    Nodo<H>* iter = get_head();

    while ( (iter != NULL) && (*iter->get_key() != x) )
    {
        iter = iter->get_succ();
    }
    if (iter)
    {
        return iter->get_key();   
    }
    else
    {
        return NULL;
    }                                 
}                                      
//fine primo esercizio
//fine lista e nodo


template<class H>
class NodoTree
{
private:
    H* key;
    NodoTree<H>* left;
    NodoTree<H>* right;
    NodoTree<H>* padre;

public:
    NodoTree(H k) 
    {
        key = new H(k);
        left = right = padre = NULL;
    }
    void set_key(H* in) {key=in;}
    H* get_key() {return key;}
    NodoTree<H>* get_left() {return left;}
    NodoTree<H>* get_right() {return right;}
    NodoTree<H>* get_padre() {return padre;}
    void set_left(NodoTree<H>* left) {this->left = left;}
    void set_right(NodoTree<H>* right) {this->right = right;}
    void set_padre(NodoTree<H>* padre) {this->padre = padre;}
};

template<class H>
class BST
{
private:
    NodoTree<H>* root;
    int altezza;
    void inorder(NodoTree<H>*);

    NodoTree<H>* _min(NodoTree<H>* p) 
    {
        NodoTree<H>* x = p;
        while (x->get_left() != NULL)
        {
            x = x->get_left();
        }
        return x;
    }

    NodoTree<H>* _search(H x)
    {
        NodoTree<H>* iter = root;
        while ( (iter != NULL) && (*iter->get_key() != x) )
        {
            if (*iter->get_key() > x)
            {
                iter = iter->get_left();
            }
            else
            {
                iter = iter->get_right();
            }
        }
        return iter;
    }

    void trapianta(NodoTree<H>* u, NodoTree<H>* v)
    {
        if (u->get_padre() == NULL)
        {
            root = v;
        }
        else if (u == u->get_padre()->get_left())
        {
            u->get_padre()->set_left(v);
        }
        else
        {
            u->get_padre()->set_right(v);            
        }
        if (v != NULL)
        {
            v->set_padre(u->get_padre());
        }
    }

public:
    BST() : root(NULL), altezza(-1) {};
    BST<H>* ins(H x);
    BST<H>* canc(H x);
    H* search(H x);
    void print();
    H* minimum();
    H* successor(H x);

    int get_altezza() {return altezza;}
    void set_altezza(int x) {altezza = x;}
    NodoTree<H>* get_root() {return root;}
    int calcola_altezza(NodoTree<H>* nodo);
};                                          //fine classe BST

int operator>=(BST<int>& a, BST<int>& b)
{
    if (a.get_altezza() > b.get_altezza())
    {
        return 1;
    }
    else if ( (a.get_altezza() == b.get_altezza()) && (*a.minimum() >= *b.minimum()) )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int operator==(BST<int>& a, BST<int>& b)
{
    if ((a.get_altezza() == b.get_altezza()) && (*a.minimum() == *b.minimum()))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int operator!=(BST<int>& a, BST<int>& b)
{
    if ((a.get_altezza() == b.get_altezza()) && (*a.minimum() == *b.minimum()))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int operator>(BST<int>& a, BST<int>& b)
{
    if (a.get_altezza() > b.get_altezza())
    {
        return 1;
    }
    else if ((a.get_altezza() == b.get_altezza()) && (*a.minimum() > *b.minimum()))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


template<class H>
int BST<H>::calcola_altezza(NodoTree<H>* nodo)
{
    if (nodo == NULL)
    {
        return -1;
    }
    int sin = calcola_altezza(nodo->get_left());
    int des = calcola_altezza(nodo->get_right());
    int max;
    if (sin > des)
    {
        max = sin;
    }
    else
    {
        max = des;
    }
    return 1+max;
}

template<class H>
BST<H>* BST<H>::ins(H val)
{
    NodoTree<H>* nuovo = new NodoTree<H>(val);
    NodoTree<H>* x = root;
    NodoTree<H>* y = NULL;

    while (x != NULL)
    {
        y = x;
        if (*x->get_key() <= val)
        {
            x = x->get_right();
        }
        else
        {
            x = x->get_left();
        }
    }
    nuovo->set_padre(y);
    if (y == NULL)
    {
        root = nuovo;
    }
    else if (val < *y->get_key())
    {
        y->set_left(nuovo);
    }
    else
    {
        y->set_right(nuovo);
    }
    set_altezza(calcola_altezza(root));
    return this;
}

template<class H>
void BST<H>::inorder(NodoTree<H>* p)
{
    if (p)
    {
        inorder(p->get_left());
        cout << *p->get_key() << "\t";
        inorder(p->get_right());
    }
}

template<class H>
void BST<H>::print()
{
    inorder(root);
    cout << endl;
}

template<class H>
BST<H>* BST<H>::canc(H val)
{
    NodoTree<H> *y, *z;
    z = _search(val);
    if (z != NULL)
    {
        if (z->get_left() == NULL)
        {
            trapianta(z, z->get_right());
        }
        else if (z->get_right() == NULL)
        {
            trapianta(z, z->get_left());
        }
        else
        {
            y = _min(z->get_right());
            if (y->get_padre() != z)
            {
                trapianta(y, y->get_right());
                y->set_right(z->get_right());
                y->get_right()->set_padre(y);
            }
            trapianta(z,y);
            y->set_left(z->get_left());
            y->get_left()->set_padre(y);
        }
        delete z;
        set_altezza(calcola_altezza(root));
    }
    return this;
}

template<class H>
H* BST<H>::search(H x)
{
    NodoTree<H>* iter = root;

    while ((iter != NULL) && (*iter->get_key() != x))
    {
        if (*iter->get_key() > x)
        {
            iter = iter->get_left();
        }
        else
        {
            iter = iter->get_right();
        }
    }
    if (iter != NULL)
    {
        return iter->get_key();
    }
    else
    {
        return NULL;
    }
}

template<class H>
H* BST<H>::minimum()
{
    NodoTree<H>* x = root;

    if (x)
    {
        while (x->get_left() != NULL)
        {
            x = x->get_left();
        }
        return x->get_key();
    }
    else
    {
        return NULL;
    }
}

template<class H>
H* BST<H>::successor(H x)
{
    NodoTree<H>* z = _search(x);

    if (z)
    {
        if (z->get_right() != NULL) 
        {
            return (  _min( z->get_right() )  )->get_key();
        }
        else
        {
            NodoTree<H>* y = z->get_padre();
            while (  (y != NULL) && (z == y->get_right())  )
            {
                z = y;
                y = y->get_padre();
            }
            if (y != NULL)
            {
                return y->get_key();
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
        return NULL;
    }                              
}                                  

//fine secondo esercizio
//fine albero e nodotree



//foresta crescente
template<class H>
class IF
{
private:
    int max_alt;
    LList<BST<H> >* testa;
    void _rearrange(BST<H>*);

public:
    IF(int k) :max_alt(k), testa(NULL) {};
    IF<H>* ins(H x);
    IF<H>* canc(H x);
    void print();

    int get_max_alt() {return max_alt;}
};

template<class H>
void IF<H>::_rearrange(BST<H>* iter)
{
    BST<H>* new_tree = new BST<H>();

    new_tree = iter;
    testa->canc(*iter);
    testa->ins(*new_tree);
}

template<class H>
IF<H>* IF<H>::ins(H x)
{
    BST<H>* new_tree = new BST<H>();
    
    if (testa == NULL)
    {
        new_tree->ins(x);
        LList<BST<H> >* nuova_lista = new LList<BST<H> >();
        testa = nuova_lista;
        testa->ins(*new_tree);
    }
    else
    {
        Nodo<BST<H> >* iter = testa->get_head();
        if ((*iter->get_key()).get_altezza() == max_alt)
        {
            new_tree->ins(x);
            testa->ins(*new_tree);
        }
        else
        {
            (*iter->get_key()).ins(x);
            _rearrange(iter->get_key());
        }
    }
    return this;
}

template<class H>
void IF<H>::print()
{
    if (testa != NULL)
    {
        Nodo<BST<H> >* iter = testa->get_head();
        while (iter != NULL)
        {
            (*iter->get_key()).print();
            iter = iter->get_succ();
        }
        cout << endl;
    }
}

template<class H>
IF<H>* IF<H>::canc(H x)
{
    if (testa != NULL)
    {
        Nodo<BST<H> >* iter = testa->get_head();
        while (iter != NULL)
        {
            (*iter->get_key()).canc(x);
            _rearrange(iter->get_key());
            iter = iter->get_succ();
        }
    }
    return this;
}


int main(int argc, char const *argv[])
{   
    //Lista
    cout << "Lista concatenata:\n";
    LList<int>* l = new LList<int>();
    l->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
    l->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
    if (l->search(5)) cout << "elemento 5 presente\n";
    else cout << "elemento 5 non presente\n";
    if (l->search(3)) cout << "elemento 3 presente\n";
    else cout << "elemento 3 non presente\n";


    //Albero
    cout << "\nAlbero Binario\n";
    BST<int>* t = new BST<int>();
    t->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
    cout << "altezza albero= " << t->get_altezza() << endl;
    t->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
    if (t->search(5)) cout << "elemento 5 presente\n";
    else cout << "elemento 5 non presente\n";
    if (t->search(3)) cout << "elemento 3 presente\n";
    else cout << "elemento 3 non presente\n";
    int* r = t->minimum();
    if(r) cout << "il valore più piccolo è " << *r << endl;
    if((r = t->successor(5))) cout << "il successore di 5 è " << *r << endl;
    if((r = t->successor(3))) cout << "il successore di 3 è " << *r << endl;


    //IF
    IF<int>* b = new IF<int>(3);
    b->ins(3)->ins(14)->ins(2)->ins(5)->ins(8)->ins(9)->print();
    b->ins(4)->ins(7)->ins(11)->ins(5)->ins(6)->ins(12)->print();
    b->canc(11)->canc(3)->canc(2)->canc(9)->canc(9)->print();


    return 0;
}