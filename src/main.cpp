#ifdef _WIN32
#include <windows.h>
#endif
#include "memoria.h"
#include "generador.h"
#include "primer_ajuste.h"
#include "buddy.h"
#include "simulador.h"
#include "menu.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Configuracion c = pedirConfiguracion();
    Memoria* memoria = nullptr;
    if (c.algoritmo == 1) {
        memoria = new PrimerAjuste(c.memoriaKB);
    } else {
        memoria = new Buddy(c.memoriaKB);
    }
    Generador generador(c.maxTamano, c.maxCuanto);
    Simulador simulador(*memoria, generador, c.cuantoSistema);
    simulador.ponerPausa(c.pausa);
    simulador.correr();
    delete memoria;
    return 0;
}
