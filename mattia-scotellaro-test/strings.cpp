#include <iostream>
#include <string>
using namespace std;

string compose(const string& name, const string& domain){
    return name + '@' + domain;
}

int main(){
    // auto riconosce automaticamente il tipo da assegnare alla variabile
    // al momento della sua inizializzazione
    auto addr=compose("anna.corazza","unina.it");

    cout << addr;

    return 0;
}