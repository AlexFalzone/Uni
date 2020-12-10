#include<iostream>
using namespace std;

template<class H>
class MultiBST
{
public:
    virtual MultiBST<H>* ins(H x) = 0;
    virtual int Multiplicity(H x) = 0;
    virtual void inorder() = 0;
};

template<class H>
class Nodo
{
private:
    Nodo<H>* padre, *left, *right;
    int chiave;
    int molt;

public:
    Nodo(int val) {chiave = val; padre = left = right = NULL; molt = 1;}

    int getChiave() {return chiave;}
    void setChiave(int p) {chiave = p;}

    int getMultiplicity() {return molt;}
    void setMultiplicity(int p) {molt = p;}

    Nodo<H>* getPadre() {return padre;}
    void setPadre(Nodo<H>* p) {padre = p;}

    Nodo<H>* getDestro() {return right;}
    void setDestro(Nodo<H>* p) {right = p;}

    Nodo<H>* getSinistro() {return left;}
    void setSinistro(Nodo<H>* p) {left = p;}

};



template<class H>
class MyMultiBST :public MultiBST<H>
{
private:
    Nodo<H>* radice;
    void visita_inorder(Nodo<H>* p);
    void Trapianta(Nodo<H>*, Nodo<H>*);
    Nodo<H>* Minimo(Nodo<H>* x);

public:
    MyMultiBST() {radice = NULL;}

    Nodo<H>* getRoot() {return radice;}
    void setRoot(Nodo<H>* p) {radice = p;}

    MultiBST<H>* ins(H x);
    int multiplicity(H x);
    Nodo<H>* search(H x);
    void inorder();

    MultiBST<H>* del(H x);

    int rank(H x);
    Nodo<H>* successore(Nodo<H>* x);
};

template<class H>
Nodo<H>* MyMultiBST<H>::search(H p)
{
    Nodo<H>* temp = radice;

    while ((temp != NULL) && (temp->getChiave() != p))
    {
        if (temp->getChiave() > p)
        {
            temp = temp->getSinistro();
        }
        else
        {
            temp = temp->getDestro();
        }    
    }
    return temp;
}

template<class H>
MultiBST<H>* MyMultiBST<H>::ins(H key)
{
    Nodo<H>* x = radice;
    Nodo<H>* y = NULL;

    Nodo<H>* temp = search(key);

    if (temp)
    {
        temp->setMultiplicity( (temp->getMultiplicity() + 1) );
        return this;
    }
    else
    {
        while (x != NULL)
        {
            y = x;
            if (key < x->getChiave())
            {
                x = x->getSinistro();
            }
            else
            {
                x = x->getDestro();
            }
        }

        Nodo<H>* nuovo = new Nodo<H>(key);
        nuovo->setPadre(y);
        if (y == NULL)
        {
            radice = nuovo;
        }
        else if (key < y->getChiave())
        {
            y->setSinistro(nuovo);
        }
        else
        {
            y->setDestro(nuovo);
        }
        return this;
    }
}

template<class H>
void MyMultiBST<H>::visita_inorder(Nodo<H>* p)
{
    if (p)
    {
        visita_inorder(p->getSinistro());
        for (int i = 0; i < p->getMultiplicity(); i++)
        {
            cout << p->getChiave() << "\t";
        }
        visita_inorder(p->getDestro());
    }
}

template<class H>
void MyMultiBST<H>::inorder()
{
    cout << endl;
    visita_inorder(radice);
    cout << endl;
}

template<class H>
int MyMultiBST<H>::multiplicity(H x)
{
    Nodo<H>* temp = search(x);

    if (temp)
    {
        return temp->getMultiplicity();
    }
    else
    {
        return 0;
    }
}

//fine Esercizio 1
//Esercizio 2

template<class H>
void MyMultiBST<H>::Trapianta(Nodo<H>* u, Nodo<H>* v)
{
    if (u->getPadre() == NULL)
    {
        radice = v;
    }
    else if (u == u->getPadre()->getSinistro())
    {
        u->getPadre()->setSinistro(v);
    }
    else
    {
        u->getPadre()->setDestro(v);
    }

    if (v)
    {
        v->setPadre(u->getPadre());
    }
}

template<class H>
Nodo<H>* MyMultiBST<H>::Minimo(Nodo<H>* x)
{
    Nodo<H>* min = x;

    while (min->getSinistro() != NULL)
    {
        min = min->getSinistro();
    }
    return min;
}

template<class H>
MultiBST<H>* MyMultiBST<H>::del(H p)
{
    Nodo<H>* y;
    Nodo<H>* z = search(p);

    if (z)
    {
        if (z->getMultiplicity() > 1)
        {
            z->setMultiplicity( (z->getMultiplicity() - 1) );
        }
        else
        {
            if (z->getSinistro() == NULL)
            {
                Trapianta(z, z->getDestro());
            }
            else if (z->getDestro() == NULL)
            {
                Trapianta(z, z->getSinistro());
            }
            else //caso più generale
            {
                y = Minimo(z->getDestro());
                if (y->getPadre() != z)
                {
                    Trapianta(y, y->getDestro());
                    y->setDestro(z->getDestro());
                    y->getDestro()->setPadre(y);
                }
                Trapianta(z, y);
                y->setSinistro(z->getSinistro());
                y->getDestro()->setPadre(y);
            }
            delete z;   
        } 
    }
    else
    {
        cout << "Elemento non presente nell'albero!\n";
    }
    return this;
}

//fine Esercizio 2
//Esercizio 3

template<class H>
int MyMultiBST<H>::rank(H p)
{
    Nodo<H>* x = search(p);

    if (!x)
    {
        return 0;
    }
    else
    {
        int rango = 1;
        x = Minimo(radice);

        while (x->getChiave() < p)
        {
            rango = rango + (x->getMultiplicity());
            x = successore(x);
        }
    }
}


template<class H>
Nodo<H>* MyMultiBST<H>::successore(Nodo<H>* x)
{
    if (x == NULL)
    {
        return NULL;
    }
    if (x->getDestro())
    {
        return Minimo(x)->getDestro();
    }

    Nodo<H>* y = x->getPadre();
    while ( (y != NULL) && (y->getChiave() < x->getChiave()) )
    {
        y = y->getPadre();
    }
    return y;
}




int main(int argc, char const *argv[])
{
    MyMultiBST<int> Tree;
    int input[] = {10,7,7,23,30,4,1,5,9,5,1,7,1,9};

    cout << "Vettore inserito: \n";
    for (int i = 0; i < 14; i++)
    {
        cout << input[i] << "\t";
    }
    cout << endl;


    for (int i = 0; i < 14; i++)
    {
        Tree.ins(input[i]);
    }
    Tree.inorder();

    cout << "Molteplicità di 5: " << Tree.multiplicity(5);
    cout << "\nMolteplicità di 7: " << Tree.multiplicity(7);
    cout << "\nMolteplicità di 17: " << Tree.multiplicity(17);

    cout << endl;

    //Tree.del(7); Tree.del(4); Tree.del(23); Tree.del(7); Tree.del(7);
    //Tree.inorder();

    cout << endl;

    cout << "Rango di 5: " << Tree.rank(5) << endl;
    cout << "Rango di 9: " << Tree.rank(9) << endl;
    cout << "\n Rango di 30: " << Tree.rank(30) << endl;

    return 0;
}
