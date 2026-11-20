#include "../src/generador.h"

Generador::Generador(int, int) {}

Generador::Generador(std::vector<Proceso> lista) : fijos(lista) {}

Proceso* Generador::siguiente() {
    if (pos < fijos.size()) {
        return new Proceso(fijos[pos++]);
    }
    return nullptr;
}
