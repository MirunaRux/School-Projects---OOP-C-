#include <iostream>
#include <fstream>
#include <string.h>
#include "Constants.h"
using namespace std;

fstream f("date.in", ios :: in);

fstream g("date.out", ios :: out);

const int NMAX = 10;

class Angajat
{
protected :
    char *nume;

    long int cnp;

    char* nume_film;

    float salariu;

    int procent;

public :
    Angajat();

    Angajat(char *nume, long int cnp, char* nume_film, float salariu);

    Angajat(Angajat &aux);

    virtual ~Angajat();

    friend ifstream & operator >> (ifstream &c, Angajat &A);

    Angajat& operator = (const Angajat &A);

    void Afisare();

    void setSalariu(int salariu);

    void setNumeFilm(char* nume_film);
};

Angajat :: Angajat()
{
     nume = NULL;

     cnp = 0;

     salariu = 0;

     nume_film = NULL;

     procent = 0;
};

Angajat :: Angajat(char *nume, long int cnp, char* nume_film, float salariu, int procent)
{
    this -> nume = new char[strlen(nume)];

    strcpy(this -> nume, nume);

    this -> cnp = cnp;

    this -> salariu = salariu;

    this -> nume_film = new char[strlen(nume_film)];

    strcpy(this -> nume_film, nume_film);

    this -> procent = procent;
};

Angajat :: Angajat(Angajat &aux)
{
    this -> nume = new char[strlen(aux.nume)];

    strcpy(this -> nume, aux.nume);

    this -> cnp = aux.cnp;

    this -> salariu = aux.salariu;

    this -> nume_film = new char[strlen(aux.nume_film)];

    strcpy(this -> nume_film, aux.nume_film);

    this -> procent = aux.procent;
};

Angajat :: ~Angajat()
{
    nume = NULL;

    cnp = 0;

    salariu = 0;

    nume_film = NULL;

    procent = 0;
};

ifstream & operator >> (ifstream &c, Angajat &A)
{
    A.nume = new char[20];

    c>>A.nume;

    c>>A.cnp;

    c>>A.procent;

    return c;
};

Angajat& Angajat :: operator = (const Angajat &A)
{
    this -> nume = new char[strlen(A.nume)];

    strcpy(this -> nume, A.nume);

    this -> cnp = A.cnp;

    this -> salariu = A.salariu;

    this -> nume_film = new char[strlen(A.nume_film)];

    strcpy(this -> nume_film, A.nume_film);

    this -> procent = A.procent;

    return *this;
};

void Angajat :: Afisare()
{
    cout<<nume<<'\t';

    cout<<cnp<<'\t';

    cout<<nume_film<<'\t';

    cout<<salariu<<'\t';

    cout<<procent<<'\n';
};

void Angajat :: setSalariu(int salariu)
{
    this -> salariu += salariu;
};

void Angajat :: setNumeFilm(char* nume_film)
{
    this -> nume_film = new char[strlen(nume_film)];

    strcpy(this -> nume_film, nume_film);
}

class Regizor : public Angajat
{
public :
    Regizor() : Angajat(){};

    Regizor(char *nume, long int cnp, int nr_filme, float salariu) : Angajat(nume, cnp, nr_filme, salariu){};

    Regizor(Regizor &aux) : Angajat(aux){};

    virtual ~Regizor(){ nume = NULL; cnp = 0; };

    friend ifstream & operator >> (ifstream &c, Regizor &R);

    Regizor& operator = (const Regizor &R);

    void Afisare();

    int Castig();
};

ifstream & operator >> (ifstream &c, Regizor &R)
{
    R.nume = new char[20];

    c>>R.nume;

    c>>R.cnp;

    c>>R.nr_filme;

    return c;
};

Regizor& Regizor :: operator = (const Regizor &R)
{
    this -> nume = new char[strlen(R.nume)];

    strcpy(this -> nume, R.nume);

    this -> cnp = R.cnp;

    this -> salariu = R.salariu;

    this -> nr_filme = R.nr_filme;

    return *this;
};

void Regizor :: Afisare()
{
    cout<<nume<<'\n';

    cout<<cnp<<'\n';

    cout<<nr_filme<<'\n';

    cout<<salariu<<'\n';
};

int Regizor :: Castig()
{
    salariu = 1000;

    return salariu;
};

class Actor : public Angajat
{
protected :
    char *rol;

public :
    Actor() : Angajat(){};

    Actor(char *nume, long int cnp, char *rol, int nr_filme, float salariu) : Angajat(nume, cnp, nr_filme, salariu)
    {
        this -> rol = new char[20];

        strcpy(this -> rol, rol);
    };

    Actor(Actor &aux) : Angajat(aux)
    {
        this -> rol = new char[strlen(aux.rol) + 1];

        strcpy(this -> rol, aux.rol);
    };

    virtual ~Actor(){ nume = NULL; cnp = 0; nr_filme = 0; salariu = 0;};

    friend ifstream & operator >> (ifstream &c, Actor &A);

    Actor& operator = (const Actor &A);

    void Afisare();

    int Castig();

};

ifstream & operator >> (ifstream &c, Actor &A)
{
    A.nume = new char[20];

    c>>A.nume;

    c>>A.cnp;

    c>>A.rol;

    c>>A.salariu;

    c>>A.nr_filme;

    return c;
};

Actor& Actor :: operator = (const Actor &A)
{
    this -> nume = new char[strlen(A.nume)];

    strcpy(this -> nume, A.nume);

    this -> cnp = A.cnp;

    this -> rol = new char[strlen(A.rol) + 1];

    strcpy(this -> rol, A.rol);

    this -> salariu = A.salariu;

    this -> nr_filme = nr_filme;

    return *this;
};

void Actor :: Afisare()
{
    cout<<nume<<'\n';

    cout<<cnp<<'\n';

    cout<<rol<<'\n';

    cout<<nr_filme<<'\n';

    cout<<salariu<<'\n';
};

int Actor :: Castig()
{
    if(strcmp(rol, "principal") == 0)
       salariu += 10 / 100 * salariu;

    return salariu;
};

class Tehnician : public Angajat
{
public :
    Tehnician() : Angajat(){};

    Tehnician(char *nume, long int cnp, int nr_filme, float salariu) : Angajat(nume, cnp, nr_filme, salariu){};

    Tehnician(Tehnician &aux) : Angajat(aux){};

    virtual ~Tehnician(){ nume = NULL; cnp = 0; };

    friend ifstream & operator >> (ifstream &c, Tehnician &T);

    Tehnician& operator = (const Tehnician &T);

    void Afisare();

    int Castig();
};

ifstream & operator >> (ifstream &c, Tehnician &T)
{
    T.nume = new char[20];

    c>>T.nume;

    c>>T.cnp;

    c>>T.nr_filme;

    c>>T.salariu;

    return c;
};

Tehnician& Tehnician :: operator = (const Tehnician &T)
{
    this -> nume = new char[strlen(T.nume)];

    strcpy(this -> nume, T.nume);

    this -> cnp = T.cnp;

    this -> nr_filme = T.nr_filme;

    this -> salariu = T.salariu;

    return *this;
}

void Tehnician :: Afisare()
{
    cout<<nume<<'\n';

    cout<<cnp<<'\n';

    cout<<nr_filme<<'\n';

    cout<<salariu<<'\n';
};

int Tehnician :: Castig()
{
    salariu = 200;

    return salariu;
};

class Cinematograf
{
protected :
    char *nume_cinematograf;

public :
    Cinematograf();

    Cinematograf(char *nume_cinematograf);

    Cinematograf(Cinematograf &C);

    virtual ~Cinematograf();

    friend ifstream & operator >> (ifstream &c, Cinematograf &C);

    Cinematograf& operator = (const Cinematograf &C);
};

Cinematograf :: Cinematograf()
{
    nume_cinematograf = NULL;
};

Cinematograf :: Cinematograf(char *nume_cinematograf)
{
    this -> nume_cinematograf = new char[20];

    strcpy(this -> nume_cinematograf, nume_cinematograf);
};

Cinematograf :: Cinematograf(Cinematograf &C)
{
    this -> nume_cinematograf = new char[strlen(C.nume_cinematograf)];

    strcpy(this -> nume_cinematograf, C.nume_cinematograf);
};

Cinematograf :: ~Cinematograf()
{
    nume_cinematograf = NULL;
};

ifstream & operator >> (ifstream &c, Cinematograf &C)
{
    C.nume_cinematograf = new char[20];

    c>>C.nume_cinematograf;

    return c;
};

Cinematograf& Cinematograf :: operator = (const Cinematograf &C)
{
    this -> nume_cinematograf = new char[strlen(C.nume_cinematograf)];

    strcpy(this -> nume_cinematograf, C.nume_cinematograf);

    return *this;
};

class Film
{
protected :
    char *nume_film;

    char *tip;

    int durata;

    int nr_tehnicieni;

    Tehnician *T[10];

    int nr_actori;

    Actor *A[10];

    int nr_cinema;

    Cinematograf *C[10];

    Regizor *R;

public :
    Film();

    Film(char *nume_film, char *tip, int durata, int nr_tehnicieni, Tehnician *T[], int nr_actori, Actor *A[], int nr_cinema, Cinematograf *C[], Regizor R);

    Film(Film &aux);

    virtual ~Film();

    friend ifstream & operator >> (ifstream &c, Film &F);

    friend ofstream & operator << (ofstream &c, Film &F);

    Film& operator = (const Film &F);
};

Film :: Film()
{
    nume_film = NULL;

    tip = NULL;

    durata = 0;

    nr_tehnicieni = 0;

    for(int i = 1;i <= nr_tehnicieni; i++)
        T[i] = NULL;

    nr_actori = 0;

    for(int i = 1;i <= nr_actori; i++)
        A[i] = NULL;

    nr_cinema = 0;

    for(int i = 1;i <= nr_cinema; i++)
        C[i] = NULL;

    R = new Regizor();
};

Film :: Film(char *nume_film, char *tip, int durata, int nr_tehnicieni, Tehnician *T[], int nr_actori, Actor *A[], int nr_cinema, Cinematograf *C[], Regizor R)
{
    this -> nume_film = new char[20];

    strcpy(this -> nume_film, nume_film);

    this -> tip = new char[10];

    strcpy(this -> tip, tip);

    this -> durata = durata;

    this -> nr_tehnicieni = nr_tehnicieni;

    T = new Tehnician *[this -> nr_tehnicieni + 1];

    for(int i = 1;i <= this -> nr_tehnicieni; i++)
        this -> T[i] = T[i];

    this -> nr_actori = nr_actori;

    A = new Actor *[this -> nr_actori + 1];

    for(int i = 1;i <= this -> nr_actori; i++)
        this -> A[i] = A[i];

    this -> nr_cinema = nr_cinema;

    C = new Cinematograf *[this -> nr_cinema + 1];

    for(int i = 1;i <= this -> nr_cinema; i++)
        this -> C[i] = C[i];

    this -> R = new Regizor();

    this -> R = R;
};

Film :: Film(Film &aux)
{
    this -> nume_film = new char[strlen(aux.nume_film)];

    strcpy(this -> nume_film, aux.nume_film);

    this -> tip = new char[strlen(aux.tip)];

    strcpy(this -> tip, aux.tip);

    this -> durata = aux.durata;

    this -> nr_pers = aux.nr_pers;

    this -> nr_actori = aux.nr_actori;

    this -> nr_cinema = aux.nr_cinema;
};

Film :: ~Film()
{
    nume_film = NULL;

    tip = NULL;

    durata = 0;

    nr_pers = 0;

    nr_actori = 0;

    nr_cinema = 0;
};

ifstream & operator >> (ifstream &c, Film &F)
{
   F.nume_film = new char[20];

   c>>F.nume_film;

   F.tip = new char[10];

   c>>F.tip;

   c>>F.nr_pers;

   c>>F.nr_actori;

   c>>F.nr_cinema;

   c>>F.durata;

    return c;
};

ofstream & operator << (ofstream &c, Film &F)
{
   c<<F.nume_film;

   c<<F.tip;

   c<<F.nr_pers;

   c<<F.nr_actori;

   c<<F.nr_cinema;

   c<<F.durata;

    return c;
};


Film& Film :: operator = (const Film &F)
{
    this -> nume_film = new char[strlen(F.nume_film)];

    strcpy(this -> nume_film, F.nume_film);

    this -> tip = new char[strlen(F.tip)];

    strcpy(this -> tip, F.tip);

    this -> durata = F.durata;

    this -> nr_pers = F.nr_pers;

    this -> nr_actori = F.nr_actori;

    this -> nr_cinema = F.nr_cinema;

    return *this;
};

template <class T>
class FirmaDistributie
{
private :
    T *film;

    Angajat **persoane;

    static int nr_pers;

    static int nr_actori;

public :
    FirmaDistributie();

    FirmaDistributie(T *film, Angajat *persoane[NMAX], int nr_pers, int nr_actori);

    virtual ~FirmaDistributie();

    void Citire(Film *F[NMAX], int n, int &nr_actori_principali);

    void Afisare(Film *F[NMAX], int n);

    static void incrementare(){nr_pers ++; nr_actori++;};
};

template <class T>
FirmaDistributie<T> :: FirmaDistributie()
{
    film = NULL;

    nr_pers = 0;

    nr_actori = 0;

    persoane = NULL;
};

template <class T>
FirmaDistributie<T> :: FirmaDistributie(T *film, Angajat *persoane[NMAX], int nr_pers, int nr_actori)
{
    this -> film = new char[100];

    strcpy(this -> film, film);

    this -> nr_pers = nr_pers;

    this -> nr_actori = nr_actori;

    persoane = new Angajat[nr_pers];

    for(int i = 1;i <= this -> nr_pers; i++)
        this -> persoane[i] = persoane[i];
};

template <class T>
FirmaDistributie<T> :: ~FirmaDistributie()
{
    film = NULL;

    nr_pers = 0;

    nr_actori = 0;

    persoane = NULL;
};

void Try_in_functie(int a)
{
    try
    {
        if(a < 0)
           throw a;
    }
    catch(int x)
    {
        cout<<"Exceptie pe valoarea "<<x<<"\n";
    }
}

template <class T>
void FirmaDistributie<T> :: Citire(Film *F[NMAX], int n, int &nr_act_princ)
{
    f>>n;

    nr_act_princ = 0;

    for(int i = 1;i <= n; i++)
    {
        char nume[20], tip[10];
        int d, nr_persoane, nr_act, nr_cin;

        f>>nume;

        f>>tip;

        f>>d;
        Try_in_functie(d);

        f>>nr_persoane;
        Try_in_functie(nr_persoane);

        f>>nr_act;
        Try_in_functie(nr_act);

        f>>nr_cin;
        Try_in_functie(nr_cin);

        for(int i = 1;i <= nr_persoane; i++)
            {
                char *num;

                long int cnp;

                float sal;

                int nr;

                char *r;

                num = new char [20];

                f>>num;

                f>>cnp;

                f>>sal;

                f>>nr;

                r = new char [10];

                f>>r;

                if(r != "0" && r != "1")
                {
                    persoane[i] = new Actor(num, cnp, r, nr, sal);

                    if(r == "principal")
                        nr_act_princ ++;
                }
                else
                if(r == "0")
                   persoane[i] = new Regizor(num, cnp, nr, sal);
                else
                if(r == "1")
                   persoane[i] = new Tehnician(num, cnp, nr, sal);

            }

        F[i] = new Film(nume, tip, d, nr_persoane, nr_act, nr_cin);

        incrementare();
    }
}

template <class T>
void FirmaDistributie<T> :: Afisare(Film *F[NMAX], int n)
{
    for(int i = 1;i <= n; i++)
        g<<F[i]<<'\n';

    g<<"Numar total de persoane care au participat : "<<nr_pers<<'\n';

    g<<"Numar total de actori care au participat : "<<nr_actori<<'\n';
};

template <>
class FirmaDistributie<unsigned>
{
private :
    unsigned nr_actori_principali;

public:
    void set_nr_actori_principali(unsigned a){nr_actori_principali = a;}

    void afis(){cout<<"\nUnsigned "<<nr_actori_principali;}
};

int main()
{
    ///dynamic cast
    Angajat *a, *c, x;
    Tehnician *b, *d, *f, y;

    a = &y;

    a -> Afisare();

    d = dynamic_cast<Tehnician*>(a);

    if(d)
      d -> Afisare();

    f = new Tehnician;

    b = dynamic_cast <Tehnician*>(f);

    if(b)
       b->Afisare();

    ///citirea a n obiecte si afisarea lor
    FirmaDistributie<char *> T;

    Film *F[NMAX];

    int n, nr;

    T.Citire(F, n, nr);

    T.Afisare(F, n);

    /// specializare
    FirmaDistributie<unsigned> nr_p;

    nr_p.set_nr_actori_principali(nr);

    nr_p.afis();

    return 0;
}
