
#include "../include/BdD.h"
#include "../include/Logger.h"

BdD::BdD(long nroCliente) : nroCliente (nroCliente) {
    this->consultas = new Cola<Persona> ( "/bin/bash", 'q' );
}

BdD::~BdD() {
    delete consultas;
}

/*vector<Persona>* BdD::buscar(Persona consulta) {*/
Persona* BdD::buscar(Persona consulta) {
    consultas->escribir(consulta);
    //vector<Persona>* respuesta;
    Persona personaEncontrada;
    consultas->leer(RESPUESTA, &personaEncontrada);
    //TODO: para mas de un resultado deberia usarse esto de abajo. Lo dejo comentado.
    /*do {
        consultas->leer( nroCliente, &personaEncontrada );
        respuesta->push_back(personaEncontrada);
    } while (!personaEncontrada.esUnicoResultado);*/
    return &personaEncontrada;
}

Persona BdD::insertar(Persona nuevaPersona) {
    consultas->escribir(nuevaPersona);
    Persona personaConfirmada;
    consultas->leer( RESPUESTA, &personaConfirmada );
    return personaConfirmada;
}
