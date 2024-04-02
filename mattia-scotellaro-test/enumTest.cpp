#include <iostream>
using namespace std;

enum class Color {red, blue, green};
enum class Traffic_light {green, yellow, red};

Color col = Color::red;
Traffic_light light = Traffic_light::green;

 // sovraccaricamento dell'operatore ++ come pre-incremento
Traffic_light& operator++(Traffic_light& t){
    switch (t)
    {
    case Traffic_light::green: return t=Traffic_light::yellow;
        break;

    case Traffic_light::yellow: return t=Traffic_light::red;
        break;

    case Traffic_light::red: return t=Traffic_light::green;
        break;
    
    default:
        break;
    }
};
 // sovraccaricamento dell'operatore ++ come post-incremento
Traffic_light operator++(Traffic_light& t, int) {
    Traffic_light temp = t;  // Salva il valore corrente di t
    ++t;                     // Incrementa il valore di t utilizzando l'operatore di pre-incremento
    return temp;             // Restituisce il valore salvato prima dell'incremento
}

int main(){
    cout << static_cast<int>(light++) << "\n";
    cout << static_cast<int>(light) << "\n";
    cout << static_cast<int>(++light) << "\n";

    return 0;
};