#include <iostream>
using namespace std;

class Vector{
    public:
        // metodo costruttore, dopo i : vengono inizializzate le variabili, un po' come i this in java
        // in questo caso il corpo effettivo del costruttore è vuoto
        Vector(int s) :elem{new double[s]}, sz{s}{}

        // facciamo un overloading dell'operatore [] in modo che restituisca il valore contenuto in elem all'indice specificato
        double& operator[](int i) {return elem[i];}
        int size() {return sz;}
    
    private:
        // array dinamico di double
        double* elem;
        int sz;
};

double read_and_sum(int s){
    Vector v(s);

    for (int i = 0; i < s; i++)
        cin >> v[i];

    double sum = 0;

    for (int i = 0; i < s; i++)
        sum += v[i];

    return sum;
}

int main(){
    cout << read_and_sum(5);

    return 0;
}