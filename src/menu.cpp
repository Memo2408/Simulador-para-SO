#include "menu.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

static int pedirNumero(const std::string& texto, int minimo, int maximo) {
    while (true) {
        std::cout << texto;
        std::string linea;
        if (!std::getline(std::cin, linea)) {
            std::exit(1);
        }
        try {
            std::size_t usados = 0;
            int n = std::stoi(linea, &usados);
            if (usados == linea.size() && n >= minimo && n <= maximo) {
                return n;
            }
        } catch (...) {
        }
        std::cout << "Dato no válido.\n";
    }
}

Configuracion pedirConfiguracion() {
    const int sinLimite = std::numeric_limits<int>::max();
    Configuracion c;
    c.algoritmo = pedirNumero("Algoritmo de colocación (1 = Primer Ajuste, 2 = Buddy System): ", 1, 2);
    int mb = pedirNumero("Tamaño de la memoria (1, 4 u 8 MB): ", 1, 8);
    while (mb != 1 && mb != 4 && mb != 8) {
        std::cout << "Dato no válido.\n";
        mb = pedirNumero("Tamaño de la memoria (1, 4 u 8 MB): ", 1, 8);
    }
    c.memoriaKB = mb * 1024;
    c.cuantoSistema = pedirNumero("Cuanto (quantum) de procesamiento asignado a cada proceso (cuanto del sistema): ", 1, sinLimite);
    c.maxTamano = pedirNumero("Tamaño máximo de memoria de proceso (KB): ", 1, c.memoriaKB);
    c.maxCuanto = pedirNumero("Tamaño máximo del cuanto de procesamiento por proceso: ", 1, sinLimite);
    int velocidad = pedirNumero("Velocidad de la simulación (1 = lenta, 2 = normal, 3 = rápida; con + y - se cambia y con S se termina): ", 1, 3);
    if (velocidad == 1) {
        c.pausa = 1000;
    } else if (velocidad == 2) {
        c.pausa = 500;
    } else {
        c.pausa = 200;
    }
    std::cout << '\n';
    return c;
}
