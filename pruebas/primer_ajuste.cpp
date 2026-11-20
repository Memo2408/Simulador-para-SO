#include <iostream>
#include <string>
#include <vector>
#include "../src/primer_ajuste.h"

static int fallas = 0;
static std::vector<std::string> detalles;
static std::vector<Proceso*> creados;

static Proceso* nuevo(int id, int tamano, int cuanto) {
    Proceso* p = new Proceso{id, tamano, cuanto};
    creados.push_back(p);
    return p;
}

static void comprobar(bool ok, const std::string& que) {
    if (!ok) detalles.push_back(que);
}

static void comparar(const std::string& salio, const std::string& esperado, const std::string& que) {
    if (salio != esperado) {
        detalles.push_back(que + "\n        esperado: " + esperado + "\n        salio:    " + salio);
    }
}

static void terminar(int numero) {
    std::cout << (detalles.empty() ? "OK    " : "FALLA ") << "Prueba " << numero << "\n";
    for (const std::string& d : detalles) std::cout << "      " << d << "\n";
    if (!detalles.empty()) ++fallas;
    detalles.clear();
}

int main() {
    PrimerAjuste memoria(4096);

    comprobar(memoria.colocar(nuevo(1, 300, 2)), "colocar [1,300,2] regresa true");
    comprobar(memoria.colocar(nuevo(2, 96, 1)), "colocar [2,96,1] regresa true");
    comprobar(memoria.colocar(nuevo(5, 500, 9)), "colocar [5,500,9] regresa true");
    comparar(memoria.imprimir(), "[1,300,2][2,96,1][5,500,9][0,3200,0]", "despues de colocar 1, 2 y 5");
    memoria.descargar(2);
    comparar(memoria.imprimir(), "[1,300,2][0,96,0][5,500,9][0,3200,0]", "despues de descargar(2)");
    comprobar(!memoria.condensar(), "condensar() regresa false");
    terminar(1);

    Proceso* p6 = nuevo(6, 256, 10);
    comprobar(memoria.colocar(p6), "colocar [6,256,10] regresa true");
    comparar(memoria.imprimir(), "[1,300,2][0,96,0][5,500,9][6,256,10][0,2944,0]", "despues de colocar 6");
    terminar(2);

    memoria.descargar(1);
    comprobar(memoria.condensar(), "condensar() regresa true");
    comparar(memoria.imprimir(), "[0,396,0][5,500,9][6,256,10][0,2944,0]", "despues de descargar(1) y condensar()");
    std::vector<std::string> avisos = memoria.eventos();
    comprobar(avisos.size() == 1 && avisos[0] == "Condensando huecos", "eventos() trae solo \"Condensando huecos\"");
    comprobar(memoria.eventos().empty(), "eventos() viene vacio la segunda vez");
    terminar(3);

    comprobar(memoria.colocar(nuevo(8, 200, 4)), "colocar [8,200,4] regresa true");
    comparar(memoria.imprimir(), "[8,200,4][0,196,0][5,500,9][6,256,10][0,2944,0]", "despues de colocar 8");
    terminar(4);

    comprobar(memoria.colocar(nuevo(9, 196, 3)), "colocar [9,196,3] regresa true");
    comparar(memoria.imprimir(), "[8,200,4][9,196,3][5,500,9][6,256,10][0,2944,0]", "despues de colocar 9");
    comprobar(memoria.colocar(nuevo(10, 2944, 1)), "colocar [10,2944,1] regresa true");
    comparar(memoria.imprimir(), "[8,200,4][9,196,3][5,500,9][6,256,10][10,2944,1]", "despues de colocar 10");
    comprobar(!memoria.colocar(nuevo(11, 1, 1)), "colocar [11,1,1] regresa false");
    comparar(memoria.imprimir(), "[8,200,4][9,196,3][5,500,9][6,256,10][10,2944,1]", "la memoria no cambia");
    comprobar(memoria.eventos().empty(), "eventos() viene vacio");
    p6->cuanto = 7;
    comparar(memoria.imprimir(), "[8,200,4][9,196,3][5,500,9][6,256,7][10,2944,1]", "cuanto del 6 cambiado a 7");
    terminar(5);

    for (Proceso* p : creados) delete p;
    std::cout << (fallas ? "Hay fallas\n" : "Todo bien\n");
    return fallas ? 1 : 0;
}
