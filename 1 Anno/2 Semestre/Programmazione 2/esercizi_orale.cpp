#include<iostream>
#include<cmath>
using namespace std;

void sqrt(int z)
{   
    double xn = 0;
    for (int i = 0; i < 10; i++)
    {
        if (xn == 0)
        {
            xn = 1;
        }
        else
        {
            xn = ( (xn/2) + (z/(2*xn)) );
        }
    }
    cout << xn << endl;
}

void power(int base, int esponente)
{
    int tmp = base;
    for(int i=0; i < esponente; i++)
    {
        base = base+tmp;
    }
    return base;
}
 
 
 
int main(int argc, char const *argv[])
{   
    double x = 25;
    //cout << "inserisci x "; cin >> x;
    //cout << "log di " << x << " = " << log(x);
    return 0;
}
