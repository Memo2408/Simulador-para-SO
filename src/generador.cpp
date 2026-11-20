#include <random>
#include <stdexcept>
#include <utility>
#include "generador.h"

static std::mt19937 azar(std::random_device{}());

Generador::Generador(int maxTamano, int maxCuanto)
    : maxTamano(maxTamano), maxCuanto(maxCuanto) {
    if (maxTamano < 1 || maxCuanto < 1) {
        throw std::invalid_argument("Los limites de tamano y cuanto deben ser positivos.");
    }
}

Generador::Generador(std::vector<Proceso> fijos)
    : fijos(std::move(fijos)) {}

Proceso* Generador::siguiente() {
    if (maxTamano == 0) {
        if (pos == fijos.size()) {
            return nullptr;
        }
        return new Proceso(fijos[pos++]);
    }

    std::uniform_int_distribution<int> tamano(1, maxTamano);
    std::uniform_int_distribution<int> cuanto(1, maxCuanto);
    return new Proceso{siguienteId++, tamano(azar), cuanto(azar)};
}
