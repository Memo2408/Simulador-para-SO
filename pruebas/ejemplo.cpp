#include <iostream>
#include <string>
#include "../src/proceso.h"

static int fallas = 0;

static void revisar(bool ok, const std::string& que) {
    std::cout << (ok ? "OK    " : "FALLA ") << que << "\n";
    if (!ok) ++fallas;
}

int main() {
    Proceso p{1, 300, 10};
    revisar(p.id == 1 && p.tamano == 300 && p.cuanto == 10, "Proceso [1,300,10]");
    std::cout << (fallas ? "Hay fallas\n" : "Todo bien\n");
    return fallas ? 1 : 0;
}
