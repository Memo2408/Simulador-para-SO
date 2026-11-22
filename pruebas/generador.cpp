#include <iostream>
#include "../src/generador.h"

int main() {
    bool ok6 = true;
    Generador azar(10, 5);
    for (int i = 1; i <= 1000; i++) {
        Proceso* p = azar.siguiente();
        if (p == nullptr || p->id != i || p->tamano < 1 || p->tamano > 10 || p->cuanto < 1 || p->cuanto > 5) {
            ok6 = false;
        }
        delete p;
    }
    std::cout << (ok6 ? "OK    Prueba 6\n" : "FALLA Prueba 6\n");

    Generador lista({{6, 256, 10}, {7, 384, 7}, {8, 200, 4}});
    Proceso* a = lista.siguiente();
    Proceso* b = lista.siguiente();
    Proceso* c = lista.siguiente();
    Proceso* d = lista.siguiente();
    bool ok7 = a && b && c && !d
        && a->id == 6 && a->tamano == 256 && a->cuanto == 10
        && b->id == 7 && b->tamano == 384 && b->cuanto == 7
        && c->id == 8 && c->tamano == 200 && c->cuanto == 4;
    std::cout << (ok7 ? "OK    Prueba 7\n" : "FALLA Prueba 7\n");
    delete a;
    delete b;
    delete c;
    return ok6 && ok7 ? 0 : 1;
}
