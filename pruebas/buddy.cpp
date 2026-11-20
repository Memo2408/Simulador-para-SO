#include "../src/buddy.h"

#include <iostream>
#include <string>
#include <vector>

static int fallas = 0;

static void revisar(bool ok, int prueba, const std::string& esperado = "",
                   const std::string& obtenido = "") {
    std::cout << (ok ? "OK    Prueba " : "FALLA Prueba ") << prueba << '\n';
    if (!ok) {
        std::cout << "  Esperado: " << esperado << '\n'
                  << "  Obtenido: " << obtenido << '\n';
        ++fallas;
    }
}

static bool eventosIguales(const std::vector<std::string>& obtenidos,
                           const std::vector<std::string>& esperados) {
    return obtenidos == esperados;
}

int main() {
    {
        Buddy memoria(4096);
        Proceso* p = new Proceso{1, 300, 10};
        const bool colocado = memoria.colocar(p);
        const std::string esperado =
            "@0[1,300,10|512] @512[0,512,0] @1024[0,1024,0] @2048[0,2048,0]";
        bool ok = colocado && memoria.imprimir() == esperado;

        const std::vector<std::string> eventosEsperados = {
            "Partiendo bloque @0 de 4096 en 2048 + 2048",
            "Partiendo bloque @0 de 2048 en 1024 + 1024",
            "Partiendo bloque @0 de 1024 en 512 + 512"};
        ok = eventosIguales(memoria.eventos(), eventosEsperados) && ok;
        ok = memoria.eventos().empty() && ok;
        revisar(ok, 1, esperado + " y avisos de partida en orden",
                memoria.imprimir());
        delete p;
    }

    {
        Buddy memoria(1024);
        Proceso* p = new Proceso{2, 10, 3};
        const bool colocado = memoria.colocar(p);
        const std::string esperado =
            "@0[2,10,3|32] @32[0,32,0] @64[0,64,0] @128[0,128,0] "
            "@256[0,256,0] @512[0,512,0]";
        bool ok = colocado && memoria.imprimir() == esperado;

        p->cuanto = 1;
        const std::string conCuantoActualizado =
            "@0[2,10,1|32] @32[0,32,0] @64[0,64,0] @128[0,128,0] "
            "@256[0,256,0] @512[0,512,0]";
        ok = memoria.imprimir() == conCuantoActualizado && ok;
        revisar(ok, 2, conCuantoActualizado, memoria.imprimir());
        delete p;
    }

    {
        Buddy memoria(1024);
        Proceso* a = new Proceso{1, 100, 1};
        Proceso* b = new Proceso{2, 240, 1};
        Proceso* c = new Proceso{3, 64, 1};
        Proceso* d = new Proceso{4, 256, 1};
        const bool colocados = memoria.colocar(a) && memoria.colocar(b) &&
                               memoria.colocar(c) && memoria.colocar(d);
        const std::string esperado =
            "@0[1,100,1|128] @128[3,64,1|64] @192[0,64,0] "
            "@256[2,240,1|256] @512[4,256,1|256] @768[0,256,0]";
        revisar(colocados && memoria.imprimir() == esperado, 3, esperado,
                memoria.imprimir());
        delete a;
        delete b;
        delete c;
        delete d;
    }

    {
        Buddy memoria(1024);
        Proceso* procesos[4] = {
            new Proceso{1, 256, 1}, new Proceso{2, 256, 1},
            new Proceso{3, 256, 1}, new Proceso{4, 256, 1}};
        bool colocados = true;
        for (Proceso* p : procesos) {
            colocados = memoria.colocar(p) && colocados;
        }
        const std::string lleno =
            "@0[1,256,1|256] @256[2,256,1|256] "
            "@512[3,256,1|256] @768[4,256,1|256]";
        bool ok = colocados && memoria.imprimir() == lleno;

        Proceso* grande = new Proceso{5, 600, 1};
        memoria.eventos();
        const std::string antes = memoria.imprimir();
        const bool rechazo = !memoria.colocar(grande) && memoria.imprimir() == antes;
        ok = rechazo && memoria.eventos().empty() && ok;
        revisar(ok, 4, lleno + " y rechazo sin cambios ni avisos",
                memoria.imprimir());
        delete grande;
        for (Proceso* p : procesos) {
            delete p;
        }
    }

    {
        Buddy memoria(1024);
        Proceso* a = new Proceso{1, 100, 1};
        Proceso* b = new Proceso{2, 100, 1};
        bool ok = memoria.colocar(a) && memoria.colocar(b);
        memoria.eventos();

        memoria.descargar(1);
        memoria.descargar(2);
        const std::string antes =
            "@0[0,128,0] @128[0,128,0] @256[0,256,0] @512[0,512,0]";
        ok = memoria.imprimir() == antes && ok;
        ok = memoria.condensar() && ok;

        const std::vector<std::string> eventosEsperados = {
            "Condensando huecos",
            "Uniendo compañeros @0 + @128 = 256",
            "Uniendo compañeros @0 + @256 = 512",
            "Uniendo compañeros @0 + @512 = 1024"};
        ok = eventosIguales(memoria.eventos(), eventosEsperados) && ok;

        const std::string despues = "@0[0,1024,0]";
        ok = memoria.imprimir() == despues && ok;
        ok = !memoria.condensar() && ok;
        memoria.descargar(999);
        ok = memoria.imprimir() == despues && ok;

        revisar(ok, 5, despues + " tras liberar y unir hasta el bloque mayor",
                memoria.imprimir());
        delete a;
        delete b;
    }

    std::cout << (fallas == 0 ? "Todo bien\n" : "Hay fallas\n");
    return fallas == 0 ? 0 : 1;
}
