#include <iostream>
#include <string>
using namespace std;

struct Cliente{
    string nome;
    int numero;
};

// creo una stampa customizzata per il tipo definito da me
ostream& operator<<(ostream& os, const Cliente& e){
    return os << "{\"" << e.nome << "\"," << e.numero << "}";
}

// creo un inserimento di dati personalizzato per il tipo definito da me
// in questo caso è molto semplice ma si potrebbe rendere molto più complesso e di conseguenza completo
istream& operator>>(istream& is, Cliente& e){
    cout << "Inserisci il nome: ";
    cin >> e.nome;

    cout << "Inserisci il numero: ";
    cin >> e.numero;

    // è fondamentale fare il return dello stream per far si che le modifiche vengano apportate correttamente
    return is;
}

int main(){
    Cliente c;

    cin >> c;

    cout << c;
}