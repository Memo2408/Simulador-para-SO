#pragma once
#include "memoria.h"
class Buddy : public Memoria {
public:
    Buddy(int memoriaKB);
    bool colocar(Proceso* p) override;
    void descargar(int id) override;
    bool condensar() override;
    std::vector<std::string> eventos() override;
    std::string imprimir() override;
private:
};
