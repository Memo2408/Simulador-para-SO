#pragma once
#include "memoria.h"
class PrimerAjuste : public Memoria {
public:
    PrimerAjuste(int memoriaKB);
    bool colocar(Proceso* p) override;
    void descargar(int id) override;
    bool condensar() override;
    std::vector<std::string> eventos() override;
    std::string imprimir() override;
private:
    struct Bloque {
        int tamano;
        Proceso* proceso;
    };

    std::vector<Bloque> bloques;
    std::vector<std::string> avisos;
};
