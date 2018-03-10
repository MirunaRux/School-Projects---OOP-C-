/// Budoias Miruna Ruxandra - Grupa 141
#include <iostream>
#include <fstream>
#define NMAX 20
using namespace std;
fstream f("arbore.in", ios :: in);

class Arbore {
    int nr_noduri;
    int rad;
    int h;
    int mat_adiacenta[NMAX][NMAX];
    int M[NMAX][NMAX];
    int frunze[NMAX], k = 0;
    int coada[NMAX]; /// folosita la parcurgerea pe niveluri
    int stiva[NMAX]; /// folosita la parcurgerea in adancime


public :
    Arbore(){nr_noduri = 0;h = 0;rad = 0;}; /// constructorul de initializare
    Arbore& (Arbore aux){ /// constructor de copiere
        this -> nr_noduri = aux.nr_noduri;
        this -> rad = aux.rad;
        this -> h = aux.h;
        for(int i = 1;i <= aux.nr_noduri; i++)
        for(int j = 1; j<= aux.nr_noduri; j++)
            this -> mat_adiacenta[i][j] = aux.mat_adiacenta[i][j];
        for(int i = 1;i <= aux.nr_noduri; i++)
            this -> frunze[i] = aux.funze[i];
        return *this;
    };
    ~Arbore(){nr_noduri = 0;h = 0;rad = 0;}; /// destructorul
    void creare_mat_adiacenta(); /// metoda care citeste matricea de adiacenta a arborelui din fisier
    void parcurgere_niveluri(); /// metoda care parcurge in latime/pe niveluri arborele
    void afisare_BFS(); /// metoda care afiseaza parcurgerea pe niveluri
    void parcurgere_adancime(); /// metoda care parcurge in adancime arborele
    void afisare_DFS(); /// metoda care afiseaza parcurgerea in adancime
    void inaltime_arbore(); /// metoda care calculeaza si afiseaza inaltimea arborelui
    friend void afisare_frunze(Arbore B); /// metoda care afiseaza frunzele arborelui
    Arbore& operator --(int a) /// operator de decrementare prefixat
    {
        --rad; ///decrementarea valorii radacinii arborelui
    };
    Arbore& operator --() /// operator de decrementare postfixat
    {
        rad--; ///decrementarea valorii radacinii arborelui
    };
    Arbore& operator !=(Arbore& aux)
    {
        if(this -> rad != aux.rad)
           return true;
        return false;
    };

};

void Arbore :: creare_mat_adiacenta(){
    f>>nr_noduri;
    f>>rad;

    for(int i = 1;i <= nr_noduri; i++)
        for(int j = 1;j <= nr_noduri; j++)
            f>>mat_adiacenta[i][j];
}

void Arbore :: parcurgere_niveluri() {
  bool viz[NMAX]; /// tablou de elemente de tip bool care retine daca un nod a fost sau nu vizitat
  int prim, ultim, lin;

  for(int i = 1;i <= nr_noduri; i++)
      viz[i] = false; /// initial toate nodurile sunt nevizitate

  coada[1] = rad; /// se adauga in coada radacina arborelui
  viz[rad] = true; /// si se marcheaza ca fiind vizitata
  ultim = 1;
  prim = 1;

  while(prim <= ultim)
   { lin = coada[prim]; /// se retine parintele in coada
     for(int j = 1;j <= nr_noduri; j++) /// si apoi se adauga in coada fii lui lin
        if((mat_adiacenta[lin][j] == 1) && (viz[j] == false))
            {
                coada[++ultim] = j;
                viz[j] = true; /// si se marcheaza ca fiind vizitati
            }
     ++prim;
   }
}

void Arbore :: afisare_BFS(){
    cout<<"Parcurgerea pe niveluri : ";
    for(int i = 1;i <= nr_noduri; i++)
        cout<<coada[i]<<" ";
    cout<<'\n';
}

void Arbore :: parcurgere_adancime(){
  bool viz[NMAX]; /// tablou de elemente de tip bool care retine daca un nod a fost sau nu vizitat
  int prim, ultim, lin;

  for(int j = 1;j <= nr_noduri; j++)
      viz[j] = false; /// initial toate nodurile sunt nevizitate

  prim = 1;
  ultim = 1;
  stiva[1] = rad; /// se adauga in stiva radacina arborelui
  viz[rad] = true; /// si se marcheaza ca fiind vizitata
  while (prim > 0)
  {
      lin = stiva[prim]; /// se retine parintele in stiva
      int j = 1;
      while(j <= nr_noduri) /// si apoi se adauga in stiva fii lui lin
	  {
	      if(mat_adiacenta[lin][j] == 0 || viz[j] == true)
            j++;
	      else
	      {
            stiva[++ultim] = j;
		    viz[j] = true; /// si se marcheaza ca fiind vizitati
		    prim = ultim + 1;
		    j = nr_noduri + 1;
          }
	  }
      prim --;
   }
}

void Arbore :: afisare_DFS(){
    cout<<"Parcurgerea in adancime : ";
    for(int i = 1;i <= nr_noduri; i++)
        cout<<stiva[i]<<" ";
    cout<<'\n';
}

void Arbore :: inaltime_arbore(){
  int c[NMAX]; /// coada in care se vor pune nodurile arborelui in timpul parcurgerii pe nivele
  int vizit[NMAX]; /// tablou care retine pe ce nivel au fost vizitate nodurile
  int prim, ultim, lin;

  for(int i = 1;i <= nr_noduri; i++)
      vizit[i] = 0; /// initial toate nodurile sunt nevizitate

  c[1] = rad; /// se adauga in coada radacina arborelui
  vizit[rad] = 1; /// si se viziteaza pe nivelul 1
  ultim = 1;
  prim = 1;

  while(prim <= ultim) /// se realizeaza parcurgerea pe nivele a arborelui
   { lin = c[prim];
     for(int j = 1;j <= nr_noduri; j++)
        if((mat_adiacenta[lin][j] == 1) && (vizit[j] == 0))
            {
                c[++ultim] = j;
                vizit[j] = vizit[lin] + 1; /// iar elementele tabloului vizit primesc valoarea nivelului
            }                              /// pe care nodurile au fost parcurse
     ++prim;

   }
   h = vizit[nr_noduri] - 1; /// inaltimea arborelui este = cu nivelul pe care a fost vizitat ultimul nod - 1
   cout<<"Inaltimea arborelui : "<<h<<'\n';
}

void afisare_frunze(Arbore B){
    for(int i = 1;i <= B.nr_noduri; i++) /// se construieste o matrice auxiliara M care va retine
    for(int j = 1;j <= B.nr_noduri; j++) /// doar partea de deasupra diagonalei principale
        if(j > i && B.mat_adiacenta[i][j] == 1) /// a matricei de adiacenta
           B.M[i][j] = B.mat_adiacenta[i][j];
        else
           B.M[i][j] = 0;

    for(int i = 1;i <= B.nr_noduri; i++) /// aceasta amtrice va fi folosita in locul unu vector de tati
        {
            bool ok = false; /// se va parcurge matricea si numarul acelor linii care nu contin niciun 1
            for(int j = 1;j <= B.nr_noduri && ok == false; j++)
                if(B.M[i][j] == 1)
                   ok = true;
            if(ok == false) /// vor fi considerate valorile nodurilor frunza
               B.frunze[++B.k] = i; /// si vor fi adaugate in tabloul frunze
        }

    cout<<"Frunzele arborelui : ";

    for(int i = 1;i <= B.k; i++)
        cout<<B.frunze[i]<<" ";

    cout<<'\n';
}

int main()
{
    Arbore A; /// se creeaza un obiect de tipul clasei Arbore
              ///si se apeleaza pentru acest obiect metodele clasei

    A.creare_mat_adiacenta();

    A.parcurgere_niveluri();

    A.afisare_BFS();

    A.parcurgere_adancime();

    A.afisare_DFS();

    A.inaltime_arbore();

    afisare_frunze(A);

    f.close();

    return 0;
}
