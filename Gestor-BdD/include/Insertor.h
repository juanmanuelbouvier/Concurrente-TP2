
#ifndef GESTOR_BDD_INSERTOR_H
#define GESTOR_BDD_INSERTOR_H

#include <iostream>
#include "Persona.h"

using namespace std;

class Insertor {

public:
    Insertor();
    ~Insertor();
    void insertar (Persona nuevoRegistro);

private:
    int crearDirectorioSiNoExiste(string rutaCompletaArchivo);

};


#endif //GESTOR_BDD_INSERTOR_H
