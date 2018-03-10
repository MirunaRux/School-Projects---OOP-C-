#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class Angajat
{
protected:
    char *nume;
    char *data_angajarii;
    char *functia;
    int cod[10];
    static int index;
public:
    Angajat()
    {
        nume = NULL;
        data_angajarii = NULL;
        functia = NULL;
        index++;
    }
    Angajat(char *a, char *b, char *c, int d[10])
    {
        try
        {
            nume = new char[strlen(a)+1];
            data_angajarii = new char[strlen(b)+1];
            functia = new char[strlen(c)+1];
        }
        catch (bad_alloc t)
        {
            cout << "Nu s-a putut aloca memorie." << endl;
            exit(EXIT_FAILURE);
        }
        strcpy (nume, a);
        strcpy (data_angajarii, b);
        strcpy (functia, c);
        index++;
        try
        {
            for (int i = 1; i <= 10; i++)
                if (d[i] <= 0)
                    throw d[i];
                else cod[i] = d[i];
        }
        catch (int x)
        {
            cout << "Codul nu este valid." << endl;
            exit(EXIT_FAILURE);
        }
    }
    Angajat(const Angajat& a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        for (int i = 1; i <= 10; i++)
            cod[i] = a.cod[i];
    }
    virtual ~Angajat()
    {
        if (nume)
            delete []nume;
        if (data_angajarii)
            delete []data_angajarii;
        if (functia)
            delete []functia;
        index--;
    }
    friend istream &operator >>(istream &i, Angajat &a);

    virtual void afisare() = 0;

    virtual void citire() = 0;

    Angajat &operator = (Angajat &a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        for (int i = 1; i <= 10; i++)
            cod[i] = a.cod[i];
        return *this;
    }

    static void get_index()
    {
        cout << "index = " << index << endl;
    }

};

istream &operator >>(istream &i, Angajat &a)
{
    char b[100], c[100], d[100];
    cout << "Nume: ";
    i >> b;
    a.nume = new char[strlen(b)+1];
    strcpy(a.nume, b);
    cout << "Functia: ";
    i >> c;
    a.functia = new char[strlen(c)+1];
    strcpy(a.functia, c);
    cout << "Data angajarii: ";
    i >> d;
    a.data_angajarii = new char[strlen(d)+1];
    strcpy(a.data_angajarii, d);
    cout << "Cod: ";
    for (int i = 1; i <= 10; i++)
            i >> a.cod[i];
    return i;
}

int Angajat :: index = 0;

class Permanent : public Angajat
{
    float salariu;
public:
    Permanent()
    {
        salariu = 0;
    }
    Permanent(char *a, char *b, char *c, float d, int e[10]) : Angajat(a, b, c, e)
    {
        salariu = d;
        try
        {
            if (d <= 0)
                throw d;
        }
        catch (int t)
        {
            cout << "Salariul nu poate fi negativ." << endl;
            exit(EXIT_FAILURE);
        }
    }
    Permanent(const Permanent& a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        salariu = a.salariu;
    }
    ~Permanent()
    {
        salariu = 0;
    }
    friend istream &operator >>(istream &i, Permanent &a);

    void afisare()
    {
        cout << nume << "   " << functia << "   " << data_angajarii << "    ";
        cout << salariu << endl;
    }

    void citire()
    {
        cin >> *this;
    }

    Permanent &operator = (Permanent &a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        salariu = a.salariu;
        return *this;
    }
};

istream &operator >>(istream &i, Permanent &a)
{
    char b[100], c[100], d[100];
    cout << "Nume: ";
    i >> b;
    a.nume = new char[strlen(b)+1];
    strcpy(a.nume, b);
    cout << "Functia: ";
    i >> c;
    a.functia = new char[strlen(c)+1];
    strcpy(a.functia, c);
    cout << "Data angajarii: ";
    i >> d;
    a.data_angajarii = new char[strlen(d)+1];
    strcpy(a.data_angajarii, d);
    cout << "Salariu: ";
    i >> a.salariu;
    return i;
}

class Part_Time : public Angajat
{
    float tarif_ora;
    int nr_ore;
    char *data_terminare;
public:
    Part_Time()
    {
        tarif_ora = 0;
        nr_ore = 0;
        data_terminare = NULL;
    }
    Part_Time(char *a, char *b, char *c, float d, int e, char *f, int g[10]) : Angajat(a, b, c, g)
    {
        try
        {
            if (d <= 0 || nr_ore < 0)
                throw d;
        }
        catch (int t)
        {
            cout << "Date incorecte" << endl;
            exit(EXIT_FAILURE);
        }

        tarif_ora = d;
        nr_ore = e;
        data_terminare = new char[strlen(f)+1];
        strcpy (data_terminare, f);
    }
    Part_Time(const Part_Time& a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        tarif_ora = a.tarif_ora;
        nr_ore = a.nr_ore;
        data_terminare = new char[strlen(a.data_terminare)+1];
        strcpy (data_terminare, a.data_terminare);
    }
    ~Part_Time()
    {
        tarif_ora = 0;
        nr_ore = 0;
        if (data_terminare)
            delete []data_terminare;
    }
    friend istream &operator >>(istream &i, Part_Time &a);

    void afisare()
    {
        cout << nume << "   " << functia << "   " << data_angajarii << "   ";
        cout << tarif_ora << "    " << nr_ore << "   " << data_terminare;
        cout << endl;
    }

    void citire()
    {
        cin >> *this;
    }

    Part_Time &operator = (Part_Time &a)
    {
        nume = new char[strlen(a.nume)+1];
        strcpy (nume, a.nume);
        data_angajarii = new char[strlen(a.data_angajarii)+1];
        strcpy (data_angajarii, a.data_angajarii);
        functia = new char[strlen(a.functia)+1];
        strcpy (functia, a.functia);
        tarif_ora = a.tarif_ora;
        nr_ore = a.nr_ore;
        data_terminare = new char[strlen(a.data_terminare)+1];
        strcpy (data_terminare, a.data_terminare);
        return *this;
    }
};

istream &operator >>(istream &i, Part_Time &a)
{
    char b[100], c[100], d[100], e[100];
    cout << "Nume: ";
    i >> b;
    a.nume = new char[strlen(b)+1];
    strcpy(a.nume, b);
    cout << "Functia: ";
    i >> c;
    a.functia = new char[strlen(c)+1];
    strcpy(a.functia, c);
    cout << "Data angajarii: ";
    i >> d;
    a.data_angajarii = new char[strlen(d)+1];
    strcpy(a.data_angajarii, d);
    cout << "Tarif pe ora: ";
    i >> a.tarif_ora;
    cout << "Numar ore pe luna: ";
    i >> a.nr_ore;
    cout << "Data terminarii contractului: ";
    i >> e;
    a.data_terminare = new char[strlen(e)+1];
    strcpy(a.data_terminare, e);

    return i;
}

int main()
{
    Permanent a;
    Angajat *A[100];
    int n;
    cout << "n = ";
    cin >> n;

    cout << "Angajat permanent --> TASTA 1" << endl;
    cout << "Angajat part-time --> TASTA 2" << endl;

    for (int i = 1; i <= n; i++)
    {
        int p;
        cout << "Tip = ";
        cin >> p;
        if (p == 1)
        {
            A[i] = new Permanent;
            Permanent *a = dynamic_cast <Permanent*>(A[i]);
            A[i]->citire();
        }
       else if (p == 2)
        {
            A[i] = new Part_Time;
            Part_Time *d = dynamic_cast <Part_Time*>(A[i]);
            A[i]->citire();
        }
        else
        {
            cout << "Tip inexistent" << endl;
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= n; i++)
        A[i]->afisare();
    return 0;
}
