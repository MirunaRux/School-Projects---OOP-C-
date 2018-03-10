#include <iostream>
#include <fstream>
#define NMAX 20
#define AMAX 5
using namespace std;

fstream f("date.in", ios :: in);
fstream g("date.out", ios :: out);

class Graf{
protected :
    int nr_noduri;
    int mat_adiacenta[NMAX][NMAX];

public :
    ///constructori
    Graf(); ///neparametrizat

    Graf(int nr_noduri, int mat_adiacenta[][NMAX]); ///parametrizat

    Graf (Graf &aux); ///de copiere

    ///destructor
    virtual ~Graf();

    ///supraincarcare de operatori
    friend istream & operator >> (istream &c, Graf &G);

    friend ostream & operator << (ostream &a, Graf &G);

    Graf& operator = (const Graf &G);

    ///functie virtuala care parcurge graful in latime
    virtual void BFS(int x);
};

Graf :: Graf() ///constructorul neparametrizat
    {///se initializeaza cu 0 matricea de adiacenta
        nr_noduri = 0;

        for(int i = 1;i <= nr_noduri; i++)
            for(int j = 1;j <= nr_noduri; j++)
                mat_adiacenta[i][j] = 0;
    };

Graf :: Graf(int nr_noduri, int mat_adiacenta[][NMAX]) ///constructor parametrizat
    {///se initializeaza matricea de adiacentacu valori date
        this -> nr_noduri = nr_noduri;

        for(int i = 1;i <= nr_noduri; i++)
            for(int j = 1;j <= nr_noduri; j++)
                this -> mat_adiacenta[i][j] = mat_adiacenta[i][j];
    };

Graf :: Graf(Graf &aux) ///constructor de copiere
    {///se copiaza in this obiectul aux
        this -> nr_noduri = aux.nr_noduri;

        for(int i = 1;i <= this -> nr_noduri; i++)
        return *this;    for(int j = 1;j <= this -> nr_noduri; j++)
                this -> mat_adiacenta[i][j] = aux.mat_adiacenta[i][j];
    };

Graf :: ~Graf() ///destructor
    {///numarul de noduri devine 0, matricea este initializata cu valori de 0
        nr_noduri = 0;

        for(int i = 1;i <= nr_noduri; i++)
            for(int j = 1;j <= nr_noduri; j++)
                mat_adiacenta[i][j] = 0;
    };

istream & operator >>(istream &c, Graf &G) ///supraincarcarea operatorului de citire de la tastatura
    {
        c>>G.nr_noduri;

        for(int i = 1;i <= G.nr_noduri; i++)
            for(int j = 1;j <= G.nr_noduri; j++)
                c>>G.mat_adiacenta[i][j];

        return c;
    };

ostream & operator <<(ostream &a, Graf &G) ///supraincarcarea operatorului de afisare la consola
    {
        a<<G.nr_noduri;

        for(int i = 1;i <= G.nr_noduri; i++)
            for(int j = 1;j <= G.nr_noduri; j++)
                a<<G.mat_adiacenta[i][j];

        return a;
    };

Graf& Graf :: operator = (const Graf &G) ///supraincarcarea operatorului de atribuire
    {
       this -> nr_noduri = G.nr_noduri;

       for(int i = 1;i <= this -> nr_noduri; i++)
           for(int j = 1;j <= this ->nr_noduri; j++)
               this -> mat_adiacenta[i][j] = G.mat_adiacenta[i][j];

       return *this;
    };

void Graf :: BFS(int x) ///parcurgerea in latime a unui graf
    {
       int coada[NMAX];
       bool viz[NMAX]; /// tablou de elemente de tip bool care retine daca un nod a fost sau nu vizitat
       int prim, ultim, lin;

       for(int i = 1;i <= nr_noduri; i++)
           viz[i] = false; /// initial toate nodurile sunt nevizitate

       coada[1] = x; /// se adauga in coada nodul x cu care se incepe parcurgerea
       viz[x] = true; /// si se marcheaza ca fiind vizitata
       ultim = 1;
       prim = 1;

       while(prim <= ultim)
       {
           lin = coada[prim]; /// se retine parintele in coada
           for(int j = 1;j <= nr_noduri; j++) /// si apoi se adauga in coada fii lui lin
           if((mat_adiacenta[lin][j] == 1) && (viz[j] == false))
             {
                coada[++ultim] = j;
                viz[j] = true; /// si se marcheaza ca fiind vizitati
             }
            ++prim;
       }
    };

class Arbore : public Graf{
    int rad;
    int tata[NMAX];

public :
    ///constructori
    Arbore(); ///neparametrizat

    Arbore(int rad, int tata[], int nr_noduri, int mat_adiacenta[][NMAX]); ///parametrizat

    Arbore(Arbore &aux); ///de copiere

    ///destructor
    ~Arbore();

    ///supraincarcare de operatori
    friend istream & operator >>(istream &c, Arbore &A);

    friend ostream & operator <<(ostream &a, Arbore &A);

    Arbore& operator = (const Arbore &A);

    ///functie virtuala de afisare a vectorului de tati
    virtual void afisare_tata();
};

Arbore :: Arbore() : Graf() ///constructor neparametrizat
    {///se initializeaza rad cu 0 si vectorul de tati cu -1
        rad = 0;
        for(int i = 1;i <= nr_noduri; i++)
            tata[i] = -1;
    };

Arbore :: Arbore(int rad, int tata[], int nr_noduri, int mat_adiacenta[][NMAX]) : Graf(nr_noduri, mat_adiacenta)///constructor parametrizat
    {///se initializeaza rad cu o valoare data si vectorul tata
        this -> rad = rad;

        for(int i = 1;i <= this -> nr_noduri; i++)
            this -> tata[i] = tata[i];
    };

Arbore :: Arbore(Arbore &aux) : Graf (aux) ///constructor de copiere
    {///se copiaza in this obiectul aux
        this -> rad = aux.rad;

        for(int i = 1;i <= this -> nr_noduri; i++)
            this -> tata[i] = aux.tata[i];
    };

Arbore :: ~Arbore() ///destructorrad devine 0 si vectorul tata se reinitializeaza cu -1
    {///rad devine 0 si vectorul tata se reinitializeaza cu -1
        rad = 0;
        for(int i = 1;i <= nr_noduri; i++)
            tata[i] = -1;
    };

istream & operator >>(istream &c, Arbore &A) ///supraincarcarea operatorului de citire de la tastatura
    {
        c>>A.nr_noduri;

        c>>A.rad;

        for(int i = 1;i <= A.nr_noduri; i++)
            c>>A.tata[i];

        return c;
    };

ostream & operator <<(ostream &a, Arbore &A) ///supraincarcarea operatorului de afisare la consola
    {
        a<<A.nr_noduri;

        a<<A.rad;

        for(int i = 1;i <= A.nr_noduri; i++)
            a<<A.tata[i];

        return a;
    };

Arbore& Arbore :: operator = (const Arbore &A) ///supraincarcarea operatorului de atribuire
    {
        this -> rad = A.rad;

        this -> nr_noduri = A.nr_noduri;

        for(int i = 1;i <= this -> nr_noduri; i++)
            this -> tata[i] = A.tata[i];

        return *this;
    };

void Arbore :: afisare_tata()
    {
        for(int i = 1;i <= nr_noduri; i++)
            g<<tata[i]<<" ";

        g<<'\n';
    };

void citire(Arbore *arb[AMAX],int &n) ///functie care citeste n arbori din fisierul de intrare
{
    int nr, r;
    int mat[NMAX][NMAX], t[NMAX];

    f>>n; ///n = numarul de arbori de citit

    for(int i = 1;i <= n; i++)
    {
        f>>nr; ///nr = numarul de noduri al arborelui i

        for(int j = 1;j <= nr; j++) ///matricea de adiacenta
            for(int k = 1;k <= nr; k++)
                f>>mat[j][k];

        f>>r; ///radacina arborelui i

        for(int i = 1;i <= nr; i++) ///vectorul de tati
            f>>t[i];

        arb[i] = new Arbore(r, t, nr, mat); ///se creaza arborele cu datele citite din fisier
    }
}

void afisare(Arbore *arb[AMAX], int n) ///functie care afiseaza n arbori
{
    for(int i = 1;i <= n; i++)
    {
        g<<"Arborele : "<<i<<'\n';

        arb[i]->afisare_tata(); ///se afiseaza vectorul de tati pentru arborele i

        g<<'\n';
    }
}

int main()
{
    Arbore *arb[AMAX];

    int n;

    citire(arb, n);

    afisare(arb, n);

    f.close();

    g.close();

    return 0;
}
