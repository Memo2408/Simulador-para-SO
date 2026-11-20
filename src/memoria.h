#pragma once
#include <string>
#include <vector>
#include "proceso.h"
class Memoria {
public:
    virtual bool colocar(Proceso* p) = 0;
    virtual void descargar(int id) = 0;
    virtual bool condensar() = 0;
    virtual std::vector<std::string> eventos() = 0;
    virtual std::string imprimir() = 0;
    virtual ~Memoria() {}
};
