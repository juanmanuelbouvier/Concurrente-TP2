
#ifndef CLIENTE_BDD_BDD_H
#define CLIENTE_BDD_BDD_H


#include "../include/ipc/Cola.h"
#include "../include/Persona.h"
#include "../include/ipc/MemoriaCompartida.h"

class BdD {

private:
    Cola<Persona> consultas;
    long nroCliente;

public:
    BdD ( long nroCliente );
    ~BdD ();
    Persona* buscar (Persona consulta);
    Persona insertar (Persona nuevaPersona);


};


#endif //CLIENTE_BDD_BDD_H
