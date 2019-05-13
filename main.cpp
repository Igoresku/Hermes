#include <iostream>
#include <string>
#include <fstream>
#include "include/Game_Map.h"
#include "include/Agent.h"

int main() {
    int komanda;

    do {
        std::cout << "----------------------------";
        std::cout << "Unesite komandu\n";

        std::cout << "(0) Izlazak iz programa\n";
        std::cout << "(1) Generisanje random mape\n";
        std::cout << "(2) Unosenje fajla koji sadrzi mapu\n";
        std::cout << "";

        std::cout << "() Objasnjenje formata mape";

        std::cin >> komanda;
        switch (komanda) {
            case 1: {

                break;
            }

            case 2: {
                break;
            }

            default: {
                break;
            }

        } // switch : komanda
    } while (komanda != 0);
}