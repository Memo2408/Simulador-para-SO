#pragma once
#include <deque>
#include "memoria.h"
#include "generador.h"
class Simulador {
public:
    Simulador(Memoria& memoria, Generador& generador, int cuantoSistema);
    void correr();
    void ciclo();
    void agregar(Proceso* p);
    void ponerPausa(int milisegundos);
private:
    Memoria& memoria;
    Generador& generador;
    int cuantoSistema;
    int pausa = 500;
    std::deque<Proceso*> lista;
    Proceso* listo = nullptr;
};