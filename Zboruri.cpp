#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

fstream f("date.in", ios :: in);

const int NMAX = 10;

class Cursa
{
private :
    char *ID;

    char *orasPlecare;

    char *orasSosire;

    char *data;

    float pretBilet;

    int durataZbor;

public :
    Cursa();

    Cursa(char *ID, char *orasPlecare, char *orasSosire, char *data, float pretBilet, int durataZbor);

    Cursa(Cursa &aux);

    virtual ~Cursa();

    Cursa & operator = (const Cursa &C);

    friend ifstream & operator >> (ifstream &c, Cursa &C);

    virtual void Afisare();

    char * get_ID() { return ID; };

    char * get_orasPlecare() { return orasPlecare; };

    char * get_orasSosire() { return orasSosire; };

    char * get_data() { return data; };

    float get_pretBilet() { return pretBilet; };

    int get_durataZbor() { return durataZbor; };

    void set_ID(char *ID) { this -> ID = new char [10]; this -> ID = ID; };

    void set_orasPlecare(char *orasPlecare) { this -> orasPlecare = new char [10]; this -> orasPlecare = orasPlecare; };

    void set_orasSosire(char *orasSosire) { this -> orasSosire = new char [10]; this -> orasSosire = orasSosire; };

    void set_data(char *data) { this -> data = new char [10]; this -> data = data; };

    void set_pretBilet(float pretBilet) { this -> pretBilet = pretBilet; };

    void set_durataZbor(int durataZbor) { this -> durataZbor = durataZbor; };
};

Cursa :: Cursa()
{
    ID = NULL;

    orasPlecare = NULL;

    orasSosire = NULL;

    data = NULL;

    pretBilet = 0;

    durataZbor = 0;
};

Cursa :: Cursa(char *ID, char *orasPlecare, char *orasSosire, char *data, float pretBilet, int durataZbor)
{
    this -> ID = new char [10];

    this -> ID = ID;

    this -> orasPlecare = new char [10];

    strcpy(this -> orasPlecare, orasPlecare);

    this -> orasSosire = new char [10];

    strcpy(this -> orasSosire, orasSosire);

    this -> data = new char [10];

    strcpy(this -> data, data);

    this -> pretBilet = pretBilet;

    this -> durataZbor = durataZbor;
};

Cursa :: Cursa(Cursa &aux)
{

    this -> ID = new char [strlen(aux.ID)];

    strcpy(this -> ID, aux.ID);

    this -> orasPlecare = new char [strlen(aux.orasPlecare)];

    strcpy(this -> orasPlecare, aux.orasPlecare);

    this -> orasSosire = new char [strlen(aux.orasSosire)];

    strcpy(this -> orasSosire, aux.orasSosire);

    this -> data = new char [strlen(aux.data)];

    strcpy(this -> data, aux.data);

    this -> pretBilet = aux.pretBilet;

    this -> durataZbor = aux.durataZbor;
};

Cursa :: ~Cursa()
{
    ID = NULL;

    orasPlecare = NULL;

    orasSosire = NULL;

    data = NULL;

    pretBilet = 0;

    durataZbor = 0;
};

Cursa& Cursa :: operator = (const Cursa &C)
{
    this -> ID = new char [strlen(C.ID)];

    strcpy(this -> ID, C.ID);

    this -> orasPlecare = new char [strlen( C.orasPlecare)];

    strcpy(this -> orasPlecare, C.orasPlecare);

    this -> orasSosire = new char [strlen(C.orasSosire)];

    strcpy(this -> orasSosire, C.orasSosire);

    this -> data = new char [strlen(C.data)];

    strcpy(this -> data, C.data);

    this -> pretBilet = C.pretBilet;

    this -> durataZbor = C.durataZbor;

    return *this;
};

ifstream & operator >> (ifstream &c, Cursa &C)
{
    char id[10], orasP[10], orasS[10], data[10];

    float pret;

    int durata;

    c>>id;

    C.set_ID(id);

    c>>orasP;

    C.set_orasPlecare(orasP);

    c>>orasS;

    C.set_orasSosire(orasS);

    c>>data;

    C.set_data(data);

    c>>pret;

    C.set_pretBilet(pret);

    c>>durata;

    C.set_durataZbor(durata);

    return c;
};

void Cursa :: Afisare()
{
    cout<<"ID : "<<ID<<'\n';

    cout<<"Oras plecare : "<<orasPlecare<<'\n';

    cout<<"Oras sosire : "<<orasSosire<<'\n';

    cout<<"Data : "<<data<<'\n';

    cout<<"Pret bilet : "<<pretBilet<<'\n';
};

class CursaTemporara : virtual public Cursa
{
private:
    int perioadaExistenta;

public :
    CursaTemporara();

    CursaTemporara(char *ID, char *orasPlecare, char *orasSosire,
                   char *data, float pretBilet, int durataZbor, int perioadaExistenta) : Cursa(ID, orasPlecare, orasSosire, data, pretBilet, durataZbor)
    {
        this -> perioadaExistenta = perioadaExistenta;
    };

    CursaTemporara(CursaTemporara &aux) : Cursa(aux)
    {
        this -> perioadaExistenta = aux.perioadaExistenta;
    };

    ~CursaTemporara()
    {
        perioadaExistenta = 0;
    };

    CursaTemporara & operator = (const CursaTemporara &T)
    {
        Cursa :: operator = (T);

        this -> perioadaExistenta = T.perioadaExistenta;

        return *this;
    };

    friend ifstream & operator >> (ifstream &c, CursaTemporara &T);

    void Afisare();

    int get_perioadaExistenta() {return perioadaExistenta; };

    void set_perioadaExistenta(int perioadaExistenta) { this -> perioadaExistenta = perioadaExistenta; };
};

ifstream & operator >> (ifstream &c, CursaTemporara &T)
{
    char id[10], orasP[10], orasS[10], data[10];

    float pret;

    int durata, perioada;

    c>>id;

    T.set_ID(id);

    c>>orasP;

    T.set_orasPlecare(orasP);

    c>>orasS;

    T.set_orasSosire(orasS);

    c>>data;

    T.set_data(data);

    c>>pret;

    T.set_pretBilet(pret);

    c>>durata;

    T.set_durataZbor(durata);

    c>>perioada;

    T.set_perioadaExistenta(perioada);

    return c;
};

void CursaTemporara :: Afisare()
{
    cout<<"ID : "<<get_ID()<<'\n';

    cout<<"Oras plecare : "<<get_orasPlecare()<<'\n';

    cout<<"Oras sosire : "<<get_orasSosire()<<'\n';

    cout<<"Data : "<<get_data()<<'\n';

    cout<<"Pret bilet : "<<get_pretBilet()<<'\n';

    cout<<"Durata zbor : "<<get_durataZbor()<<'\n';

    cout<<"Perioada existenta : "<<perioadaExistenta<<'\n';
}

class CursaDiscount : virtual public Cursa
{
private :
    int discount;

public :
    CursaDiscount();

    CursaDiscount(char *ID, char *orasPlecare, char *orasSosire,
                   char *data, float pretBilet, int durataZbor, int discount) : Cursa(ID, orasPlecare, orasSosire, data, pretBilet, durataZbor)
    {
        this -> discount = discount;
    };

    CursaDiscount(CursaDiscount &aux) : Cursa(aux)
    {
        this -> discount = aux.discount;
    };

    ~CursaDiscount()
    {
        discount = 0;
    };

    CursaDiscount & operator = (const CursaDiscount &D)
    {
        Cursa :: operator = (D);

        this -> discount = D.discount;

        return *this;
    };

    friend ifstream & operator >> (ifstream &c, CursaDiscount &D);

    void Afisare();

    int get_discount() {return discount; };

    void set_discount(int discount) { this -> discount = discount; };
};

ifstream & operator >> (ifstream &c, CursaDiscount &D)
{
    char id[10], orasP[10], orasS[10], data[10];

    float pret;

    int durata, discount;

    c>>id;

    D.set_ID(id);

    c>>orasP;

    D.set_orasPlecare(orasP);

    c>>orasS;

    D.set_orasSosire(orasS);

    c>>data;

    D.set_data(data);

    c>>pret;

    D.set_pretBilet(pret);

    c>>durata;

    D.set_durataZbor(durata);

    c>>discount;

    D.set_discount(discount);

    return c;
};

void CursaDiscount :: Afisare()
{
    cout<<"ID : "<<get_ID()<<'\n';

    cout<<"Oras plecare : "<<get_orasPlecare()<<'\n';

    cout<<"Oras sosire : "<<get_orasSosire()<<'\n';

    cout<<"Data : "<<get_data()<<'\n';

    cout<<"Pret bilet : "<<get_pretBilet()<<'\n';

    cout<<"Durata zbor : "<<get_durataZbor()<<'\n';

    cout<<"Discount : "<<discount<<'\n';
};

class CursaTemporaraDiscount : public CursaTemporara , public CursaDiscount
{
public :

    CursaTemporaraDiscount() : CursaTemporara(), CursaDiscount() {};

    CursaTemporaraDiscount(char *ID, char *orasPlecare, char *orasSosire,
                   char *data, float pretBilet, int durataZbor, int perioadaExistenta, int discount) :
                   CursaTemporara(ID, orasPlecare, orasSosire, data, pretBilet, durataZbor, perioadaExistenta),
                   CursaDiscount(ID, orasPlecare, orasSosire, data, pretBilet, durataZbor, discount) {};

    CursaTemporaraDiscount(CursaTemporaraDiscount &aux) : CursaTemporara(aux), CursaDiscount(aux) {};

    ~CursaTemporaraDiscount() {};

    CursaTemporaraDiscount & operator = (const CursaTemporaraDiscount &CD)
    {
        CursaTemporara :: operator = (CD);

        CursaDiscount :: operator = (CD);

        return *this;
    };

    void Afisare();
};

void CursaTemporaraDiscount :: Afisare()
{
    cout<<"ID : "<<get_ID()<<'\n';

    cout<<"Oras plecare : "<<get_orasPlecare()<<'\n';

    cout<<"Oras sosire : "<<get_orasSosire()<<'\n';

    cout<<"Data : "<<get_data()<<'\n';

    cout<<"Pret bilet : "<<get_pretBilet()<<'\n';

    cout<<"Durata zbor : "<<get_durataZbor()<<'\n';

    cout<<"Perioada existenta : "<<get_perioadaExistenta()<<'\n';

    cout<<"Discount : "<<get_discount()<<'\n';
};

class Ruta
{
private :
    char *orasPlecare;

    char *orasSosire;

    int nrCurse;

    float pretBilet;

    float pretEconomic;

protected :
    Cursa *C[NMAX];

    CursaTemporara *T[NMAX];

    CursaDiscount *D[NMAX];

    CursaTemporaraDiscount *CD[NMAX];

public :
    Ruta();

    Ruta(char *orasPlecare, char *orasSosire, int nrCurse, float pretBilet, float pretEconomic,
         Cursa *C[NMAX], CursaTemporara *T[NMAX], CursaDiscount *D[NMAX], CursaTemporaraDiscount *CD[NMAX]);

    virtual ~Ruta();

    friend ifstream & operator >> (ifstream &c, Ruta &R);

    void Afisare();

    void Citire_curse();

    void Afisare_curse();

    char *get_orasPlecare() { return orasPlecare; };

    void set_orasPlecare(char *orasPlecare) { this -> orasPlecare = new char [10]; this -> orasPlecare = orasPlecare; };

    char *get_orasSosire() { return orasSosire; };

    void set_orasSosire(char *orasSosire) { this -> orasSosire = new char [10]; this -> orasSosire = orasSosire; };

    int get_nrCurse() { return nrCurse; };

    void set_nrCurse(int nrCurse) { this -> nrCurse = nrCurse; };

    float get_pretBilet() { return pretBilet; };

    void set_pretBilet(float pretBilet) { this -> pretBilet = pretBilet; };

    float get_pretEconomic() { return pretEconomic; };

    void set_pretEconomic(float pretEconomic) { this -> pretEconomic = pretEconomic; };
};

Ruta :: Ruta()
{
    orasPlecare = NULL;

    orasSosire = NULL;

    nrCurse = 0;

    pretBilet = 0;

    pretEconomic = 0;

    *C = NULL;

    *T = NULL;

    *D = NULL;

    *CD = NULL;
};

Ruta :: Ruta(char *orasPlecare, char *orasSosire, int nrCurse, float pretBilet, float pretEconomic,
             Cursa *C[NMAX], CursaTemporara *T[NMAX], CursaDiscount *D[NMAX], CursaTemporaraDiscount *CD[NMAX])
{
    this -> orasPlecare = new char [10];

    this -> orasPlecare = orasPlecare;

    this -> orasSosire = new char [10];

    this -> orasSosire = orasSosire;

    this -> nrCurse = nrCurse;

    this -> pretBilet = pretBilet;

    this -> pretEconomic = pretEconomic;

    C = new Cursa *[1];

    *this -> C = *C;

    T = new CursaTemporara *[1];

    *this -> T = *T;

    D = new CursaDiscount *[1];

    *this -> D = *D;

    CD = new CursaTemporaraDiscount *[1];

    *this -> CD = *CD;
};

Ruta :: ~Ruta()
{
    orasPlecare = NULL;

    orasSosire = NULL;

    nrCurse = 0;

    pretBilet = 0;

    pretEconomic = 0;
};

ifstream & operator >> (ifstream &c, Ruta &R)
{
    char orasP[10], orasS[10];

    int nrC;

    float pret, pretEco;

    c>>orasP;

    R.set_orasPlecare(orasP);

    c>>orasS;

    R.set_orasSosire(orasS);

    c>>nrC;

    R.set_nrCurse(nrC);

    c>>pret;

    R.set_pretBilet(pret);

    c>>pretEco;

    R.set_pretEconomic(pretEco);

    return c;
}

void Ruta :: Afisare()
{
    cout<<"Ruta : "<<orasPlecare<< " -> "<<orasSosire<<'\n';

    cout<<"Numar curse : "<<nrCurse<<'\n';

    cout<<"Pret bilet : "<<pretBilet<<'\n';

    cout<<"Pret bilet la clasa Economic : "<<pretEconomic<<'\n';

    Afisare_curse();
};

void Ruta :: Citire_curse()
{
    Cursa *C[NMAX];

    CursaTemporara *T[NMAX];

    CursaDiscount *D[NMAX];

    CursaTemporaraDiscount *CD[NMAX];

    int n, m, p, q;

    for(int i = 1;i <= n; i++)
        {
            char id[10], orasP[10], orasS[10], data[10];

            float pret;

            int durata;

            f>>id;

            f>>orasP;

            f>>orasS;

            f>>data;

            f>>pret;

            f>>durata;

            C[i] = new Cursa(id, orasP, orasS, data, pret, durata);
        }

    for(int i = 1;i <= m; i++)
        {
            char id[10], orasP[10], orasS[10], data[10];

            float pret;

            int durata, perioada;

            f>>id;

            f>>orasP;

            f>>orasS;

            f>>data;

            f>>pret;

            f>>durata;

            f>>perioada;

            T[i] = new CursaTemporara(id, orasP, orasS, data, pret, durata, perioada);
        }

    for(int  i = 1;i <= p; i++)
        {
            char id[10], orasP[10], orasS[10], data[10];

            float pret;

            int durata, discount;

            f>>id;

            f>>orasP;

            f>>orasS;

            f>>data;

            f>>pret;

            f>>durata;

            f>>discount;

            D[i] = new CursaDiscount(id, orasP, orasS, data, pret, durata, discount);
        }

    for(int i = 1;i <= q; i++)
        {
            char id[10], orasP[10], orasS[10], data[10];

            float pret;

            int durata, perioada, discount;

            f>>id;

            f>>orasP;

            f>>orasS;

            f>>data;

            f>>pret;

            f>>durata;

            f>>perioada;

            f>>discount;

            CD[i] = new CursaTemporaraDiscount(id, orasP, orasS, data, pret, durata, perioada, discount);
        }
};

void Ruta :: Afisare_curse()
{
    Cursa *C[NMAX];

    CursaTemporara *T[NMAX];

    CursaDiscount *D[NMAX];

    CursaTemporaraDiscount *CD[NMAX];

    cout<<"CURSE : "<<'\n';

    for(int i = 1;i <= nrCurse / 4; i++)
        C[i] -> Afisare();

    cout<<"CURSE TEMPORARE : "<<'\n';

    for(int i = 1;i <= nrCurse / 4; i++)
        T[i] -> Afisare();

    cout<<"CURSE CU DISCOUCOUNT : "<<'\n';

    for(int i = 1;i <= nrCurse / 4; i++)
        D[i] -> Afisare();

    cout<<"CURSE TEMPORARE SI CU DISCOUNT : "<<'\n';

    for(int i = 1;i <= nrCurse / 4; i++)
        CD[i] -> Afisare();
};

void Citire_Rute(Ruta *R[NMAX], int N)
{
    for(int i = 1;i <= N; i++)
    {
        R[i] = new Ruta();

        char orasP[10], orasS[10];

        int nrC;

        float pret, pretEco;

        Cursa *C[NMAX];

        CursaTemporara *T[NMAX];

        CursaDiscount *D[NMAX];

        CursaTemporaraDiscount *CD[NMAX];

        f>>orasP;

        f>>orasS;

        f>>nrC;

        f>>pret;

        f>>pretEco;

        R[i] -> Citire_curse();

        *R[i] = Ruta(orasP, orasS, nrC, pret, pretEco, C, T, D, CD);
    }
};

void Afisare_Rute(Ruta *R[NMAX], int N)
{
    for(int i = 1;i <= N; i++)
        R[i] -> Afisare();
};


int main()
{

    Ruta *R[NMAX];

    int N;

    Citire_Rute(R, N);

    Afisare_Rute(R, N);

    f.close();

    return 0;
}
