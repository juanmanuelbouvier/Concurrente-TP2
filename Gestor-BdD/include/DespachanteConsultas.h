
#ifndef GESTOR_BDD_DESPACHANTECONSULTAS_H
#define GESTOR_BDD_DESPACHANTECONSULTAS_H

#include <unistd.h>
#include "Persona.h"
#include "ipc/Cola.h"
#include "../include/Buscador.h"
#include "../include/Insertor.h"
#include "../include/Logger.h"


class DespachanteConsultas {

private:
    Cola<Persona>* consultas;

public:
    DespachanteConsultas();
    ~DespachanteConsultas();
    void despachar();

};


#endif //GESTOR_BDD_DESPACHANTECONSULTAS_H
