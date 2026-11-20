#include "buddy.h"

#include <sstream>

const int MINIMO = 32;

Buddy::Buddy(int memoriaKB) : memoriaKB(memoriaKB) {
    bloques.push_back({0, memoriaKB, nullptr});
}

bool Buddy::colocar(Proceso* p) {
    if (p == nullptr || p->tamano <= 0) {
        return false;
    }

    int necesario = MINIMO;
    while (necesario < p->tamano) {
        if (necesario > memoriaKB / 2) {
            return false;
        }
        necesario *= 2;
    }
    if (necesario > memoriaKB) {
        return false;
    }

    while (true) {
        int candidato = -1;
        for (std::size_t i = 0; i < bloques.size(); ++i) {
            const Bloque& bloque = bloques[i];
            if (bloque.proceso != nullptr || bloque.tamano < necesario) {
                continue;
            }
            if (candidato == -1 ||
                bloque.tamano < bloques[candidato].tamano ||
                (bloque.tamano == bloques[candidato].tamano &&
                 bloque.inicio < bloques[candidato].inicio)) {
                candidato = static_cast<int>(i);
            }
        }

        if (candidato == -1) {
            return false;
        }

        Bloque& bloque = bloques[candidato];
        if (bloque.tamano == necesario) {
            bloque.proceso = p;
            return true;
        }

        const int mitad = bloque.tamano / 2;
        std::ostringstream aviso;
        aviso << "Partiendo bloque @" << bloque.inicio << " de "
              << bloque.tamano << " en " << mitad << " + " << mitad;
        avisos.push_back(aviso.str());

        const Bloque derecha{bloque.inicio + mitad, mitad, nullptr};
        bloques[candidato].tamano = mitad;
        bloques.insert(bloques.begin() + candidato + 1, derecha);
    }
}

void Buddy::descargar(int id) {
    for (Bloque& bloque : bloques) {
        if (bloque.proceso != nullptr && bloque.proceso->id == id) {
            bloque.proceso = nullptr;
            return;
        }
    }
}

bool Buddy::condensar() {
    bool unido = false;

    bool huboUnion = true;
    bool avisoInicioAgregado = false;
    while (huboUnion) {
        huboUnion = false;
        for (std::size_t i = 0; i + 1 < bloques.size(); ++i) {
            const Bloque& izquierda = bloques[i];
            const Bloque& derecha = bloques[i + 1];
            if (izquierda.proceso != nullptr || derecha.proceso != nullptr ||
                izquierda.tamano != derecha.tamano ||
                izquierda.inicio + izquierda.tamano != derecha.inicio ||
                izquierda.inicio % (izquierda.tamano * 2) != 0) {
                continue;
            }

            if (!avisoInicioAgregado) {
                avisos.push_back("Condensando huecos");
                avisoInicioAgregado = true;
            }
            std::ostringstream aviso;
            aviso << "Uniendo compañeros @" << izquierda.inicio << " + @"
                  << derecha.inicio << " = " << izquierda.tamano * 2;
            avisos.push_back(aviso.str());

            bloques[i].tamano *= 2;
            bloques.erase(bloques.begin() + i + 1);
            huboUnion = true;
            unido = true;
            break;
        }
    }
    return unido;
}

std::vector<std::string> Buddy::eventos() {
    std::vector<std::string> pendientes;
    pendientes.swap(avisos);
    return pendientes;
}

std::string Buddy::imprimir() {
    std::ostringstream salida;
    for (std::size_t i = 0; i < bloques.size(); ++i) {
        if (i > 0) {
            salida << ' ';
        }

        const Bloque& bloque = bloques[i];
        salida << '@' << bloque.inicio << '[';
        if (bloque.proceso == nullptr) {
            salida << "0," << bloque.tamano << ",0]";
        } else {
            salida << bloque.proceso->id << ',' << bloque.proceso->tamano << ','
                   << bloque.proceso->cuanto << '|' << bloque.tamano << ']';
        }
    }
    return salida.str();
}
