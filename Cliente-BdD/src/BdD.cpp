
#include "../include/BdD.h"
#include "../include/Logger.h"

BdD::BdD(long nroCliente) : nroCliente (nroCliente) {
    this->consultas = new Cola<Persona> ( "/bin/bash", 'q' );
}

BdD::~BdD() {
    delete consultas;
}

vector<Persona>* BdD::buscar(Persona consulta) {
    consultas->escribir(consulta);
    vector<Persona>* respuesta;
    Persona personaEncontrada;
    do {
        consultas->leer( nroCliente, &personaEncontrada );
        respuesta->push_back(personaEncontrada);
    } while (!personaEncontrada.esUnicoResultado);
    return respuesta;
}

Persona BdD::insertar(Persona nuevaPersona) {
    Persona personaConfirmada;
    consultas->escribir(nuevaPersona);
    consultas->leer( nroCliente, &personaConfirmada );
    return personaConfirmada;
}
