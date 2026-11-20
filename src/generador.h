#pragma once
#include <cstddef>
#include <vector>
#include "proceso.h"
class Generador {
public:
    Generador(int maxTamano, int maxCuanto);
    Generador(std::vector<Proceso> fijos);
    Proceso* siguiente();
private:
    int maxTamano = 0, maxCuanto = 0, siguienteId = 1;
    std::vector<Proceso> fijos;
    std::size_t pos = 0;
};
