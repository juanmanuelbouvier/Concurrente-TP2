
#ifndef GESTOR_BDD_BUSCADOR_H
#define GESTOR_BDD_BUSCADOR_H


#include <vector>
#include "ipc/SharedLockFile.h"
#include "Persona.h"

using namespace std;

class Buscador {

public:
    Buscador();
    ~Buscador();
    vector<Persona> buscar(Persona filtros);

};


#endif //GESTOR_BDD_BUSCADOR_H
