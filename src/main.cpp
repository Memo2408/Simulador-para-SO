#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include "proceso.h"
#include "memoria.h"
#include "generador.h"
#include "primer_ajuste.h"
#include "buddy.h"
#include "simulador.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::cout << "Simulador de memoria y Round Robin - Equipo 5\n";
    std::cout << "Esqueleto: faltan el menú y las partes de cada quien.\n";
    return 0;
}
