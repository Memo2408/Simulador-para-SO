#include "../src/simulador.h"

struct MemoriaFalsa : Memoria {
    bool colocar(Proceso*) override { return true; }
    void descargar(int) override {}
    bool condensar() override { return false; }
    std::vector<std::string> eventos() override { return {}; }
    std::string imprimir() override { return "[mem]"; }
};

int main() {
    MemoriaFalsa memoria;
    Generador generador({{1, 10, 5}, {2, 10, 3}});
    Simulador simulador(memoria, generador, 2);
    for (int i = 0; i < 5; ++i) {
        simulador.ciclo();
    }
}
