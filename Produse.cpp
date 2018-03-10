#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int NMAX = 10;

class Produs
{
private :
    string nume;

    string unitate_masura;

    bool perisabil;

public :
    Produs() { nume = ""; unitate_masura = ""; perisabil = false; };

    Produs(string nume, string unitate_masura, bool perisabil)
    { this -> nume = nume; this -> unitate_masura = unitate_masura; this -> perisabil = perisabil; };

    Produs(Produs &aux)
    { this -> nume = aux.nume; this -> unitate_masura = aux.unitate_masura; this -> perisabil = aux.perisabil; };

    virtual ~Produs() { nume = ""; unitate_masura = ""; perisabil = false; };

    Produs & operator = (const Produs &P)
    {
      if(this != &P)
      {
          this -> nume = P.nume;
          this -> unitate_masura = P.unitate_masura;
          this -> perisabil = P.perisabil;
      }
      return *this;
    };

    friend istream & operator >> (istream &c, Produs &P);

    void Citire();

    void Afisare();

    string getNume() { return nume; };

    string getUnitate() { return unitate_masura; };

    bool getPerisabil() { return perisabil; };

    void setNume(string nume) { this -> nume = nume; };

    void setUnitate(string unitate_masura) { this -> unitate_masura = unitate_masura; };

    void setPerisabil(bool perisabil) { this -> perisabil = perisabil; };
};

istream & operator >> (istream &c, Produs &P)
{
    string nume, unitate;

    bool per;

    c>>nume;

    P.setNume(nume);

    c>>unitate;
    P.setUnitate(unitate);

    c>>per;
    P.setPerisabil(per);

    return c;
};

void Produs :: Citire()
{
    cin>>*this;
};

void Produs :: Afisare()
{
    cout<<"Nume produs : "<<nume<<'\n';

    cout<<"Unitate de masura : "<<unitate_masura<<'\n';

    if(perisabil == true)
        cout<<"Perisabil"<<'\n';
    else
        cout<<"Nu este perisabil"<<'\n';
};

struct date
{
    int zi;

    int luna;

    int an;
};

class Lot
{
private :
    Produs *P;

    float cantitate;

    float pret;

    date data;

public :

    Lot() { P = NULL; cantitate = 0; pret = 0; data.zi = 0; data.luna = 0; data.an = 0; };

    Lot(Produs *P, float cantitate, float pret, date data)
    {
        this -> P = P;

        this -> cantitate = cantitate;

        this -> pret = pret;

        this -> data = data;
    };

    Lot(Lot &aux)
    {
        this -> P = aux.P;

        this -> cantitate = aux.cantitate;

        this -> pret = aux.pret;

        this -> data = aux.data;
    };

    virtual ~Lot() { P = NULL; cantitate = 0; pret = 0; data.zi = 0; data.luna = 0; data.an = 0; };

    Lot & operator = (const Lot &L)
    {
       if(this != &L)
       {
            this -> P = L.P;

            this -> cantitate = L.cantitate;

            this -> pret = L.pret;

            this -> data = L.data;

            return *this;
       }
    };

    friend istream & operator >> (istream &c, Lot &L);

    void Citire();

    virtual void Afisare();

    bool expirat() {};

    Produs* getProdus() { return P; };

    float getCantitate() { return cantitate; };

    float getPret() { return pret; };

    int getData_zi() { return data.zi; };

    int getData_luna() { return data.luna; };

    int getData_an() { return data.an; };

    void setProdus(Produs *P) { this -> P = P; };

    void setCantitate(float cantitate) { this -> cantitate = cantitate; };

    void setPret(float pret) { this -> pret = pret; };

    void setData(date data) { this -> data = data; };
};

istream & operator >> (istream &c, Lot &L)
{
    Produs *p = new Produs();

    float cant, pret;

    date d;

    p -> Citire();
    L.setProdus(p);

    c>>cant;
    L.setCantitate(cant);

    c>>pret;
    L.setPret(pret);

    c>>d.zi;
    c>>d.luna;
    c>>d.an;
    L.setData(d);

    return c;
};

void Lot :: Citire()
{
    cin>>*this;
};

void Lot :: Afisare()
{
    P -> Afisare();

    cout<<"Cantitate : "<<cantitate<<'\n';

    cout<<"Pret pe unitate de masura : "<<pret<<'\n';

    cout<<"Data primire : "<<data.zi<<" . "<<data.luna<<" . "<<data.an<<'\n';
};

class LotPromotional : virtual public Lot
{
private :
    int discount;

public :
    LotPromotional() : Lot() { discount = 0; };

    LotPromotional(Produs *P, float cantitate, float pret, date data, int discount) : Lot(P, cantitate, pret, data)
    {
        this -> discount = discount;
    };

    LotPromotional(LotPromotional &aux) : Lot(aux) { this -> discount = aux.discount; };

    virtual ~LotPromotional() { discount = 0; };

    LotPromotional & operator = (const LotPromotional &LPRM)
    {
        if(this != &LPRM)
        {
            Lot :: operator = (LPRM);

            this -> discount = LPRM.discount;
        }

        return *this;
    };

    friend istream & operator >> (istream &c, LotPromotional &LPRM);

    void Citire();

    void Afisare();

    int getDiscount() { return discount; };

    void setDiscount(int discount) { this -> discount = discount; };
};

istream & operator >> (istream &c, LotPromotional &LPRM)
{
    Produs *p = new Produs();

    float cant, pret;

    int disc;

    date d;

    p -> Citire();
    LPRM.setProdus(p);

    c>>cant;
    LPRM.setCantitate(cant);

    c>>pret;
    LPRM.setPret(pret);

    c>>d.zi;
    c>>d.luna;
    c>>d.an;
    LPRM.setData(d);

    c>>disc;
    LPRM.setDiscount(disc);

    return c;
};

void LotPromotional :: Citire()
{
    cin>>*this;
};

void LotPromotional :: Afisare()
{
    this -> getProdus() -> Afisare();

    cout<<"Cantitate : "<<getCantitate()<<'\n';

    cout<<"Pret pe unitate de masura : "<<getPret()<<'\n';

    cout<<"Data primire : "<<getData_zi()<<" . "<<getData_luna()<<" . "<<getData_an()<<'\n';

    cout<<"Discount : "<<discount<<" % "<<'\n';
};

class LotPerisabil : virtual public Lot
{
private :
    int valabilitate;

public :
    LotPerisabil() : Lot() { valabilitate = 0;};

    LotPerisabil(Produs *P, float cantitate, float pret, date data, int valabilitate) : Lot(P, cantitate, pret, data)
    {
        this -> valabilitate = valabilitate;
    };

    LotPerisabil(LotPerisabil &aux) : Lot(aux)
    {
        this -> valabilitate = aux.valabilitate;
    };

    virtual ~LotPerisabil() { valabilitate = 0; };

    LotPerisabil & operator = (const LotPerisabil &LPR)
    {
      if(this != &LPR)
      {
          Lot :: operator = (LPR);
          this -> valabilitate = LPR.valabilitate;
      }

      return *this;
    };

    friend istream & operator >> (istream &c, LotPerisabil &LPR);

    void Citire();

    void Afisare();

    bool expirat(date d);

    int getValabilitate() { return valabilitate; };

    void setValabilitate(int valabilitate) { this -> valabilitate = valabilitate; };
};

istream & operator >> (istream &c, LotPerisabil &LPR)
{
    Produs *p = new Produs();

    float cant, pret;

    int valabil;

    date d;

    p -> Citire();
    LPR.setProdus(p);

    c>>cant;
    LPR.setCantitate(cant);

    c>>pret;
    LPR.setPret(pret);

    c>>d.zi;
    c>>d.luna;
    c>>d.an;
    LPR.setData(d);

    c>>valabil;
    LPR.setValabilitate(valabil);

    return c;
};

void LotPerisabil :: Citire()
{
    cin>>*this;
};

void LotPerisabil :: Afisare()
{
    this -> getProdus() -> Afisare();

    cout<<"Cantitate : "<<getCantitate()<<'\n';

    cout<<"Pret pe unitate de masura : "<<getPret()<<'\n';

    cout<<"Data primire : "<<getData_zi()<<" . "<<getData_luna()<<" . "<<getData_an()<<'\n';

    cout<<"Termen de valabilitate : "<<valabilitate<<" zile"<<'\n';
};

bool LotPerisabil :: expirat(date d)
{
    date aux;

    aux.an = getData_an();

    int x = (getData_zi() + valabilitate) / 30;

    int y = (getData_zi() + valabilitate) % 30;

    aux.zi = y;

    if(x > 0)
      aux.luna = getData_luna() + x;
    else
      aux.luna = getData_luna();

    if(aux.luna < d.luna || (aux.luna = d.luna && aux.zi < d.zi))
       return false;

    return true;
}

class LotPeriPromo : public LotPerisabil, public LotPromotional
{
public :
    LotPeriPromo() : LotPromotional(), LotPerisabil() {};

    LotPeriPromo(Produs *P, float cantitate, float pret, date data, int discount, int valabilitate):
                 LotPromotional(P, cantitate, pret, data, discount), LotPerisabil(P, cantitate, pret, data, valabilitate) {};

    LotPeriPromo(LotPeriPromo &aux) : LotPromotional(aux), LotPerisabil(aux) {};

    virtual ~LotPeriPromo() {};

    LotPeriPromo & operator = (LotPeriPromo &LPP)
    {
        if(this != &LPP)
      {
          LotPromotional :: operator = (LPP);

          LotPerisabil :: operator = (LPP);
      }

      return *this;
    };

    friend istream & operator >> (istream &c, LotPeriPromo &LPP);

    void Citire();

    void Afisare();

    bool expirat(date d);
};

istream & operator >> (istream &c, LotPeriPromo &LPP)
{
    Produs *p = new Produs();

    float cant, pret;

    int disc, valabil;

    date d;

    p -> Citire();
    LPP.setProdus(p);

    c>>cant;
    LPP.setCantitate(cant);

    c>>pret;
    LPP.setPret(pret);

    c>>d.zi;
    c>>d.luna;
    c>>d.an;
    LPP.setData(d);

    c>>disc;
    LPP.setDiscount(disc);

    c>>valabil;
    LPP.setValabilitate(valabil);

    return c;
};

void LotPeriPromo :: Citire()
{
    cin>>*this;
};

void LotPeriPromo :: Afisare()
{
    this -> getProdus() -> Afisare();

    cout<<"Cantitate : "<<getCantitate()<<'\n';

    cout<<"Pret pe unitate de masura : "<<getPret()<<'\n';

    cout<<"Data primire : "<<getData_zi()<<" . "<<getData_luna()<<" . "<<getData_an()<<'\n';

    cout<<"Discount : "<<getDiscount()<<'\n';

    cout<<"Termen de valabilitate : "<<getValabilitate()<<" zile"<<'\n';
};

bool LotPeriPromo :: expirat(date d)
{
    date aux;

    aux.an = getData_an();

    int x = (getData_zi() + getValabilitate()) / 30;

    int y = (getData_zi() + getValabilitate()) % 30;

    aux.zi = y;

    if(x > 0)
      aux.luna = getData_luna() + x;
    else
      aux.luna = getData_luna();

    if(aux.luna < d.luna || (aux.luna = d.luna && aux.zi < d.zi))
       return false;

    return true;
}

void citire_produse(Produs *Pr[NMAX], int n)
{
    cin>>n;

    for(int i = 1;i <= n; i++)
       {
           Pr[i] = new Produs();

           Pr[i] -> Citire();
       }
}

void afisare_produse(Produs *Pr[NMAX], int n)
{
    for(int i = 1;i <= n; i++)
        Pr[i] -> Afisare();
}

void citire_loturi(Lot *Lt[NMAX], int m)
{
    int tip;
    for(int i = 1;i <= m; i++)
    {
        cin>>m;

        cout<<"Tip : ";

        cin>>tip;

        if(tip == 1)
        {
            Lt[i] = new Lot();

            Lt[i] -> Citire();
        }
        if(tip == 2)
        {
            Lt[i] = new LotPromotional();

            Lt[i] -> Citire();
        }
        if(tip == 3)
        {
            Lt[i] = new LotPerisabil();

            Lt[i] -> Citire();
        }
        if(tip == 4)
        {
            Lt[i] = new LotPeriPromo();

            Lt[i] -> Citire();
        }
    }
}

void meniu()
{
    int separator;

    cout<<"MENIU : "<<'\n';

    cout<<" 0.EXIT \n 1. adaugare produs nou \n 2. afisare produse \n 3. adaugare lot \n 4. afisare loturi intre doua date \n 5. afisare loturi la data curenta \n";

    cin>>separator;

    Produs *Pr[NMAX];

    Lot *Lt[NMAX];

    int n, m;

    citire_produse(Pr, n);

    citire_loturi(Lt, m);

    while(separator != 0)
    {
        if(separator == 0)
           break;
        else
        if(separator == 1)
        {
            Pr[++n] = new Produs();

            Pr[n] -> Citire();
        }
        else
        if(separator == 2)
        {
            afisare_produse(Pr, n);
        }
        else
        if(separator == 3)
        {
            int tip;

            cout<<"Tip : ";

            cin>>tip;

            if(tip == 1)
            {
                Lt[++m] = new Lot();

                Lt[m] -> Citire();
            }
            if(tip == 2)
            {
                Lt[++m] = new LotPromotional();

                Lt[m] -> Citire();
            }
            if(tip == 3)
            {
                Lt[++m] = new LotPerisabil();

                Lt[m] -> Citire();
            }
            if(tip == 4)
            {
                Lt[++m] = new LotPeriPromo();

                Lt[m] -> Citire();
            }
        }
        else
        if(separator == 4)
        {
            date d1, d2;

            cin>>d1.zi>>d1.luna>>d1.an;

            cin>>d2.zi>>d2.luna>>d2.an;

            for(int i = 1;i <= m; i++)
            {
                date d;

                d.zi = Lt[i] -> getData_zi();

                d.luna = Lt[i] -> getData_luna();

                d.an = Lt[i] -> getData_an();

                if(d.an >= d1.an && d.an <= d2.an)
                    if(d.luna >= d1.luna && d.luna <= d2.luna)
                      {
                          if(d.luna == d1.luna && d.luna < d2.luna && d.zi > d1.zi)
                             Lt[i] -> Afisare();
                          else
                          if(d.luna > d1.luna && d.luna < d2.luna)
                             Lt[i] -> Afisare();
                          else
                          if(d.luna > d1.luna && d.luna == d2.luna && d.zi < d2.zi)
                             Lt[i] -> Afisare();
                      }
            }
        }
        else
        if(separator == 5)
        {
            date d;

            cout<<"Introduceti data curenta : ";

            cin>>d.zi>>d.luna>>d.an;

            for(int i = 1;i <= m; i++)
                if(Lt[i] -> getProdus() -> getPerisabil() && !Lt[i] -> expirat())
                   Lt[i] -> Afisare();
        }

        cin>>separator;
    }
}

int main()
{
    meniu();
    return 0;
}
