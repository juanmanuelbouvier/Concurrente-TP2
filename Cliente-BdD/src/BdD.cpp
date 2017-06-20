
#include "../include/BdD.h"
#include "../include/Logger.h"

BdD::BdD(long nroCliente) : nroCliente (nroCliente) {
    this->peticiones = new Cola<Persona> ( "/bin/bash", 'p' );
    this->respuestas = new Cola<Persona> ( "/bin/bash", 'r' );
}

BdD::~BdD() {
    delete peticiones;
    delete respuestas;
}

/*vector<Persona>* BdD::buscar(Persona consulta) {*/
Persona BdD::buscar(Persona consulta) {
    consulta.mtype = nroCliente;
    peticiones->escribir(consulta);
    //vector<Persona>* respuesta;
    Persona personaEncontrada;
    respuestas->leer(nroCliente, &personaEncontrada);
    //TODO: para mas de un resultado deberia usarse esto de abajo. Lo dejo comentado.
    /*do {
        consultas->leer( nroCliente, &personaEncontrada );
        respuesta->push_back(personaEncontrada);
    } while (!personaEncontrada.esUnicoResultado);*/
    return personaEncontrada;
}

Persona BdD::insertar(Persona nuevaPersona) {
    nuevaPersona.mtype = nroCliente;
    peticiones->escribir(nuevaPersona);
    Persona personaConfirmada;
    respuestas->leer( nroCliente, &personaConfirmada );
    return personaConfirmada;
}
