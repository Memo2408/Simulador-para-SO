#include "primer_ajuste.h"

PrimerAjuste::PrimerAjuste(int memoriaKB) {
    bloques.push_back({memoriaKB, nullptr});
}

bool PrimerAjuste::colocar(Proceso* p) {
    if (p == nullptr) {
        return false;
    }
    for (std::size_t i = 0; i < bloques.size(); i++) {
        if (bloques[i].proceso == nullptr && bloques[i].tamano >= p->tamano) {
            int sobra = bloques[i].tamano - p->tamano;
            bloques[i] = {p->tamano, p};
            if (sobra > 0) {
                bloques.insert(bloques.begin() + i + 1, Bloque{sobra, nullptr});
            }
            return true;
        }
    }
    return false;
}

void PrimerAjuste::descargar(int id) {
    for (Bloque& b : bloques) {
        if (b.proceso != nullptr && b.proceso->id == id) {
            b.proceso = nullptr;
            return;
        }
    }
}

bool PrimerAjuste::condensar() {
    bool unio = false;
    std::size_t i = 0;
    while (i + 1 < bloques.size()) {
        if (bloques[i].proceso == nullptr && bloques[i + 1].proceso == nullptr) {
            bloques[i].tamano += bloques[i + 1].tamano;
            bloques.erase(bloques.begin() + i + 1);
            unio = true;
        } else {
            i++;
        }
    }
    if (unio) {
        avisos.push_back("Condensando huecos");
    }
    return unio;
}

std::vector<std::string> PrimerAjuste::eventos() {
    std::vector<std::string> pendientes = avisos;
    avisos.clear();
    return pendientes;
}

std::string PrimerAjuste::imprimir() {
    std::string texto;
    for (const Bloque& b : bloques) {
        if (b.proceso != nullptr) {
            texto += "[" + std::to_string(b.proceso->id) + "," + std::to_string(b.proceso->tamano) + ","
                   + std::to_string(b.proceso->cuanto) + "]";
        } else {
            texto += "[0," + std::to_string(b.tamano) + ",0]";
        }
    }
    return texto;
}
