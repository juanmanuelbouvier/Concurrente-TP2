
#ifndef CLIENTE_BDD_BDD_H
#define CLIENTE_BDD_BDD_H


#include <vector>
#include "ipc/Cola.h"
#include "Persona.h"
#include "ipc/MemoriaCompartida.h"

using namespace std;

class BdD {

private:
    Cola<Persona>* peticiones;
    Cola<Persona>* respuestas;
    long nroCliente;

public:
    BdD ( long nroCliente );
    ~BdD ();
    Persona buscar (Persona consulta);
    Persona insertar (Persona nuevaPersona);


};


#endif //CLIENTE_BDD_BDD_H
