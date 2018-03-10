#include <iostream>
#include <string.h>
#define NMAX 100
#define STRING_SIZE 20
using namespace std;

class Ingredient
{
    char *denumire;
    char culoare[10];
    double pretUnitar;
    int cantitate;

public :
    friend class Pizza;
    Ingredient()
    {
        denumire = new char [STRING_SIZE];
        strcpy(culoare, "");
        pretUnitar = 0;
        cantitate = 0;
    };

    Ingredient(char *denumire, char culoare, double pretUnitar, int cantitate) {};
    ~Ingredient()
    {
        strcpy(culoare, "");
        pretUnitar = 0;
        cantitate = 0;
    };

    Ingredient& operator +=(int val)
    {
        cantitate = cantitate + val;
    };
    Ingredient& operator =(Ingredient& I1)
    {
        strcpy(this -> denumire, I1.denumire);
        strcpy(this -> culoare, I1.culoare);
        this -> pretUnitar = I1.pretUnitar;
        this -> cantitate = I1.cantitate;
        return *this;
    };

    friend istream & operator >>(istream &c, Ingredient &I)
    {
        char nume[10];
        c>>nume;
        strcpy(I.denumire, nume);
        c>>I.culoare;
        c>>I.pretUnitar;
        c>>I.cantitate;
        return c;
    };
    friend ostream & operator <<(ostream &a, const Ingredient &I)
    {
        a<<I.denumire;
        a<<I.culoare;
        a<<I.pretUnitar;
        a<<I.cantitate;
        return a;
    };
};

class Pizza
{
    char *denumire;
    Ingredient lista[NMAX];
    int nrIngrediente;
    bool vegetariana;

public :
    Pizza() {};
    Pizza(char * denumire, int nrIngrediente, bool vegetariana)
    {
        denumire = new char [STRING_SIZE];
        nrIngrediente = 0;
        vegetariana = false;
    };

    ~Pizza()
    {
        nrIngrediente = 0;
        vegetariana = false;
    };

    friend istream & operator >>(istream &c,Pizza &P)
    {
        char nume[10];
        c>>nume;
        strcpy(P.denumire, nume);
        c>>P.nrIngrediente;
        for(int i = 1;i <= P.nrIngrediente; i++)
            c>>P.lista[i];
        c>>P.vegetariana;
        return c;
    };
    friend ostream & operator <<(ostream &a, const Pizza &P)
    {
        a<<P.denumire;
        for(int i = 1;i <= P.nrIngrediente; i++)
            a<<P.lista[i];
        if(P.vegetariana  == true)
           a<<"vegetariana"<<'\n';
        else
           a<<" nu este vegetariana"<<'\n';
        return a;
    };

    Pizza operator +(Ingredient &I)
    {
        lista[++nrIngrediente] = I;
    };

    friend bool operator >(Pizza &P1, Pizza &P2)
    {
        if(P1.nrIngrediente > P2.nrIngrediente)
           return true;
        return false;
    };
};

int main()
{
    Ingredient i1("Piper","negru",0.5, 10), i2("Nimic","", 0.0, 0);
    cout<<i1;
    cin>>i2;
    i1 += 500; /// aduna o valoare la cantitatea disponibila
    Ingredient i3 = i1, i4, i5(i1);
    i4 = i1;

    Pizza pizza1("Clasic", 0, false), pizza2;
    pizza1 = i1 + pizza1 /// adaugare ingredient 1
    cin>>pizza;
    cout<<pizza2;
    if (pizza1 > pizza2) cout<<"pizza1 are mai multe ingrediente decat pizza2";
    else cout<<"pizza2 are mai multe ingrediente decat pizza1";


    return 0;
}
