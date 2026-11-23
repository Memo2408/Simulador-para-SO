#include "simulador.h"

#include <algorithm>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <chrono>
#include <thread>
#endif

Simulador::Simulador(Memoria& m, Generador& g, int c)
    : memoria(m), generador(g), cuantoSistema(c) {}

void Simulador::agregar(Proceso* p) {
    lista.push_back(p);
}

void Simulador::ciclo() {
    if (listo == nullptr) {
        listo = generador.siguiente();
    }

    if (listo != nullptr) {
        if (memoria.colocar(listo)) {
            std::cout << "Entra Proceso [" << listo->id << ',' << listo->tamano
                      << ',' << listo->cuanto << "]\n";
            for (const std::string& evento : memoria.eventos()) {
                std::cout << evento << '\n';
            }
            std::cout << memoria.imprimir() << '\n';
            lista.push_back(listo);
            listo = nullptr;
        }
    }

    if (lista.empty()) {
        std::cout << '\n';
        return;
    }

    Proceso* p = lista.front();
    lista.pop_front();
    std::cout << "Atendiendo proceso [" << p->id << ',' << p->tamano << ','
              << p->cuanto << "]\n";

    p->cuanto -= std::min(cuantoSistema, p->cuanto);
    if (p->cuanto > 0) {
        lista.push_back(p);
    }

    std::cout << "Lista RR";
    for (const Proceso* proceso : lista) {
        std::cout << " [" << proceso->id << ',' << proceso->tamano << ','
                  << proceso->cuanto << ']';
    }
    std::cout << '\n';

    if (p->cuanto == 0) {
        std::cout << "Descargando proceso [" << p->id << ',' << p->tamano
                  << ",0]\n";
        memoria.descargar(p->id);
        std::cout << memoria.imprimir() << '\n';
        if (memoria.condensar()) {
            for (const std::string& evento : memoria.eventos()) {
                std::cout << evento << '\n';
            }
            std::cout << memoria.imprimir() << '\n';
        }
        delete p;
    } else {
        std::cout << memoria.imprimir() << '\n';
    }

    std::cout << '\n';
}

void Simulador::ponerPausa(int milisegundos) {
    pausa = milisegundos;
}

void Simulador::correr() {
    std::cout << memoria.imprimir() << "\n\n";

    while (true) {
        ciclo();
#ifdef _WIN32
        Sleep(pausa);
        if (_kbhit()) {
            const int tecla = _getch();
            if (tecla == 0 || tecla == 224) {
                _getch();
            } else if (tecla == 's' || tecla == 'S') {
                break;
            } else if (tecla == '+' && pausa > 100) {
                pausa -= 100;
            } else if (tecla == '-' && pausa < 2000) {
                pausa += 100;
            }
        }
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(pausa));
#endif
    }

    while (!lista.empty()) {
        Proceso* p = lista.front();
        lista.pop_front();
        memoria.descargar(p->id);
        delete p;
    }
    if (listo != nullptr) {
        delete listo;
        listo = nullptr;
    }
}